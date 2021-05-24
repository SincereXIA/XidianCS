//
// Created by 93773 on 2019/5/9.
//

#include "myarray.h"
#include <iostream>
#include <myarray.h>


void myarray::push(char *val) {
    arrayNode arrayNode1{arrayNode::CHNODE, val};
    this->nodes.push_back(arrayNode1);
    std::cout << "push success" << endl;
}

void myarray::push(int val) {
    arrayNode arrayNode1{arrayNode::INTNODE, to_string(val)};
    this->nodes.push_back(arrayNode1);
}

myarray myarray::operator+(const myarray & a) {

    myarray array1;
    std:: cout << "a1" << endl;
    for (auto n:this->nodes){
        cout << n.val << ", ";
    }
    array1.nodes.insert(array1.nodes.end(), this->nodes.begin(), this->nodes.end());
    std:: cout << "a2" << endl;
    for (auto n:a.nodes){
        cout << n.val << ", ";
    }
    cout << endl;
    array1.nodes.insert(array1.nodes.end(), a.nodes.begin(), a.nodes.end());
    std::cout << "add result" << endl;
    for (auto n:array1.nodes){
        cout << n.val << ", ";
    }
    cout << endl;
    return array1;
}

vector<arrayNode> myarray::get() {
    return this->nodes;
}

void myarray::print() {
    for (auto n:this->nodes){
        cout << n.val << ", ";
    }
    cout << endl;
}
