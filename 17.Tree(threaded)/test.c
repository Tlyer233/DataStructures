#include "threadedTree.h"

void testIn() {
    TreeNode *tree;
    initTree(&tree);

    TreeNode *pre = NULL;
    inThreadTree(tree, &pre);
    traverseinThreadTree(tree);
}
void testPre() {
    TreeNode *tree;
    initTree(&tree);

    TreeNode *pre = NULL;
    preThreadTree(tree, &pre);
    traversePreThreadTree(tree);
}

void testPost() {
    TripleTreeNode *tree;
    initTripleTree(&tree, NULL);

    TripleTreeNode *pre = NULL;
    postThreadTree(tree, &pre);
    traversePostThreadTree(tree);
}

int main() {
    testPost();
    return 0;
}
// 测试数据:
// ABD##E##C#F##