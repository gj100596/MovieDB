//
// Created by hail-drago on 2/9/17.
//
#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <ctime>
#include "Client_printless.h"
using namespace std;

extern int client_printless(int,int,char,char);
//const int no_of_clients = 100;
const int no_of_req_per_client=50;
float *rtime;
time_t start_time;
float allowed_time = 300.0;

void * runCommand(void * id){
    int iid = *((int *)id);
    float time_of_thread = 0.0;
    int no_request = 0;
    while(true){
        if (difftime(time(NULL),start_time)  > allowed_time){
            break;
        }
        int m = rand() % 20 + 1;
        clock_t begin = clock();
        client_printless(1,m,'y','n',iid,no_request,8090);
        clock_t end = clock();
        float time = float(end - begin) / CLOCKS_PER_SEC;
        time_of_thread += time;
        no_request++;
    }
//    cout << iid << "," << no_request << endl;
    rtime[iid] = no_request;
}

float do_work(int no_of_clients){
    pthread_t thread[no_of_clients];
    for (int i = 0; i < no_of_clients; ++i) {
        int* id=(int *) malloc(1* sizeof(int));
        *id=i;
        pthread_create(&thread[i], NULL, runCommand, (void *) id);
    }
//    sleep(allowed_time);
    for (int i = 0; i < no_of_clients; ++i) {
        pthread_join(thread[i], NULL);
    }
    float total_time = 0;
    for (int i = 0; i < no_of_clients; ++i)
        total_time+=rtime[i];

    return total_time/allowed_time;

}


int main(int argc, char *argv[]){
//    int client_arry[] = {5,10,15,20,25,50,75,100,125,150,200,250,300,400,500,750,1000};

    int batch_size = atoi(argv[1]);
//    for (int i=0;i<;i++){
    time(&start_time);
    rtime = new float[batch_size];
    cout << batch_size <<"," << do_work(batch_size)<<endl;
//    }
//    while(true)sleep(20);
}