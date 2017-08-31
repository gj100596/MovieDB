//
// Created by gaurav on 15/8/17.
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include "iostream"
#include "arpa/inet.h"
#include "stdlib.h"
#include "sys/socket.h"

#define PORTNO 8080
using namespace cv;
using namespace std;

void get_user_choice(int server_socket) {
    cout<<"\nEnter Movie ID: \n";
    char inp[128];
    cin >> inp;
    send(server_socket,inp, sizeof(inp),0);
}

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

void open_image(char* abs_path){
    Mat image;
    image = imread(abs_path, CV_LOAD_IMAGE_COLOR);      // Read the file
    if (!image.data){                                   // Check for invalid input
        cout << "Could not open or find the image" << std::endl;
        return;
    }
    cout<<"Displaying Poster"<<endl;
    namedWindow("Display window", WINDOW_AUTOSIZE);     // Create a window for display.
    imshow("Display window", image);                    // Show our image inside it.
    waitKey(0);                                         // Wait for a keystroke in the window
}

void get_movie_poster(int server_socket){

    cout<< "\nDownloading Poster: \n";
    char buff[1024];
    int n;
    char* path = "/tmp/poster.jpg";
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
    int option=0;
    cin>>option;
    if(option==1){
        open_image(path);//Absolute Path
    }
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
    get_user_choice(my_socket);
    get_movie_detail(my_socket);
    get_movie_poster(my_socket);


    return 0;
}
