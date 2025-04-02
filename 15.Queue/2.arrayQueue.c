#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
typedef struct Queue {
    DataType *queue;
    int front;    // 指向下一元素出队的位置
    int rear;     // 指向队尾元素
    int maxSize;  // 数组的最大容量(初始化用)
} Queue;

// 1.初始化
Queue *init(int maxSize) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->queue = (DataType *)malloc(sizeof(DataType) * maxSize);
    q->front = 0;
    q->rear = -1;  // 表示(下一次没有可以出队的元素[空队列])
    q->maxSize = maxSize;
    return q;
}
// 2.销毁
void destory(Queue *q) {
    free(q->queue);
    free(q);
}
// 3.入队
void push(Queue *q, DataType data) {
    assert(!(q->rear >= q->maxSize - 1) && "rear reach maxSize!");  // 可能存在伪溢出
    q->queue[++q->rear] = data;
}
// 4.出队
void pop(Queue *q) {
    assert(!(q->rear < q->front) && "queue is empty!");  // 空
    q->front++;
}
// 5.判空
bool empty(Queue *q) {
    return q->rear < q->front;
}
// 6.元素个数
int size(Queue *q) {
    return q->rear - q->front + 1;
}
// 7.获取队头元素
int peek(Queue *q) {
    assert(!(q->rear < q->front) && "queue is empty!");  // 空
    return q->queue[q->front];
}
// 8.遍历
void traverse(Queue *q) {
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d->", q->queue[i]);
    }
    puts("END");
}

// 展示伪溢出
void test(void) {
    Queue *q = init(3);
    push(q, 1);
    push(q, 2);
    push(q, 3);
    pop(q);        //  这里弹出了一个
    push(q, 300);  // 再插入应该不会报才对(但还是报错了)
    traverse(q);
    destory(q);
}

int main() {
    test();
    return 0;
}