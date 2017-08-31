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

//void ask_movie_id_for_movie_details(int my_socket) {
//    cout<<"\nEnter movie id for details: \n";
//    char inp[128];
//    cin >> inp;
//    send(my_socket,inp, sizeof(inp),0);
//}

void send_oss_str_to_socket(int my_socket,string str){
    char buff[1024];
    strcpy(buff,str);
    send(my_socket,buff,sizeof(buff),0);
}


void receive_movie_detail(int my_socket){
    cout<< "\n Movie Details: "<<endl;
    char buff[1024];
    while(recv(my_socket,buff,1024,0) > 0) {
        string s = buff;
        if(s.compare("-1")==0){
            break;
        }
        cout << buff;
    }
}

void receive_movie_list(int my_socket){
    char buff[1024];
    int n;
    cout<< "ID\tMovie Title\n";
    while((n= recv(my_socket,buff,1024,0)) > 0) {
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

void get_movie_poster(int my_socket){

    cout<< "\nDownloading Poster: \n";
    char buff[1024];
    int n;
    char* path = "/tmp/poster.jpg";
    fstream poster;
    poster.open(path,ios::out|ios::binary);

    while((n= recv(my_socket,buff,1024,0)) > 0) {
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

#define LIST_BY_POPULARITY 1
#define LIST_BY_RELEASE_DATE 2
#define SEARCH_BY_NAME 3
#define UPLOAD_MOVIE_DETAILS 4
#define RATE_MOVIE 5

int ask_for_movie_id(int my_socket){
    //Ask Movie ID for getting Movie Details
    cout<<"\nEnter movie id for details: ";
    int movie_id;
    cin>>movie_id;
    ostringstream oss;
    oss<<movie_id;
    send_oss_str_to_socket(my_socket,oss.str());
}
void handle_movie_listing(int my_socket){
    receive_movie_list(my_socket);
    ask_for_movie_id(my_socket);
    receive_movie_detail(my_socket);
    get_movie_poster(my_socket);
}

int ask_request_type(){
    int request_no;
    do {
        cout << "Select Action: " << endl;
        cout << LIST_BY_POPULARITY << " Get movie list sorted by popularity" << endl;
        cout << LIST_BY_RELEASE_DATE << " Get movie list sorted by release date" << endl;
        cout << SEARCH_BY_NAME << " Search movies by name" << endl;
        cout << UPLOAD_MOVIE_DETAILS << " Upload a new movie details" << endl;
        cout << "Enter your choice: ";
        cin >> request_no;
    }while (request_no!=LIST_BY_POPULARITY||request_no!=LIST_BY_RELEASE_DATE
            ||request_no!=SEARCH_BY_NAME||request_no!=UPLOAD_MOVIE_DETAILS);
    return request_no;
}

void search_by_name(int my_socket){

}

void upload_movie_details(int my_socket){

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
    //Ask for request type (All type of Search or Upload)
    int request_type = ask_request_type();
    ostringstream oss;
    oss<<request_type;
    send_oss_str_to_socket(my_socket,oss.str());
    switch(request_type){
        case LIST_BY_POPULARITY:
        case LIST_BY_RELEASE_DATE:
            handle_movie_listing(my_socket);
            break;
        case SEARCH_BY_NAME:
            search_by_name(my_socket);
            break;
        case UPLOAD_MOVIE_DETAILS:
            upload_movie_details(my_socket);
            break;
        default:
            break;
    }

//    cout<<"connected"<<endl;
//    receive_movie_list(my_socket);
//    get_user_choice(my_socket);
//    receive_movie_detail(my_socket);
//    get_movie_poster(my_socket);
    return 0;
}
