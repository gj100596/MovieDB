//
// Created by hail-drago on 2/9/17.
//
#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std;
const int no_of_clients = 150;
float rtime[no_of_clients];

void * runCommand(void * id){
    int iid = *((int *)id);
    float time_of_thread = 0.0;
    for(int i=0;i<50;i++) {
        clock_t begin = clock();
//    cout<<system("echo '1 20 n y 10' | ./client")<<endl;

        int m = rand() % 10 + 1;
        ostringstream oss;
        oss << m;
        string com = "echo '1 "+oss.str()+" n n' | ./client_phase2";

        system(com.c_str());
//        system("echo '1 20 n n' | ./client_phase2");

        clock_t end = clock();
        float time = float(end - begin) / CLOCKS_PER_SEC;
        time_of_thread += time;
    }
    rtime[iid] = time_of_thread;
}

int main(){
    pthread_t thread[no_of_clients];
    for (int i = 0; i < no_of_clients; ++i) {
        pthread_create(&thread[i], NULL, runCommand, (void *) &i);
    }
    for (int i = 0; i < no_of_clients; ++i) {
        pthread_join(thread[i],NULL);
    }
    float total_time=0;
    for (int i = 0; i < no_of_clients; ++i)
            total_time+=rtime[i];

    cout << total_time/(no_of_clients*50);

}