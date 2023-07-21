//
// Created by 93773 on 2019/5/7.
//

#ifndef MYSQL_DATABASE_H
#define MYSQL_DATABASE_H

#endif //MYSQL_DATABASE_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class column {
public:
    string columnName;
    int columnType;
    int columnSize;
};

struct recordNode {
    int nodeType;
    string charval;
    int intval;
};

class Table {
private:
    vector<vector<recordNode>> result;
public:
    string name;
    vector<column> columns;
    vector<vector<recordNode>> records;
};

class Database {
private:
    map<string, Table> tables;
    vector<column> columnsNow;
public:
    string name;
    void createTable(char * tableName);
    void addColumn(char* columnName, int columnType,  int size = 0);
    void showTables();
    void droptable(char * tableName);

};

class DBDriver {
    map<string, Database> databases;
    Database * databaseInUse;
public:
    DBDriver(){
        cout << "======================" << endl;
        cout << "      my mini mysql  "  << endl;
        cout << "======================" << endl;
        createDatabase("default");
        useDB("default");
    }
    void createDatabase(char * databaseName);
    void useDB(char * databaseName);
    Database * getDB();
    void showDatabases();
    void dropDatabase(char * databaseName);





};