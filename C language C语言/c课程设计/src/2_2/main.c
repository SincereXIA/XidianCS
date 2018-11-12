#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdlib.h>

void countAlpha() {
    /**
     * @brief 计算字母出现的次数
     * @author 张俊华 16030199025
     */
    FILE *fp;
    char c;
    int countlist[26] = {0};
    /*
     * countlist存放了不同字母的字符数
     */
    fp = fopen("text.txt", "r");
    //只读打开文件
    if (fp == NULL) return;

    while (fscanf(fp, "%c", &c) != EOF) {
        if (isalpha(c)) {
            if (c >= 'a') {
                countlist[c - 'a']++;
            } else {
                countlist[c - 'A']++;
            }
        }
    }
    printf("统计完成，结果如下：\n");
    printf("\t字母\t--------\t个数\n");
    for (int i = 0; i < 26; ++i) {
        printf("\t%c\t--------\t%d\n", 'a' + i, countlist[i]);
    }

    fclose(fp);
}

void StrReplace(char *strSrc, char *strReplace, int position, int len) {
    /**
     * @brief 替换字符串
     * @param strSrc 原始字符串
     * @param strReplace 替换字符串
     * @param position 替换位置
     * @return <description>
     * @exception <name> <description>
     * @see <name>
     * @warning <text>
     * @author 张俊华 16030199025
     */
    char tempString[1000] = {0};
    //暂存字符串
    int oldlen = strlen(strSrc);
    memcpy(tempString, strSrc + position + len, strlen(strSrc) - position - len);

    memcpy(strSrc + position, strReplace, strlen(strReplace));
    //把替换字符串覆盖到源字符串的对应位置上
    memcpy(strSrc + position + strlen(strReplace), tempString, strlen(tempString));
    //加上原来保存的后半部分
    *(strSrc + oldlen + strlen(strReplace) - len) = '\0';
}

void replaceString() {
    /**
     * @brief 替换文件中的字符串
     * @author 张俊华 16030199025
     */

    FILE *fp;
    FILE *fptemp;
    char string[1000]; //用于读取原始字符串
    char keyword[200] = {0}; //检索字符串
    char strReplace[200]; //替换字符串

    fp = fopen("text.txt", "r");
    fptemp = fopen("temp.txt", "wt");
    if (fp == NULL) return;
    if (fptemp == NULL) return;
    //初始化文件指针

    printf("请输入关键字:");
    scanf("%s", keyword);
    printf("请输入替换字符:");
    scanf("%s", strReplace);

    //读取用户输入
    while (fgets(string, 1000, fp)) {
        //逐行处理
        for (int j = 0; j < strlen(string); j++) {
            //检索是否包含keyword
            int findflag = 1;
            //检索状态
            for (int i = 0; i < strlen(keyword); i++) {
                if (*(string + j + i) != keyword[i]) {
                    findflag = 0;//检索到
                    break;
                }
            }
            if (findflag) {
                printf("检索到以下匹配项包含关键字：\n");
                printf("%s\n", string);

                StrReplace(string, strReplace, j, strlen(keyword));
                //替换字符串

                printf("替换完成\n");
                printf("替换后的结果为：\n");
                printf("%s\n\n-------\n", string);

            }//执行替换
        }
        fputs(string, fptemp);
    }
    printf("所有内容处理完毕\n");
    fclose(fp);
    fclose(fptemp);
    fp = fopen("text.txt", "wt");
    fptemp = fopen("temp.txt", "r");
    while (fgets(string, 1000, fptemp)) {
        fputs(string, fp);
    }
    fclose(fptemp);
    fclose(fp);
    printf("操作成功结束！\n");
}


int main(int argc, char const *argv[]) {
    int choose = 0;

    while (1) {

        printf("\t==================\n");
        printf("\t英文文本处理工具=\n");
        printf("\t==================\n");
        printf("\t序号\t--------\t功能\n");
        printf("\t1\t--------\t统计字母个数\n");
        printf("\t2\t--------\t修改文本字符串\n");
        printf("\t0\t--------\t退出系统\n");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                countAlpha();
                break;
            case 2:
                replaceString();
                break;
            case 0:
                return 0;
            default:
                puts("请检查输入...");
        }
        puts("请按任意键继续...");
        fflush(stdin);
        getchar();
        system("cls");

    }
}



