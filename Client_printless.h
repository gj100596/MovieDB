#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <mutex>
#include "iostream"
#include "arpa/inet.h"

#define LIST_BY_POPULARITY 1
#define LIST_BY_RELEASE_DATE 2
#define SEARCH_BY_NAME 3
#define RATE_MOVIE 4

using namespace cv;
using namespace std;

int a,b;
char c,d;
//IP Address of Movie server
//string ipaddress ="127.0.0.1";
//string ipaddress ="192.168.137.161";
string ipaddress ="10.130.4.192";

/**
 * This function sends string data to the socket in the bunch of 1024 bytes
 * @param my_socket id of the socket setup with server
 * @param str string that we want to send through socket
 */
void send_str_to_socket(int my_socket, string str) {
    char buff[1024];
    strcpy(buff, str.c_str());
    send(my_socket, buff, 1024, 0);
}

/**
 * This function opens a image with the given path using opencv library and waits for a key to close the image. Path should be absolute path
 * @param abs_path it is the absolute path of image
 */
void open_image(string abs_path) {
    string command = "shotwell ";
    command.append(abs_path);
//    system(command.c_str());
}

/**
 * Downloads the movie's poster and ask for opening it. If yes: opens poster
 * @param my_socket id of the socket setup with server
 * @param movie_id id of the movie whose poster need to be opened
 */
void get_movie_poster(int my_socket,int movie_id) {

//    cout << "\nDownloading Poster...\n";
    ostringstream oss;
    oss<<"/tmp/"<<movie_id<<".jpg";
    string path=oss.str();
    oss.clear();
    fstream poster;
    poster.open(path, ios::out | ios::binary);
    int n;
    sleep(1);
    char pos[1024];
    while ((n=recv(my_socket, pos, 1024, 0)) > 0) {
        string s = pos;
        if (s.compare("-1") == 0) {
            break;
        }

        poster.write(pos, sizeof(pos));
    }
    poster.close();
//    cout << "\nPoster Downloaded.\n";
//    open_image(path);//Absolute Path
}

/**
 * Shows a movies details and downloads it's poster
 * @param my_socket id of the socket setup with server
 * @param movie_id id of the movie whose details need to be shown
 */
void receive_movie_detail(int my_socket,int movie_id) {
//    cout << "\n Movie Details: " << endl;
    char buff[16];
    int n;
    while (n=recv(my_socket, buff, 16, 0) > 0) {
        string s = buff;
        s = s.substr(0,16);
        if (s.compare("-1") == 0) {
            break;
        }
//        cout << buff;
    }
    //    cout << "Do you want to see poster? (y|N):\n";
    char op;
    op = c;
//    cin >> op;
//    delete(buff);
    if (op == 'y') {
        send_str_to_socket(my_socket, "1");

        get_movie_poster(my_socket,movie_id);
    }

}

/**
 * Downloads the list of movies that server sends through socket
 * @param my_socket  id of the socket setup with server
 */
void receive_movie_list(int my_socket) {
    char buff[16];
    int n;
//    cout << "ID\tMovie Title\n";
    while ((n = recv(my_socket, buff, 16, 0)) > 0) {
        string s = buff;
        s = s.substr(0,16);
//        cout<<"....................." << n << "..." <<s <<endl;
        if (s.compare("-1") == 0) {
            break;
        }
//        cout << buff;
    }
}

/**
 * Asks user to enter id of a movie
 * @param my_socket id of the socket setup with server
 * @return id of movie entered by user
 */
int ask_for_movie_id(int my_socket) {
    //Ask Movie ID for getting Movie Details
//    cout << "\nEnter movie id for details: ";
    int movie_id=b;
//    cout << "Sending id " << b;
//    cin >> movie_id;
    ostringstream oss;
    oss << movie_id;
    send_str_to_socket(my_socket, oss.str());
    return atoi(oss.str().c_str());
}

