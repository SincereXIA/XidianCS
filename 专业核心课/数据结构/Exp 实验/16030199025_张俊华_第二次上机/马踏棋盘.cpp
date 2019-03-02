#include <iostream>
#include <queue>
#include <stack>
#include <time.h>

using namespace std;

typedef struct chessNode{
    int i;
    int j;
    int nextNodeNum[8] = {0,1,2,3,4,5,6,7};
}chessNode;

int Board[8][8] = {0};

int htry1[] = {-2,-1,1,2,2,1,-1,-2};
int htry2[] = {1,2,2,1,-1,-2,-2,-1};

chessNode ScanChessNode(){
    printf("please in put the start position(i<=7,j<=7):");
    chessNode chessNode1;
    scanf("%d%d",&chessNode1.i,&chessNode1.j);
    //chessNode1.nextNodeNum = 0;
    return chessNode1;
}

bool isFinish(stack<chessNode> &result){

    return result.size() == 63;
}

bool available(chessNode chessNode1){

    if(chessNode1.i>7||chessNode1.i<0||chessNode1.j>7||chessNode1.j<0){
        return false;
    }

    return Board[chessNode1.i][chessNode1.j] == 0;
}

void mark(chessNode chessNode1){
    Board[chessNode1.i][chessNode1.j] = 1;
}

void unMark(chessNode chessNode1){
    Board[chessNode1.i][chessNode1.j] = 0;
}



void printBoard(){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            printf("\t%2.d",Board[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void PrintRoute(stack<chessNode> result){
    if (result.empty()){
        printf("There is no way found!\n\n");
        return;
    }
    chessNode chessNode1;
    int i = 63;
    while (!result.empty()){
        chessNode1 = result.top();
        Board[chessNode1.i][chessNode1.j] = i;
        i--;
        result.pop();
        //printf("(%d, %d)\n",chessNode1.i,chessNode1.j);
    }
    printBoard();
}

int AavailableLevel(chessNode chessNode1){
    int count = 0;

    for (int i = 0; i < 8; ++i) {
        int xi = chessNode1.i + htry1[i];
        int xj = chessNode1.j + htry2[i];
        if (Board[xi][xj] == 0){
            count++;
        }
    }
    return count;
}

stack<chessNode> DFSchess(chessNode startNode){

    int maxdeep = 0;

    clock_t start, finish;
    start = clock();


    chessNode nextChessNode = startNode;
    stack<chessNode> result;

    while (!isFinish(result)){
        if(maxdeep<=result.size()){
            PrintRoute(result);
            printf("Deep: %ld\n",result.size());
            maxdeep = (int )result.size();
        }

        //getchar();
        int i;
        //开始遍历下一步节点
        int availableLevel = 9;
        int findFlag = -1;
        for (i = 0; i < 8; ++i) {
            if (startNode.nextNodeNum[i] == -1){
                continue;
            }
            nextChessNode.i = startNode.i + htry1[startNode.nextNodeNum[i]];
            nextChessNode.j = startNode.j + htry2[startNode.nextNodeNum[i]];
            //printf("Try: %d,%d\n",nextChessNode.i,nextChessNode.j);
            if (available(nextChessNode)){
                int ta = AavailableLevel(nextChessNode);
                if (ta<=availableLevel){
                    availableLevel =ta;
                    findFlag = i;
                }
            }

        }
        if (findFlag!=-1){
            //发现可用节点
            startNode.nextNodeNum[findFlag] = -1; //保存本次遍历位置
            //printf("Check %d,%d,%d Ok\n",startNode.i,startNode.j,i);
            result.push(startNode); //节点入栈
            mark(startNode); //在棋盘上标注节点
            nextChessNode.i = startNode.i + htry1[findFlag];
            nextChessNode.j = startNode.j + htry2[findFlag];
            startNode = nextChessNode;  //更新下一步节点位置
            //printf("Find %d,%d\n",startNode.i,startNode.j);
        } else{ //遍历后发现无可走位置

            startNode = result.top();
            unMark(startNode); //撤回已走标记
            result.pop();
            //startNode = result.top();
            //unMark(startNode);
            //result.pop();

            if (result.empty()){ //根本无路可走
                return result;
            }
            //startNode.nextNodeNum++;
            //printf("Back to %d,%d,%d\n",startNode.i,startNode.j,startNode.nextNodeNum);

        }

    }
    finish = clock();
    double duration;
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Done Done Done!!!!!!\n\nSpend time:%lf sec\n\n",duration);
    return result;
}


int main(){
    PrintRoute(DFSchess(ScanChessNode()));
}
