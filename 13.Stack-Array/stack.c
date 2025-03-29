#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DataType int

typedef struct Stack {
    DataType *stack;
    int head;  // 永远指向栈顶
    int maxSize;
} Stack;

// 一.初始化
Stack *init(int maxSize) {
    Stack *myStack = (Stack *)malloc(sizeof(Stack));
    myStack->stack = (DataType *)malloc(sizeof(DataType) * maxSize);
    myStack->maxSize = maxSize;
    myStack->head = -1;
    return myStack;
}
// 二.压栈
void push(Stack *myStack, DataType data) {
    assert(!(myStack->head == myStack->maxSize - 1) && "Stack is over maxSize!");
    myStack->stack[++myStack->head] = data;
}
// 三.出栈
void pop(Stack *myStack) {
    assert(!(myStack->head == -1) && " illegal stack is empty");
    myStack->head--;
}
// 四.遍历
void traverse(Stack *myStack) {
    for (int i = myStack->head; i >= 0; i--) {
        printf("%d\n", myStack->stack[i]);
    }
    puts("END");
}
// 五.取栈顶元素
DataType top(Stack *myStack) {
    return myStack->stack[myStack->head];
}
// 六.判空
bool empty(Stack *myStack) {
    return myStack->head == -1;
}
// 七.栈的大小
int size(Stack *myStack) {
    return myStack->head + 1;
}

void oj(void);  // https://www.luogu.com.cn/problem/U295781
int main() {
    oj();
    return 0;
}

void oj(void) {
    int n;
    scanf("%d", &n);
    Stack *stack = init(1000);
    while (n--) {
        char instruction[100];
        scanf("%s", instruction);
        // 1.push x – 向栈顶插入一个数 x ；
        if (!strcmp(instruction, "push")) {
            int x;
            scanf("%d", &x);
            push(stack, x);
        }
        // 2.pop – 从栈顶弹出一个数；
        else if (!strcmp(instruction, "pop")) {
            pop(stack);
        }
        // 3.empty – 判断栈是否为空；
        else if (!strcmp(instruction, "empty")) {
            printf("%s\n", empty(stack) ? "YES" : "NO");
        }
        // 4.query – 查询栈顶元素。
        else if (!strcmp(instruction, "query")) {
            printf("%d\n", top(stack));
        }
    }
}
