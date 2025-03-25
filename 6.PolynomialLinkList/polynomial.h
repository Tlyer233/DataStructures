
// 单链表实现多项式(带有头节点)
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkListNode {
    int exp;     // 指数
    float coef;  // 系数
    struct LinkListNode *next;
} LinkListNode;

// 创建多项式
LinkListNode *initPolynomial(void);
// 销毁多项式
void destoryPolynomial(LinkListNode *poly);
// 遍历多项式
void traversePolynomial(LinkListNode *poly);
// 多项式相加
LinkListNode *addPoly(LinkListNode *poly1, LinkListNode *poly2);