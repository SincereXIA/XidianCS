#include <iostream>
#include <list>
#include <stack>
#include <cstring>

using namespace std;
typedef struct hfmTreeNode {
    char c;
    int freq;
    hfmTreeNode *leftChild;
    hfmTreeNode *rightChild;
} hfmTreeNode, *hfmTree;


class hfmFreq {
public:
    char c;
    int freq;

    bool operator<(const hfmFreq &freqNode) {
        return freq > freqNode.freq;
    }
};

hfmTree tree;

/**
 * 添加哈夫曼节点
 * @param c
 * @param code
 * @param tree
 */
void buildHfmNode(char c, char* code, hfmTree tree) {
    if(!tree){
        tree = new hfmTreeNode;
    }
    for (int i = 0; i < strlen(code); ++i) {
        if (code[i]-'0'){
            if (tree->leftChild){
                tree = tree->leftChild;
            } else {
                hfmTreeNode * newLChild = new  hfmTreeNode;
                newLChild->c = NULL;
                newLChild->leftChild = NULL;
                newLChild->rightChild = NULL;
                tree->leftChild = newLChild;
                tree = tree->leftChild;
            }
        } else{
            if (tree->rightChild){
                tree = tree->rightChild;
            } else {
                hfmTreeNode * newRChild = new  hfmTreeNode;
                tree->rightChild = newRChild;
                newRChild->c = NULL;
                newRChild->leftChild = NULL;
                newRChild->rightChild = NULL;
                tree = tree->rightChild;
            }
        }
    }
    tree->c = c;
}


/**
 * 初始化哈夫曼树
 */
hfmTree initHfmTree() {
    hfmTree tree = new hfmTreeNode;
    tree->c = NULL;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    return tree;
}

/**
 * 打印哈夫曼树
 */
void printHfmTree(hfmTree tree, string ss = "") {
    if (tree == NULL)
        return;
    ss += "   ";
    printHfmTree(tree->rightChild, ss);
    char c = tree->c ? tree->c : '*';
    cout << ss << c << endl;
    printHfmTree(tree->leftChild, ss);
}

void printHfmCode(hfmTree tree, string code = "", FILE* outFile = NULL, bool outputToFile = false) {
    if (!tree)
        return;
    string LCode = code + "1";
    printHfmCode(tree->leftChild, LCode,outFile,outputToFile);

    string RCode = code + "0";
    printHfmCode(tree->rightChild, RCode,outFile,outputToFile);

    if (tree->c) {
        cout << "'" << tree->c << "'" << "\t,\t" << code << endl;
        if (outputToFile&&outFile){
            fprintf(outFile,"%c,%s\n",tree->c,code.c_str());
        }
    }
}

void buildHfmTreeFromFreq(FILE *fin, FILE *fout) {
    list<hfmFreq> freq;
    char c;
    int cfreq;
    while (fscanf(fin, "%c%*[,]", &c) != EOF) {
        fscanf(fin, "%d%*[\n,\r]", &cfreq);
        hfmFreq freqNode;
        freqNode.c = c;
        freqNode.freq = cfreq;
        freq.push_back(freqNode);
    }
    freq.sort();
    /*while (!freq.empty()) {
        hfmFreq Node = freq.front();
        printf("%c,%d\n",Node.c,Node.freq);
        freq.pop_front();
    }*/
    stack<hfmTree> hfmTreeStack;
    hfmTree node = new hfmTreeNode;
    node->c = freq.front().c;
    node->freq = freq.front().freq;
    node->rightChild = NULL;
    node->leftChild = NULL;
    hfmTreeStack.push(node);
    freq.pop_front();
    while (!freq.empty() || !hfmTreeStack.empty()) {
        hfmTree newParentNode = new hfmTreeNode;
        if (freq.empty()) {
            if (hfmTreeStack.size() == 1) {
                tree = hfmTreeStack.top();
                printHfmCode(tree,"",fout, true);
                break;
            }
            newParentNode->leftChild = hfmTreeStack.top();
            hfmTreeStack.pop();
            newParentNode->rightChild = hfmTreeStack.top();
            hfmTreeStack.pop();
            newParentNode->freq = newParentNode->leftChild->freq + newParentNode->rightChild->freq;
            newParentNode->c = NULL;
        } else if (hfmTreeStack.top()->freq <= freq.front().freq) {
            hfmTree newRNode = new hfmTreeNode;
            newRNode->c = freq.front().c;
            newRNode->freq = freq.front().freq;
            newRNode->leftChild = NULL;
            newRNode->rightChild = NULL;

            hfmTree newLNode = hfmTreeStack.top();
            newParentNode->leftChild = newLNode;
            newParentNode->rightChild = newRNode;
            newParentNode->freq = newRNode->freq + newLNode->freq;
            newParentNode->c = NULL;
            hfmTreeStack.pop();
            freq.pop_front();
        } else {
            hfmTree newRNode = new hfmTreeNode;
            newRNode->c = freq.front().c;
            newRNode->freq = freq.front().freq;
            newRNode->leftChild = NULL;
            newRNode->rightChild = NULL;
            freq.pop_front();


            hfmTree newLNode = new hfmTreeNode;
            newLNode->c = freq.front().c;
            newLNode->freq = freq.front().freq;
            newLNode->leftChild = NULL;
            newLNode->rightChild = NULL;
            newParentNode->leftChild = newLNode;
            newParentNode->rightChild = newRNode;
            newParentNode->freq = newRNode->freq + newLNode->freq;
            newParentNode->c = NULL;
            freq.pop_front();
        }

        stack<hfmTree> tempStack;
        while (!hfmTreeStack.empty() && hfmTreeStack.top()->freq < newParentNode->freq) {
            hfmTree tempNode = hfmTreeStack.top();
            tempStack.push(tempNode);
            hfmTreeStack.pop();
        }
        hfmTreeStack.push(newParentNode);
        while (!tempStack.empty()) {
            hfmTree tempNode = tempStack.top();
            hfmTreeStack.push(tempNode);
            tempStack.pop();
        }

    }
}

