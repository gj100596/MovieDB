//
// Created by gaurav on 15/8/17.
//

#include <netinet/in.h>
#include "iostream"
#include "sys/socket.h"
#include <mysql_driver.h>
#include <cstring>
#include <sstream>
#include "mysql_connection.h"
#include "cppconn/statement.h"

#define PORTNO 8086

using namespace sql;

using namespace std;

void send_movie_list(int client_socket){
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "0882");

    if(con->isValid()) {

        stmt = con->createStatement();
        stmt->execute("USE moviedb");

        res = stmt->executeQuery("Select id,title from movie");

//        char *title = "ID \t Title\n";
//        send(client_socket,title,sizeof(title),0);
        while(res->next()){
            ostringstream oss;
            oss << res->getInt(1);
            string entry;
            entry.append(oss.str());
            entry.append("\t");
            entry.append(res->getString(2));
            entry.append("\n");

            char buff[1024];
            strcpy(buff,entry.c_str());
            send(client_socket,buff,sizeof(buff),0);
            cout<< res->getInt(1) << "\t" << res->getString(2) <<endl;

        }

        char end[1024] = "-1";
        send(client_socket,end,1024,0);

        delete res;
        delete stmt;
        delete con;
    }
}

void send_movie_details(int client_socket, int id){
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "0882");

    if(con->isValid()) {
        ostringstream oss;

        stmt = con->createStatement();
        stmt->execute("USE moviedb");

        string query = "select id,title,release_date,overview,vote_average,popularity,"
                "genre_ids from movie where id =";
        oss<<id;
        query.append(oss.str());

        res = stmt->executeQuery(query);

        string col[] = {"Id","Title","Release Date","Overview","Vote_average","Popularity",
                        "Genre Id"};

        while(res->next()){

            string row;
            for(int i=0;i<7;i++){
                if (i==0 || i==6){
                    oss << res->getInt(i+1);
                    row.append(col[i]);
                    row.append("\t");
                    row.append(oss.str());
                    row.append("\n");
                }
                else if (i==4 || i==5){
                    oss << res->getDouble(i+1);
                    row.append(col[i]);
                    row.append("\t");
                    row.append(oss.str());
                    row.append("\n");
                }
                else{
                    row.append(col[i]);
                    row.append("\t");
                    row.append(res->getString(i+1).c_str());
                    row.append("\n");
                }
            }

            char buff[1024];
            strcpy(buff,row.c_str());
            send(client_socket,buff,sizeof(buff),0);
            cout<< buff <<endl;
        }

        char end[1024] = "-1";
        send(client_socket,end,1024,0);

        delete res;
        delete stmt;
        delete con;
    }
}

void communicate(int client_socket){
    send_movie_list(client_socket);
    char no[128];
    recv(client_socket,no, sizeof(no),0);
    int n = atoi(no);
    send_movie_details(client_socket,n);
    cout << n <<"..............."<<no;
}

int main(){

    int server_socket,client_socket;
    struct sockaddr_in my_address,client_address;
    int clinet_size = sizeof(client_address);

    server_socket = socket(AF_INET,SOCK_STREAM,0);

    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = INADDR_ANY;
    my_address.sin_port = htons(PORTNO);

    bind(server_socket,(struct sockaddr *)&my_address, sizeof(my_address));

    while(true){
        listen(server_socket,50);

        cout << "listening"<<endl;
        if((client_socket = accept(server_socket,(struct sockaddr *) &client_address,
                                   (socklen_t *)(&clinet_size))) <0){
            cout << "Error" <<endl;
        }

        //char* h = "Hello";
        cout << client_socket <<endl;
        cout<< "Starting Giving Data"<<endl;
        communicate(client_socket);

    }
    return 0;
}




////
//// Created by gaurav on 15/8/17.
////
//
//#include <netinet/in.h>
//#include "iostream"
//#include "sys/socket.h"
//#include <mysql_driver.h>
//#include <cstring>
//#include <sstream>
//#include "mysql_connection.h"
//
//#include "cppconn/statement.h"
//#include "Classes.cpp"
//
//using namespace sql;
//
//using namespace std;
//
//void send_movie_list(int client_socket){
//    sql::Driver *driver;
//    sql::Connection *con;
//    sql::Statement *stmt;
//    sql::ResultSet *res;
//
//    driver = get_driver_instance();
//    con = driver->connect("tcp://127.0.0.1:3306", "root", "0882");
//
//    if(con->isValid()) {
//
//        stmt = con->createStatement();
//        stmt->execute("USE moviedb");
//
//        res = stmt->executeQuery("Select id,title from movie");
//
////        send(client_socket,&title,sizeof(title),0);
//
//        string buffer = "ID \t Title\n";
//        while(res->next()){
//            ostringstream oss;
//            oss<<res->getInt(1);
////
////            movie obj(res->getInt(1),res->getString(2));
////            obj.print_table();
////            send(client_socket,&obj,sizeof(obj),0);
//
//            string entry;
//            entry.append(oss.str());
////            entry.append(std::to_string(res->getInt(1)));
//            entry.append("\t");
//            entry.append(res->getString(2));
//            entry.append("\n");
//
//            int a = send(client_socket,&entry,sizeof(entry),0);
//            cout<<entry<<"................."<<a;
//        }
//
////        char buff[1024];
////        strcpy(buff,buffer.c_str());
////        send(client_socket,buff,sizeof(buff),0);
////        cout<<"Sending...\n"<<buff;
////        cout<<sizeof(buff);
////        cout<< res->getInt(1) << "\t" << res->getString(2) <<endl;
//
//        delete res;
//        delete stmt;
//        delete con;
//    }
//}
//
//int main(){
//
//    int server_socket,client_socket;
//    struct sockaddr_in my_address,client_address;
//    int clinet_size = sizeof(client_address);
//
//    server_socket = socket(AF_INET,SOCK_STREAM,0);
//
//    my_address.sin_family = AF_INET;
//    my_address.sin_addr.s_addr = INADDR_ANY;
//    my_address.sin_port = htons(8080);
//
//    bind(server_socket,(struct sockaddr *)&my_address, sizeof(my_address));
//
//    while(true){
//        listen(server_socket,50);
//
//        cout << "listening"<<endl;
//        if((client_socket = accept(server_socket,(struct sockaddr *) &client_address,
//                               (socklen_t *)(&clinet_size))) <0){
//            cout << "Error" <<endl;
//        }
//
//        //char* h = "Hello";
//        cout << client_socket <<endl;
//        cout<< "Starting Giving Data"<<endl;
//        send_movie_list(client_socket);
//
//    }
//    return 0;
//}
