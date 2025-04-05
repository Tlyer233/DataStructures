#include "binarySearchTree.h"

// 1.插入节点
void insertVal(TreeNode **tree, int x) {
    if (*tree == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->val = x;
        newNode->lchild = newNode->rchild = NULL;
        *tree = newNode;
    } else if (x == (*tree)->val) {
        assert(0 && "standard BST is not allow same val node!");
    }
    // 小=>往左走
    else if (x < (*tree)->val) {
        insertVal(&(*tree)->lchild, x);
    }
    // 大=>往右走
    else {
        insertVal(&(*tree)->rchild, x);
    }
}
// 2.创建BST
TreeNode *createBinarySearchTree() {
    int input;
    TreeNode *retNod = NULL;
    while (scanf("%d", &input) == 1 && input != -1) {
        insertVal(&retNod, input);
    }
    return retNod;
}
// 3.查找指定元素(注意:标准的BST中没有两个节点的val值相同)
// 坑:你返回的一级指针是无论如何都不可能变为二级的, 尽管你TreeNode *temp = search(tree, 3);
//    &temp这个不是树中的那个节点的二级地址, 只是temp这个变量的地址;
// 坑: 放到search方法里面去理解 如果想这样①TreeNode** search(TreeNode* tree, int x) ②找到时返回&pmove, 也不可以
//     因为, pmove遍历到目标节点时, &pmove和&目标节点并不是一样的地址; 当search方法结束,pmove会归还给C, 你&pomve就等同于&NULL
//     没有任何意义,返回仅仅是NULL
TreeNode *search(TreeNode *tree, int x) {
    TreeNode *pmove = tree;
    while (pmove) {
        if (x == pmove->val)
            return pmove;
        else if (x < pmove->val) {
            pmove = pmove->lchild;
        } else if (x > pmove->val) {
            pmove = pmove->rchild;
        }
    }
    return NULL;
}
// 4.删除指定元素(传二级,有可能把自己删了)
/**
 * case1:如果tree是叶子, 直接删除;不会影响BST
 * case2:如果tree只有左/右孩子, 让tree->lchild/rchild为根; 删tree即可
 * case3:如果tree左右孩子都有,swap(tree,找中序遍历的(tree.val的)下一个节点);然后删除tree
 */
void deleteNode(TreeNode **tree, int x) {
    if ((*tree) == NULL)  // 空树
        return;
    if (x < (*tree)->val) {
        deleteNode(&(*tree)->lchild, x);
    } else if (x > (*tree)->val) {
        deleteNode(&(*tree)->rchild, x);
    } else {  // 找到了
        // case1:如果tree是叶子, 直接删除;不会影响BST
        if ((*tree)->lchild == NULL && (*tree)->rchild == NULL) {
            free(*tree);
            *tree = NULL;
        }
        // case3:如果tree左右孩子都有,swap(tree,tree所在树比tree大的首个节点);然后删除tree
        else if ((*tree)->lchild != NULL && (*tree)->rchild != NULL) {
            // 如何找中序遍历的(tree.val的)下一个节点;
            // 找右边这颗树的最小值(就是首个比tree大的): 因为中序遍历,如果遍历到tree那左边都是比我小的,那右边的第一个值就是比我大的
            // 而对于右边这颗树来说,第一个就是"右边这棵树"最左边的节点
            TreeNode *successor = (*tree)->rchild;
            while (successor->lchild != NULL) {
                successor = successor->lchild;
            }
            // 交换值  // 非常妙!!! BST能拿到6分很大的原因在于这里(45%);另外是C语言指针的理解(55%)
            int temp = (*tree)->val;
            (*tree)->val = successor->val;
            successor->val = temp;
            // 再递归的去删 
            deleteNode(&(*tree)->rchild, temp);
        }
        // case2:如果tree只有左/右孩子, 让tree->lchild/rchild为根; 删tree即可
        else {
            if ((*tree)->lchild) {
                *tree = (*tree)->lchild;
            } else {
                *tree = (*tree)->rchild;
            }
        }
    }
}

// [for test] 中序遍历(递增序列)(左中右)
TreeNode *stack[100];
int top = -1;
void inOrderTraverse(TreeNode *tree) {
    top = -1;
    while (top != -1 || tree != NULL) {
        if (tree == NULL) {
            printf("%d ", stack[top]->val);
            tree = stack[top--]->rchild;  // 再一次温馨提示:一级指针不会修改外部变量
        } else {
            stack[++top] = tree;
            tree = tree->lchild;
        }
    }
}

// [for test] 层次遍历
TreeNode *q[100];
int hh = 0, tt = -1;
void levelTraverse(TreeNode *tree) {
    q[++tt] = tree;
    while (hh <= tt) {
        TreeNode *temp = q[hh++];
        printf("%d ", temp->val);
        if (temp->lchild != NULL)
            q[++tt] = temp->lchild;
        if (temp->rchild != NULL)
            q[++tt] = temp->rchild;
    }
}