#include <iostream>
#include <list>
#include <stack>

#define InfoType int
#define VertexType string


using namespace std;



typedef struct ArcNode{ //弧
    int adjvex;   //弧所指向的头下标
    struct ArcNode *nestArc = NULL;   //下一条弧
    InfoType *info;   //弧信息
}ArcNode;

typedef struct VNode{  //头结点
    VertexType* data  = NULL;
    ArcNode *firstArc = NULL;  //第一条弧指针
    int num;
    int credit;

    bool searched = false;
}VNode,* AdjList;

typedef struct ALGraphHead{
    AdjList vertices;   //头节点表
    int vexNum,arcNum;  //顶点数、弧数
}*ALGraph;

typedef struct Arc{
    string startNode;
    string endNode;
}Arc;

stack<VNode> learningStack;
/**
 * 初始化邻接表图
 * @param graph
 * @param vexNum
 */
void initALGraph(ALGraph graph,int vexNum){
    graph->vertices = (AdjList)malloc(sizeof(VNode)*vexNum);
    graph->vexNum = 1;
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
    graph->vertices[graph->vexNum].num = graph->vexNum;
    graph->vertices[graph->vexNum].data = data;
    graph->vertices[graph->vexNum].firstArc = NULL;
    graph->vexNum++;
}

int findVnode(ALGraph graph,VertexType nodeData){
    for (int i = 1; i < graph->vexNum; ++i) {
        if(*(graph->vertices[i].data) == nodeData){
            return i;
        }
    }
    return -1;
}

void initialize(ALGraph graph){

    initALGraph(graph,100);
    FILE *fin = fopen("subjectGraph.csv","r");
    if (!fin)   printf("Can't open file \"subjectGraph.csv\", please check");
    else{
        puts(">>检测到教学计划文件：subjectGraph.csv 使用该文件进行配置");
        int number;
        char*  subjectName;
        subjectName = (char *)malloc(sizeof(char)*20);
        while (fscanf(fin,"%d,%[^,||\r\n]",&number,subjectName)!=EOF){
            string name = subjectName;
                addVNode(graph,subjectName);
            char ch;
            while ((ch = fgetc(fin))!='\r'&&ch!=EOF){
                int preNum;
                fscanf(fin,"%d",&preNum);
                addArcToALGraph(graph,preNum,number,NULL);
            }
            subjectName = (char *)malloc(sizeof(char)*20);
        };
    }
    cout<<"\033[32;1m>>教学计划成功导入，本次共导入了"<<graph->vexNum-1<<"个科目，"<<graph->arcNum<<"条依赖规则\033[0m"<<endl;
    fclose(fin);
    fin = fopen("subjectCredit.csv","r");
    if (!fin)   printf("Can't open file \"subjectCredit.csv\", please check");
    else{
        puts(">>检测到学分文件：subjectCredit.csv 使用该文件进行配置");
        int credit;
        char*  subjectName;
        int n = 0;
        subjectName = (char *)malloc(sizeof(char)*20);
        while (fscanf(fin,"%[^,],%d\r\n",subjectName,&credit)!=EOF) {
            string name = subjectName;
            graph->vertices[findVnode(graph,name)].credit = credit;
            n++;
        }
        cout<<"\033[32;1m>>学分数据导入完毕，共导入"<<n<<"个科目的学分\033[0m"<<endl;
    }
}

int DFSGraph(ALGraph graph,int startNodePosition){
    if (graph->vertices[startNodePosition].searched)
        return -1;
    //cout<<*(graph->vertices[startNodePosition].data)<<endl;
    graph->vertices[startNodePosition].searched = true;

    ArcNode * arcNode = graph->vertices[startNodePosition].firstArc;

    while (arcNode){
        if(!graph->vertices[arcNode->adjvex].searched){
            DFSGraph(graph,arcNode->adjvex);
        }
        arcNode = arcNode->nestArc;
    }
    //cout<<*(graph->vertices[startNodePosition].data)<<",\t";
    learningStack.push(graph->vertices[startNodePosition]);
}

void BFSGraph(ALGraph graph,int startNodePosition){
    list<VNode> nodeList;
    list<Arc> arcList;
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
                Arc newArc;
                newArc.startNode = *node.data;
                newArc.endNode = *graph->vertices[arcNode->adjvex].data;
                arcList.push_back(newArc);
                graph->vertices[arcNode->adjvex].searched = true;
            }
            arcNode = arcNode->nestArc;
        }
    }

    while (!arcList.empty()){
        cout<<arcList.front().startNode<<"->"<<arcList.front().endNode<<endl;
        arcList.pop_front();
    }
}


