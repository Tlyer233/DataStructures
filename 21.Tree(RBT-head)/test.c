#include "rbt.h"

void test() {
    int input[] = {15, 9, 18, 6, 13, 17, 27, 10, 23, 34, 25, 37};
    TreeNode *rbTree = init(input, SIZE(input));
    levelTraverse(rbTree->parent);
    // 测试删除
    int deleteInput[] = {18, 25, 15, 6, 13, 37, 27, 17, 34, 9, 10, 23};
    for (int i = 0; i < SIZE(deleteInput); i++) {
        printf("准备删除:%d\n", deleteInput[i]);
        earse(rbTree->parent, deleteInput[i]);
        levelTraverse(rbTree->parent);
    }
}

int main() {
    test();
    return 0;
}