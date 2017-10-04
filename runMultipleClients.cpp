//
// Created by hail-drago on 2/9/17.
//
#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <ctime>

using namespace std;


void * runCommand(void * nc){
    while(true) {
        clock_t begin = clock();
//    cout<<system("echo '1 20 n y 10' | ./client")<<endl;

        system("echo '1 20 n n' | ./client_phase2");

        clock_t end = clock();
        cout << double(end - begin) / CLOCKS_PER_SEC << endl;
    }
}

int main(){
    int no_of_clients=20;
    pthread_t thread[no_of_clients];
    for (int i = 0; i < no_of_clients; ++i) {
        pthread_create(&thread[i], NULL, runCommand, (void *) no_of_clients);
    }
    for (int i = 0; i < no_of_clients; ++i) {
        pthread_join(thread[i],NULL);
    }

}