/**
 * Ask user for rating and check the correctness of rating. If rating < 0: it makes it zero. else if rating > 10 : it makes it 10.
 * @return integer rating between 1 to 10
 */
int get_and_check_rating(){
    float rating=10;
//    cout<<"Rate on the scale of 1 to 10: ";
//    cin>>rating;
    if(rating<1){
        rating=1;
    }else if(rating>10){
        rating = 10;
    }else{
        rating=(int)rating;
    }
    return (int) rating;
}

/**
 * Ask user if he wants to rate that movie.
 * @param my_socket id of the socket setup with server
 */
void ask_for_movie_rating(int my_socket){
    char option;
//    cout<<"Would you like to rate this movie(y/N): ";
    option = d;
//    cin>>option;
    if(option=='y' or option=='Y'){
        ostringstream oss;
        oss<<RATE_MOVIE;
        send_str_to_socket(my_socket,oss.str());
        int rating;
        rating = get_and_check_rating();
        ostringstream oss1;
        oss1<<rating;
        send_str_to_socket(my_socket,oss1.str());
//        cout<<"Thank you for rating the movie!"<<endl;
    }else{
        send_str_to_socket(my_socket,"-1");
    }
}

/**
 * Handle all the functions related to listing a movie list
 * 1. Receive movie list
 * 2. Ask movie id
 * 3. Receive movie details
 * 4. Ask for movie rating
 * @param my_socket id of the socket setup with server
 */
void handle_movie_listing(int my_socket) {
//    sleep(1);
    receive_movie_list(my_socket);
    int movie_id=ask_for_movie_id(my_socket);
    receive_movie_detail(my_socket,movie_id);
    ask_for_movie_rating(my_socket);
}

/**
 * Ask user for the action that he wants to perform
 * 1. List by Poularity
 * 2. List by Release Date
 * 3. Search a movie by entering movie name or substring of a movie name
 * @return type of action user wants to take
 */
int ask_request_type() {
    int request_no;
//    cout << "Select Action: " << endl;
//    cout << LIST_BY_POPULARITY << " Get movie list sorted by popularity" << endl;
//    cout << LIST_BY_RELEASE_DATE << " Get movie list sorted by release date" << endl;
//    cout << SEARCH_BY_NAME << " Search movies by name" << endl;
//    cout << "Enter your choice: ";
    request_no = a;
//    cin >> request_no;
    return request_no;
}

/**
 * Handles search of a movie by its name
 * @param my_socket id of the socket setup with server
 */
void search_by_name(int my_socket) {
//    sleep(1);
    string movie_name;
//    cout<<"Enter movie name: ";
    cin>>movie_name;
    send_str_to_socket(my_socket,movie_name);
    handle_movie_listing(my_socket);
}

/**
 * Main functions. Ask user for action and perform accordingly
 * @return success of a program
 */
std::mutex mtxx;
int client_printless(int a,int b,char c, char d,int iid, int i,int PORTNO){//},int my_socket) {
//    mtxx.lock();
    ::a = a;
    ::b = b;
    ::c = c;
    ::d = d;
//    mtxx.unlock();


    /* un comment after experiment...*/
    int my_socket;
    struct sockaddr_in server_address;
    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORTNO);
    inet_aton(ipaddress.c_str(), &server_address.sin_addr);
    connect(my_socket, (sockaddr *) &server_address, sizeof(server_address));
//     */
//    cout<<"Client id: "<<iid<<" req_no: "<<i<<" socket_id: "<<my_socket<<endl;
    //Ask for request type (All type of Search)
    int request_type = ask_request_type();
    ostringstream oss;
    oss << request_type;
    send_str_to_socket(my_socket, oss.str());
    switch (request_type) {
        case LIST_BY_POPULARITY:
        case LIST_BY_RELEASE_DATE:
            handle_movie_listing(my_socket);
            break;
        case SEARCH_BY_NAME:
            search_by_name(my_socket);
            break;
        default:
            break;
    }
    close(my_socket);
    return 0;
}