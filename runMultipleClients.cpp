//
// Created by hail-drago on 2/9/17.
//
#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <ctime>
#include <mutex>
#include "Client_printless.h"

using namespace std;

extern int client_printless(int, int, char, char);

int PORTNO = 8090;
//const int no_of_clients = 100;
const int no_of_req_per_client = 50;
float *rtime;
std::mutex mtx;

void *runCommand(void *id) {
    int iid = *((int *) id);
    int * temp_id = (int *) id;
    free(temp_id);
    float time_of_thread = 0.0;
    for (int i = 0; i < no_of_req_per_client; i++) {
        int m = rand() % 10 + 1;
        mtx.lock();
        cout<<"No of Client: "<<(iid)<<"--"<<i<<endl;
        mtx.unlock();
        clock_t begin = clock();
        client_printless(1, m, 'n', 'n', iid, i, PORTNO);
        clock_t end = clock();
        float time = float(end - begin) / CLOCKS_PER_SEC;
        time_of_thread += time;
//        cout<<time<<endl;
    }
    rtime[iid] = time_of_thread;
}

float do_work(int no_of_clients) {
    pthread_t thread[no_of_clients];
    for (int i = 0; i < no_of_clients; ++i) {
        int *id = (int *) malloc(1 * sizeof(int));
        *id = i;
        pthread_create(&thread[i], NULL, runCommand, (void *) id);
        pthread_detach(thread[i]);
    }
//    for (int i = 0; i < no_of_clients; ++i) {
//        mtx.lock();
////        cout << "Thread joined START: " << i << endl;
//        mtx.unlock();
//        pthread_join(thread[i], NULL);
//        mtx.lock();
////        cout << "Thread joined END: " << i << endl;
//        mtx.unlock();
//    }
    float total_time = 0;
    for (int i = 0; i < no_of_clients; ++i)
        total_time += rtime[i];

    return total_time / (no_of_clients * no_of_req_per_client);
//    cout <<"Total Time: "<<total_time<<endl;
//    cout <<"Time per request: "<<total_time/(no_of_clients*no_of_req_per_client)<<endl;
//    cout <<"Requests served per second: " <<(no_of_clients*no_of_req_per_client)/total_time<<endl;
}


int main() {
    cout << "Enter Portno: ";
    cin >> PORTNO;
    if (PORTNO == 0) {
        PORTNO = 8090;
    }
    int client_arry[] = {10, 20, 50, 100, 150, 200, 250, 300, 400, 500, 750, 1000};
    for (int i = 0; i < 12; i++) {
        rtime = new float[client_arry[i]];
        cout << client_arry[i] << ".... time ...." << do_work(client_arry[i]) << endl;
    }
    while(true)sleep(20);
}