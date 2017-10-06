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
const int no_of_clients = 150;
const int no_of_req_per_client=10;
float rtime[no_of_clients];

void * runCommand(void * id){
    int iid = *((int *)id);
    float time_of_thread = 0.0;
    for(int i=0;i<no_of_req_per_client;i++) {
        int m = rand() % 10 + 1;
        clock_t begin = clock();
        client_printless(1,m,'n','n');
        clock_t end = clock();
        float time = float(end - begin) / CLOCKS_PER_SEC;
        time_of_thread += time;
        cout<<time<<endl;
    }
    rtime[iid] = time_of_thread;
}

int main(){
    pthread_t thread[no_of_clients];
    for (int i = 0; i < no_of_clients; ++i) {
        int* id=(int *) malloc(1* sizeof(int));
        *id=i;
        pthread_create(&thread[i], NULL, runCommand, (void *) id);
    }
    for (int i = 0; i < no_of_clients; ++i) {
        pthread_join(thread[i],NULL);
    }
    float total_time=0;
    for (int i = 0; i < no_of_clients; ++i)
            total_time+=rtime[i];
    cout <<"Total Time: "<<total_time<<endl;
    cout <<"Time per request: "<<total_time/(no_of_clients*no_of_req_per_client)<<endl;
    cout <<"Requests served per second: " <<(no_of_clients*no_of_req_per_client)/total_time<<endl;
}