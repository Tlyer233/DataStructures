#include "balanceBinaryTree.h"

// 获取一颗树的高度
int getHeight(TreeNode *tree) {
    return tree == NULL ? 0 : tree->height;
}
void updataNodeHeight(TreeNode *tree) {
    tree->height = MAX(getHeight(tree->lchild), getHeight(tree->rchild)) + 1;
}

// 左旋
void LRotation(TreeNode **tree) {
    TreeNode *root = *tree;
    TreeNode *rootRChild = (*tree)->rchild;
    TreeNode *orphan = rootRChild->lchild;

    rootRChild->lchild = root;
    root->rchild = orphan;
    *tree = rootRChild;
    // 更新高度
    updataNodeHeight(*tree);
    updataNodeHeight(rootRChild->lchild);
}

// 右旋
void RRotation(TreeNode **tree) {
    TreeNode *root = *tree;
    TreeNode *rootLChild = (*tree)->lchild;
    TreeNode *orphan = rootLChild->rchild;

    rootLChild->rchild = root;
    root->lchild = orphan;
    *tree = rootLChild;

    // 更新高度
    updataNodeHeight(*tree);
    updataNodeHeight(rootLChild->rchild);
}

// 1.插入节点
void insert(TreeNode **tree, int x) {
    if ((*tree) == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->data = x;
        newNode->height = 1;
        newNode->lchild = newNode->rchild = NULL;
        *tree = newNode;
    } else if (x < (*tree)->data) {  // node在root的哪一侧?->L
        insert(&(*tree)->lchild, x);
        if (abs(getHeight((*tree)->lchild) - getHeight((*tree)->rchild)) == 2) {
            printf("test: %d", (*tree)->data);
            if (x < (*tree)->lchild->data) {  // node在root的孩子的哪一侧? ->L
                // LL
                puts("LL");
                RRotation(tree);
            } else {
                // LR
                puts("LR");
                LRotation(&(*tree)->lchild);
                RRotation(tree);
            }
        }
    } else {  // node在root的哪一侧?->R
        insert(&(*tree)->rchild, x);
        if (abs(getHeight((*tree)->lchild) - getHeight((*tree)->rchild)) == 2) {
            printf("test: %d", (*tree)->data);
            if (x < (*tree)->rchild->data) {  // node在root的孩子的哪一侧? ->L
                // RL
                puts("RL");
                RRotation(&(*tree)->rchild);
                LRotation(tree);
            } else {
                // RR
                puts("RR");
                LRotation(tree);
            }
        }
    }
    updataNodeHeight(*tree);  // 要是都平衡,就不会再R|L Rotation中更新了;所以需要在外面更新
}

// 2.创建BST
TreeNode *createBSTTree() {
    TreeNode *res = NULL;
    int input;
    while (scanf("%d", &input) == 1 && input != -1) {
        insert(&res, input);
    }
    return res;
}

// 3.删除指定元素
// 3-1.依据"左右平衡"因子, 来更新树的平衡
void balanceCurTree(TreeNode **tree) {
    if (getHeight((*tree)->rchild) - getHeight((*tree)->lchild) == 2) {
        printf("%d ", (*tree)->data);
        // 右子树比左子树高2，需要左旋相关操作
        if (getHeight((*tree)->rchild->rchild) >= getHeight((*tree)->rchild->lchild)) {
            // RR型：右子树的右子树更高或相等
            LRotation(tree);
            puts("RR");
        } else {
            // RL型：右子树的左子树更高
            RRotation(&(*tree)->rchild);
            LRotation(tree);
            puts("RL");
        }
    } else if (getHeight((*tree)->lchild) - getHeight((*tree)->rchild) == 2) {
        // 左子树比右子树高2，需要右旋相关操作
        printf("%d ", (*tree)->data);
        if (getHeight((*tree)->lchild->lchild) >= getHeight((*tree)->lchild->rchild)) {
            // LL型：左子树的左子树更高或相等
            RRotation(tree);
            puts("LL");
        } else {
            // LR型：左子树的右子树更高
            LRotation(&(*tree)->lchild);
            RRotation(tree);
            puts("LR");
        }
    }
}
void deleteNode(TreeNode **tree, int x) {
    if (x < (*tree)->data) {
        deleteNode(&(*tree)->lchild, x);
        // updataNodeHeight(*tree);  // 因为改变了"直接子节点",所以必须更新
        // balanceCurTree(tree);
    } else if (x > (*tree)->data) {
        deleteNode(&(*tree)->rchild, x);
        // updataNodeHeight(*tree);
        // balanceCurTree(tree);
    } else {  // 找到了
        // case1:叶子节点(直接删)
        if ((*tree)->lchild == NULL && (*tree)->rchild == NULL) {
            free(*tree);
            *tree = NULL;
        }
        // case3:左右孩子都有 (找右子树最小的, 换值+从右子树递归删)
        else if ((*tree)->lchild != NULL && (*tree)->rchild != NULL) {
            // 一.找右子树最小的
            TreeNode *successor = (*tree)->rchild;
            while (successor->lchild != NULL)
                successor = successor->lchild;
            // 二.换值
            int temp = (*tree)->data;
            (*tree)->data = successor->data;
            successor->data = temp;
            // 三.右子树递归删
            deleteNode(&(*tree)->rchild, temp);
        }
        // case2:只有其中一个孩子
        else {
            if ((*tree)->lchild != NULL) {
                *tree = (*tree)->lchild;
            } else {
                *tree = (*tree)->rchild;
            }
        }
    }
    if (*tree != NULL) {          // 更新
        updataNodeHeight(*tree);  // 第一次更新高度(因为有可能找到并删除了节点) [这次的updata其实可以不要]
        balanceCurTree(tree);     // 检查并修复平衡
        updataNodeHeight(*tree);  // 再次更新高度(即使没有发生旋转，也能保证高度信息是最新的)
    }
}

// [for test] 层次遍历
void levelTraverse(TreeNode *tree) {
    TreeNode *q[100];
    int hh = 0, tt = -1;
    q[++tt] = tree;
    while (hh <= tt) {
        printf("%d[%d] ", q[hh]->data, q[hh]->height);

        if (q[hh]->lchild != NULL)
            q[++tt] = q[hh]->lchild;
        if (q[hh]->rchild != NULL)
            q[++tt] = q[hh]->rchild;
        hh++;
    }
    puts("");
}