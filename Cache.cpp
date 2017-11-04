//
// Created by gaurav on 1/11/17.
//
#include "list"
#include "Movies.cpp"
#include <iostream>
#include <mutex>

using namespace std;

std::mutex mtx_cache;

//
class Cache {
    int cache_size = 10;
//    int index = 0;
    list<Movies> objects;
//    int tag[cache_size];
//    Classes objects[cache_size];

public:
    Cache() {

    }

    Movies query(int id) {
        try {
            for (list<Movies>::iterator obj = objects.begin(); obj != objects.end(); obj++) {
                if (obj->getId() == id)
                    return *obj;
            }
        } catch(std::exception& e){
            cout<<"Exception: "<<e.what()<<endl;
        }

        return Movies(-1);
    }

    void insert(Movies new_obj) {
        mtx_cache.lock();
        if (this->objects.size() == cache_size) {
            this->objects.pop_back();
        }
        this->objects.push_front(new_obj);
        mtx_cache.unlock();

    }
};
