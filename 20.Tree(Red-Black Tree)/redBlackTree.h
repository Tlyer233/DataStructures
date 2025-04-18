// 写累了?太难了? 去看看人家Linux内核的红黑树,当消遣看看
// https://github.com/torvalds/linux/blob/master/lib/rbtree.c#L630
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX(a, b) (a > b ? a : b)
#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct TreeNode {
    int data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    struct TreeNode *parent;
    int color;  // 1表示红色 0表示黑色
} TreeNode;
/** 为什么不需要维护高度; 不是要LR, RL..类型判断吗?
 * 在"红黑树"中,类型的判断是通过 node在root和root->child的什么位置来判断的
 * 并不是和"AVL"一样, 通过平衡因子判断
 * 所以不需要维护height;
 */

// 1.插入节点
TreeNode *insert(TreeNode **tree, int x);
// 2.创建Red-Black Tree
TreeNode *createRedBlackTree();
// 3.删除指定元素
void deleteNodeRecursion(TreeNode **tree, int x,TreeNode **root);

// [for test] 层次遍历
void levelTraverse(TreeNode *tree);

void deleteNode(TreeNode **tree, int x);