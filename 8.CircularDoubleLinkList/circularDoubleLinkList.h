// 带头节点(数据域表示 链表长度)
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;

typedef struct circularDoubleLinkListNode {
    DataType data;
    struct circularDoubleLinkListNode *prev;
    struct circularDoubleLinkListNode *next;
} CDLNode;

// 初始化
CDLNode *initCircularDoubleLinkList(void);
// 销毁
void destory(CDLNode *cdlist);
// 遍历
void traverse(CDLNode *cdlist);
// 指定位置插入
void insert(CDLNode *cdlist, DataType data, int posIndex);
// 删除指的位置
void erase(CDLNode *cdlist, int posIndex);
