//
// Created by zhangjh on 2020/8/9.
//

#include "calculator_server.h"
#include "phxpaxos/options.h"
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace phxpaxos;
using namespace std;


PhxCalculatorServer::~PhxCalculatorServer() {

}

PhxCalculatorServer::PhxCalculatorServer(const phxpaxos::NodeInfo &oMyNode,
                                         const phxpaxos::NodeInfoList &vecNodeList )
        : m_oCalculatorSM(PhxCalculatorSM(1)) {
    this->m_oMyNode = oMyNode;
    this->m_vecNodeList = vecNodeList;
    this->m_poPaxosNode = nullptr;
}

int PhxCalculatorServer::MakeLogStoragePath(std::string & sLogStoragePath)
{
    char sTmp[128] = {0};
    snprintf(sTmp, sizeof(sTmp), "./logpath_%s_%d", m_oMyNode.GetIP().c_str(), m_oMyNode.GetPort());

    sLogStoragePath = string(sTmp);

    if (access(sLogStoragePath.c_str(), F_OK) == -1)
    {
        if (mkdir(sLogStoragePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
        {
            printf("Create dir fail, path %s\n", sLogStoragePath.c_str());
            return -1;
        }
    }

    return 0;
}

int PhxCalculatorServer::RunPaxos() {
    Options* oOptions = new Options();
    printf("Start Run Paxos\n");

    int ret = MakeLogStoragePath(oOptions->sLogStoragePath);
    if (ret != 0)
    {
        return ret;
    }

    //this groupcount means run paxos group count.
    //every paxos group is independent, there are no any communicate between any 2 paxos group.
    oOptions->iGroupCount = 1;

    oOptions->oMyNode = m_oMyNode;
    oOptions->vecNodeInfoList = m_vecNodeList;

    GroupSMInfo *oSMInfo = new GroupSMInfo;
    oSMInfo->iGroupIdx = 0;
    //one paxos group can have multi state machine.
    oSMInfo->vecSMList.push_back(&m_oCalculatorSM);
    oOptions->vecGroupSMInfoList.push_back(*oSMInfo);

    //use logger_google to print log
    LogFunc pLogFunc;
    ret = LoggerGoogle :: GetLogger("phxecho", "./log", 3, pLogFunc);
    if (ret != 0)
    {
        printf("get logger_google fail, ret %d\n", ret);
        return ret;
    }

    //set logger
    oOptions->pLogFunc = pLogFunc;

    ret = Node::RunNode(*oOptions, m_poPaxosNode);
    if (ret != 0)
    {
        printf("run paxos fail, ret %d\n", ret);
        return ret;
    }
    printf("run paxos ok\n");
    return 0;
}

int PhxCalculatorServer::RunCommand(string &command, string &result) {
    SMCtx oCtx;
    PhxCalculatorSMCtx calculatorSmCtx; // 上下文

    int smid = 1; // 当前选择的状态机
    oCtx.m_iSMID = smid;
    oCtx.m_pCtx = (void *)&calculatorSmCtx;  // 将自定义上下文的指针送往状态机上下文中

    uint64_t llInstanceId = 1; // 实例编号
    int ret = m_poPaxosNode->Propose(0, command, llInstanceId, &oCtx);
    if (ret != 0) {
        printf("paxos propose fail, ret %d\n", ret);
        return ret;
    }
    if (calculatorSmCtx.iExecuteRet != 0)
    {
        printf("Calculator SM excute fail, %d \n", calculatorSmCtx.iExecuteRet);
        return  calculatorSmCtx.iExecuteRet;
    }
    result = calculatorSmCtx.sEchoRespValue.c_str();
    return 0;
}
