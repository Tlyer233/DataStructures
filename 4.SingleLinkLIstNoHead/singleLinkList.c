#include "singleLinkList.h"

// 创建链表
SingleLinkListNode *initSingleLinkList() {

    DataType input;
    if (scanf("%d", &input) == 1) {
        SingleLinkListNode *phead = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
        phead->data = input;
        phead->next = NULL;

        SingleLinkListNode *pmove = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
        pmove = phead;

        while (scanf("%d", &input) == 1) {
            SingleLinkListNode *newNode = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
            newNode->data = input;
            pmove->next = newNode;

            pmove = pmove->next;
        }
        pmove->next = NULL;
        return phead;
    } else {
        return NULL;
    }
}
// 销毁链表
void destorySingleLinkList(SingleLinkListNode *list) {
    while (list) {
        SingleLinkListNode *temp = list;
        list = list->next;
        free(list);
    }  // TODO
}
// 遍历
void traverseSingleLinkList(SingleLinkListNode *list) {
    SingleLinkListNode *temp = list;
    while (temp) {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
// 插入
void insert(SingleLinkListNode **list, DataType data, int posIndex) {
    SingleLinkListNode *newNode = (SingleLinkListNode *)malloc(sizeof(SingleLinkListNode));
    newNode->data = data;

    if ((*list) == NULL || !posIndex) {  // 相当于头插
        assert(!posIndex && "insert posIndex is illegal!");
        newNode->next = *list;
        *list = newNode;  // 改变表头
    }
    // 现在就是有头的了
    else {
        SingleLinkListNode *cur = (*list)->next;
        SingleLinkListNode *pre = (*list);
        while (--posIndex > 0) {  // 循环postIndex-1次; 后置的话会循环postIndex次
            pre = cur;
            assert(pre && "insert posIndex out of range");  // 及时断言
            cur = cur->next;
        }
        pre->next = newNode;
        newNode->next = cur;
    }
}
// 删除
void erase(SingleLinkListNode **list, int posIndex) {
    assert(*list && "list is empty!");
    if (!(*list)->next || !posIndex) {  // 相当于头删
        assert(!posIndex && "insert posIndex is illegal!");
        *list = (*list)->next;
    }
    // 现在就是有头的了
    else {
        SingleLinkListNode *cur = (*list)->next;
        SingleLinkListNode *pre = (*list);
        while (--posIndex > 0) {
            pre = cur;
            cur = cur->next;
            assert(cur && "earse posIndex out of range");  // 及时断言
        }
        pre->next = cur->next;
    }
}