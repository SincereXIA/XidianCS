//
// Created by zhangjh on 2020/8/9.
//

#ifndef PHXCALCULATOR_CALCULATOR_SM_H
#define PHXCALCULATOR_CALCULATOR_SM_H

#include "phxpaxos/sm.h"
#include "phxpaxos/options.h"
#include <stdio.h>
#include <unistd.h>
#include <stack>
#include <map>
class PhxCalculatorSM : public phxpaxos::StateMachine{
public:
    PhxCalculatorSM(int smid);

    bool Execute(const int iGroupIdx, const uint64_t llInstanceId,
                 const std::string & sPaxosValue, phxpaxos::SMCtx * poSMCtx);

    const int SMID() const {return smid;}

    int Create();
    int Delete(int instanceId);
    int Push(int instanceId, int x);
    int Pop(int instanceId);
    int Add(int instanceId);
    int Sub(int instanceId);
    int Mul(int instanceId);
    int Div(int instanceId);
    int Inc(int instanceId);
    int Dec(int instanceId);
    int Get(int instanceId);
    int Pop(int instanceId, bool &ret);

private:
    int smid = 0;
    int max_stack_id_now = 0;
    std::map<int, std::stack<int> *> m_instanceDict;

    int Calculate(std::vector<std::string> params);

    bool isInstanceExist(int instanceId);
};

class PhxCalculatorSMCtx {
public:
    int iExecuteRet;
    std::string sEchoRespValue;

    PhxCalculatorSMCtx(){
        iExecuteRet = -1;
    }
};
void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
#endif //PHXCALCULATOR_CALCULATOR_SM_H
