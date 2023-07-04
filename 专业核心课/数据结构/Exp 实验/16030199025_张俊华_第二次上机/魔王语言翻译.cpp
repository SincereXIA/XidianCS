#include <iostream>
#include <queue>
#include <stack>


using namespace std;

stack<char> ScanMonsterWord(){
    char c;
    stack<char> tempMonsterWord;

    printf("Monster:");
    while (tempMonsterWord.empty()){
        while ((c=getchar())!='\n'){
            tempMonsterWord.push(c);
        }
    }
    stack<char> MonsterWord;
    while (!tempMonsterWord.empty()){
        c = tempMonsterWord.top();
        MonsterWord.push(c);
        tempMonsterWord.pop();
    }
    return MonsterWord;
}



queue<char> TransMonsterWord(stack<char> monsterWord,string charA,string charB){



    queue<char> humanWord;
    queue<char> tempQueue;

    char c;

    while (!monsterWord.empty()){
        c =monsterWord.top();
        monsterWord.pop();
        //B(ehnxgz)B

        switch (c){
            case 'A':
                for (int i = charA.length()-1; i >= 0; --i) {
                    monsterWord.push(charA[i]);
                }
                break;
            case 'B':
                for (int i = charB.length()-1; i >= 0; --i) {
                    monsterWord.push(charB[i]);
                }
                break;
            case '(':

                char key;
                key = monsterWord.top();
                monsterWord.pop();
                while ((c = monsterWord.top())!=')') {
                    monsterWord.pop();
                    tempQueue.push(c);
                }
                monsterWord.pop();
                while (!tempQueue.empty()){
                    c = tempQueue.front();
                    tempQueue.pop();
                    monsterWord.push(key);
                    monsterWord.push(c);
                }
                monsterWord.push(key);
                break;
            default:
                humanWord.push(c);
        }
    }
    return humanWord;
}

void speakHumanWord(queue<char> humanWord){
    char c;
    string origin = "tdsaaezgxnh";
    string trans = "天地上一只鹅追赶下蛋恨";



    queue<char> chineseWord;

    printf("Human:");
    while (!humanWord.empty()){
        c = humanWord.front();
        printf("%c",c);
        humanWord.pop();
        chineseWord.push(c);

    }

    printf("\nChinese:");
    char cc;
    while (!chineseWord.empty()) {
        cc = chineseWord.front();
        chineseWord.pop();
        for (int i = 0; i < origin.length(); ++i) {
            if (cc == origin[i]){
                printf("%c%c%c",trans[3*i],trans[3*i+1],trans[3*i+2]);
            }
        }

    }


    printf("\n\n");
}

int main(){

    string charB ;
    string charA ;
    printf("魔王语言翻译器 by SincereXIA\n\n\n");
    printf("请输入魔王charA （输入“=”使用默认“sae”）:");
    cin>>charA;
    if (charA == "=")   charA = "sae";

    printf("请输入魔王charB （输入“=”使用默认“tAdA”）:");
    cin>>charB;
    if (charB == "=")   charB = "tAdA";

    do{
        speakHumanWord(TransMonsterWord(ScanMonsterWord(),charA,charB));
        printf("Continue?(y/n):");
    }while (getchar() == 'y');
}