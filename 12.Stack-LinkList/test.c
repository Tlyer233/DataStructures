#include "stack.h"

// https://www.luogu.com.cn/record/210348083
void oj() {
    int n;
    scanf("%d", &n);

    LinkStackNode *stack = initStack();
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
    destroy(stack);
}

int main() {
    oj();

    return 0;
}