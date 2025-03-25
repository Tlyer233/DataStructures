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
// 销毁链表
void destorySingleLinkList(SingleLinkListNode *list);
// 遍历
void traverseSingleLinkList(SingleLinkListNode *list);
// 插入
void insert(SingleLinkListNode **list, DataType data, int posIndex);
// 删除
void erase(SingleLinkListNode **list, int posIndex);