#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 4
#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define MAX(a, b) (a > b ? a : b)

typedef struct TreeNode {
    int keys[M];
    int keyNums;
    struct TreeNode *children[M + 1];
    int childNums;

    int isLeaf;  // 1表示当前节点为叶子节点
} TreeNode;

typedef struct BTree {
    TreeNode *root;  // 整棵树的根
} BTree;

// 1.初始化BTree
BTree *init(int *arr, int len);
// 2.插入元素
void insert(BTree *head, int x);
// 3.删除元素
void earse(BTree *head, int x);
// 4.层次遍历BTree
void traverseBTree(BTree *head);

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    init(arr, SIZE(arr));
    return 0;
}
// 1.初始化BTree
BTree *init(int *arr, int len) {
    BTree *head = (BTree *)malloc(sizeof(BTree));  // 哨兵头

    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));  // 整棵树真正的根
    root->isLeaf = 1;
    root->childNums = root->keyNums = 0;

    head->root = root;
    // 插入填充初始化的值
    for (int i = 0; i < len; i++) {
        insert(head, *(arr + i));
        traverseBTree(head);
    }
    return head;
}

// 2.插入元素
/** 2.2取中值 getMiddle()分析
 M = 3   中值:M/2=1  如下例子对2,4,6这个需要分裂的结点做分析
  2, 4, 6  keyNum=3                childToSplit   newNode
  / | \ \  childNum=4        keys   [0,M/2)      (M/2, keyNum)
 1  3 5  7               children   [0,M/2]      (M/2, childNum)
                           keyNum    M/2            不用计算      //  统一就是 getMiddle()
                         childNum    M/2+1          不用计算      //  统一就是 getMiddle()+1

     4
    / \
   2   6
  /|   |\
 1 3   5 7
===============================================================
 M = 4 中值:M/2=2   如下例子对2,4,6,8这个需要分裂的结点做分析
  2,4,6,8    keyNum=4           childToSplit  newNode
  / / | \ \  childNum=5    keys [0, M/2-1)    (M/2-1, keyNum)
 1 3  5 7  9,10        children [0, M/2-1]    (M/2-1, childNum)
                         keyNum   M/2-1             不用计算    //  统一就是 getMiddle()
                       childNum    M/2              不用计算     //  统一就是 getMiddle()+1
     4
    / \
   2  6,8
 / |  / | \
 1 3  5 7  9,10
 */
int getMiddle() {
    return M % 2 == 0 ? M / 2 - 1 : M / 2;
}
// 2-1.分裂结点
/**
 * TreeNode* parent   : 需要分裂结点的父亲 (当满的节点为根时, parent可能为NULL)
 * Tree* childToSplite: 需要分裂的节点
 * int index          : parent->children[index]=splitToNode; //满的结点, 也就是需要分离的结点
 * @return 返回true说明(parent)要继续分裂
 */
