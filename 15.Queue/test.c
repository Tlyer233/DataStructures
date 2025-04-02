#include "queue.h"

void test(void) {
    Queue *q = init();
    push(q, 1);
    push(q, 2);
    push(q, 3);
    push(q, 4);
    traverse(q);
    pop(q);
    printf("size: %d\n", size(q));
    pop(q);
    pop(q);
    printf("peek: %d\n", peek(q));
    pop(q);
    traverse(q);
    printf("empty? %s\n", empty(q) ? "true" : "false");

    destory(q);
}

int main() {
    test();
    return 0;
}