string findCharHfmCode(char c, string tempCode = "",hfmTree tree = tree) {

    string code = "";

    if (tree->c == c) {
        return tempCode;
    }

    if (tree->leftChild) {
        string LCode = tempCode + "1";
        code = findCharHfmCode(c, LCode,tree->leftChild);
        if (code.length())
            return code;
    }
    if (tree->rightChild) {
        string RCode = tempCode + "0";
        code = findCharHfmCode(c, RCode,tree->rightChild);
        if (code.length())
            return code;
    }

    return code;


}

string zipTextByHfm(string text, hfmTree tree = tree, bool TerminalPrint = true) {
    string zippedText = "";
    for (int i = 0; i < text.length(); ++i) {
        char c;
        c = text[i];
        zippedText += findCharHfmCode(c);
    }
    if (TerminalPrint)
        cout << zippedText;
    return zippedText;
}

void unzipTextByHfm(string text, hfmTree tree = tree) {
    hfmTree originTree = tree;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] - '0') {
            tree = tree->leftChild;
        } else {
            tree = tree->rightChild;
        }
        if (tree->c) {
            cout << tree->c;
            tree = originTree;
        }
    }
}

/**
 * 初始化
 * @return
 */
int initialization() {

    puts("hfmCoding System alpha");
    puts("----------------------");
    puts("CopyRight SincereXIA");
    puts("张俊华 16030199025");
    puts("----------------------");
    puts("初始化...");

    FILE *fin, *fout;
    fin = fopen("hfmTree.csv", "r");
    if (fin) {
        cout<<">>检测到存在保存的哈夫曼树：hfmTree.csv，使用？"<<endl;
        cout<<">>";

        char c;
        if ((c = getchar())=='y')
        {
            char code[100];
            tree = initHfmTree();
            char c;
            while (fscanf(fin, "%c%*[,]", &c) != EOF) {
                fscanf(fin, "%s%*[\n,\r]", code);
                buildHfmNode(c, code, tree);
            }
            string ss;
            printHfmTree(tree,ss);
            fclose(fin);
            cout<<">>哈夫曼树初始化完毕"<<endl;
        }
    }
    {
        fin = fopen("charFre.csv", "r");
        if (fin) {
            setbuf(stdin,NULL);
            cout<<"检测到存在字典频率：charFre.csv，使用？"<<endl;
            char c = getchar();
            if (c == 'y'){
                fout = fopen("hfmTree.csv", "w");
                buildHfmTreeFromFreq(fin, fout);
                fclose(fout);
            }
        }
        fclose(fin);

    }
}

/**
 * 对文件编码
 * @param file
 * @param tree
 */
void encodingFromTXT(FILE *inputFile,FILE* outputFile,hfmTree tree = tree){
    char c;
    while ((c = fgetc(inputFile))!=EOF){
        string s = findCharHfmCode(c);
        fprintf(outputFile,"%s",s.c_str());
    }
}

void  decodingFromTXT(FILE *inputFile,FILE *outputFile, hfmTree tree = tree){
    hfmTree originTree = tree;
    char c;
    while ((c = fgetc(inputFile))!=EOF){
        if (c-'0'){
            tree = tree->leftChild;
        } else {
            tree = tree->rightChild;
        }
        if (tree->c) {
            fputc(tree->c,outputFile);
            tree = originTree;
        }
    }
}

void menu(){

    char c;
    FILE* inputFile;
    FILE* outputFile;
    string string1;
    string string2;

    while ((c = getchar())!='q'){
        puts("[options]\tfunction");
        puts("[p]\t凹入表打印当前霍夫曼树");
        puts("[v]\t霍夫曼码打印当前霍夫曼树");
        puts("[e]\t控制台编码");
        puts("[d]\t控制台解码");
        puts("[t]\t编码文件TextFile.txt->CodeFile.txt");
        puts("[c]\t解码文件CodeFile.txt->TextFile.txt");
        puts("[q]\t退出");

        switch (c){
            case 'p':
                printHfmTree(tree);
                break;
            case 'v':
                printHfmCode(tree);
                break;
            case 'e':
                setbuf(stdin,NULL);
                puts(">>请输入:");
                cin>>string1;
                cout<<string1<<"的哈夫曼码为：";
                zipTextByHfm(string1);
                cout<<endl;
                break;
            case 'd':
                setbuf(stdin,NULL);
                puts(">>请输入:");
                cin>>string2;
                cout<<string2<<"的原码为：";
                unzipTextByHfm(string2);
                cout<<endl;
                break;
            case 't':
                inputFile = fopen("TextFile.txt","r");
                outputFile = fopen("CodeFile.txt","wb");
                encodingFromTXT(inputFile,outputFile);
                fclose(inputFile);
                fclose(outputFile);
                puts("文件编码完成！");
                break;
            case 'c':
                inputFile = fopen("CodeFile.txt","r");
                outputFile = fopen("TextFile.txt","wb");
                decodingFromTXT(inputFile,outputFile);
                fclose(inputFile);
                fclose(outputFile);
                puts("文件解码完成！");

        }
        setbuf(stdin,NULL);
        puts("\n\n\n");
        setbuf(stdout,NULL);
    }
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);

    setbuf(stdin,NULL);

}



int main() {
    initialization(); //初始化
    menu();           //菜单                   //SincereXIA 2017/11/12
    return 0;
}