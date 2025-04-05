#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef char DataType;
typedef struct TreeNode {
    DataType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

// 1.创建树(前序序列的顺序)
void createTree(TreeNode **tree);
// 2.前序遍历
void preOrder(TreeNode *tree);
// 3.中序遍历
void inOrder(TreeNode *tree);
// 4.后续遍历
void postOrder(TreeNode *tree);
// 5.[栈]前序遍历
void preOrderWithStack(TreeNode *tree);
// 6.[栈]中序遍历
void inOrderWithStack(TreeNode *tree);
// 7.[栈]后续遍历
void postOrderWithStack(TreeNode *tree);
// 8.层次遍历
void levelOrder(TreeNode *tree);