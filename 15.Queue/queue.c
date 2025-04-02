#include "queue.h"

// 1.初始化
Queue *init(void) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->queueSize = 0;
    return q;
}
// 2.销毁
void destory(Queue *q) {
    while (q->front) {
        Node *temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    free(q);
}
// 3.遍历
void traverse(Queue *q) {
    Node *pmove = q->front;
    while (pmove) {
        printf("%d->", pmove->data);
        pmove = pmove->next;
    }
    printf("END Size:%d\n", q->queueSize);
}
// 4.入队(尾插)
void push(Queue *q, DataType data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (q->front == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->queueSize++;
}
// 5.出队(头删)
void pop(Queue *q) {
    assert(q->front && "queue is empty!");
    Node *temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL) { // 如果删空了,尾指针也要指向NULL
        q->rear = NULL;
    }

    free(temp);
    q->queueSize--;
}
// 6.获取队头元素
DataType peek(Queue *q) {
    assert(q->front && "queue is empty!");
    return q->front->data;
}
// 7.判空
bool empty(Queue *q) {
    return q->front == NULL;
}
// 8.获取队列元素个数
int size(Queue *q) {
    return q->queueSize;
}
