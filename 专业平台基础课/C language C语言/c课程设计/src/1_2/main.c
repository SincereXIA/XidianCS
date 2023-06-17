#include <stdio.h>
#include <stdlib.h>
int compInc(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int main() {
    /**
     * @brief  对两个txt中的数字进行排序并输出新的txt
     * @author 张俊华 16030199025
     */

    const int MAX_COUNT = 1000;//最大排序数字数目
    puts("请将需要进行数字排序的txt文件分别命名为\"num1.txt\",\"num2.txt\",和本程序放在相同目录下。");
    puts("准备好了吗？");
    puts("请输入任意字符继续...");
    getchar();

    FILE * fp1;
    FILE * fp2;
    fp1=fopen("num1.txt","r");
    fp2 = fopen("num2.txt","r");
    if(fp1==NULL||fp2==NULL){
        puts("读取文件出错，请检查！");
        getchar();
        return 0;
    }
    //初始化文件指针_只读模式

    int numbers[MAX_COUNT];
    int i = 0; //numbers下标
    int j = 0; //文件读入下标
    while (fscanf(fp1,"%d",&numbers[i++])!=EOF);
    i--;
    //输出原始数据
    puts("num1中的数字：");
    for (j = 0; j < i; j++) {
        printf("%d ",numbers[j]);
    }
    printf("\n");

    while (fscanf(fp2,"%d",&numbers[i++])!=EOF);
    i--;
    puts("num2中的数字：");
    for (; j < i; j++) {
        printf("%d ",numbers[j]);
    }
    printf("\n");

    //关闭文件指针
    fclose(fp1);
    fclose(fp2);

    qsort(numbers,i, sizeof(numbers[0]),compInc); //进行排序

    puts("排序后的数字：");
    for (int l = 0; l < i; l++) {
        printf("%d ",numbers[l]);
    }//展示排序结果
    //写入文件
    FILE * fp3;
    fp3=fopen("num3.txt","w+");
    for (int m = 0; m < i; ++m) {
        fprintf(fp3,"%d ",numbers[m]);
    }
    puts("\n\n文件写入成功！");
    fclose(fp3);
    return 0;
}
