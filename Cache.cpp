//
// Created by gaurav on 1/11/17.
//
#include "list"
#include "Movies.cpp"
//
class Cache{
    int cache_size = 10;
//    int index = 0;
    list<Movies> objects;
//    int tag[cache_size];
//    Classes objects[cache_size];

public:
    Cache(){

    }

    Movies query(int id){
        for (list<Movies>::iterator obj = objects.begin(); obj != objects.end(); obj++){
            if(obj->getId() == id)
                return *obj;
        }
        return Movies(-1) ;
    }

    void insert(Movies new_obj){
        if (objects.size() == cache_size){
            objects.pop_back();
        }
        objects.push_front(new_obj);
    }
};
