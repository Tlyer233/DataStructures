#include "redBlackTree.h"

// 右旋(需要维护parent字段)
void RRotation(TreeNode **tree) {
    /**
     *       23 root/*tree
     *      /  \
     *     /    \
     *   10(rL)  34
     *  /
     * 9
     * orphan=NULL
     */
    TreeNode *root = *tree;
    TreeNode *rootLChild = root->lchild;
    TreeNode *orphan = rootLChild->rchild;

    /**
     *   10(rL)          23(root)
     *   /  \            /
     *  9   23(root)   NULL
     *        \
     *         34
     */
    rootLChild->rchild = root;
    root->lchild = orphan;

    // 调整rootLChild下方parent引用
    rootLChild->parent = root->parent;
    root->parent = rootLChild;
    if (orphan)
        orphan->parent = root;

    // 调整rootLChild上方parent引用
    if (rootLChild->parent) {
        // 如果原根不是整棵树的根，需要更新父节点的子节点指针
        if (rootLChild->parent->lchild == root)
            rootLChild->parent->lchild = rootLChild;
        else
            rootLChild->parent->rchild = rootLChild;
    } else {
        // 如果原根是整棵树的根，更新树根指针
        *tree = rootLChild;
    }
}

// 左旋(需要维护parent字段)
void LRotation(TreeNode **tree) {
    TreeNode *root = *tree;
    TreeNode *rootRChild = root->rchild;
    TreeNode *orphan = rootRChild->lchild;

    // 调整子节点关系
    rootRChild->lchild = root;
    root->rchild = orphan;

    // 调整父节点关系
    rootRChild->parent = root->parent;  // 新根节点指向原根父节点
    root->parent = rootRChild;          // 原根节点指向新根节点
    if (orphan)
        orphan->parent = root;  // 孤儿节点指向原根节点

    // 天天天坑!!!!!!!!!
    // 调整原根父节点的子节点指针
    if (rootRChild->parent) {
        // 如果原根不是整棵树的根，需要更新父节点的子节点指针
        if (rootRChild->parent->lchild == root)
            rootRChild->parent->lchild = rootRChild;
        else
            rootRChild->parent->rchild = rootRChild;
    } else {
        // 如果原根是整棵树的根，更新树根指针
        *tree = rootRChild;
    }
}

// BST的插入(返回插入的新节点)
TreeNode *recursionInsert(TreeNode **tree, int x, TreeNode *parent) {
    if ((*tree) == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->data = x;
        newNode->color = 1;  // 初始为"红色"
        newNode->lchild = newNode->rchild = NULL;
        newNode->parent = parent;
        *tree = newNode;
        return newNode;
    } else if (x < (*tree)->data) {
        return recursionInsert(&(*tree)->lchild, x, *tree);
    } else {
        return recursionInsert(&(*tree)->rchild, x, *tree);
    }
}
/** 修复红黑树
 * tree: 整棵树的根
 * node: 新插入的节点
 * 修复逻辑
 * case1: 插入节点是根节点==>变黑  [违反 根叶黑]
 * case2: 插入节点的叔叔是红色 ①gparent变为红色(1)，parent和uncle变为黑色(0) ②让gparent节点变为插入的节点,继续向上检查
 * case3: 插入节点的叔叔是黑色 ①新根为黑色; 原根为红色 ②以node在gparetn和parent的位置;判断旋转类型
 */
