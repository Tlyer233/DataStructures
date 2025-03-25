#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef char DataType;

typedef struct GeneralListNode {
    int tag;  //  1表示字表节点; 0表示元素节点
    union {
        DataType data;
        struct GeneralListNode *subList;
    };
    struct GeneralListNode *next;
} GeneralListNode;

// 初始化
void initGeneralList(GeneralListNode **glist);
// 遍历
void traverseGeneralList(GeneralListNode *glist);

// 获取广义表长度(元素个数)
int getLength(GeneralListNode *glist);
// 获取广义表的深度
int getDepth(GeneralListNode *glist);
// 获取广义表的表头
GeneralListNode *getHead(GeneralListNode *glist);
// 获取广义表的表尾
GeneralListNode *getTail(GeneralListNode *glist);
