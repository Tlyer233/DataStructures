#include "binarySearchTree.h"

void test(void) {
    TreeNode *tree = createBinarySearchTree();
    levelTraverse(tree);
    puts("");

    
    deleteNode(&tree, 78);
    levelTraverse(tree);
    puts("");
}

int main() {
    test();
    return 0;
}
// 4 5 19 23 2 8 -1
// 53 17 9 45 23 78 65 94 81 88 -1