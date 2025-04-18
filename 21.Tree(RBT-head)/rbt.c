#include "rbt.h"

// 1.初始化红黑树
TreeNode *init(int *input, int length) {
    TreeNode *head = (TreeNode *)malloc(sizeof(TreeNode));
    head->parent = NULL;
    head->data = -1;  // 哨兵头的值域为-1
    for (int i = 0; i < length; i++) {
        TreeNode *newNod = insert(&(head->parent), *(input + i), head);
        fixRBTree(head->parent, newNod);
    }
    return head;
}

// 左旋
void LRotation(TreeNode *tree) {
    /** 变量定义
     *     1(root)
     *      \
     *       2(rRChild)
     *     /    \
     *    /      \
     *  0(orphan)  3
     *
     */
    TreeNode *root = tree;
    TreeNode *rRChild = root->rchild;
    TreeNode *orphan = rRChild->lchild;
    TreeNode *outerNode = root->parent;  // 一定存在, 因为有哨兵头

    /** 旋转
     *      2(rRChild)
     *    /   \
     *   /     \
     *  1(root) 3
     *    \
     *     \
     *      0 (orphan)
     */
    rRChild->lchild = root;
    root->rchild = orphan;

    /** 父节点修正
     *   X(outerNode)
     *    ③
     *     ③双向修正
     *      2(rRChild)
     *    ②   \
     *   /     \
     *  1(root) 3
     *    ①
     *     \
     *      0 (orphan)
     */
    if (orphan)
        orphan->parent = root;    // ①
    root->parent = rRChild;       // ②
    rRChild->parent = outerNode;  // ③
    if (outerNode->data == -1) {  // 哨兵头
        outerNode->parent = rRChild;
    } else {
        if (outerNode->lchild == root) {
            outerNode->lchild = rRChild;
        } else {
            outerNode->rchild = rRChild;
        }
    }
}
// 右旋
void RRotation(TreeNode *tree) {
    /** 变量定义
     *     1(root)
     *     /
     *    2(rLChild)
     *   /   \
     *  3     0(orphan)
     *
     */
    TreeNode *root = tree;
    TreeNode *rLChild = root->lchild;  // (rootLeftChild)
    TreeNode *orphan = rLChild->rchild;
    TreeNode *outerNode = root->parent;

    /** 旋转
     *    2(rLChild)
     *   /   \
     *  3    1(root)
     *        /
     *     0(orphan)
     */
    rLChild->rchild = root;
    root->lchild = orphan;

    /** 父节点修正
     *   X(outerNode)
     *    ③
     *     ③双向修正
     *     2(rLChild)
     *     / ②
     *    /   \
     *   3    1(root)
     *        ①
     *        /
     *     0(orphan)
     */
    if (orphan)
        orphan->parent = root;    // ①
    root->parent = rLChild;       // ②
    rLChild->parent = outerNode;  // ③
    if (outerNode->data == -1) {
        outerNode->parent = rLChild;
    } else {
        if (outerNode->lchild == root) {
            outerNode->lchild = rLChild;
        } else {
            outerNode->rchild = rLChild;
        }
    }
}

/** 2.插入
 *  TreeNode *head:传入的红黑树头
 *  int x: 插入的值
 *  :return
 *      返回新插入的节点
 */
TreeNode *insert(TreeNode **root, int x, TreeNode *parent) {
    if (*root == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->data = x;
        newNode->color = 1;
        newNode->lchild = newNode->rchild = NULL;
        newNode->parent = parent;

        *root = newNode;
        return newNode;
    } else if (x < (*root)->data) {
        return insert(&(*root)->lchild, x, *root);
    } else {
        return insert(&(*root)->rchild, x, *root);
    }
}

/**  2-1 修复红黑树
 * TreeNode *root:整棵树的根
 * TreeNode *node:新插入的节点
 */
void fixRBTree(TreeNode *root, TreeNode *node) {
    TreeNode *newNode = root;
    while (node->data != newNode->data) {
        newNode = node->data < newNode->data ? newNode->lchild : newNode->rchild;
    }
    while (newNode->parent->data != -1 && newNode->parent->color == 1) {
        // 开始修复
        TreeNode *parent = newNode->parent;
        TreeNode *gparent = parent->parent;
        TreeNode *uncle = gparent->lchild == parent ? gparent->rchild : gparent->lchild;
        int uncleColor = uncle ? uncle->color : 0;

        // 红色叔叔
        if (uncleColor == 1) {
            parent->color = 0;
            gparent->color = 1;
            uncle->color = 0;
            newNode = gparent;
            continue;
        }
        // 黑色叔叔
        else {
            if (parent->data < gparent->data) {
                if (newNode->data < parent->data) {
                    // LL
                    parent->color = 0;
                    gparent->color = 1;
                    RRotation(gparent);
                } else {
                    // LR
                    newNode->color = 0;
                    gparent->color = 1;
                    LRotation(gparent->lchild);
                    RRotation(gparent);
                }
            } else {
                if (newNode->data < parent->data) {
                    // RL
                    newNode->color = 0;
                    gparent->color = 1;
                    RRotation(gparent->rchild);
                    LRotation(gparent);
                } else {
                    // RR
                    parent->color = 0;
                    gparent->color = 1;
                    LRotation(gparent);
                }
            }
            break;  // 必须有
        }
    }

    root->color = 0;  // 保证根叶黑
}

