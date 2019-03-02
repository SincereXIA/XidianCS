#include <ctime>
#include <iostream>
#include <queue>
#include <windows.h>
#define MAX_NUM_OF_GRADES 10
#define MAX_NUM_OF_STUDENTS 100
using namespace std;
typedef struct studentsInfo {
    string students_id;
    string students_name;
    int grades[MAX_NUM_OF_GRADES];
} studentsInfo;
string subjectName[MAX_NUM_OF_GRADES];
studentsInfo studentsInfos[MAX_NUM_OF_STUDENTS];
int STUDENTS_NUM = 0;
int SUBJECT_NUM = 0;

void scanInfo() {
    FILE *fp = fopen("studentsGrades.csv", "r");
    int subjectNum = 0;
    char Name[100];

    fscanf(fp, "%[^,\r,\n]", Name);
    fgetc(fp);
    fscanf(fp, "%[^,\r,\n]", Name);
    while (fgetc(fp) != '\r') {
        fscanf(fp, "%[^,\r,\n]", Name);
        subjectName[subjectNum++] = Name;
    }
    int studentNum = 1;
    while (getc(fp) && fscanf(fp, "%[^,]%*[,]", Name) != EOF) {
        studentsInfos[studentNum].students_id = Name;
        fscanf(fp, "%[^,]", Name);
        studentsInfos[studentNum].students_name = Name;
        subjectNum = 0;
        while (fgetc(fp) != '\r') {
            fscanf(fp, "%d", &studentsInfos[studentNum].grades[subjectNum++]);
        }
        studentNum++;
    }
    STUDENTS_NUM = studentNum;
    SUBJECT_NUM = subjectNum;
    printf(">>成绩信息导入完成！\n");
    cout<<">>共导入"<<STUDENTS_NUM-1<<"位同学信息, 有效科目共"<<SUBJECT_NUM-1<<"个"<<endl;
}

void radixSort(int key,int start,int end){
    queue<studentsInfo> infoQueue[100];
    for (int i = 1; i <= STUDENTS_NUM; ++i) {
        infoQueue[studentsInfos[i].grades[key]].push(studentsInfos[i]);
    }
    int i = 1;
    for (int j = 100; j >= 0; --j) {
        while (!infoQueue[j].empty()){
            studentsInfos[i++] = infoQueue[j].front();
            infoQueue[j].pop();
        }
    }
}

void sort(int key, int start, int end) {
    bool flag = true;
    for (int i = start; i < end && flag; ++i) {
        flag = false;
        for (int j = end; j > i; --j) {
            if (studentsInfos[j].grades[key] > studentsInfos[j - 1].grades[key]) {
                studentsInfos[0] = studentsInfos[j];
                studentsInfos[j] = studentsInfos[j - 1];
                studentsInfos[j - 1] = studentsInfos[0];
                flag = true;
            }
        }
    }
}

int paration(int key, int low, int high) {
    studentsInfos[0] = studentsInfos[low];
    int pivotkey = studentsInfos[low].grades[key];
    while (low < high) {
        while (low < high && studentsInfos[high].grades[key] >= pivotkey)
            --high;
        studentsInfos[low] = studentsInfos[high];
        while (low < high && studentsInfos[low].grades[key] <= pivotkey)
            ++low;
        studentsInfos[high] = studentsInfos[low];
    }
    studentsInfos[low] = studentsInfos[0];
    return low;
}

void quickSort(int key, int low, int high) {
    if (low < high) {
        int pivotloc = paration(key, low, high);
        quickSort(key, low, pivotloc - 1);
        quickSort(key, pivotloc + 1, high);
    }
}

void printResult() {
    printf("排名\t姓名\t学号\t");
    for (int k = 0; k < SUBJECT_NUM; ++k) {
        printf("%s\t",subjectName[k].c_str());
    }
    cout<<endl;
    for (int i = 1; i < STUDENTS_NUM; ++i) {
        cout << i <<"\t"<< studentsInfos[i].students_name + "\t" + studentsInfos[i].students_id + "\t\t\t\t";
        for (int j = 0; j < SUBJECT_NUM; ++j) {
            cout << studentsInfos[i].grades[j] << "\t\t\t\t\t";
        }
        cout << endl;
    }
}

void multSort(bool isRadix){

    cout<<"当前科目关键字"<<endl;
    for (int k = 0; k < SUBJECT_NUM; ++k) {
        printf("%d:\t%s\n",k,subjectName[k].c_str());
    }
    printf("\n\n");
    cout<<"请输入多个关键字序号（权重依次降低）：";
    char line[100];
    int keys[MAX_NUM_OF_GRADES];
    int i = 0;
    int l = 0;
    char c;
    while((c = getchar()) != '\n' && c != EOF);
    gets(line);
    while (sscanf(&line[l],"%d",&keys[i++])){
        while (line[l]!=' '){
            l++;
        }
        if(!line[++l]) break;
    }

    LARGE_INTEGER  num;
    long long start,end,freq;
    QueryPerformanceFrequency(&num);
    freq=num.QuadPart;
    QueryPerformanceCounter(&num);
    start= num.QuadPart;
    for (int j = i-1 ; j >= 0 ; --j) {
        if (isRadix){
            radixSort(keys[j],1,30);
        } else{
            sort(keys[j],1,30);
        }
    }

    QueryPerformanceCounter(&num);
    end= num.QuadPart;
    printf("time=%lld\n",(end-start)*1000/freq);
}
void menu(){
    char c;

    puts("[options]\tfunction");
    puts("[v]\t查看当前排名");
    puts("[j]\t多关键字排名");
    puts("[o]\t初始化");
    puts("[q]\t退出");

    while ((c = getchar())!='q'){

        switch (c){
            case 'v':
                printResult();
                break;
            case 'j':
                cout<<"使用基数排序？（y/n):";
                while((c = getchar()) != '\n' && c != EOF);
                multSort(getchar() == 'y');
                printResult();
                break;
            case 'o':
                scanInfo();
                break;
        }
        system("read -p \"请按任意键继续...\"");
        puts("[options]\tfunction");
        puts("[v]\t查看当前排名");
        puts("[j]\t多关键字排名");
        puts("[o]\t初始化");
        puts("[q]\t退出");
        setbuf(stdin,NULL);
        puts("\n\n\n");
        setbuf(stdout,NULL);
    }
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);
    setbuf(stdin,NULL);

}
int main() {
    puts("多关键字排序");
    puts("----------------------");
    puts("CopyRight SincereXIA");
    puts("张俊华 16030199025");
    puts("----------------------");
    puts(">>initializing...");
    clock_t start, finish;
    start = clock();
    scanInfo();
    puts(">>initialize Done!");
    finish = clock();
    double duration;
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Done Done Don!!!!!!\n\nSpend time:%lf sec\n\n",duration);
    system("read -p \"请按任意键继续...\"");
    puts("");
    menu();
    multSort(true);
    printResult();
}
