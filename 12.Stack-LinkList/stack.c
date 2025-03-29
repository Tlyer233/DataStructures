#include "stack.h"

// 创建栈
LinkStackNode *initStack() {
    // 初始没有数值, 返回表头即可
    LinkStackNode *stackHead = (LinkStackNode *)malloc(sizeof(LinkStackNode));
    stackHead->data = 0;
    stackHead->next = NULL;
    return stackHead;
}
// 入栈
void push(LinkStackNode *stack, DataType data) {
    LinkStackNode *newNode = (LinkStackNode *)malloc(sizeof(LinkStackNode));
    newNode->data = data;
    // 头插法
    newNode->next = stack->next;
    stack->next = newNode;

    stack->data++;  // 栈的大小++
}
// 销毁
void destroy(LinkStackNode *stack) {
    // 之前链表那块实现,都是借用2个临时变量;这里只用一个试试;
    while (stack->next) {
        //  这里相当于一直"头删"
        LinkStackNode *temp = stack->next;
        stack->next = stack->next->next;
        free(temp);
    }
    free(stack);  // 最后把"哨兵头"删掉
}
// 遍历
void traverse(LinkStackNode *stack) {
    LinkStackNode *pmove = stack->next;
    while (pmove) {
        printf("%d\n", pmove->data);
        pmove = pmove->next;
    }
    printf("End Size:%d\n", stack->data);
}
// 出栈
void pop(LinkStackNode *stack) {
    assert(stack->data && "illegal!!!! stack is empty!");
    // 头删
    LinkStackNode *temp = stack->next;  // 存储起来,等会释放
    stack->next = stack->next->next;    // 已经保证不为空了
    stack->data--;                      // 栈的大小--
    free(temp);
}
// 获取栈顶元素
DataType top(LinkStackNode *stack) {
    assert(stack->data && "illegal!!!! stack is empty!");
    return stack->next->data;
}
// 判空
bool empty(LinkStackNode *stack) { return stack->data==0; }
// 栈元素个数(突然发现,用有头的会好点😅)
int size(LinkStackNode *stack) { return stack->data; }
