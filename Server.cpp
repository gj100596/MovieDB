/*
You don't need threads, you need asynchronous or "event-driven" programming.
This can be done with select() if you want cross-platform,
or epoll() if you're on Linux and want to support thousands of clients at once.

But you don't need to implement this all from scratch--you can use Boost ASIO
(some of which may become part of C++17) or a C library like libevent or libev or libuv.
Those will handle a bunch of subtle details for you, and help you get more quickly to
the real business of your application.
*/
//
// Created by gaurav on 15/8/17.
//

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

#define PORTNO 8092
#define BY_POPULARITY 1
#define BY_DATE 2
#define BY_NAME 3
#define UPLOAD 4
#define RATE_MOVIE 5

using namespace sql;
using namespace std;

sql::Driver *driver;
sql::Connection *con;

bool writing = false;
std::mutex mtx;

sql::ResultSet* get_right_movie_list(int type,string movie_name,sql::Connection *con) {
    sql::Statement *stmt;
    sql::ResultSet *res;

    if (con->isValid()) {

        stmt = con->createStatement();
        stmt->execute("USE moviedb");

        if (type == BY_POPULARITY) {
            res = stmt->executeQuery("Select id,title from movie");
        } else if (type == BY_DATE){
            res = stmt->executeQuery("Select id,title from movie order by release_date desc");
        }
        else if(type == BY_NAME){
            string query = "select id,title from movie where title like \"%" + movie_name + "%\"";
            res = stmt->executeQuery(query);
        }
        else{
            return  NULL;
        }
        delete stmt;
        return res;
    } else {
        delete  res;
        delete con;
        delete stmt;

        return NULL;
    }
}

void send_movie_list(int client_socket, int type,string movie_name,sql::Connection *con) {
    sql::ResultSet *res;

    res = get_right_movie_list(type,movie_name,con);

    while (res->next()) {
        ostringstream oss;
        oss << res->getInt(1);
        string entry;
        entry.append(oss.str());
        entry.append("\t");
        entry.append(res->getString(2));
        entry.append("\n");

        char buff[1024];
        strcpy(buff, entry.c_str());
        send(client_socket, buff, 1024, 0);
        cout << res->getInt(1) << "\t" << res->getString(2) << endl;

    }

    char end[1024] = "-1";
    send(client_socket, end, 1024, 0);

    delete res;
}

void send_movie_details(int client_socket,int id,sql::Connection *con) {
    sql::Statement *stmt;
    sql::ResultSet *res;

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
            cout << buff << endl;
        }

        char end[1024] = "-1";
        send(client_socket, end, 1024, 0);

        delete res;
        delete stmt;
    }
}

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

void update_movie_rating(int rating,int id,sql::Connection *con){
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

        while(res->next()) {
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
            mtx.lock();
            int update = stmt->executeUpdate(update_query);
            mtx.unlock();
        }
    }
    delete res;
    delete stmt;
}

void *communicate(void *temp_client_socket) {
    int client_socket = *((int *) temp_client_socket);
    char type_c[1024];
    recv(client_socket, type_c, 1024, 0);
    int request_type = atoi(type_c);

    // If a new entry has to be updated
    if (request_type == UPLOAD){

    }
    else {
        // If we want list go to send_movie_list() it give give right list
        if (request_type == BY_POPULARITY || request_type == BY_DATE) {
            send_movie_list(client_socket, request_type, "",con);
        }
            // If we are searching by name then we have to get movie detail by name
        else if (request_type == BY_NAME) {
            // First Read the movie name
            char buff[1024];
            recv(client_socket, buff, 1024, 0);
            string movie_name = buff;
            // Send list of movie matching
            send_movie_list(client_socket, request_type, movie_name,con);
        } else {
            cout << "Wrong Choice";
        }

        char no[1024];
        recv(client_socket, no, 1024, 0);
        int movie_id = atoi(no);
        send_movie_details(client_socket, movie_id,con);
        send_movie_poster(client_socket, movie_id);

        char change[1024];
        recv(client_socket, change, 1024, 0);
        int change_rating = atoi(change);

        if (change_rating == RATE_MOVIE){
            char rating[1024];
            recv(client_socket, rating, 1024, 0);
            int new_rating = atoi(rating);
            update_movie_rating(new_rating,movie_id,con);
        }
    }
}

int main() {

    int server_socket, client_socket;
    struct sockaddr_in my_address, client_address;
    int clinet_size = sizeof(client_address);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = INADDR_ANY;
    my_address.sin_port = htons(PORTNO);

    bind(server_socket, (struct sockaddr *) &my_address, sizeof(my_address));

    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "0882");

    while (true) {
        listen(server_socket, 50);

        cout << "listening" << endl;
        if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address,
                                    (socklen_t *) (&clinet_size))) < 0) {
            cout << "Error" << endl;
        }

        //char* h = "Hello";
        cout << client_socket << endl;
        cout << "Starting Giving Data" << endl;
        pthread_t thread;
        pthread_create(&thread, NULL, communicate, (void *) &client_socket);
//        communicate(client_socket);
    }
    return 0;
}