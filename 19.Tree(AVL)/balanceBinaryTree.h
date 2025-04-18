#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (a > b ? a : b)

typedef struct TreeNode {
    int data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int height;
} TreeNode;

// 1.插入节点
void insert(TreeNode **tree, int x);
// 2.创建BST
TreeNode *createBSTTree();
// 3.删除指定元素
void deleteNode(TreeNode **tree, int x);
// [for test] 层次遍历
void levelTraverse(TreeNode *tree);