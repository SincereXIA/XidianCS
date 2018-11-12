#include <iostream>
#include <queue>
#include <stack>
#define NEED_CARRIAGE 3

using namespace std;


stack<int> EntranceWait(int startNum, int endNum,stack<int> &waitingStation){
    for(int i = endNum; i>=startNum; i--){
        waitingStation.push(i);
    }
    return waitingStation;
}

void CheckOutStack(stack<int> outStack, int needCarriage){
    if (outStack.size()==needCarriage){
        printf("Train Go Go Go!!:");
        while (!outStack.empty()){
            int carriage = outStack.top();
            outStack.pop();
            printf("%d  ",carriage);
        }
        printf("\n\n");
    }
}

void dealWaitingStack(stack<int> &waitingStack, stack<int> &waitingStation,stack<int> &outStack){

    int carriage = 0;
    if(!waitingStation.empty()){
        carriage = waitingStation.top();
        waitingStation.pop();
        //printf("Carriage %d into waitingStack!\n",carriage);
        waitingStack.push(carriage);
        dealWaitingStack(waitingStack,waitingStation,outStack);
        //printf("Carriage %d into waitingStack!\n",carriage);
        waitingStation.push(carriage);
        waitingStack.pop();
    }


    if(!waitingStack.empty()){
        carriage = waitingStack.top();
        waitingStack.pop();
        //printf("Carriage %d out waitingStack!\n",carriage);
        outStack.push(carriage);
        //printf("Carriage %d into outStack!\n",carriage);
        CheckOutStack(outStack,NEED_CARRIAGE);
        dealWaitingStack(waitingStack,waitingStation,outStack);
        //printf("Carriage %d into outStack!\n",carriage);
        waitingStack.push(carriage);
        outStack.pop();
    }


    return;
}


int main(void){

    stack<int> waitingStation;
    stack<int> waitingStack;
    stack<int> outStack;

    int startNum,endNum;

    scanf("%d%d",&startNum,&endNum);
    EntranceWait(startNum,endNum,waitingStation);
    dealWaitingStack(waitingStack,waitingStation,outStack);
    return 0;
}
