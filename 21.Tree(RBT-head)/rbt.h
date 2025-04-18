/** 带有头节点的 红黑树
 * 头节点的
 *  parent域存储: 整棵树的根 root
 *  lchild和rchlid域: 没有意义
 *  data: -1: data为0的表示头节点
 *  color: 0: 没有意义
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct TreeNode {
    int data;
    struct TreeNode *parent;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int color;  // 0表示黑色; 1表示红色
} TreeNode;

// 1.初始化红黑树
TreeNode *init(int *input, int length);
// 2.插入
// 2-1.修复红黑树
void fixRBTree(TreeNode *root, TreeNode *node);
TreeNode *insert(TreeNode **head, int x, TreeNode *parent);
// 3.删除
void earse(TreeNode *head, int x);

// [for test]层次遍历
void levelTraverse(TreeNode *tree);