// 3.删除
void earse(TreeNode *root, int x) {
    TreeNode *aimNode = root;
    while (x != aimNode->data) {
        aimNode = x < aimNode->data ? aimNode->lchild : aimNode->rchild;
    }

    // case1: 叶子节点🍃
    if ((aimNode->lchild == NULL && aimNode->rchild == NULL) || aimNode->color == -1) {
        if (aimNode->parent->data == -1) {  // 细品(当前节点时根节点+当前节点是叶子==>整棵树只有一个根)
            aimNode->parent->parent = NULL;
            return;
        }
        // case1-1: 黑色叶子
        if (aimNode->color != 1) {
            /**  左侧情况分析(另一侧对称,不赘述)
             *   有两孩?优先左       没有左?就等于右       没有右,那为NULL
             *      a(gp)             a(gp)              a(gp)
             *     /  \              /   \               /   \
             *   b(p)  c(aimNode)   b(p)  c(aimNode)   b(p)  c(aimNode)
             *   /  \                 \
             * c(n) d                 c(n)               node=NULL
             */
            TreeNode *gparent = aimNode->parent;
            TreeNode *parent = gparent->lchild == aimNode ? gparent->rchild : gparent->lchild;
            TreeNode *node = NULL;
            if (parent == gparent->lchild) {
                if (parent->lchild && parent->lchild->color == 1)  //  优先同侧孩子
                    node = parent->lchild;
                else if (parent->rchild && parent->rchild->color == 1)
                    node = parent->rchild;

            } else {
                if (parent->rchild && parent->rchild->color == 1)  //  优先同侧孩子
                    node = parent->rchild;
                else if (parent->lchild && parent->lchild->color == 1)
                    node = parent->lchild;
            }

            // case1-2-1: aimNode兄弟为红色=>兄弟变为黑色;父亲变为红色;依据兄弟和父亲进行旋转;然后继续删除aimNode所在的树
            if (parent->color == 1) {
                parent->color = 0;
                gparent->color = 1;
                if (gparent->lchild == parent) {
                    // LL
                    RRotation(gparent);
                } else {
                    // RR
                    LRotation(gparent);
                }
                earse(parent, x);
                return;
            }
            // case1-2-2: aimNode的兄弟为黑色
            else {
                // 至少有一个红孩
                if (node != NULL) {
                    if (parent->data < gparent->data) {
                        if (node->data < parent->data) {
                            // LL
                            node->color = parent->color;
                            parent->color = gparent->color;
                            gparent->color = 0;
                            RRotation(gparent);
                        } else {
                            // LR
                            node->color = gparent->color;
                            gparent->color = 0;
                            LRotation(parent);
                            RRotation(gparent);
                        }
                    } else {
                        if (node->data < parent->data) {
                            // RL
                            node->color = gparent->color;
                            gparent->color = 0;
                            RRotation(parent);
                            LRotation(gparent);
                        } else {
                            // RR
                            node->color = parent->color;
                            parent->color = gparent->color;
                            gparent->color = 0;
                            LRotation(gparent);
                        }
                    }
                }
                // 一个红色孩子都没有
                else {
                    parent->color = 1;
                    gparent->color = gparent->parent->data == -1 ? 0 : gparent->color - 1;  // -1表示双黑,如果是根就为黑,红(1)--,也变为黑
                    if (gparent->color == -1)
                        earse(root, gparent->data);  // 双黑上移=继续删除gp的值 + 假删除
                }
            }
        }
        // case1-1: 红色叶子,直接删除,这条路上的黑色不会变化(不违反黑路同)
        if (aimNode->color != -1) {  // 如果是-1,表示为假删
            if (aimNode->parent->lchild == aimNode) // 注意删节点的方式: 和没有哨兵头的区别
                aimNode->parent->lchild = NULL;
            else
                aimNode->parent->rchild = NULL;
        } else {
            aimNode->color = 0;  // 修复为黑色即可
        }

    }
    // case2: 有两个孩子
    else if (aimNode->lchild != NULL && aimNode->rchild != NULL) {
        // 找到"中序遍历"的后继节点 (aimNode右子树的最左边节点)
        TreeNode *successor = aimNode->rchild;
        while (successor->lchild) {
            successor = successor->lchild;
        }
        // 换值(真, 因为只有真换值,才能保证aimNode的右子树是BST,才能使用earse方法继续删除)
        aimNode->data = aimNode->data ^ successor->data;
        successor->data = aimNode->data ^ successor->data;
        aimNode->data = aimNode->data ^ successor->data;

        // 删除右子树上的x
        earse(aimNode->rchild, x);

    }
    // case3: 只有一个孩子
    else {
        TreeNode *outerNode = aimNode->parent;
        TreeNode *son = aimNode->lchild ? aimNode->lchild : aimNode->rchild;
        // 修改颜色
        son->color = 0;  // 一红一黑; 用红替换了黑的,会少一个黑的,所以得替换
        // 修复父节点关系
        if (outerNode->lchild == aimNode) {
            outerNode->lchild = son;
        } else {
            outerNode->rchild = son;
        }
        son->parent = outerNode;  // 修改父子,双向修改
        // 替换 (没必要了, 修正父节点的子节点即可, 相当于完成替换了)
    }
}

// [for test]层次遍历
void levelTraverse(TreeNode *tree) {
    if (tree == NULL) {
        puts("Empty");
        return;
    }
    TreeNode *q[100];
    int hh = 0, tt = -1;
    q[++tt] = tree;
    while (hh <= tt) {
        if (q[hh]->color == 1)
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