void fixRBTree(TreeNode **tree, TreeNode *node) {
    // ①确保不为"整棵树"的根
    // ③因为node是插入的新节点, 那一定是红色;那只有parent也是红色,才违反了"不红红",才需要调整
    while (node->parent && node->parent->color == 1) {
        TreeNode *parent = node->parent;     // root->child
        TreeNode *gparent = parent->parent;  // root // 一定有gparent,想想为什么?因为根节点不可能为红色
        TreeNode *uncle = gparent->lchild == parent ? gparent->rchild : gparent->lchild;
        int uncleColor = uncle ? uncle->color : 0;
        // case2: 插入节点的叔叔是红色
        if (uncleColor == 1) {
            gparent->color = 1;
            parent->color = uncle->color = 0;
            node = gparent;
            continue;
        }
        // case3: 插入节点的叔叔是黑色
        TreeNode **rotate_pos;
        // 如果祖父是根节点，直接使用树根指针
        if (gparent == *tree) {
            rotate_pos = tree;
        }
        // 否则找到祖父在其父节点中的准确引用位置
        else {
            TreeNode *great_gparent = gparent->parent;
            rotate_pos = (great_gparent->lchild == gparent) ? &(great_gparent->lchild) : &(great_gparent->rchild);
        }

        // 分情况处理，变色和旋转
        if (node->data < gparent->data) {
            if (node->data < parent->data) {
                // LL
                parent->color = 0;  // 先变色
                gparent->color = 1;
                RRotation(rotate_pos);
            } else {
                // LR
                node->color = 0;
                gparent->color = 1;
                LRotation(parent == gparent->lchild ? &(gparent->lchild) : &(gparent->rchild));
                RRotation(rotate_pos);
            }
        } else {
            if (node->data < parent->data) {
                // RL
                node->color = 0;
                gparent->color = 1;
                RRotation(parent == gparent->lchild ? &(gparent->lchild) : &(gparent->rchild));
                LRotation(rotate_pos);
            } else {
                // RR
                parent->color = 0;
                gparent->color = 1;
                LRotation(rotate_pos);
            }
        }
        break;  // 旋转完成后,可以直接退出, 因为我们选择了无需向上递归的着色方法
    }
    // case1: 插入节点是根节点
    (*tree)->color = 0;
}
// 2.创建Red-Black Tree
TreeNode *createRedBlackTree(int *input, int arrSize) {
    TreeNode *root = NULL;
    for (int i = 0; i < arrSize; i++) {
        TreeNode *newNode = recursionInsert(&root, input[i], NULL);
        fixRBTree(&root, newNode);
        // levelTraverse(root);
    }
    return root;
}

// [for test] 层次遍历
void levelTraverse(TreeNode *tree) {
    if (!tree) {
        puts("Empty");
        return;
    }
    TreeNode *q[100];
    int hh = 0, tt = -1;
    q[++tt] = tree;
    while (hh <= tt) {
        if (q[hh]->color)
            printf("\033[31m%d\033[0m ", q[hh]->data);
        else
            printf("%d ", q[hh]->data);
        if (q[hh]->lchild)
            q[++tt] = q[hh]->lchild;
        if (q[hh]->rchild)
            q[++tt] = q[hh]->rchild;
        hh++;
    }
    puts("");
}

/**
 * TreeNode** tree: 整棵树的根
 *           int x: 需要删除的值
 */