bool splitNode(TreeNode *parent, TreeNode *childToSplite, int index) {
    int midVal = childToSplite->keys[getMiddle()];

    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->isLeaf = childToSplite->isLeaf;
    newNode->childNums = newNode->keyNums = 0;
    // 分keys
    for (int i = getMiddle() + 1, j = 0; i < childToSplite->keyNums; i++, j++) {
        newNode->keys[j] = childToSplite->keys[i];
        newNode->keyNums++;
    }
    childToSplite->keyNums = getMiddle();
    // 分children
    if (!newNode->isLeaf) {
        for (int i = getMiddle() + 1, j = 0; i < childToSplite->childNums; i++, j++) {
            newNode->children[j] = childToSplite->children[i];
            newNode->childNums++;
        }
        childToSplite->childNums = getMiddle() + 1;
    }

    // 如果是根节点 childToSplit还需要分一个左边的节点出来
    // childToSplit为根节点   leftNode为根节点的左节点,  newNode为根节点的右节点
    // 为什么这样, 因为这样不用换"哨兵头"的根指向
    if (parent == NULL) {
        // 程序执行到这一行时, childToSplit没有中间结点 , 正是我们想要的leftNode
        TreeNode *leftNode = (TreeNode *)malloc(sizeof(TreeNode));
        memcpy(leftNode, childToSplite, sizeof(TreeNode));  // 拷贝(浅)

        // childToSplit作为新根
        childToSplite->isLeaf = 0;
        childToSplite->childNums = 2;
        childToSplite->children[0] = leftNode, childToSplite->children[1] = newNode;
        childToSplite->keyNums = 1;
        childToSplite->keys[0] = midVal;
    }
    // 正常情况下维护父节点的 keys 和 children
    else {
        // keys:  在父节点的index位置进行插入 midVal
        int insertPos = parent->keyNums - 1;
        while (insertPos >= index)
            parent->keys[insertPos + 1] = parent->keys[insertPos];
        parent->keys[index] = midVal;
        parent->keyNums++;
        // children: 在父节点的index+1伪造插入 newNode
        insertPos = parent->childNums - 1;
        while (insertPos >= index + 1)
            parent->children[insertPos + 1] = parent->children[insertPos];
        parent->children[index + 1] = newNode;
        parent->childNums++;

        return parent->keyNums == M;  // 可能parent也爆了, 返回true继续向上分离
    }
    return false;
}
void insert(BTree *head, int x) {
    TreeNode *pmove = head->root;

    // 记录插入节点, 经过的所有路径; 由traceParent[i]的traceIndex[i]索引的孩子进入下一结点
    int traceI = 0;
    TreeNode *traceParent[100];
    int traceIndex[100];
    memset(traceParent, 0, sizeof(traceParent));  // 全部初始化为NULL

    // STEP1:确保在🍃节点插入
    while (pmove->isLeaf != 1) {
        int index = 0;
        // 找插入的位置
        while (index < pmove->keyNums && x > pmove->keys[index])
            index++;
        traceParent[traceI] = pmove;
        traceIndex[traceI] = index;
        traceI++;
        pmove = pmove->children[index];
    }

    // STEP2:先插入,再分裂;
    int insertPos = pmove->keyNums - 1;
    while (pmove->keys[insertPos] > x) {
        pmove->keys[insertPos + 1] = pmove->keys[insertPos];
        insertPos--;
    }
    insertPos++;
    pmove->keys[MAX(0, insertPos)] = x;  // insertPost可能为-1; 如x=0, keys=[1,2,3,4]
    pmove->keyNums++;

    // STEP3:判断是否需要分裂
    if (pmove->keyNums == M) {
        // 妙
        for (int i = traceI - 1; splitNode(traceParent[i], pmove, traceIndex[i]); i--) {
            pmove = traceParent[i];
        }
    }
}

// 3.删除元素
void earse(BTree *head, int x) {
    // 逻辑有问题
    // // 找到要删除的节点 (也需要记录路径,因为可能导致 链式下溢)
    // TreeNode *pmove = head->root;

    // int traceI;
    // TreeNode *traceParent[100];
    // int traceIndex[100];
    // memset(traceParent, 0, sizeof(traceParent));  // 初始化全NULL

    // // STEP1:找到需要删除结点
    // while () {
    //     int index = 0;
    //     while (index < pmove->keyNums && pmove->keys[index] < x)
    //         index++;
    //     traceParent[traceI] = pmove;
    //     traceIndex[traceI] = index;
    //     traceI++;
    //     pmove = pmove->children[index];
    // }
    // // STEP2:先删除,后判断是否下溢
    // for (int i = 0; i < pmove->keyNums; i++) {
    //     if (pmove->keys[i] == x) {
    //         while (i + 1 < pmove->keyNums) {  // 后面的值覆盖前面
    //             pmove[i] = pmove[i + 1];
    //             i++;
    //         }
    //         pmove->keyNums--;
    //         break;
    //     }
    // }

    // // STEP3:判断下溢
    // if (pmove->keyNums < (int)ceil(M / 2)) {

    // }
}

// 4.层次遍历BTree
void traverseBTree(BTree *head) {
    TreeNode *q[100];
    int hh = 0, tt = -1;
    q[++tt] = head->root;
    while (hh <= tt) {
        for (int i = 0; i < q[hh]->keyNums; i++) {
            printf("%d%s", q[hh]->keys[i], i < q[hh]->keyNums - 1 ? "," : "");
        }
        // 入队下一层
        for (int i = 0; i < q[hh]->childNums; i++) {
            q[++tt] = q[hh]->children[i];
        }
        hh++;
        printf("  ");
    }
    puts("");
}
