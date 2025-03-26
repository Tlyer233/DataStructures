#include "circularDoubleLinkList.h"

// 初始化
CDLNode *initCircularDoubleLinkList(void) {
    CDLNode *phead = (CDLNode *)malloc(sizeof(CDLNode));
    phead->data = 0;
    phead->next = phead->prev = phead;

    int input;
    while (scanf("%d", &input) == 1 && input != -1) {
        CDLNode *newNode = (CDLNode *)malloc(sizeof(CDLNode));
        newNode->data = input;
        // 尾插法
        phead->prev->next = newNode;
        newNode->prev = phead->prev;
        newNode->next = phead;

        phead->data++;
    }
    return phead;
}
// 销毁
void destory(CDLNode *cdlist) {
    CDLNode *pmove = cdlist->next;
    while (pmove != cdlist) {
        CDLNode *temp = pmove;
        pmove = pmove->next;
        free(temp);
    }
    free(cdlist);
}
// 遍历
void traverse(CDLNode *cdlist) {
    int flag = 0;  // 1为正向遍历
    if (flag) {
        CDLNode *pmove = cdlist->next;
        while (pmove != cdlist) {
            printf("%d->", pmove->data);
            pmove = pmove->next;
        }
        printf("NULL Length:%d\n", cdlist->data);  // 实际上没有NULL
    } else {
        CDLNode *pmove = cdlist->prev;
        while (pmove != cdlist) {
            printf("%d<-", pmove->data);
            pmove = pmove->prev;
        }
        printf("Length:%d\n", cdlist->data);
    }
}
// 指定位置插入
void insert(CDLNode *cdlist, DataType data, int posIndex) {
    assert(!(posIndex < 0 || posIndex > cdlist->data) && "insert posIndex is illegal!");
    CDLNode *newNode = (CDLNode *)malloc(sizeof(CDLNode));
    newNode->data = data;

    CDLNode *pmove = cdlist;
    while (posIndex-- > 0) pmove = pmove->next;
    newNode->next = pmove->next;
    pmove->next->prev = newNode;
    pmove->next = newNode;
    newNode->prev = pmove;
    cdlist->data++;
}
// 删除指的位置
void erase(CDLNode *cdlist, int posIndex) {
    assert(!(posIndex < 0 || posIndex >= cdlist->data) && "erase posIndex is illegal!");
    CDLNode *pmove = cdlist;
    while (posIndex-- > 0) pmove = pmove->next;

    pmove->next->next->prev = pmove;
    pmove->next = pmove->next->next;  // 因为循环了,分析时可以把链表倍长一倍,进行考虑

    cdlist->data--;
}
