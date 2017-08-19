//
// Created by gaurav on 15/8/17.
//

#include <netinet/in.h>
#include <unistd.h>
#include "iostream"
#include "arpa/inet.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "Classes.cpp"

using namespace std;

int main(){

    int my_socket;
    struct sockaddr_in server_address;
    //int clinet_size = sizeof(client_address);

    my_socket = socket(AF_INET,SOCK_STREAM,0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_aton( "127.0.0.1", &server_address.sin_addr);

    connect(my_socket,(sockaddr *) &server_address, sizeof(server_address));
    cout<<"connected"<<endl;

    void* buff[1024];
    string final;
    int n;
    while((n= recv(my_socket,buff,1024,0)) > 0) {
        movie *obj;
        obj = (movie *)&buff;
        obj->print_table();
        //cout << buff;
    }
    cout << final;
    return 0;
}
