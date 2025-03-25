#include "polynomial.h"

// 创建多项式
LinkListNode *initPolynomial(void) {
    // 创建头节点(值域无意义)
    LinkListNode *phead = (LinkListNode *)malloc(sizeof(LinkListNode));
    phead->next = NULL;
    phead->exp = phead->coef = -1;

    float inputCoef;
    int inputExp;
    printf("请输入系数和指数(系数输入-1结束):\n");
    while (scanf("%f %d", &inputCoef, &inputExp) == 2 && inputExp != -1) {
        LinkListNode *newNode = (LinkListNode *)malloc(sizeof(LinkListNode));
        newNode->coef = inputCoef;
        newNode->exp = inputExp;
        //  按照指数(exp)升序插入链表中
        LinkListNode *pmove = phead;
        while (pmove->next != NULL && newNode->exp > pmove->next->exp) pmove = pmove->next;
        // 油饼的用户(x^2 + 2x^2 + 3x^2)这样输入
        if (pmove->next != NULL && newNode->exp == pmove->next->exp) {
            pmove->next->coef += newNode->coef;  // 合并下
        }
        // 否则就正常插入进来
        else {
            newNode->next = pmove->next;
            pmove->next = newNode;
        }
    }
    return phead;
}
// 销毁多项式
void destoryPolynomial(LinkListNode *poly) {
    while (poly) {
        LinkListNode *pre = poly;
        poly = poly->next;
        free(pre);
    }
}

// 遍历多项式
void traversePolynomial(LinkListNode *poly) {
    LinkListNode *pmove = poly->next;
    while (pmove) {
        // 打印符号
        if (pmove->coef >= 0 && pmove != poly->next) { printf("+"); }
        // 打印值
        printf("%.1fx^%d", pmove->coef, pmove->exp);
        pmove = pmove->next;
    }
    puts("");
}

// 多项式相加
LinkListNode *addPoly(LinkListNode *poly1, LinkListNode *poly2) {
    LinkListNode *newPoly = (LinkListNode *)malloc(sizeof(LinkListNode));
    newPoly->coef = newPoly->exp = -1;

    // 创建左右指针(分别指向两个有序链表的第一个元素)
    LinkListNode *l = poly1->next;
    LinkListNode *r = poly2->next;
    LinkListNode *pmove = newPoly;  // 控制newPoly的移动

    while (l && r) {
        if (l->exp < r->exp) {
            pmove->next = l;
            l = l->next;
        }
        // 两个指数相等, 可以合并
        else if (l->exp == r->exp) {
            l->coef += r->coef;  // 合并系数
            pmove->next = l;     // 任意合并一边都可以
            l = l->next;
            r = r->next;
        } else {
            pmove->next = r;
            r = r->next;
        }
        pmove = pmove->next;
    }
    // 处理剩余
    while (l) pmove->next = l, pmove = pmove->next, l = l->next;
    while (r) pmove->next = r, pmove = pmove->next, r = r->next;

    return newPoly;
}
