#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define N 5

int q[N];
int front = 0, rear = 0;  // 注意front在队头元素的位置, rear在尾元素的下一个位置

/**
 * 一定是 (rear-front+N)%N 因为计算一段的长度一定是"末尾-头",只是因为这里是循环的, 减为负的情况,+N%N就解决了
 * 问题:如果N个空间全部利用的话 (rear-front+N)%N 初始时:rear和front都是0, 结果为0;  添加5个元素后rear绕一圈回来还是0,front不动,从而导致不知道是空还是满
 * 解决:牺牲一个空间使得 队空(front==rear) 和 队满((rear+1)%N==front) 状态有明确区分
 *      也就是, 如果((rear+1)%N==front)就不能push了==>满了
 *              如果front==rear就不能pop了==>空了
 */

// 入队
void push(int x) {
    assert(!((rear + 1) % N == front) && "circularQueue is full");
    q[rear] = x;
    rear = (rear + 1) % N;
}
// 出队
void pop() {
    assert(!(front == rear) && "circularQueue is empty");
    front = (front + 1) % N;
}
// 获取队头元素
int peek() {
    assert(!(front == rear) && "circularQueue is empty");
    return q[front];
}
// 判空
bool empty() {
    return front == rear;
}
// 获取元素个数
int size() {
    return (rear - front + N) % N;
}

// 遍历
void traverse() {
    for (int i = front; i != rear; i = (i + 1) % N) {
        printf("%d->", q[i]);
    }
    puts("END");
}

void test01(void) {
    push(1);
    push(2);
    traverse();
    pop();
    // push(3);
    push(4);
    push(5);
    push(6);
    traverse();
}

int main() {
    test01();
    return 0;
}