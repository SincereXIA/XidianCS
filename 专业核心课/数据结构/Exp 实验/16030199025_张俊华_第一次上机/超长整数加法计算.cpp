#include <stdio.h>
#include <stdlib.h>

typedef struct SuperLongInt{
    int data=0;
    SuperLongInt * next;
    SuperLongInt * prior;
}SuperLongInt ,*LongIntNode;

/**
 * 在链表指针后部插入新节点
 * @param longIntNode
 * @param data
 */
void InsDataAfter(LongIntNode &longIntNode, int data);

/**
 * 初始化超长整数链表
 * @param superLongInt
 */
void InitSuperLongInt(SuperLongInt *&superLongInt);

/**
 * 从控制台捕捉超长整数输入
 * @param superLongInt
 * @return
 */
SuperLongInt * ScanSuperLongInt(SuperLongInt *&superLongInt);




void InitSuperLongInt(SuperLongInt *&superLongInt) {
    superLongInt = (SuperLongInt *) malloc(sizeof(SuperLongInt));
    superLongInt->data = 1;
    superLongInt->next = superLongInt;
    superLongInt->prior = superLongInt;
}

void InsDataAfter(LongIntNode &longIntNode, int data) {
    LongIntNode p = (LongIntNode) malloc(sizeof(SuperLongInt));
    p->data = data;
    p->next = longIntNode->next;
    p->prior = longIntNode;
    longIntNode->next->prior = p;
    longIntNode ->next = p;
}


SuperLongInt *ScanSuperLongInt(SuperLongInt *&superLongInt) {
    char headData[6]={0};
    scanf("%[^,;0-9]",headData);
    if (headData[0] == '-'){//负数判断
        superLongInt ->data = -1;
    } else {
        superLongInt->data = 1;
    }

    LongIntNode p = superLongInt;
    //sscanf(headData,"%d",p->data);
    //录入数据
    int nodeData;
    do{
        scanf("%d",&nodeData);
        InsDataAfter(p, nodeData);
        p = p->next;
    }while (getchar()!='\n');
    return superLongInt;
}

void PrintSuperLongInt(SuperLongInt *&superLongInt){
    if (superLongInt->data==-1){
        printf("%c",'-');
    }

    LongIntNode p = superLongInt->next;

    while (p->data==0&&p->next!=superLongInt){
        p = p->next;
    }


    printf("%d",p->data);
    if (p->next == superLongInt)
    {
        return;
    }

    while (p->next!=superLongInt&&printf(",")){
        p=p->next;
        if(p->data>1000){

        } else if (p->data>100){
            printf("0");
        } else if (p->data>10){
            printf("00");
        } else{
            printf("000");
        }
        printf("%d",p->data);
    }
    return;
}

/*
 *               9999,9999
 *     -1,-0000,-0000,-0000
 *        -9999, 0000, 0001
 *
 *
 */
SuperLongInt * AddSuperLongInt(SuperLongInt *&a, SuperLongInt *&b){
    LongIntNode pa = a;
    LongIntNode pb = b;
    SuperLongInt *result;
    InitSuperLongInt(result);
    int largeFlag = 1;
    while (pa->prior!=a||pb->prior!=b){
        if(pa->prior==a) {
            InsDataAfter(a, 0);
            largeFlag = -1;
        }
        if(pb->prior==b){
            InsDataAfter(b,0);
            largeFlag = 1;
        }

        pa = pa->prior;
        pb = pb->prior;

    }

    if(a->data * b->data > 0){

        result->data = a->data;

        int nodeResult;
        int addPrior = 0;

        pa = a;
        pb = b;
        while ((pa->prior)!=a&&(pb->prior)!=b){
            pa = pa->prior;
            pb = pb->prior;
            nodeResult = (pa->data)+(pb->data)+addPrior;
            addPrior = 0;
            if(nodeResult<0){
                addPrior = -1;
                nodeResult = 10000+nodeResult;
            } else if (nodeResult>9999){
                nodeResult = nodeResult-10000;
                addPrior =1;
            };

            InsDataAfter(result, nodeResult);
        }

        if (addPrior!=0){
            InsDataAfter(result, addPrior);
        }
    } else{

        result->data = largeFlag;

        int addPrior = 0;
        int nodeResult;

        pa = a;
        pb = b;
        while ((pa->prior)!=a&&(pb->prior)!=b){
            pa = pa->prior;
            pb = pb->prior;
            nodeResult = largeFlag==1?(pa->data)-(pb->data)+addPrior:-(pa->data)+(pb->data)+addPrior;
            addPrior = 0;
            if(nodeResult<0){
                addPrior = -1;
                nodeResult = 10000+nodeResult;
            } else if (nodeResult>9999){
                nodeResult = nodeResult-10000;
                addPrior =1;
            };

            InsDataAfter(result, nodeResult);
        }

        if (addPrior!=0){
            InsDataAfter(result, addPrior>0?addPrior:-addPrior);
        }

        result->data = largeFlag==1?a->data*addPrior:b->data*addPrior;
    }
    return result;
}


int main(){
    SuperLongInt *superLongInt;
    InitSuperLongInt(superLongInt);
    printf("please input a super long number:");
    ScanSuperLongInt(superLongInt);

    SuperLongInt *superLongInt2;
    InitSuperLongInt(superLongInt2);
    printf("please input a super long number:");
    ScanSuperLongInt(superLongInt2);

    SuperLongInt *result;
    result = AddSuperLongInt(superLongInt,superLongInt2);
    PrintSuperLongInt(result);


    return 0;
}

