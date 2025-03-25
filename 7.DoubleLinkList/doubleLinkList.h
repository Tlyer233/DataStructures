// 带头节点
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct DoubleLinkListNode {
    DataType data;
    struct DoubleLinkListNode *prev;
    struct DoubleLinkListNode *next;
} DListNode;

// 初始化
DListNode *initDoubleLinkList(void);
// 销毁
void destoryDoubleLinkList(DListNode *dlist);
// 遍历
void traverseDoubleLinkeList(DListNode* dlist);
// 指定位置插入
void insert(DListNode* dlist, DataType data, int posIndex);
// 指定位置删除
void earse(DListNode* dlist, int posIndex);
