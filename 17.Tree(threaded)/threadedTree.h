#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
typedef struct TreeNode {
    DataType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int ltag, rtag;  // (右边就是next,左边就是pre)如果tag=1说明是线索的; 0表示原前驱or后继
} TreeNode;

// 1.前序遍历创建树
void initTree(TreeNode **tree);
// 2.中序线索二叉树
void inThreadTree(TreeNode *tree, TreeNode **pre);
// 3.遍历中序线索二叉树
void traverseinThreadTree(TreeNode *tree);

// 4.前序线索二叉树
void preThreadTree(TreeNode *tree, TreeNode **pre);
// 5.遍历前序线索二叉树
void traversePreThreadTree(TreeNode *tree);

typedef struct TripleTreeNode {  // 三叉链表
    DataType data;
    struct TripleTreeNode *lchild;
    struct TripleTreeNode *rchild;
    struct TripleTreeNode *parent;
    int ltag, rtag;
} TripleTreeNode;
// 6.前序遍历构建'三叉链表'二叉树
void initTripleTree(TripleTreeNode **tree, TripleTreeNode *parent);
// 7.后续线索二叉树
void postThreadTree(TripleTreeNode *tree, TripleTreeNode **pre);
// 8.遍历后续线索二叉树
void traversePostThreadTree(TripleTreeNode *tree);
