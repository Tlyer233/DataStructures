#include "generalList.h"

// 初始化
void initGeneralList(GeneralListNode **glist) {
    char input;
    scanf("%c", &input);
    if (input == '(') {  // 说明是一个表节点
        GeneralListNode *newNode = (GeneralListNode *)malloc(sizeof(GeneralListNode));
        newNode->tag = 1;
        // TODO
        initGeneralList(&(newNode->subList));
        initGeneralList(&(newNode->next));
        *glist = newNode;
    } else if (input == ',') {
        initGeneralList(glist);
    } else if (input == ')' || input == '\n') {
        *glist = NULL;
    } else {  // 是元素(原子)
        GeneralListNode *newNode = (GeneralListNode *)malloc(sizeof(GeneralListNode));
        newNode->tag = 0;
        newNode->data = input;
        initGeneralList(&(newNode->next));
        *glist = newNode;
    }
}
// 遍历
void traverseGeneralList(GeneralListNode *glist) {
    if (glist == NULL) {
        printf("不存在该表");
        return;
    }
    if (glist->tag == 1) {
        printf("(");
        traverseGeneralList(glist->subList);
        printf(")");
    } else {
        if (glist->data == '#')
            printf("");
        else
            printf("%c", glist->data);
    }

    if (glist->next != NULL) {
        printf(",");
        traverseGeneralList(glist->next);
    }
}

// 获取广义表长度(元素个数)
int getLength(GeneralListNode *glist) {
    int len = 0;
    GeneralListNode *ghead = glist->subList;
    // 空表
    if (ghead->tag == 0 && ghead->data == '#')
        return len;
    // 长度至少为1 or 至少有一个元素
    else {
        while (ghead) {
            len++;
            ghead = ghead->next;
        }
        return len;
    }
}

/**
 * 获取广义表的深度
 * 广义表深度的定义: 空表的深度为1, 原子(元素)的深度为0
 * 考试就 数左括号, 数到第一个右括号为止
 */
int getDepth(GeneralListNode *glist) {
    if (glist->tag == 0 && glist->next == NULL)
        return 0;
    else {
        int p1 = glist->next != NULL ? getDepth(glist->next) : 0;
        // 只有tag为1才有子表; 不能判断这个glist->subList != NULL, 有坑哈
        int p2 = glist->tag == 1 ? getDepth(glist->subList) : 0;
        return glist->tag + MAX(p1, p2);  // 只有表才会多送1层; 节点是不能送1层(否则会凭空多一层)
    }
}
// 获取广义表的表头
GeneralListNode *getHead(GeneralListNode *glist) {
    GeneralListNode *ghead = glist->subList;
    // 空广义表,没有表头
    if (ghead->tag == 0 && ghead->data == '#')
        return NULL;
    GeneralListNode *resGHead = (GeneralListNode *)malloc(sizeof(GeneralListNode));
    resGHead->tag = ghead->tag;
    resGHead->next = NULL;
    if (resGHead->tag)
        resGHead->subList = ghead->subList;
    else
        resGHead->data = ghead->data;
    return resGHead;
}
// 获取广义表的表尾
GeneralListNode *getTail(GeneralListNode *glist) {
    GeneralListNode *ghead = glist->subList;
    // 空广义表,没有表头
    if (ghead->tag == 0 && ghead->data == '#')
        return NULL;

    // 表尾一定是一个表
    GeneralListNode *newGList = (GeneralListNode *)malloc(sizeof(GeneralListNode));
    newGList->tag = 1;
    newGList->next = NULL;

    GeneralListNode *tailGList = ghead->next;  // 假"表尾"
    // 说明是表尾是一个空表
    if (tailGList == NULL) {
        tailGList = (GeneralListNode *)malloc(sizeof(GeneralListNode));
        tailGList->tag = 0;
        tailGList->data = '#';  // #表示空表
        tailGList->next = NULL;
    }
    newGList->subList = tailGList;  // 封装为一个表
    return newGList;
}
