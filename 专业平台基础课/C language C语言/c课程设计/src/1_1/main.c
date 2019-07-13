#include <stdio.h>
#include <memory.h>
#include <windows.h>

void findDifferent(FILE *fp1, FILE *fp2) {
    /**
     * @brief 比较两个文件指针对应的txt不同之处
     * @param fp1 第一个txt对应的文件指针
     * @param fp2 第二个txt对应的文件指针
     * @author 张俊华 16030199025
     */
    const int MAX_LENGTH = 80; //每行的最大长度
    char tempString1[MAX_LENGTH];   //保存文件一的字符串
    char tempString2[MAX_LENGTH];   //保存文件一的字符串
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    int j = 0; //保存行号
    int i = 0;
    while (1) {
        j++;//增加行号
        if ((fgets(tempString1, MAX_LENGTH, fp1) == NULL) &
            (fgets(tempString2, MAX_LENGTH, fp2) == NULL)) {
            puts("未检测到不同");
        };

        if (isspace(*(tempString1 + strlen(tempString1) - 1)))
            tempString1[strlen(tempString1) - 1] = '\0';
        if (isspace(*(tempString2 + strlen(tempString2) - 1)))
            tempString2[strlen(tempString2) - 1] = '\0';
        //去掉末尾的空白字符

        if (strcmp(tempString1, tempString2)) {
            printf("在第%d行捕捉到不同\n",j);
            for (i = 0;
                 i <= (strlen(tempString1) < strlen(tempString2) ? strlen(tempString1) : strlen(tempString2)); i++) {
                if (*(tempString1 + i) == *(tempString2 + i)) {
                    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                    printf("%c", *(tempString1 + i));
                } else {
                    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    printf("%c", *(tempString1 + i));
                    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                }
            }
            if (i < strlen(tempString1)) {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                puts(tempString1 + i);
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
            } else printf("\n");

            for (i = 0;
                 i <= (strlen(tempString2) < strlen(tempString1) ? strlen(tempString2) : strlen(tempString1)); i++) {
                if (*(tempString1 + i) == *(tempString2 + i)) {
                    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                    printf("%c", *(tempString2 + i));
                } else {
                    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                    printf("%c", *(tempString2 + i));
                    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                }
            }
            if (i < strlen(tempString2)) {
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
                puts(tempString2 + i);
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
            } else printf("\n");

            return;
        }
    }


}

int main() {
    /**
     * @brief 比较两个txt的不同之处，打印第一个不同的行
     * @author 张俊华 16030199025
     */

    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE); //输出句柄
    puts("txt文件比较工具");
    puts("请将需要比较的txt文件分别命名为\"txt1.txt\",\"txt2.txt\",和本程序放在相同目录下。");
    puts("准备好了吗？");
    getchar();

    FILE *fp1;
    FILE *fp2;
    fp1 = fopen("txt1.txt", "r");
    fp2 = fopen("txt2.txt", "r");
    if (fp1 == NULL || fp2 == NULL) {
        puts("读取文件出错，请检查！");
        getchar();
        exit(1);
    }
    //初始化文件指针_只读模式

    findDifferent(fp1, fp2); //调用findDifferent比较两个文件指针对应的txt不同之处
    fclose(fp1);
    fclose(fp2);
}
