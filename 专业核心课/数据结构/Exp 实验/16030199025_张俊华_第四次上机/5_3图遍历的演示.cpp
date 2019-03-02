#include <iostream>
#include <list>
#include<malloc.h> 

#define InfoType int
#define VertexType string


using namespace std;


typedef struct ArcNode{ //弧
    int adjvex;   //弧所指向的头下标
    struct ArcNode *nestArc = NULL;   //下一条弧
    InfoType *info;   //弧信息
}ArcNode;

typedef struct VNode{  //头结点
    VertexType* data ;
    ArcNode *firstArc;  //第一条弧指针
    bool searched = false;
}VNode,* AdjList;

typedef struct ALGraphHead{
    AdjList vertices;   //头节点表
    int vexNum,arcNum;  //顶点数、弧数
}*ALGraph;

/**
 * 初始化邻接表图
 * @param graph
 * @param vexNum
 */
void initALGraph(ALGraph graph,int vexNum){
    graph->vertices = (AdjList)malloc(sizeof(VNode)*vexNum);
    graph->vexNum = 0;
    graph->arcNum = 0;
}

/**
 * 添加边
 * @param graph
 * @param startNodePosition
 * @param endNodePosition
 * @param info
 */
void addArcToALGraph(ALGraph graph,int startNodePosition, int endNodePosition,InfoType *info){
    ArcNode * arcNodePoint = graph->vertices[startNodePosition].firstArc;
    while (arcNodePoint&&arcNodePoint->nestArc!=NULL){
        arcNodePoint = arcNodePoint->nestArc;
    }
    ArcNode * newArcNode = new ArcNode;
    newArcNode->adjvex = endNodePosition;
    newArcNode->info = info;
    if (!arcNodePoint){
        graph->vertices[startNodePosition].firstArc = newArcNode;
    }else{
        arcNodePoint->nestArc = newArcNode;
    }



    graph->arcNum++;
}

/**
 * 添加头结点
 * @param graph
 * @param nodeData
 */
void addVNode(ALGraph graph,VertexType nodeData){
    string *data = new string(nodeData);
    graph->vertices[graph->vexNum].data = data;
    graph->vertices[graph->vexNum].firstArc = NULL;
    graph->vexNum++;
}

int findVnode(ALGraph graph,VertexType nodeData){
    for (int i = 0; i < graph->vexNum; ++i) {
        if(*(graph->vertices[i].data) == nodeData){
            return i;
        }
    }
    return -1;
}

void initialize(ALGraph graph){

    initALGraph(graph,100);
    FILE *fin = fopen("Graph.csv","r");
    if (!fin)   printf("Can't open file \"Graph.csv\", please check");
    else{
        char*  startData;
        char*  endData;
        startData = (char *)malloc(sizeof(char)*20);
        endData = (char *)malloc(sizeof(char)*20);
        while (fscanf(fin,"%[^,],%s%*[\r,\n]",startData,endData)!=EOF){
            string start = startData;
            string end = endData;
            if (findVnode(graph,start)==-1){
                addVNode(graph,start);

            }
            if (findVnode(graph,end)==-1){
                addVNode(graph,end);
            }
            addArcToALGraph(graph,findVnode(graph,start),findVnode(graph,end),NULL);
            startData = (char *)malloc(sizeof(char)*20);
            endData = (char *)malloc(sizeof(char)*20);
        };
    }
    fclose(fin);
}

void DFSGraph(ALGraph graph,int startNodePosition){
    if (graph->vertices[startNodePosition].searched)
        return;
    cout<<*(graph->vertices[startNodePosition].data)<<endl;
    graph->vertices[startNodePosition].searched = true;
    ArcNode * arcNode = graph->vertices[startNodePosition].firstArc;
    while (arcNode){
        DFSGraph(graph,arcNode->adjvex);
        arcNode = arcNode->nestArc;
    }
}

void BFSGraph(ALGraph graph,int startNodePosition){
    list<VNode> nodeList;
    nodeList.push_back(graph->vertices[startNodePosition]);
    graph->vertices[startNodePosition].searched = true;
    while (!nodeList.empty()){
        VNode node = nodeList.front();
        nodeList.pop_front();
        cout<<*(node.data)<<endl;
        ArcNode* arcNode = node.firstArc;
        while (arcNode){
            if (!graph->vertices[arcNode->adjvex].searched){
                nodeList.push_back(graph->vertices[arcNode->adjvex]);
                graph->vertices[arcNode->adjvex].searched = true;
            }
            arcNode = arcNode->nestArc;
        }
    }
}


int main(){
    ALGraph graph = new ALGraphHead;
    initialize(graph);
    DFSGraph(graph,0);

    for (int i = 0; i < graph->vexNum; ++i) {
        graph->vertices[i].searched = false;
    }

    cout<<"广度优先"<<endl;
    BFSGraph(graph,0);
}
