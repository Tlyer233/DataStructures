// 无头单链表+再封装 实现队列
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
typedef struct Node {
    DataType data;
    struct Node *next;
} Node;

// 再封装(这个才是实际上的"队列")
// 再封装的思想,Node还是链表, 只是用front和rear记录了下头和尾
typedef struct Queue {
    Node *front;
    Node *rear;
    int queueSize;  // 队列大小
} Queue;

// 1.初始化
Queue *init(void);
// 2.销毁
void destory(Queue *q);
// 3.遍历
void traverse(Queue *q);
// 4.入队
void push(Queue *q, DataType data);
// 5.出队
void pop(Queue *q);
// 6.获取队头元素
DataType peek(Queue *q);
// 7.判空
bool empty(Queue *q);
// 8.获取队列元素个数
int size(Queue *q);
