#include <stdbool.h>
#include <stdio.h>

#define N 100

int q[N];
int hh = 0, tt = -1;  // hh指向队头元素, tt指向队尾元素
// 1.push
void push(int x) {
    q[++tt] = x;
}
// 2.pop
void pop() {
    hh++;
}

// 3.取队头
int peek() {
    return q[hh];
}
// 4.判空
bool empty() {
    return tt < hh;  // 空的
}
