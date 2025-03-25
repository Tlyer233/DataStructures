#include "singleLinkList.h"

// 创建链表
SingleLinkListNode *initSingleLinkList() {
    SingleLinkListNode *phead = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
    phead->data = 0;  // 头节点的数据域存储=>链表的长度

    SingleLinkListNode *pmove = phead;  // 移动指针

    int input;
    while (scanf("%d", &input) == 1) {  // 按下任意CTRL+英文字母(除C和Z)scanf都会返回0
        SingleLinkListNode *newNode = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
        newNode->data = input;
        pmove->next = newNode;

        pmove = pmove->next;
        phead->data++;
    }
    pmove->next = NULL;  // 记得置空
    return phead;
}
// 销毁链表(不是清空,所以头节点也需要free)
void destorySingleLinkList(SingleLinkListNode *list) {
    SingleLinkListNode *pmove = list;
    while (pmove) {
        SingleLinkListNode *temp = pmove->next;
        free(pmove);
        pmove = temp;
    }
}
// 遍历
void traverseSingleLinkList(SingleLinkListNode *list) {
    SingleLinkListNode *pmove = list->next;
    while (pmove) {
        printf("%d->", pmove->data);
        pmove = pmove->next;
    }
    printf("NULL Length:%d\n", list->data);
}
// 插入
void pushBack(SingleLinkListNode *list, DataType data) {
    SingleLinkListNode *newNode = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
    newNode->data = data;
    newNode->next = NULL;
    SingleLinkListNode *pmove = list;
    while (pmove->next)
        pmove = pmove->next;
    pmove->next = newNode;
    list->data++;
}
void pushFront(SingleLinkListNode *list, DataType data) {
    SingleLinkListNode *newNode = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
    newNode->data = data;
    newNode->next = list->next;
    list->next = newNode;
    list->data++;
}
void insert(SingleLinkListNode *list, DataType data, int posIndex) {
    // 断言里面一定是非,才会触发
    assert(!(posIndex > list->data || posIndex < 0) && "insert posIndex is illegal!");

    SingleLinkListNode *newNode = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
    newNode->data = data;

    SingleLinkListNode *cur = list->next;
    SingleLinkListNode *pre = list;
    while (posIndex--) {
        pre = cur;
        cur = cur->next;
    }
    pre->next = newNode;
    newNode->next = cur;
    list->data++;
}
// 删除
void popBack(SingleLinkListNode *list) {
    assert(list->data && "list is empty");

    SingleLinkListNode *pmove = list;
    while (pmove->next->next) {
        pmove = pmove->next;
    }
    free(pmove->next);
    pmove->next = NULL;
    list->data--;
}
void popFront(SingleLinkListNode *list) {
    assert(list->data && "list is empty");
    SingleLinkListNode *temp = list->next;
    list->next = list->next->next;
    free(temp);
    list->data--;
}
void erase(SingleLinkListNode *list, int posIndex) {
    assert(!(posIndex >= list->data || posIndex < 0) && "erase posIndex is illegal!");
    assert(list->data && "list is empty");
    SingleLinkListNode *cur = list->next;
    SingleLinkListNode *pre = list;
    while (posIndex--) {
        pre = cur;
        cur = cur->next;
    }
    pre->next = cur->next;
    free(cur);
    list->data--;
}

// 30+30+30+15=1h:45min
