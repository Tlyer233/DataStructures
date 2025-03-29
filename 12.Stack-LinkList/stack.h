// 单链表(有头,头节点存储栈的元素个数) 实现 栈

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int DataType;
typedef struct LinkStackNode {
    DataType data;
    struct LinkStackNode *next;
} LinkStackNode;

// 创建栈
LinkStackNode *initStack();
// 销毁
void destroy(LinkStackNode *stack);
// 遍历
void traverse(LinkStackNode *stack);
// 入栈
void push(LinkStackNode *stack, DataType data);
// 出栈
void pop(LinkStackNode *stack);
// 获取栈顶元素
DataType top(LinkStackNode *stack);
// 判空
bool empty(LinkStackNode *stack);
// 栈元素个数(突然发现,用有头的会好点😅)
int size(LinkStackNode *stack);
