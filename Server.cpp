//
// Created by gaurav on 15/8/17.
//

#include <netinet/in.h>
#include "iostream"
#include "sys/socket.h"
#include <mysql_driver.h>
#include <cstring>
#include "mysql_connection.h"

#include "cppconn/statement.h"
#include "Classes.cpp"

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

        char *title = "ID \t Title\n";
        send(client_socket,title,sizeof(title),0);
        while(res->next()){

            movie obj(res->getInt(1),res->getString(2));
            obj.print_table();
            send(client_socket,&obj,sizeof(obj),0);

//            string entry;
//            entry.append(string(""+res->getInt(1)));
//            entry.append("\t");
//            entry.append(res->getString(2));
//            entry.append("\n");
//
//            char buff[1024];
//            strcpy(buff,entry.c_str());
//            send(client_socket,buff,sizeof(buff),0);
//            cout<< res->getInt(1) << "\t" << res->getString(2) <<endl;
        }

        delete res;
        delete stmt;
        delete con;
    }
}

int main(){

    int server_socket,client_socket;
    struct sockaddr_in my_address,client_address;
    int clinet_size = sizeof(client_address);

    server_socket = socket(AF_INET,SOCK_STREAM,0);

    my_address.sin_family = AF_INET;
    my_address.sin_addr.s_addr = INADDR_ANY;
    my_address.sin_port = htons(8080);

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
        send_movie_list(client_socket);

    }
    return 0;
}
