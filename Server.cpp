#include <cstdlib>
#include <pthread.h>

#include <netinet/in.h>
#include "iostream"
#include "sys/socket.h"
#include <mysql_driver.h>
#include <cstring>
#include <sstream>
#include <fstream>
#include "mysql_connection.h"
#include "cppconn/statement.h"
#include <mutex>

#define PORTNO 8090

// Different IDs for request types
#define BY_POPULARITY 1
#define BY_DATE 2
#define BY_NAME 3
#define RATE_MOVIE 4

// Database related variables
#define DB_URL "tcp://127.0.0.1:3306"
#define DB_USER "root"
#define DB_PASS "0882"

bool DEBUG = false;

using namespace sql;
using namespace std;

sql::Driver *driver;

std::mutex mtx;

sql::Connection* get_connection(){
    return driver->connect(DB_URL, DB_USER, DB_PASS);
}

/**
 * The methods call get_right_movie_list() to get list of all movies.
 * And then pass those records over socket
 * @param client_socket The socket where data is to be passed
 * @param type Request type. (what needed by get_right_movie_list())
 * @param movie_name Name of movie. (what needed by get_right_movie_list())
 * @param con Database connection. (what needed by get_right_movie_list())
 */
void send_movie_list(int client_socket, int type, string movie_name) {
    sql::Connection *con = get_connection(); // get it from pool
    int flag = 3;

    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = con->createStatement();
    stmt->execute("USE moviedb");

    if (type == BY_POPULARITY) {
        res = stmt->executeQuery("Select id,title from movie");
    } else if (type == BY_DATE) {
        res = stmt->executeQuery("Select id,title from movie order by release_date desc");
    } else if (type == BY_NAME) {
        string query = "select id,title from movie where title like \"%" + movie_name + "%\"";
        res = stmt->executeQuery(query);
    } else {
        cout << "Exception" << endl;
    }


    while (res->next()) {
        ostringstream oss;
        string entry;
        oss << res->getInt(1);
        entry.append(oss.str());
        entry.append("\t");
        entry.append(res->getString(2));
        entry.append("\n");
        char buff[1024];
        strcpy(buff, entry.c_str());
        send(client_socket, buff, 1024, 0);
        if (DEBUG) {
            if (flag > 0) {
                if (DEBUG)
                    cout << entry << endl;
                flag--;
            } else {
                if (DEBUG)
                    cout << "..." << endl;
            }
        }
    }
    res->close();
    delete res;
    stmt->close();
    delete stmt;
    con->close();
    delete con;
    char end[1024] = "-1";
    send(client_socket, end, 1024, 0);
}

/**
 * This method sends data of movie to user over socket.
 * @param client_socket Socket over which data is to be passed.
 * @param id Id of movie in DB whose details are to be given.
 * @param con Database connection object used to get data from db.
 */
void send_movie_details(int client_socket, int id) {
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::Connection *con = get_connection(); // get it from pool
    if (con->isValid()) {
        ostringstream oss;
        stmt = con->createStatement();
        stmt->execute("USE moviedb");
        string query = "select id,title,release_date,overview,vote_average,popularity,"
                "genre_ids from movie where id =";
        oss << id;
        query.append(oss.str());
        res = stmt->executeQuery(query);
        string col[] = {"Id", "Title", "Release Date", "Overview", "Vote_average", "Popularity",
                        "Genre Id"};
        while (res->next()) {
            string row;
            for (int i = 0; i < 7; i++) {
                if (i == 0 || i == 6) {
                    ostringstream s;
                    s << res->getInt(i + 1);
                    row.append(col[i]);
                    row.append("\t");
                    row.append(s.str());
                    row.append("\n");
                } else if (i == 4 || i == 5) {
                    ostringstream s;
                    s << res->getDouble(i + 1);
                    row.append(col[i]);
                    row.append("\t");
                    row.append(s.str());
                    row.append("\n");
                } else {
                    row.append(col[i]);
                    row.append("\t");
                    row.append(res->getString(i + 1).c_str());
                    row.append("\n");
                }
            }

            char buff[1024];
            strcpy(buff, row.c_str());
            send(client_socket, buff, 1024, 0);
            if(DEBUG)
                cout << buff << endl;
        }

        char end[1024] = "-1";
        send(client_socket, end, 1024, 0);

        res->close();
        delete res;
        stmt->close();
        delete stmt;
        con->close();
        delete con;

    }
}

/**
 * This method sends movie's poster over the socket.
 * @param client_socket Socket over which data is to be passed.
 * @param movie_id ID of movie whose poster has to be transfered.
 */
void send_movie_poster(int client_socket, int movie_id) {

    ostringstream os;
    os << movie_id;

    string path = "../images/" + os.str() + ".jpg";
    ifstream poster(path, ios::binary);

    char buffer[1024];

    while (poster.read(buffer, 1024) || poster.gcount() != 0)
        send(client_socket, buffer, 1024, 0);

    char end[1024] = "-1";
    send(client_socket, end, 1024, 0);

    poster.close();

}

