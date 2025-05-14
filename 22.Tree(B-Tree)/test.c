#include "btree.h"

void test(void) {
    int inputArr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    BTree *btree = init(inputArr, SIZE(inputArr));
}

int main() {
    test();
    return 0;
}