#include <stdio.h>
#include <stdlib.h>

#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define M 3  // B树的阶

// 定义BTree的每一个"结点"
// 使用"哨兵头", 哨兵头的keyNum==-1 && parent位置存储整棵BTree的根
typedef struct TreeNode {
    int keyNum;                        // 当前节点"键"  的个数
    int keys[M + 1];                   // 键值 (代码实现上,最多能存到M个,所以开M+1的大小)
    int childrenNum;                   // 当前节点"子树"的个数
    struct TreeNode *children[M + 1];  // 子树 (每个节点最多有M个子树,所以开M+1的大小)

    int isLeaf;  // 1为叶子🍃结点,0为非叶子
} TreeNode;

typedef struct BTree {
    struct TreeNode *root;  // B树的根
} BTree;

// 1.初始化BTree
BTree *init(int *arr, int len);
// 2.插入元素
void insert(BTree *head, int x);
// 3.删除元素
void earse(BTree *head, int x);
// 4.层次遍历BTree
void traverseBTree(BTree *head);