/**
 * This function updates rating in the database.
 * This is called only when client says it want to rate the mocie. (obvioulsy!)
 * @param rating Rating given by client.
 * @param id Id of movie which client has rated.
 * @param con Databse connection variable used to connect to DB.
 */
void update_movie_rating(int rating, int id) {
    sql::Connection *con = get_connection(); // get it from pool

    mtx.lock();
    sql::Statement *stmt;
    sql::ResultSet *res;
    if (con->isValid()) {
        stmt = con->createStatement();
        stmt->execute("USE moviedb");
        ostringstream oss;
        string query = "select vote_count,vote_average from movie where id =";
        oss << id;
        query.append(oss.str());
        res = stmt->executeQuery(query);
        while (res->next()) {
            int count;
            double current_rating;
            count = res->getInt(1);
            current_rating = res->getDouble(2);
            double sum = count * current_rating;
            count += 1;
            double new_rating = (sum + rating) / count;
            ostringstream count_oss, rating_oss;
            count_oss << count;
            rating_oss << new_rating;
            string update_query = "update movie set vote_count "
                                          "= " + count_oss.str() + ",vote_average=" + rating_oss.str() + " "
                                          "where id = " + oss.str();
            int update = stmt->executeUpdate(update_query);
            if (DEBUG)
                cout<<"Update: "<<update<<endl;
            stmt->close();
        }
        res->close();
    }
    delete res;
    delete stmt;
    con->close();
    delete con;
    mtx.unlock();
}

/**
 * The main driver method. It is called by the client thread.
 * It controls the flow of what thread does.
 * @param temp_client_socket The client socet. But it is passed as void pointer instead of
 *                           int pointer.
 */
void *communicate(void *temp_client_socket) {
//    Connection* con = get_connection();
    int client_socket = *((int *) temp_client_socket);
    free(temp_client_socket);
    if (DEBUG)
        cout << "Client In Thread!! socketid: " << client_socket << endl;

    // Wait for what type of request client wants to do.
    char type_c[1024];
    int result = recv(client_socket, type_c, 1024, 0);
//    cout<<"Error: "<<errno<<endl;
    int request_type = atoi(type_c);
//    cout <<"No of received bytes: "<<result<<endl;
    if (request_type == 0) {
        result = recv(client_socket, type_c, 1024, 0);
        request_type = atoi(type_c);
//        cout <<"No of received bytes: "<<result<<endl;
    }
    // If we want list go to send_movie_list() it will give right list
    if (request_type == BY_POPULARITY || request_type == BY_DATE) {
        send_movie_list(client_socket, request_type, "");
    }
        // If we are searching by name then call send_movie_list() with name
    else if (request_type == BY_NAME) {
        // First Read the movie name
        char buff[1024];
        recv(client_socket, buff, 1024, 0);
        string movie_name = buff;
        // Send list of movie matching
        send_movie_list(client_socket, request_type, movie_name);
    } else {
        if (DEBUG)
            cout << "Wrong Choice";
    }

    // Wait for the Movie Id client wants to know about.
    char no[1024];
    recv(client_socket, no, 1024, 0);
    int movie_id = atoi(no);

    // Send Details of that movie
    send_movie_details(client_socket, movie_id);

    // Send Poster of it.
    send_movie_poster(client_socket, movie_id);

    // Wait if we are getting rating or not.
    char change[1024];
    recv(client_socket, change, 1024, 0);
    int change_rating = atoi(change);

    if (change_rating == RATE_MOVIE) {
        // If client wants to rate, then wait for rating value.
        char rating[1024];
        recv(client_socket, rating, 1024, 0);
        int new_rating = atoi(rating);

        // Once we have rating update the movie in db
        update_movie_rating(new_rating, movie_id);
    }
}

int main() {

    int server_socket;
    struct sockaddr_in my_address;

    // Set up the server socket.
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = INADDR_ANY;
    my_address.sin_port = htons(PORTNO);
    int bind_result = -1;
    do {
        bind_result = bind(server_socket, (struct sockaddr *) &my_address, sizeof(my_address));
        if (bind_result == -1)
            if (DEBUG)
                cout << "Could not bind to port: " << PORTNO << endl;
        if(DEBUG)
            cout << "Bind result(0->success,-1->failure): " << bind_result << endl;
        sleep(1);
    } while (bind_result == -1);

    // Open one common connection to db.
    driver = get_driver_instance();

    while (true) {
        listen(server_socket, 50);

        // Once a client gets connected spawn a new thread.
        struct sockaddr_in client_address;
        int* new_client_socket=(int *) malloc(10* sizeof(int));
        int clinet_size = sizeof(client_address);
        if ((*new_client_socket = accept(server_socket, (struct sockaddr *) &client_address,
                                    (socklen_t *) (&clinet_size))) < 0) {
            if (DEBUG)
                cout << "Error while connecting socket" << endl;
        }
//        int client_socket = new_client_socket;
        if (DEBUG)
            cout << "Client arrived!! socketid: " << *new_client_socket<< endl;
        pthread_t thread;
        pthread_create(&thread, NULL, communicate, (void *) new_client_socket);
//        communicate(&client_socket);
    }
}
