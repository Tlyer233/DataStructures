#include "balanceBinaryTree.h"

void test() {
    TreeNode *tree = createBSTTree();
    levelTraverse(tree);
}
void test01() {
    TreeNode *tree = createBSTTree();
    levelTraverse(tree);
    // 测试 case1
    // deleteNode(&tree, 70);  
    // deleteNode(&tree, 55);  
    // 测试 case2
    // deleteNode(&tree, 70);
    // deleteNode(&tree, 60);
    // 测试 case3
    // deleteNode(&tree, 40);

    deleteNode(&tree, 8);
    deleteNode(&tree, 7);
    levelTraverse(tree);
}

int main() {
    test01();
    return 0;
}
// 10 6 11 1 7 12 0 2 3 -1
// 50 40 60 30 45 55 70 20 -1
// 5 3 7 2 4 6 8 1 -1