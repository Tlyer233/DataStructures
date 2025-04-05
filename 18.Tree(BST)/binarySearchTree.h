#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

// 1.插入节点
void insertVal(TreeNode **tree, int x);
// 2.创建BST
TreeNode *createBinarySearchTree();
// 3.查找指定元素(注意:标准的BST中没有两个节点的val值相同)
TreeNode *search(TreeNode *tree, int x);
// 4.删除指定元素(传二级,有可能把自己删了)
void deleteNode(TreeNode **tree, int x);

// [for test] 中序遍历(递增序列)
void inOrderTraverse(TreeNode *tree);
// [for test] 层次遍历
void levelTraverse(TreeNode* tree);