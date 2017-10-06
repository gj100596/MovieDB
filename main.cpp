#include <iostream>
#include <mysql_driver.h>
#include <fstream>
#include "mysql_connection.h"

#include "cppconn/statement.h"

using namespace std;
using namespace sql;


int main() {

    char *path = realpath("./..",NULL);
    ifstream poster("../images/5.jpg",ios::binary);
    if (poster){
        cout << "h";
    }
//    poster.open(path,ios::in|ios::binary);

    ofstream op("/home/gaurav/CLionProjects/moviedb/images/a.jpg",ios::binary);
    char buffer[1024];


    while(poster.read(buffer,1024) || poster.gcount() != 0  )
        op.write(buffer,sizeof(buffer));

    op.flush();
    op.close();
    poster.close();


//    //cout << "Hello, World!" <<endl;
//    sql::Driver *driver;
//    sql::Connection *con;
//    sql::Statement *stmt;
//    sql::ResultSet *res;
//
//    driver = get_driver_instance();
//    con = driver->connect("tcp://127.0.0.1:3306", "root", "0882");
//
//    if(con->isValid()) {
//
//        stmt = con->createStatement();
//        stmt->execute("USE moviedb");
//
//        res = stmt->executeQuery("Select id,title from movie");
//
//        cout <<"ID \t Title" << endl;
//        while(res->next()){
//            cout<< res->getInt(1) << "\t" << res->getString(2) <<endl;
//        }
//
//        delete res;
//        delete stmt;
//        delete con;
//    }
//
//    delete stmt;
//    delete con;
    return 0;
}