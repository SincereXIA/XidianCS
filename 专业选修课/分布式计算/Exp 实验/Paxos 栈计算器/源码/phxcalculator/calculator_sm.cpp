//
// Created by zhangjh on 2020/8/9.
//

#include "calculator_sm.h"
#include "phxpaxos/sm.h"
#include "phxpaxos/storage.h"
#include <algorithm>
#include <iostream>
using namespace std;


void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

int PhxCalculatorSM::Create() {
    int id = ++(this->max_stack_id_now);
    auto * instance = new stack<int>;
    m_instanceDict.insert(pair<int, stack<int> *> (id, instance));
    return id;
}

bool PhxCalculatorSM::isInstanceExist(int instanceId) {
    auto iter = m_instanceDict.find(instanceId);
    return iter != m_instanceDict.end();
}

int PhxCalculatorSM::Push(int instanceId, int x) {
    if (!isInstanceExist(instanceId)) {
        return -1;
    }
    auto instance = m_instanceDict[instanceId];
    instance->push(x);
    return 0;
}

typedef int (PhxCalculatorSM::*fp) (int instanceId);

int PhxCalculatorSM::Calculate(vector<string> params) {
    vector<pair<string, fp>> menu {
      pair<string, fp>("DELETE", &PhxCalculatorSM::Delete),
      pair<string, fp>("POP", &PhxCalculatorSM::Pop),
      pair<string, fp>("ADD", &PhxCalculatorSM::Add),
      pair<string, fp>("SUB", &PhxCalculatorSM::Sub),
      pair<string, fp>("MUL", &PhxCalculatorSM::Mul),
      pair<string, fp>("DIV", &PhxCalculatorSM::Div),
      pair<string, fp>("INC", &PhxCalculatorSM::Inc),
      pair<string, fp>("DEC", &PhxCalculatorSM::Dec),
      pair<string, fp>("GET", &PhxCalculatorSM::Get),

    };

    if (params.empty()) {
        //only commiter node have SMCtx.
        printf("EMPTY COMMAND\n");
        return 0;
    }
    if (params[0] == "CREATE") {
        int id = Create();
        printf("create new instance: %d\n", id);
    }else if (params[0] == "PUSH") {
        if (params.size() < 3) {
            printf("WRONG COMMAND\n");
            return -1;
        }
        int instanceId = atoi(params[1].c_str());
        int num = atoi(params[2].c_str());
        Push(instanceId, num);
        printf("PUSH %d to instance: %d\n", num, instanceId);
    }else {
        if (params.size() < 2) {
            cout << "WRONE COMMAND" << endl;
            return -1;
        }
        int instanceId = atoi(params[1].c_str());
        for (auto m : menu) {
            if (m.first == params[0]) {
                int rs =  (this->*(m.second))(instanceId);
                return rs;
            }
        }
        printf("COMMAND NOT FOUND\n");
        return -1;
    }
    return 0;
}


bool PhxCalculatorSM::Execute(const int iGroupIdx, const uint64_t llInstanceId, const std::string &sPaxosValue,
                              phxpaxos::SMCtx *poSMCtx){
    if (sPaxosValue.empty()) {
        return true;
    }
    cout <<"[COMMAND: "  << sPaxosValue << "]  ";
    std::vector<std::string> params;
    SplitString(sPaxosValue, params, " "); // 分割用空格隔开的参数
    transform(params[0].begin(), params[0].end(), params[0].begin(), ::toupper); // 不区分大小写

    cout << Calculate(params) << endl;

    //only commiter node have SMCtx.
    if (poSMCtx != nullptr && poSMCtx->m_pCtx != nullptr)
    {
        PhxCalculatorSMCtx * poPhxEchoSMCtx = (PhxCalculatorSMCtx *)poSMCtx->m_pCtx;
        poPhxEchoSMCtx->iExecuteRet = 0;
        poPhxEchoSMCtx->sEchoRespValue = string("Finish");
    }

    return true;
}

PhxCalculatorSM::PhxCalculatorSM(int smid) {
    this->smid = smid;
}

int PhxCalculatorSM::Delete(int instanceId) {
    if (!isInstanceExist(instanceId)) {
        return -1;
    }
    m_instanceDict.erase(instanceId);
    return 0;
}

int PhxCalculatorSM::Pop(int instanceId, bool& ret) {
    if(!isInstanceExist(instanceId)) {
        ret = false;
        return -1;
    }
    if (m_instanceDict[instanceId]->empty()) {
        ret = false;
        return -1;
    }
    int result = m_instanceDict[instanceId]->top();
    m_instanceDict[instanceId]->pop();
    return result;
}


int PhxCalculatorSM::Pop(int instanceId) {
    if (!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->empty()) {
        return 0;
    }
    int result = m_instanceDict[instanceId]->top();
    m_instanceDict[instanceId]->pop();
    return result;
}

int PhxCalculatorSM::Add(int instanceId) {
    if(!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->size() < 2) {
        return 1;
    }
    int a  = Pop(instanceId);
    int b = Pop(instanceId);
    Push(instanceId, a+b);
    return 0;
}

int PhxCalculatorSM::Sub(int instanceId) {
    if(!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->size() < 2) {
        return 1;
    }
    int a  = Pop(instanceId);
    int b = Pop(instanceId);
    Push(instanceId, a-b);
    return 0;
}

int PhxCalculatorSM::Mul(int instanceId) {
    if(!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->size() < 2) {
        return 1;
    }
    int a  = Pop(instanceId);
    int b = Pop(instanceId);
    Push(instanceId, a*b);
    return 0;
}

int PhxCalculatorSM::Div(int instanceId) {
    if(!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->size() < 2) {
        return 1;
    }
    int a  = Pop(instanceId);
    int b = Pop(instanceId);
    Push(instanceId, a/b);
    return 0;
}

int PhxCalculatorSM::Inc(int instanceId) {
    if(!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->empty()) {
        return 1;
    }
    int a  = Pop(instanceId);
    Push(instanceId, a+1);
    return 0;
}

int PhxCalculatorSM::Dec(int instanceId) {
    if(!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->empty()) {
        return 1;
    }
    int a  = Pop(instanceId);
    Push(instanceId, a-1);
    return 0;
}

int PhxCalculatorSM::Get(int instanceId) {
    if (!isInstanceExist(instanceId)) {
        return -1;
    }
    if (m_instanceDict[instanceId]->empty()) {
        return -1;
    }
    int result =m_instanceDict[instanceId]->top();
    printf("[RESULT] ");
    return result;
}



