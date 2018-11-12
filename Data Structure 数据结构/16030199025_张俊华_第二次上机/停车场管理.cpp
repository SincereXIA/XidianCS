#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#define ElemType ParkingInformation
typedef struct ParkingInformation{
    char status ;
    int carID = NULL;
    int time;
}ParkingInformation;

typedef struct ParkingStack{
    ElemType * base;
    ElemType * top;
    int stackSize;
}ParkingStack;

typedef struct QNode{
    ElemType carInformation;
    QNode * next;
}QNode;

typedef struct WaitingQueue{
    QNode * front;
    QNode * rear;
}WaitingQueue;


struct StackSq         //定义栈结构类型
{
    ElemType* stack;   //存栈元素的数组指针
    int top;           //存栈顶元素的下标位置
    int MaxSize;       //存stack数组长度
};

//栈满需要重新分配更大空间 的情况
void againMalloc(struct StackSq* S)
{
    ElemType *p = (ElemType *)realloc(S->stack, 2*S->MaxSize*sizeof(ElemType));//此处重新分配的空间为原来的2倍
    if (!p)  //重新分配失败
    {
        printf("存储空间用完！\n");
        exit(1);
    }
    S->stack = p;             //使list指向新栈空间
    S->MaxSize = 2 * S->MaxSize;
    printf("存储空间已扩大为当前的2倍！\n");//输出提示已扩充空间
}

//初始化栈S为空
void InitStack(struct StackSq* S, int ms)
{
    if (ms < 0)
    {
        printf("ms的值非法！\n");
        exit(1);
    }

    S->MaxSize = ms;
    S->stack = (ElemType *)malloc(ms*sizeof(ElemType));
    if (!S->stack)
    {
        printf("动态存储分配失败！\n");
        exit(1);
    }
    S->top = -1;   //值为-1，表示栈空
}

//新元素进栈，即把它插入到栈顶
void Push(struct StackSq* S, ElemType x)
{
    if (S->top == S->MaxSize - 1)
        againMalloc(S);
    S->top++;
    S->stack[S->top] = x;
}

//删除栈顶元素并返回值
ElemType Pop(struct StackSq* S)
{
    if (S->top == -1)
    {
        printf("栈空，无元素出栈！\n");
        exit(1);
    }
    S->top--;
    return S->stack[S->top + 1];
}

//4、读取栈顶元素的值（并不改变栈）
ElemType Peek(struct StackSq* S)
{
    if (S->top == -1)
    {
        printf("栈空，无任何元素！\n");
        exit(1);
    }
    return S->stack[S->top];
}

//判断S是否为空。若是空返回1，否则返回0
int EmptyStack(struct StackSq* S)
{
    if (S->top == -1)
        return 1;
    else
        return 0;
}

//清除栈S中的所有元素，释放动态存储空间
void ClearStack(struct StackSq* S)
{
    if (S->stack)
    {
        free(S->stack);   //释放存储空间
        S->stack = 0;
        S->top == -1;
        S->MaxSize = 0;
    }
}
///////////////////

//队列
/**
 * 初始化等待队列
 * @param waitingQueue
 */
void InitWaitingQueue(WaitingQueue * &waitingQueue){
    QNode * qNode = (QNode*)malloc(sizeof(QNode));
    qNode->next = NULL;
    waitingQueue = (WaitingQueue *)malloc(sizeof(WaitingQueue));
    waitingQueue->front = qNode;
    waitingQueue->rear = qNode;
}


/**
 * 出队列
 * @param waitingQueue
 * @return
 */
ElemType DeQueue(WaitingQueue *&waitingQueue){
    if (waitingQueue->rear - waitingQueue->front == 0){
        ParkingInformation parkingInformation;
        parkingInformation.carID = NULL;
        parkingInformation.status = NULL;
        return parkingInformation;
    }
    QNode *q = waitingQueue->front->next;
    ElemType carInformation = q->carInformation;
    waitingQueue->front->next = q->next;
    if (waitingQueue->rear == q)
        waitingQueue->rear = waitingQueue->front;
    free(q);
    return carInformation;
}

/**
 * 入队列
 * @param waitingQueue
 * @param carInformation
 * @return
 */
