//
// Created by zhangjh on 2020/8/9.
//

#ifndef PHXCALCULATOR_CALCULATOR_SERVER_H
#define PHXCALCULATOR_CALCULATOR_SERVER_H
#include "phxpaxos/node.h"
#include <string>
#include <vector>
#include "phxpaxos_plugin/logger_google.h"
#include "calculator_sm.h"

class PhxCalculatorServer {
public:

    PhxCalculatorServer(const phxpaxos::NodeInfo &oMyNode, const phxpaxos::NodeInfoList &vecNodeList);

    ~PhxCalculatorServer();

    int RunPaxos();

    int RunCommand(std::string &command, std::string &result);

    int MakeLogStoragePath(std::string &sLogStoragePath);

    phxpaxos::NodeInfo m_oMyNode; // 标识本机的IP/Port信息
    phxpaxos::NodeInfoList m_vecNodeList; // 标识集群信息

    phxpaxos::Node * m_poPaxosNode; // 本次需要运行的 PhxPaxos 示例指针
    PhxCalculatorSM m_oCalculatorSM; // 状态机
};

#endif //PHXCALCULATOR_CALCULATOR_SERVER_H
