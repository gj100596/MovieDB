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

bool DEBUG = true;

using namespace sql;
using namespace std;

sql::Driver *driver;

std::mutex mtx;

sql::Connection *get_connection(int client_socket) {
    sql::Connection *con;
    try {
        mtx.lock();
        con = driver->connect(DB_URL, DB_USER, DB_PASS);
        mtx.unlock();
        return con;
    } catch (std::exception &e) {
        mtx.lock();
        cout << "Exception in socket: " << client_socket << endl;
        cout << "Exception: " << e.what() << endl;
        mtx.unlock();
        exit(0);
        try {
            con = driver->connect(DB_URL, DB_USER, DB_PASS);
        } catch (std::exception &e) {
            mtx.lock();
            cout << "Second Exception in socket: " << client_socket << endl;
            cout << "Second Exception: " << e.what() << endl;
            mtx.unlock();
        }
        return con;
    }
}

int id = 0;

/**
 * The main driver method. It is called by the client thread.
 * It controls the flow of what thread does.
 * @param temp_client_socket The client socet. But it is passed as void pointer instead of
 *                           int pointer.
 */
void *communicate(void *temp_client_socket) {
//    Connection* con = get_connection();
//    unsigned int client_socket = *((unsigned  int *) temp_client_socket);
    pthread_t *thread = (pthread_t *) temp_client_socket;
    mtx.lock();
    id++;
    cout << "Thread No: " << *thread << "--" << id << endl;
    mtx.unlock();
//    mtx.lock();
//    cout << "Request In Thread!! socket: " << client_socket << endl;
//    mtx.unlock();
//    mtx.lock();
//    close(client_socket);
//    cout << "Closed socket: " << client_socket << endl;
//    mtx.unlock();

    pthread_exit(0);
}

int main() {
    driver = get_driver_instance();
    int i = 0;
    while (true) {
        unsigned int *new_client_socket = (unsigned int *) malloc(1 * sizeof(unsigned int));
        *new_client_socket = i;
        mtx.lock();
//        cout << "Client arrived!! socketid: " << *new_client_socket << endl;
        mtx.unlock();
        pthread_t *thread = (pthread_t *) malloc(sizeof(pthread_t));
//        pthread_t thread;
        pthread_create(thread, NULL, communicate, (void *) thread);
        pthread_detach(*thread);
    }
}
