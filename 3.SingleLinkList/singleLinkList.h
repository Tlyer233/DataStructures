//  带 头结点的 单链表;
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct SingleLinkListNode {
    DataType data;
    struct SingleLinkListNode *next;
} SingleLinkListNode;

// 创建链表
SingleLinkListNode *initSingleLinkList();
// 销毁链表(不是清空,所以头节点也需要free)
void destorySingleLinkList(SingleLinkListNode *list);
// 遍历
void traverseSingleLinkList(SingleLinkListNode *list);
// 插入
void pushBack(SingleLinkListNode *list, DataType data);
void pushFront(SingleLinkListNode *list, DataType data);
void insert(SingleLinkListNode *list, DataType data, int posIndex);
// 删除
void popBack(SingleLinkListNode *list);
void popFront(SingleLinkListNode *list);
void erase(SingleLinkListNode *list, int posIndex);
