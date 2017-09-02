//
// Created by hail-drago on 2/9/17.
//
#include <cstdlib>
#include <pthread.h>
#include <iostream>
using namespace std;


void * runCommand(void * nc){
    cout<<system("echo '1 20 n y 10' | ./client")<<endl;
}

int main(){
    int no_of_clients=20;
    pthread_t thread[no_of_clients];
    for (int i = 0; i < no_of_clients; ++i) {
        pthread_create(&thread[i], NULL, runCommand, (void *) no_of_clients);
    }
}