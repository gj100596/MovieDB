//
// Created by gaurav on 1/11/17.
//
#include "Cache.cpp"

int main(){
    Cache cache;
    Movies m1 = Movies(1,1,1,"ABC","10-10-17","path","over",5.8,8.7);
    Movies m2 = Movies(2,1,1,"CDE","10-10-17","path","over",5.8,8.7);
    Movies m3 = Movies(3,1,1,"EFG","10-10-17","path","over",5.8,8.7);
    Movies m4 = Movies(4,1,1,"GHI","10-10-17","path","over",5.8,8.7);
    Movies m5 = Movies(5,1,1,"IJK","10-10-17","path","over",5.8,8.7);
    Movies m6 = Movies(6,1,1,"IJK","10-10-17","path","over",5.8,8.7);
    Movies m7 = Movies(7,1,1,"IJK","10-10-17","path","over",5.8,8.7);
    Movies m8 = Movies(8,1,1,"IJK","10-10-17","path","over",5.8,8.7);
    Movies m9 = Movies(9,1,1,"IJK","10-10-17","path","over",5.8,8.7);
    Movies m10 = Movies(10,1,1,"IJK","10-10-17","path","over",5.8,8.7);
    Movies m11 = Movies(11,1,1,"IJK","10-10-17","path","over",5.8,8.7);

//    cout << cache.query(1)<< endl;
    cache.insert(m1);
    cache.insert(m2);
    cache.insert(m3);
    cache.insert(m4);
    cache.insert(m5);
    cache.insert(m6);
    cache.insert(m7);
    cache.insert(m8);
    cache.insert(m9);
    cache.insert(m10);

    cout << cache.query(2)<<endl;
    cout << cache.query(11)<<endl;
    cache.insert(m11);
    cout << cache.query(11)<<endl;
    cout << cache.query(1)<<endl;



}
