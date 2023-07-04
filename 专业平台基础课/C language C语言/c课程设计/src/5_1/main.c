#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number;
    int playerNumber;
    srand((unsigned)time(NULL));
    puts("随机数游戏开始！你准备好了吗？");
    getchar();
    while (1){
        number = rand()%100;
        while(1){
            puts("input a number:")
            scanf("%d",&playerNumber);

            if(playerNumber==number){
                puts("you Win!!");
                break;
            } else if(playerNumber>number){
                puts("too Big！！");
            } else{
                puts("too Small!!");
            }
        }
        puts("again?(y/n)");
        number = getchar();
        if(number=='n'){
            break;
        }
    }
    return 0;
}