void printTimeTable(ALGraph graph){
    puts(">>请输入学期总数：");
    cout<<">>";
    int maxSemesterNum;
    cin>>maxSemesterNum;
    puts(">>请输入每学期学分上限：");
    cout<<">>";
    int maxCreditPerSemester;
    cin>>maxCreditPerSemester;
    puts(">>均衡排课？：");
    cout<<">>";
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);
    bool balanced = false;
    if (getchar()=='y'){
        balanced = true;
    }

    int creditCurrent = 0;
    stack<VNode> tempLearningStack = learningStack;
    int semesterNum = 1;

    if(balanced){
        int totalSubjectNum = 0;
        while (!tempLearningStack.empty()){
            totalSubjectNum++;
            tempLearningStack.pop();
        }
        totalSubjectNum=totalSubjectNum/maxSemesterNum+1;
        tempLearningStack = learningStack;
        printf("第%d学期\n",semesterNum++);
        printf("编号\t\t课程名\t\t学分\n");
        while (!tempLearningStack.empty()){
            creditCurrent+=1;
            if (creditCurrent<totalSubjectNum){
                printf("%d\t\t%s\t\t%d\n",tempLearningStack.top().num,tempLearningStack.top().data->c_str(),tempLearningStack.top().credit);
                tempLearningStack.pop();
            } else{
                if (semesterNum>maxSemesterNum){
                    cout<<"[error]学期数不足！"<<endl;
                    break;
                } else{
                    printf("第%d学期\n",semesterNum++);
                    printf("编号\t\t课程名\t\t学分\n");
                    creditCurrent = 0;
                }
            }
        }
    } else{
        tempLearningStack = learningStack;
        printf("第%d学期\n",semesterNum++);
        while (!tempLearningStack.empty()){
            creditCurrent+=tempLearningStack.top().credit;
            if (creditCurrent<maxCreditPerSemester){
                printf("%d\t\t%s\t\t%d\n",tempLearningStack.top().num,tempLearningStack.top().data->c_str(),tempLearningStack.top().credit);
                tempLearningStack.pop();
            } else{
                if (semesterNum>maxSemesterNum){
                    cout<<"[error]学期数不足！"<<endl;
                    break;
                } else{
                    printf("第%d学期\n",semesterNum++);
                    creditCurrent = 0;
                }
            }
        }
    }

}

void menu(ALGraph graph){
    for (int j = 1; j < graph->vexNum; ++j) {
        DFSGraph(graph,j);
    }

    char c;

    puts("[options]\tfunction");
    puts("[v]\t查看当前课程信息");
    puts("[j]\t生成可行学习路径");
    puts("[t]\t自定义生成课表");
    puts("[q]\t退出");
    stack<VNode> tempLearningStack = learningStack;
    while ((c = getchar())!='q'){

        switch (c){
            case 'v':
                printf("编号\t\t课程名\t\t学分\n");
                for (int i = 1; i < graph->vexNum; ++i) {
                    cout<<"\t"<<i<<"\t"<<*(graph->vertices[i].data)<<"\t"<<graph->vertices[i].credit<<endl;
                }
                break;
            case 'j':
                tempLearningStack = learningStack;
                for (int j = 1; j < graph->vexNum; ++j) {
                    DFSGraph(graph,j);
                    while (!tempLearningStack.empty()){
                        cout<<*(tempLearningStack.top().data)<<"->";
                        tempLearningStack.pop();
                    }
                }
                break;
            case 't':
                printTimeTable(graph);
                break;
        }
        system("read -p \"请按任意键继续...\"");
        puts("[options]\tfunction");
        puts("[v]\t查看当前课程信息");
        puts("[j]\t生成可行学习路径");
        puts("[t]\t自定义生成课表");
        puts("[q]\t退出");
        setbuf(stdin,NULL);
        puts("\n\n\n");
        setbuf(stdout,NULL);
    }
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);
    setbuf(stdin,NULL);

}

int main(){
    puts("教学计划编制问题");
    puts("----------------------");
    puts("CopyRight SincereXIA");
    puts("张俊华 16030199025");
    puts("----------------------");
    puts(">>initializing...");
    ALGraph graph = new ALGraphHead;
    initialize(graph);
    puts(">>initialize Done!");
    system("read -p \"请按任意键继续...\"");
    puts("");

    menu(graph);


    for (int i = 0; i < graph->vexNum; ++i) {
        graph->vertices[i].searched = false;
    }

}