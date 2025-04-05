#include "tree.h"

void test01(void) {
    TreeNode *tree = NULL;
    createTree(&tree);
    preOrder(tree);
    puts("");
    inOrder(tree);
    puts("");
    postOrder(tree);
    puts("");
    puts("=================");
    preOrderWithStack(tree);
    puts("");
    inOrderWithStack(tree);
    puts("");
    postOrderWithStack(tree);
    puts("");
    puts("=================");
    levelOrder(tree);
}

int main() {
    test01();
    return 0;
}