//
// Created by 93773 on 2019/5/14.
//

#ifndef MYSQL_DBCORE_H
#define MYSQL_DBCORE_H

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#define PAGE_SIZE 2*1024
using namespace std;


struct table_field_node {
    char * field_name;
    enum type {
        INT, STRING
    }type;
    int len;
    int offset;
    table_field_node * next = nullptr;
};

struct table_node {
    table_field_node * field = nullptr;
    char * tableName;
    int beginPage;
    table_node * next = nullptr;
};


struct condexp_node {
    condexp_node * left = nullptr;
    enum op {
        AND, OR, EQ, G, B, NOT
    }op;
    condexp_node * right = nullptr;
    enum type {
        INT, STRING, COLUM, LOGIC
    }type;
    int intval;
    char * chval;
};


struct select_node {
    table_field_node * field = nullptr;
    table_node * table = nullptr;
    condexp_node * cons = nullptr;
};

struct values_node {
    enum type {
        INT, STRING
    }type;
    int intval;
    char * chval;
    values_node * next = nullptr;
};
struct insert_node {
    table_node * table = nullptr;
    table_field_node * field = nullptr;
    values_node * values = nullptr;
};

struct set_value {
    char * field_name;
    int intval;
    char * chval;
    set_value * next;
};
struct update_node {
    table_node * table = nullptr;
    condexp_node * cons = nullptr;
    set_value * setval = nullptr;
};


char * _S(const char * string);

class Core
{
public:
    Core();
    ~Core();
    void addPage(fstream& f);
    int createDatabase(const char * databaseName);
    int deleteDatabase(char * databaseName);
    int useDatabase(const char * databaseName);
    int createTable(const char * tableName, table_field_node* tfn);
    int deleteTable(const char * tableName);
    /*
    获取当前数据库中某个表所有的列
    */
    vector<table_field_node> getColumn(char * tableName);

    int insert(insert_node * insertNode);

    pair<vector<table_field_node>, vector<vector<values_node>>>
    select_single(select_node * selectNode);


    pair<vector<table_field_node>, vector<vector<values_node>>>
    select_mult(select_node * selectNode);

    int sqldelete(select_node * deleteNode);
    int sqlupdate(update_node * updateNode);


    void SysdbInit();
    vector<table_node> getTables();
    vector<char *> getDatabases();
    char * InUseDBName;



private:
    static int TEMP[10];
    static char DATPAGE[PAGE_SIZE];
    static char DBPAGE[PAGE_SIZE];
    static char TMPAGE[PAGE_SIZE];
    fstream *sysdb;
    fstream *sysdat;
    fstream * InUsedb;
    fstream * InUsedat;

    int getNewDatPage(fstream &datfile, int PageNow = 0);
    int getNextPageNum();
    int readPage(fstream &filestream, int pageNum, char * page = DATPAGE);
    int writePage(fstream &filestream, int pageNum, char * page = DATPAGE);
    int getWriteablePageNum(fstream &filestream, int pageNum);
    int getWriteablePageNum(fstream &filestream, int pageNum, int rowlen);
    int getTableStartDatPage(char * tableName);
    bool condVerify(vector<table_field_node> head, vector<values_node> record, condexp_node * cond);
};


#endif //MYSQL_DBCORE_H
