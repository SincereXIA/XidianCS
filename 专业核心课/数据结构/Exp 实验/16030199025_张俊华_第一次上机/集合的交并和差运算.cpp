//
// Created by SincereXIA on 2017/9/24.
//
/**
 *
 * 演示执行集合的并、交、和差运算的程序
 *
 * （1）集合的元素限定为小写字母字符
 * （2）演示的程序以用户和计算机的对话方式执行
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <malloc.h>

#define MAX_LENGTH 100

typedef struct LNode
{
    char data;
    LNode * next = NULL;
}LNode, *LinkList;

bool InitList(LinkList &L){
    L = (LNode*)malloc(sizeof(LNode));
    if (L)
    {
        L->next = NULL;
        return true;
    }

    else
        return false;
}

void InsertInOrder(LinkList &LinkList, char data){
    LNode *p = LinkList;
    while (p->next){
        if (p->next->data > data){
            LNode *q = (LNode*)malloc(sizeof(LNode));
            q->data = data;
            q->next = p->next;
            p->next = q;
            return;
        } else if (p->next->data == data){
            return;
        }
        p = p->next;
    }
    if (p->data<data){
        LNode *q = (LNode*)malloc(sizeof(LNode));
        q->data = data;
        q->next = NULL;
        p->next = q;
    }
    return;

}

bool Append(LNode* &LinkList, char data){
    LNode *p = LinkList;
    LNode *q = (LNode*)malloc(sizeof(LNode));
    q->data = data;
    q->next = p->next;
    p->next = q;
}


/**
 * 求两个集合的并集
 * @param Link
 * @param Link1
 * @param Link2
 * @return LinkList Link1&Link2并集
 */
LinkList Union(LinkList &Link,LinkList &Link1, LinkList &Link2){
    InitList(Link);
    LNode * p = Link;
    LNode *p1 = Link1->next;
    LNode *p2 = Link2->next;

    while (p1&&p2){
        if (p1->data<p2->data){
            Append(p,p1->data);
            p1 = p1->next;
        } else if (p1->data > p2->data){
            Append(p,p2->data);
            p2 = p2->next;
        } else{
            Append(p,p1->data);
            p1 = p1->next;
            p2 = p2->next;
        }
        p = p->next;
    }

    while (p1){
        Append(p,p1->data);
        p1 = p1->next;
    }

    while (p2){
        Append(p,p2->data);
        p2 = p2->next;
    }
    return Link;
}

void PrintList(LinkList &LinkList){
    LNode *p = LinkList->next;
    printf("{ ");
    while (p){
        printf("%c",p->data);
        p = p->next;
    }
    printf(" }\n");
    return;
}

/**
 * 求两个集合的交集
 * @param Link
 * @param LinkList1
 * @param LinkList2
 * @return LinkList 交集
 */
LinkList Intersection(LinkList &Link, LinkList &LinkList1, LinkList &LinkList2);

LinkList Intersection(LinkList &Link, LinkList &LinkList1, LinkList &LinkList2) {
    InitList(Link);
    LNode * p = Link;
    LNode *p1 = LinkList1->next;
    LNode *p2 = LinkList2->next;

    while (p1&&p2){
        if (p1->data<p2->data){
            p1 = p1->next;
        } else if (p1->data > p2->data){
            p2 = p2->next;
        } else{
            Append(p,p1->data);
            p1 = p1->next;
            p2 = p2->next;
            p = p->next;
        }
    }

    return Link;

}

/**
 * 计算两个集合的差集
 * @param LinkList
 * @param LinkList1
 * @param LinkList2
 * @return LinKList 差集
 */
LinkList Difference(LinkList &Link ,LinkList &LinkList1,LinkList &LinkList2){
    InitList(Link);
    LNode * p = Link;
    LNode *p1 = LinkList1->next;
    LNode *p2 = LinkList2->next;

    while (p1&&p2){
        if (p1->data<p2->data){
            Append(p,p1->data);
            p1 = p1->next;
            p = p->next;
        } else if (p1->data > p2->data){
            p2 = p2->next;
        } else{
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    while (p1){
        Append(p,p1->data);
        p1 = p1->next;
    }

    while (p2){
        Append(p,p2->data);
        p2 = p2->next;
    }
    return Link;
}

int main()
{
    LNode * LinkList1;
    InitList(LinkList1);

    LNode * LinkList2;
    InitList(LinkList2);

    printf("Please input Set1:");
    char dataString[MAX_LENGTH];
    scanf("%s",dataString);

    for (int i = 0; i < strlen(dataString); ++i) {
        InsertInOrder(LinkList1,dataString[i]);
    }

    printf("Please input Set2:");
    scanf("%s",dataString);

    for (int i = 0; i < strlen(dataString); ++i) {
        InsertInOrder(LinkList2,dataString[i]);
    }
    printf("Set1: ");
    PrintList(LinkList1);
    printf("Set2: ");
    PrintList(LinkList2);

    LinkList UnionList;
    printf("Union of Set1 & Set2: ");
    UnionList = Union(UnionList,LinkList1,LinkList2);
    PrintList(UnionList);

    LinkList IntersectionList;
    printf("Intersection of Set1 & Set2: ");
    IntersectionList = Intersection(IntersectionList, LinkList1,LinkList2);
    PrintList(IntersectionList);

    LinkList DifferenceList;
    printf(" Set1 - Set2: ");
    DifferenceList = Difference(DifferenceList, LinkList1,LinkList2);
    PrintList(DifferenceList);


    return 0;
}

