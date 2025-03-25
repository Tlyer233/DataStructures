#include "doubleLinkList.h"

// 初始化
DListNode *initDoubleLinkList(void) {
    // 创建头节点
    DListNode *phead = (DListNode *)malloc(sizeof(DListNode));
    phead->data = 0;  // 头节点的值域维护链表长度
    phead->prev = NULL;

    DListNode *pmove = phead;

    DataType input;
    while (scanf("%d", &input) == 1 && input != -1) {
        DListNode *newNode = (DListNode *)malloc(sizeof(DListNode));
        newNode->data = input;
        // 相互指
        newNode->prev = pmove;
        pmove->next = newNode;
        // 移动到新创建的节点
        pmove = pmove->next;
        phead->data++;
    }
    pmove->next = NULL;  // 最后一个置空
    return phead;
}
// 销毁
void destoryDoubleLinkList(DListNode *dlist) {
    DListNode *temp = dlist;
    while (dlist) {
        temp = dlist;
        dlist = dlist->next;
        free(temp);
    }
}
// 遍历
void traverseDoubleLinkeList(DListNode *dlist) {
    // 正向遍历
    int flag = 1;
    DListNode *pmove = dlist->next;
    DListNode *backward = NULL;
    while (pmove) {
        if (flag) printf("%d->", pmove->data);
        if (pmove->next == NULL) backward = pmove;  // 记录下反向指针
        pmove = pmove->next;
    }
    //  反向遍历 (为了确定, 链表生成没有问题)
    while (backward && backward->prev) {
        if (!flag) printf("%d->", backward->data);
        backward = backward->prev;
    }

    printf("NULL Length:%d\n", dlist->data);
}
// 指定位置插入
void insert(DListNode *dlist, DataType data, int posIndex) {
    assert(!(posIndex < 0 || posIndex > dlist->data) && "insert posIndex is illegal");
    DListNode *newNode = (DListNode *)malloc(sizeof(DListNode));
    newNode->data = data;

    DListNode *pmove = dlist;  // 临时变量

    while (posIndex-- > 0) pmove = pmove->next;
    if (pmove->next != NULL) pmove->next->prev = newNode;
    newNode->next = pmove->next;
    pmove->next = newNode;
    newNode->prev = pmove;
    dlist->data++;
}
// 指定位置删除
void earse(DListNode *dlist, int posIndex) {
    assert(!(posIndex < 0 || posIndex >= dlist->data) && "earse posIndex is illegal");
    DListNode *pmove = dlist;

    while (posIndex-- > 0) pmove = pmove->next;
    DListNode *temp = pmove->next;  // 存储中间节点,得会释放
    pmove->next = pmove->next->next;
    if (pmove->next != NULL) pmove->next->prev = pmove;
    free(temp);
    dlist->data--;
}