void deleteNode(TreeNode **tree, int x) {
    TreeNode *aimNode = *tree;  // 需要删除的目标节点
    // 寻找目标节点
    while (aimNode && aimNode->data != x) {
        if (x < aimNode->data) {
            aimNode = aimNode->lchild;
        } else {
            aimNode = aimNode->rchild;
        }
    }

    // case1:叶子🍃节点
    if (aimNode->color == -1 || (aimNode->lchild == NULL && aimNode->rchild == NULL)) {
        if (aimNode->parent == NULL) {  // 你细品, 找到的是叶子&& 找到的aimNode的parent为NULL; 那整棵树不就只有aimNode一个节点了吗?
            free(*tree);
            *tree = NULL;
            return;
        }
        TreeNode **gparent = aimNode->parent->parent ? &(aimNode->parent) : tree;
        TreeNode **d = (*gparent)->lchild == aimNode ? &((*gparent)->lchild) : &((*gparent)->rchild);       // 准备删除的节点
        TreeNode **parent = (*gparent)->lchild == aimNode ? &((*gparent)->rchild) : &((*gparent)->lchild);  // 三大金刚
        TreeNode **node;
        // 叶子节点, 不是红色(才需要大费周章)
        if (aimNode->color != 1) {
            if ((*gparent)->lchild == (*d)) {
                node = (*parent)->rchild ? &((*parent)->rchild) : &((*parent)->lchild);
            } else {
                node = (*parent)->lchild ? &((*parent)->lchild) : &((*parent)->rchild);
            }
            // case1-1:兄弟(*parent)为红色
            if ((*parent)->color == 1) {
                (*parent)->color = 0;   // 兄弟变为黑色
                (*gparent)->color = 1;  // 父亲变为红色
                if ((*parent)->data < (*gparent)->data) {
                    // LL
                    RRotation(gparent);
                } else {
                    // RR
                    LRotation(gparent);
                }
                // aimNode->color--;  // 因为aimNode此时必须为黑色,所以这里一定是双黑;
                deleteNode(gparent, aimNode->data);
                return;  // 否则会删除一个NULL; But从语法角度不会报错!
            }
            // case1-2:兄弟(*parent)为黑色
            else {
                // 兄弟全是黑子
                if ((*node) == NULL) {
                    (*parent)->color = 1;                                           // 兄弟变红
                    (*gparent)->color = gparent == tree ? 0 : (*gparent)->color--;  // 双黑上移(-1表示双黑)
                    if ((*gparent)->color == -1)                                    // 坑!!! 必须判断,因为如果是黑色还继续向上删,那就真的删掉了,下面删除只判断了双黑不被删除
                        deleteNode(tree, (*gparent)->data);                         // 继续删除

                }
                // 兄弟至少有一个"红节点"
                else {
                    if ((*parent)->data < (*gparent)->data) {
                        if ((*node)->data < (*parent)->data) {
                            // LL
                            (*node)->color = (*parent)->color;
                            (*parent)->color = (*gparent)->color;
                            (*gparent)->color = 0;
                            RRotation(gparent);
                        } else {
                            // LR
                            (*node)->color = (*gparent)->color;
                            (*gparent)->color = 0;
                            LRotation(parent);
                            RRotation(gparent);
                        }
                    } else {
                        if ((*node)->data < (*parent)->data) {
                            // RL
                            (*node)->color = (*gparent)->color;
                            (*gparent)->color = 0;
                            RRotation(parent);
                            LRotation(gparent);
                        } else {
                            // RR
                            (*node)->color = (*parent)->color;
                            (*parent)->color = (*gparent)->color;
                            (*gparent)->color = 0;
                            LRotation(gparent);
                        }
                    }
                }
            }
        }

        // 删除目标节点 (如果双黑,并不是删除,而是恢复为单黑)
        if (aimNode->color != -1) {
            free(*d);
            *d = NULL;
        } else {
            aimNode->color = 0;
        }
    }
    // case2:两个孩子都有
    else if (aimNode->lchild != NULL && aimNode->rchild != NULL) {
        // get nextPoster
        TreeNode *pmove = aimNode->rchild;
        while (pmove->lchild) {
            pmove = pmove->lchild;
        }
        aimNode->data = pmove->data ^ aimNode->data;
        pmove->data = pmove->data ^ aimNode->data;
        aimNode->data = pmove->data ^ aimNode->data;
        deleteNode(&aimNode->rchild, x);  // 这个地方必须交换值, 因为要保证右子树是BST
    }
    // case3: 只有一个孩子(必然是节点不可能是子树+一黑一红)
    /**
     *       27? parent         27? parent
     *      /                 /
     *    18b aimNode        25b son        STEP2:如果不变黑,这条路上就少一个(删除掉的18的)黑节点
     *      \
     *       25r son
     */
    else {
        TreeNode *parent = aimNode->parent;
        TreeNode **aimNodeRef;
        if (parent == NULL)  // 说明aimNode就是根
            aimNodeRef = tree;
        else
            aimNodeRef = parent->lchild == aimNode ? &parent->lchild : &parent->rchild;
        TreeNode *son = aimNode->lchild ? aimNode->lchild : aimNode->rchild;
        // STEP0.5: 隐藏的事情(parent节点需要维护)
        son->parent = aimNode->parent;
        // STEP1:替换
        *aimNodeRef = son;
        // STEP2:变黑
        (*aimNodeRef)->color = 0;
    }
}