//
// Created by 93773 on 2019/5/9.
//

#ifndef MYSQL_ARRAY_H

#include <string>
#include <vector>
#define MYSQL_ARRAY_H
using namespace std;
struct arrayNode{
    enum type{
        INTNODE,
        CHNODE
    } type;
    string val;
};

class myarray {
    vector<arrayNode> nodes;
public:
    void push(char* val);
    void push(int val);
    myarray operator+(const myarray&);
    vector<arrayNode> get();
    void print();
};


#endif //MYSQL_ARRAY_H
