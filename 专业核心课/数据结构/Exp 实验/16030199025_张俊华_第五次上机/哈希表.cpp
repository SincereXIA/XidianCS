#include <iostream>

using namespace std;


int conflictTime = 0;
/**
 * 用户信息
 */
typedef struct userInfo{
    string name = "";
    string id;
    string phone_number;
}userInfo;
userInfo DataBase[60];

/**
 * 姓名哈希
 * @param name
 * @return
 */
int getHash(string name){
    long long n = 0;
    for (int i = 0; i < name.length(); ++i) {
        n += toascii(name[i]);
    }
    return n%60;
}

/**
 * 伪随机散列再哈希
 * @param hash
 * @param i
 * @return
 */
int reHash(int hash,int i){
    conflictTime++;
    return (hash+3*i+7)%60;
}


/**
 * 储存信息
 * @param info
 * @param hash
 */
void addInformation(userInfo info,int hash){
    DataBase[hash].name = info.name;
    DataBase[hash].phone_number = info.phone_number;
    DataBase[hash].id = info.id;
}

/**
 * 读取信息
 * @param key
 * @return
 */
userInfo searchInformation(string key){
    int hashVal = getHash(key);
    for (int i = 0; DataBase[hashVal].name!=key&&DataBase[hashVal].name!=""; ++i) {
        hashVal = reHash(getHash(key),i);
    }
    return DataBase[hashVal];
}


/**
 * 初始化哈希表
 */
void initHashMap(){
    int userNum = 0;
    FILE * fp = fopen("userInfo.csv","r");
    if (!fp){
        cout<<"CAN NOT OPEN FILE userInfo.csv, please check";
        exit(404);
    }
    cout<<"\033[35m>>文件句柄创建成功！正在构建哈希表...\033[0m"<<endl;
    printf("\n\033[1m\033[33m姓名\t学号\t\t手机号\t\t哈希\033[0m\n");
    char name[50],id[50],phone_number[50];
    while (fscanf(fp,"%[^,],%[^,],%[^\r\n]\r\n",name,id,phone_number)!=EOF){
        userInfo info;
        info.name = name;
        info.id = id;
        info.phone_number = phone_number;

        int hashVal;
        hashVal = getHash(info.name);
        for (int i = 0 ;DataBase[hashVal].name!="";i++){
            hashVal = reHash(getHash(info.name),i);
        }
        addInformation(info, hashVal);
        cout<<info.name+"\t"+info.id+"\t"+info.phone_number+"\t\033[31m"<<hashVal<<"\033[0m"<<endl;
        userNum++;
    }

    cout<<"\033[32m哈希表共录入了"<<userNum<<"个数据，共执行了"<<conflictTime<<"次冲突处理\033[0m"<<endl;
}


void showInformation(userInfo info){
    printf("\n\033[1m\033[33m姓名\t学号\t\t手机号\033[0m\n");
    puts("-------------------------------------");
    cout<<"\033[K\033[32m\033[1m"+info.name+"\033[0m\t"+info.id+"\t"+info.phone_number<<endl;
}

int main(){
    puts("\033[1m\033[31m哈希表演示系统 Hash Show\033[0m");
    puts("----------------------");
    puts("\033[1m\033[33mCopyRight SincereXIA");
    puts("auth: 张俊华 16030199025");
    puts("2017/12/2 XDU\033[0m");
    puts("----------------------");
    puts(">>initializing...");
    initHashMap();
    puts(">>initialize Done!");
    system("read -p \"\033[32m\033[1m系统就绪，请按任意键继续...\033[0m\"");
    puts("\033[2J");
    cout<<"请输入需要查询的姓名：\033[K";
    string key;
    cin>>key;
    while (key!="q"){
        showInformation(searchInformation(key));
        printf("\033[5A请输入需要查询的姓名：\033[K");
        cin>>key;
    }
};
