//
// Created by gaurav on 15/8/17.
//

#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include "iostream"
#include "arpa/inet.h"
#include "stdlib.h"
#include "sys/socket.h"

#define PORTNO 8081

void get_user_choice(int server_socket);

using namespace std;

void get_movie_titles(int server_socket){
    char buff[1024];
    int n;
    cout<< "ID\tMovie Title\n";
    while((n= recv(server_socket,buff,1024,0)) > 0) {
        string s = buff;
        if(s.compare("-1")==0){
            break;
        }
        cout << buff;
    }
}

void get_user_choice(int server_socket) {
    cout<<"\nEnter Movie ID: \n";
    char inp[128];
    cin >> inp;
    send(server_socket,inp, sizeof(inp),0);

}

void get_movie_detail(int server_socket){
    cout<< "\n Movie Details: \n";
    char buff[1024];
    int n;

    while((n= recv(server_socket,buff,1024,0)) > 0) {
        string s = buff;
        if(s.compare("-1")==0){
            break;
        }
        cout << buff;
    }
}

void get_movie_poster(int server_socket){
    cout<< "\nDownloading Poster: \n";
    char buff[1024];
    int n;
    string path = "received/poster.jpg";
    fstream poster;
    poster.open(path,ios::out|ios::binary);

    while((n= recv(server_socket,buff,1024,0)) > 0) {
        string s = buff;
        if(s.compare("-1")==0){
            break;
        }

        poster.write(buff, sizeof(buff));
    }

    poster.close();
    cout << "\nPoster Downloaded. Press 1 to See! 0 to Exit";
}


int main(){

    int my_socket;
    struct sockaddr_in server_address;
    //int clinet_size = sizeof(client_address);

    my_socket = socket(AF_INET,SOCK_STREAM,0);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORTNO);
    inet_aton( "127.0.0.1", &server_address.sin_addr);

    connect(my_socket,(sockaddr *) &server_address, sizeof(server_address));
//    cout<<"connected"<<endl;

    get_movie_titles(my_socket);
//    char buff[1024];
//    int n;
//    cout<< "ID\tMovie Title\n";
//    while((n= recv(my_socket,buff,1024,0)) > 0) {
//        string s = buff;
//        if(s.compare("-1")==0){
//            break;
//        }
//        cout << buff;
//    }

    get_user_choice(my_socket);
//    cout<<"\nEnter Movie ID: \n";
//    char inp[128];
//    cin >> inp;
//    send(my_socket,inp, sizeof(inp),0);

    get_movie_detail(my_socket);
//    cout<< "\n Movie Details: \n";
//    while((n= recv(my_socket,buff,1024,0)) > 0) {
//        string s = buff;
//        if(s.compare("-1")==0){
//            break;
//        }
//        cout << buff;
//    }
    get_movie_poster(my_socket);

    return 0;
}




////
//// Created by gaurav on 15/8/17.
////
//
//#include <netinet/in.h>
//#include <unistd.h>
//#include <sys/ioctl.h>
//#include "iostream"
//#include "arpa/inet.h"
//#include "stdlib.h"
//#include "sys/socket.h"
//#include "Classes.cpp"
//
//using namespace std;
//
//int main(){
//
//    int my_socket;
//    struct sockaddr_in server_address;
//    //int clinet_size = sizeof(client_address);
//
//    my_socket = socket(AF_INET,SOCK_STREAM,0);
////    ioctl(my_socket, FIONBIO, 0);
//
//    server_address.sin_family = AF_INET;
//    server_address.sin_port = htons(8080);
//    inet_aton( "127.0.0.1", &server_address.sin_addr);
//
//    if(connect(my_socket,(sockaddr *) &server_address, sizeof(server_address))<0){
//        cout<<"Not Connected";
//    }
//    cout<<".......connected"<<endl;
//
//    string* buff;
//    string final_string;
//    int n;
//    cout<<"Collecting Data";
//
//
//    while((n= recv(my_socket,buff,10,MSG_WAITALL)) > 0) {
//        cout <<"n is ..."<<n<<endl;
////        movie *obj;
////        obj = (movie *)&buff;
////        obj->print_table();
//        string* b = (string *)buff;
//        cout << b;
//    }
//    cout << "Data\n"<<final_string;
//    return 0;
//}
