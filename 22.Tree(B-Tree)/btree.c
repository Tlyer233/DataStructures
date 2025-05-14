#include "btree.h"

// 1.初始化BTree
BTree *init(int *arr, int len) {
    // BTree哨兵头
    BTree *head = (BTree *)malloc(sizeof(BTree));

    // 创建整棵树的根
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->isLeaf = 1;
    root->keyNum = root->childrenNum = 0;

    head->root = root;  // 哨兵头的parent域为整棵树的根(root)

    // 使用传入的数组,初始化BTree
    for (int i = 0; i < len; i++) {
        insert(head, *(arr + i));
        traverseBTree(head);
    }
    return head;
}

/**  获取中间节点(中值靠左): 分裂时,需要提升的节点
 * 无论是keys还是children都符合, 举例试下;
 * 这里有坑哈,!!!!❗❗❗
 */
int getMiddle(int x) {
    return M % 2 == 0 ? x / 2 - 1 : x / 2;
}
/** 分裂结点
 * TreeNode *parent:需要分裂结点的父节点
 * int        index:需要分裂结点,在父节点的children[]中的下标
 * BTree      *head:BTree哨兵头
 */
void splitNode(TreeNode *parent, int index, BTree *head) {
    // 找需要分裂的节点
    TreeNode *childToSplit;
    if (parent != NULL) {
        childToSplit = parent->children[index];
    } else {
        // 等于NULL,说明,我们要分裂的节点没有Parent,一棵树中,只有根没有parent
        childToSplit = head->root;

        // 顺手new一个新parent
        parent = (TreeNode *)malloc(sizeof(TreeNode));
        parent->isLeaf = 0;
        parent->childrenNum = parent->keyNum = 0;

        // 赋值index(因为在insert方法中,因为parent为NULL,index无法查找,所以传来时index=-1)
        index = 0;
    }

    printf("for test: chlidToSplit: keyNum=>%d, childrenNum=>%d\n", childToSplit->keyNum, childToSplit->childrenNum);
    //  创建分裂出来的新节点
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->isLeaf = childToSplit->isLeaf;
    newNode->childrenNum = newNode->keyNum = 0;

    // STPE2: 提升 childToSplit->keys[keyNum/2] 插入到parent的index位置
    for (int i = parent->keyNum; i > index; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }
    parent->keys[index] = childToSplit->keys[getMiddle(childToSplit->keyNum)];
    parent->keyNum++;

    // STEP3: 分keys && 分children
    // 分keys
    for (int or = getMiddle(childToSplit->keyNum) + 1, j = 0; or < childToSplit->keyNum; or++, j++) {
        newNode->keys[j] = childToSplit->keys[or];
        newNode->keyNum++;
    }
    childToSplit->keyNum = getMiddle(childToSplit->keyNum);

    // 分children (根or非根)
    if (childToSplit->isLeaf == 0) {
        for (int or = childToSplit->childrenNum / 2, j = 0; or < childToSplit->childrenNum; or++, j++) {
            newNode->children[j] = childToSplit->children[or];
            newNode->childrenNum++;
        }
        childToSplit->childrenNum = childToSplit->childrenNum / 2;
    }

    // STEP4: 将newNode插入到parent->children[index+1] 位置;
    for (int i = parent->childrenNum; i > index + 1; i--) {
        parent->children[i] = parent->children[i - 1];
    }
    parent->children[index + 1] = newNode;
    parent->childrenNum++;
    if (head->root == childToSplit) {  // 如果head->root==childToSplit 还要将index位置等于childToSplit
        parent->children[index] = childToSplit;
        parent->childrenNum++;
        head->root = parent;  //  哨兵头换头节点的根!!!
    }
    parent->isLeaf = 0;  // 无论三种情况的哪一种,parent都不会再是根节点了

    // parent也爆炸💥了
    // 难点: parent的parent怎么找到??? 只能硬找!!!
    if (parent->keyNum == M) {
        TreeNode *pmove = head->root;
        TreeNode *gparent = NULL;
        int x = parent->keys[0];
        int pos = -1;  // 如果是根(一上来就==x)那pos正好是-1
        while (pmove->keys[0] != x) {
            // 要判断大小去找!!! TODO
            pos = 0;
            while (pos < pmove->keyNum && pmove->keys[pos] < x)
                pos++;
            gparent = pmove;
            pmove = pmove->children[pos];
        }
        splitNode(gparent, pos, head);  // 略微有点抽象
    }
}

// 2.插入元素
// 先插入,后分裂==>不管三七二十一,先插入, 如果keyNum爆了,再去分裂
void insert(BTree *head, int x) {
    TreeNode *pmove = head->root;
    TreeNode *pre = NULL;  // pmove的父亲节点
    // STEP1:找到要插入的节点(一定在🍃处插入)
    while (!pmove->isLeaf) {
        int next = 0;
        while (next < pmove->keyNum && x > pmove->keys[next])  // BTree中无相同键值
            next++;
        pre = pmove;
        pmove = pmove->children[next];
    }
    // STEP2:先插入keys
    int insertPos = pmove->keyNum - 1;
    while (pmove->keys[insertPos] > x) {  // 往右腾位置
        pmove->keys[insertPos + 1] = pmove->keys[insertPos];
        insertPos--;
    }
    insertPos++;
    pmove->keys[insertPos] = x;
    pmove->keyNum++;

    // STEP3:判断是否需要分裂
    if (pmove->keyNum == M) {  // 需要分裂 (pre为满的这个节点的父节点)
        int index = -1;        // 满的节点(需要分裂的节点) 在 父节点->children 的下标; 如果pre为NULL,index应该为-1
        if (pre != NULL) {
            for (int i = 0; i < pre->childrenNum; i++) {  // while可以压行,但这样更直观
                if (pre->children[i] == pmove) {
                    index = i;
                    break;
                }
            }
        }
        // printf("for test:%d\n", index);
        splitNode(pre, index, head);
    }
}
// 3.删除元素
void earse(BTree *head, int x);
// 4.层次遍历BTree
void traverseBTree(BTree *head) {
    TreeNode *q[100];
    int hh = 0, tt = -1;
    q[++tt] = head->root;
    while (hh <= tt) {
        // 打印当前节点的值
        for (int i = 0; i < q[hh]->keyNum; i++) {
            printf("%d", q[hh]->keys[i]);
            if (i + 1 != q[hh]->keyNum)
                printf(",");
        }
        // 入队孩子
        for (int i = 0; i < q[hh]->childrenNum; i++) {
            q[++tt] = q[hh]->children[i];
        }
        hh++;
        printf("  ");
    }
    puts("");
}