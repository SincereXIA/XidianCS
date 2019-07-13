/*
 * 现有两个文本文件db1.txt和db2.txt。
 * db1.txt中第一列为姓名，第二列为英语成绩；
 * db2.txt中第一列为姓名，第二列为数学成绩。
 * 通过姓名字段将db1.txt文件关联到db2.txt文件生成db3.txt文件。
 * db3.txt文件第一列为姓名，第二列为英语成绩，
 * 第三列为数学成绩，第四列为平均成绩，
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS_AMOUNT 100
typedef struct {
    char name[20]; //姓名
    int englishGrade; //英语成绩
    int mathGrade; //数学成绩
    double average; //平均成绩
} StuGrades;

StuGrades StructstuGrades[MAX_STUDENTS_AMOUNT];
//结构体数组,存放学生信息

int comInt(const void *p, const void *q) {
    return -(int) ((*(StuGrades *) p).average - (*(StuGrades *) q).average);
}

int main() {
    /**
     * @brief 成绩处理工具
     * @author 张俊华 16030199025
     */
    //初始化文件指针
    puts("请将需要进行处理的分数数据分别命名为\"db1.txt\",\"db2.txt\",和本程序放在相同目录下。");
    puts("准备好了吗？");
    puts("请输入任意字符继续...");
    getchar();

    FILE *fp1 = fopen("db1.txt", "r");
    FILE *fp2 = fopen("db2.txt", "r");
    FILE *fp3 = fopen("db3.txt", "w+");
    if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
        puts("打开文件失败！");
    }
    puts("打开文件成功");

    int i = 0;
    char name[20];
    int grade;
    while (fscanf(fp1, "%s%d", StructstuGrades[i].name, &StructstuGrades[i].englishGrade) != EOF)
        i++;

    while (fscanf(fp2, "%s%d", name, &grade) != EOF) {
        //寻找学生在上一个名单的位置
        for (int j = 0; j < i; ++j) {
            if (strcmp(name, StructstuGrades[j].name) == 0) {
                StructstuGrades[j].mathGrade = grade;
            }
        }
    }

    for (int j = 0; j < i; ++j) {
        StructstuGrades[j].average = (StructstuGrades[j].englishGrade + StructstuGrades[j].mathGrade) / 2.0;
    }//计算平均分数
    //排序
    qsort(StructstuGrades, i, sizeof(StuGrades), comInt);

    //输出
    puts("以下为处理结果:");
    printf("%15s %4s %4s %4s\n", "姓名", "英语", "数学", "平均分数");
    for (int k = 0; k < i; ++k) {
        printf("%15s %4d %4d %4.2lf\n", StructstuGrades[k].name, StructstuGrades[k].englishGrade,
               StructstuGrades[k].mathGrade, StructstuGrades[k].average);
    }
    //写入文件
    for (int k = 0; k < i; ++k) {
        fprintf(fp3, "%15s %4d %4d %4.2lf\n", StructstuGrades[k].name, StructstuGrades[k].englishGrade,
                StructstuGrades[k].mathGrade, StructstuGrades[k].average);
    }
    printf("写入文件\"db3.txt\"成功!!");
}
