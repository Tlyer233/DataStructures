#include "redBlackTree.h"

void test(void) {
    int input[] = {17, 18, 23, 34, 27, 15, 9, 6, 8, 5, 25};
    TreeNode *tree = createRedBlackTree(input, SIZE(input));

    // 单个解开注释测试!
    // deleteNode(&tree, 15);  // 双子都有+红兄+黑兄(红孩)
    // deleteNode(&tree, 5);  // 红叶
    // deleteNode(&tree, 6);  // 一子
    // deleteNode(&tree, 23);  //  一子
    // deleteNode(&tree, 9);  // 黑兄(LL)
    deleteNode(&tree, 34);  // 黑兄(LR)
    levelTraverse(tree);
}

void test02() {
    int input[] = {15, 9, 18, 6, 13, 17, 27, 10, 23, 34, 25, 37};
    TreeNode *tree = createRedBlackTree(input, SIZE(input));
    levelTraverse(tree);
    // 连续测试
    // TODO: 有问题的哈, 这里的34没有变为红色(叶子节点, 兄弟为红色的情况有问题)
    int deleteInput[] = {18, 25, 15, 6, 13, 37, 27, 17, 34, 9, 10, 23};
    for (int i = 0; i < SIZE(deleteInput); i++) {
        printf("准备删除:%d\n", deleteInput[i]);
        deleteNode(&tree, deleteInput[i]);
        levelTraverse(tree);
    }
}
int main() {
    test02();
    return 0;
}