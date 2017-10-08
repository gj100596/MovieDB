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
float *rtime;
time_t start_time;
float allowed_time = 60.0;

void * runCommand(void * id){
    int iid = *((int *)id);
    int no_request = 0;
    cout << iid << " thread starting"<< endl;

    while(true){
        if (difftime(time(NULL),start_time)  > allowed_time){
            cout << iid << " Breaking "<<endl;
            break;
        }

        int m = rand() % 20 + 1;
        client_printless(1,m,'n','n',iid,no_request,8090);
        no_request++;
    }
    cout << iid << " break done"<<endl;

    rtime[iid] = no_request;
    cout << iid << " thread closed"<<endl;
    pthread_exit(0);
}

float do_work(int no_of_clients){
    pthread_t thread[no_of_clients];
    cout << "Starting\n";
    for (int i = 0; i < no_of_clients; ++i) {
        int* id=(int *) malloc(1* sizeof(int));
        *id=i;
        pthread_create(&thread[i], NULL, runCommand, (void *) id);
    }
    for (int i = 0; i < no_of_clients; ++i) {
        cout << pthread_join(thread[i], NULL);
        cout << i << "... thread joined" <<endl;
    }
    cout << "Join Done" << endl;
    float total_time = 0;
    for (int i = 0; i < no_of_clients; ++i)
        total_time+=rtime[i];
    cout << "Sum Calculated" << endl;
    return total_time/allowed_time;

}


int main(int argc, char *argv[]){
    int batch_size = atoi(argv[1]);
    time(&start_time);
    rtime = new float[batch_size];
    cout << batch_size <<"," << do_work(batch_size)<<endl;
}
