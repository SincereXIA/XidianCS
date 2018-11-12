#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 100 //最大随机数量
int main() {

    int randomList[MAX_NUMBER]; //数列存储生成的随机数
    int n; //需要生成的随机数个数
    int min; //随机数最小值
    int max; //随机数最大值
	srand((unsigned) time(NULL));
    do {
        puts("请输入需要生成的随机数数量：");
        scanf("%d", &n);
        if(n>=0&&n<=MAX_NUMBER) {
            break;
        } else{
            puts("请检查输入的数字，请重新输入");
        }
    }while (1);

    do {
        puts("请输入需要生成的随机数最小值：");
        scanf("%d", &min);
        puts("请输入需要生成的随机数最大值：");
        scanf("%d", &max);
        if(min<max) {
            break;
        } else{
            puts("请检查输入的数字，请重新输入");
        }
    }while (1);
    while (1) {
        for (int i = 0; i < n; ++i) {

            int newRandomNumber = 0;
     
            newRandomNumber = (rand() % (max - min)) + min;
            int findSameFlag = 0;
            for (int j = 0; j < i; ++j) {
                if (randomList[j] == newRandomNumber) {
                    i--;
                    findSameFlag = 1;
                    break;
                    //检查到重复即重新生成
                }
            }
            if(!findSameFlag)
                randomList[i] = newRandomNumber;
            //无重复将新随机数加入数列
        }

        puts("生成了以下随机数:");
        for (int k = 0; k < n; ++k) {
            printf("%d , ", randomList[k]);
        }
        puts("继续生成吗？(y/n)");
        fflush(stdin); 
        char choise;
        choise = getchar();
        if(choise == n){
            break;
        }

    }

}