int EnQueue(WaitingQueue *&waitingQueue, ElemType carInformation){
    QNode *q =(QNode*)malloc(sizeof(QNode));
    q->carInformation =carInformation;
    q->next = NULL;
    waitingQueue->rear->next = q;
    waitingQueue->rear = q;
}
//////////////////////////////////
////车辆管理

/**
 * 车辆进入停车场
 * @param parkingStack
 * @param parkingInformation
 * @return
 */
int ParkingCar(StackSq &parkingStack,ParkingInformation parkingInformation){
    if (parkingStack.top +1  >= parkingStack.MaxSize)
        return 0;
    Push(&parkingStack,parkingInformation);
    printf("车辆进入停车场，车牌号:%d 停车位:%d\n",parkingInformation.carID,parkingStack.top+1);
    printf("时间戳: %d\n\n",parkingInformation.time);
    return 1;
}

/**
 * 车辆离开停车场
 * @param parkingStack
 * @param waitingQueue
 * @param parkingInformation
 * @return
 */
int LeavePark(StackSq &parkingStack,WaitingQueue *&waitingQueue,ParkingInformation parkingInformation){
    if (parkingStack.top == -1)
        return 0;
    ElemType car;
    while ((car = Pop(&parkingStack)).carID!=parkingInformation.carID){
        EnQueue(waitingQueue,car);
    }

    ParkingInformation carInformation;
    while (true){
        carInformation = DeQueue(waitingQueue);
        if (carInformation.carID==NULL)
            break;
        Push(&parkingStack,carInformation);
    }

    printf("车辆离开停车场，车牌号:%d , 费用:%d$\n",parkingInformation.carID,parkingInformation.time-car.time);
    printf("时间戳: %d\n\n",parkingInformation.time);
}


/**
 * 扫描车辆信息
 * @return
 */
ParkingInformation ScanParkingInformation(){

    ParkingInformation parkingInformation;
    printf("等待车辆信息:");
    //scanf("('%c",&parkingInformation.status);
    while (!isalpha(parkingInformation.status=getchar()));
    if (parkingInformation.status == 'Q')
        exit(0);
    scanf("%*[^0-9]%d",&parkingInformation.carID);
    scanf("%*[^0-9]%d",&parkingInformation.time);
    return  parkingInformation;
}


/**
 * 停车场满，等待
 * @param waitingQueue
 * @param parkingInformation
 * @return
 */
int StayWaiting(WaitingQueue *&waitingQueue ,ParkingInformation parkingInformation){
    EnQueue(waitingQueue,parkingInformation);
    printf("车位已满，请等候...\n\n");
}

/**
 * 处理等待队列
 * @param parkingStack
 * @param waitingQueue
 * @return
 */
int DealWaiting(StackSq &parkingStack,WaitingQueue *&waitingQueue){
    ParkingInformation parkingInformation;
    parkingInformation = DeQueue(waitingQueue);
    if (parkingInformation.status!=NULL){
        printf("有等待车辆，准备进入停车场...\n");
        ParkingCar(parkingStack,parkingInformation);
        return 1;
    }
    return 0;
}

int main(){

    StackSq parkingStack;
    WaitingQueue *waitingQueue;
    WaitingQueue *tempWaitingQueue;
    InitStack(&parkingStack,2);
    InitWaitingQueue(waitingQueue);
    InitWaitingQueue(tempWaitingQueue);

    printf("停车场管理系统\n");
    printf("by SincereXIA \n\n\n");
    printf("使用精简指令集模式，向下兼容 \n");
    printf("A 入库  D 出库  Q 退出系统，必选参数：车牌号  时间戳，指令与不同参数使用任意非字母数字字符分隔 \n");

    ParkingInformation parkingInformation;
    while ((parkingInformation = ScanParkingInformation()).status!='Q'){
        switch (parkingInformation.status){
            case 'A':
            case 'a':
                if (parkingStack.top + 1 >= parkingStack.MaxSize)
                    StayWaiting(waitingQueue,parkingInformation);
                ParkingCar(parkingStack,parkingInformation);
                break;
            case 'D':
            case 'd':
                LeavePark(parkingStack,tempWaitingQueue,parkingInformation);
                DealWaiting(parkingStack,waitingQueue);
                break;
        }
    }
}