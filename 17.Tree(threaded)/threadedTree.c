#include "threadedTree.h"

// 1.前序遍历创建树
void initTree(TreeNode **tree) {
    DataType input;
    while (scanf("%c", &input) == 1 && input != '\n') {
        if (input == '#') {
            *tree = NULL;
            return;
        } else {
            TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
            newNode->data = input;
            newNode->lchild = newNode->rchild = NULL;
            initTree(&(newNode->lchild));
            initTree(&(newNode->rchild));
            newNode->ltag = newNode->lchild == NULL;  // 坑:一定要有, 否则最后一个的rtag是0,会死循环(遍历时)要不就多封装一个方法
            newNode->rtag = newNode->rchild == NULL;
            *tree = newNode;
            return;
        }
    }
}
// 2.中序线索二叉树
// 思路:中序遍历的过程中,维护"线索二叉树"的前驱和后继即可
// pre是 中序遍历序列的前一个节点, 不是上一个tree的值
void inThreadTree(TreeNode *tree, TreeNode **pre) {  // 坑:注意! *tree为NULL时**tree不为NULL
    if (tree != NULL) {
        inThreadTree(tree->lchild, pre);
        if (tree->lchild == NULL) {  // 需要线索化
            tree->ltag = 1;
            tree->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rtag = 1;
            (*pre)->rchild = tree;
        }
        *pre = tree;
        inThreadTree(tree->rchild, pre);
    }
}
// 3.遍历中序线索二叉树
// 辨析:为什么需要这么"麻烦"(那我直接, 找到lchild的节点, 然后一直 打印node->data; 直到node.next=NULL不就行了,)
// 原因在于中序线索二叉树的线索化规则：
// 当节点的rtag==1时，其rchild确实直接指向下一个节点（中序后继）
// 但当节点的rtag==0时，表示有右子树，那么下一个节点应该是右子树中的最左节点

// 3-1获取当前这颗树的"中序遍历"的第一个节点
TreeNode *getFirst(TreeNode *tree) {
    // 对于任意一颗树来说,其"中序遍历"的第一个节点getFirst一定是该颗树,最左边的节点;
    while (tree->ltag == 0) {  // 是线索
        tree = tree->lchild;   // 没有传二级指针,tree这里改值,不会影响外面
    }
    return tree;
}
// 3-2获取下一个节点
TreeNode *getNext(TreeNode *tree) {
    // case1:rtag=1,说明是线索过的,就是"中序序列"的下一个,直接返回
    // case2:rtag=0,中序遍历(左根右);接下来就是右边这棵树; 说明是右边是一颗树,获取这颗树的"中序遍历"的第一个节点
    return tree->rtag ? tree->rchild : getFirst(tree->rchild);
}
void traverseinThreadTree(TreeNode *tree) {
    for (TreeNode *i = getFirst(tree); i != NULL; i = getNext(i)) {
        printf("%c ", i->data);
    }
}

/////////////////////////////////////////////////
// 4.前序线索二叉树
void preThreadTree(TreeNode *tree, TreeNode **pre) {
    if (tree != NULL) {
        if (tree->lchild == NULL) {  // 需要线索化
            tree->ltag = 1;
            tree->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rtag = 1;
            (*pre)->rchild = tree;
        }
        *pre = tree;
        if (tree->ltag == 0)  // 坑:没有线索化,才需要递归左子树,否则死循环
            preThreadTree(tree->lchild, pre);
        preThreadTree(tree->rchild, pre);
    }
}
// 5.遍历前序线索二叉树
// 5-1获取当前这颗树的"前序遍历"的第一个节点
TreeNode *getFirstPre(TreeNode *tree) {
    // 任何一颗树的"前序遍历"一定是根;
    return tree;
}
// 5-2获取下一个节点
TreeNode *getNextPre(TreeNode *tree) {
    // case1:rtag线索化了,那rchild就是"前序遍历"的下一个
    if (tree->rtag) {
        return tree->rchild;
    }
    // case2:没有线索化,前序遍历(根左右),那下一个就是左边的这颗树;这里的getFirstPre没有必要(只是为了统一)
    else {
        if (tree->ltag == 1)                   // 如果线索化过,说明原来没有左孩子
            return getFirstPre(tree->rchild);  // 那就接着遍历右孩子即可
        else
            return getFirstPre(tree->lchild);  // 有左孩子
    }
}
void traversePreThreadTree(TreeNode *tree) {
    for (TreeNode *i = getFirstPre(tree); i != NULL; i = getNextPre(i)) {
        printf("%c ", i->data);
    }
}
/////////////////////////////////////////////////

// 6.前序遍历构建'三叉链表'二叉树
void initTripleTree(TripleTreeNode **tree, TripleTreeNode *parent) {
    char input;
    while (scanf("%c", &input) == 1 && input != '\n') {
        if (input == '#') {
            *tree = NULL;
            return;
        } else {
            TripleTreeNode *newNode = (TripleTreeNode *)malloc(sizeof(TripleTreeNode));
            newNode->data = input;
            newNode->lchild = newNode->rchild = NULL;
            newNode->parent = parent;  // 记录父亲
            initTripleTree(&(newNode->lchild), newNode);
            initTripleTree(&(newNode->rchild), newNode);
            newNode->ltag = newNode->lchild == NULL;
            newNode->rtag = newNode->rchild == NULL;
            *tree = newNode;
            return;
        }
    }
}

// 7.后续线索二叉树
void postThreadTree(TripleTreeNode *tree, TripleTreeNode **pre) {
    if (tree != NULL) {
        postThreadTree(tree->lchild, pre);
        postThreadTree(tree->rchild, pre);
        if (tree->lchild == NULL) {  // 需要线索化
            tree->ltag = 1;
            tree->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL) {
            (*pre)->rtag = 1;
            (*pre)->rchild = tree;
        }
        *pre = tree;
    }
}
/** 8.遍历后序线索二叉树(左右根)
 * getFirstPost:
 *      找最左边的节点(记为ZL),因为"左右根",所以最左边的不一定是第一个;还要看右边
 *      一.ZL没有(原生)右,那ZL就是"后序遍历"的第一个节点
 *      二.ZL有  (原生)右,那getFirstPost(ZL->rchild)就是第一个节点
 * getNextPost:
 *      case0:线索过了tree->rtag==1;直接返回tree->rchild即可
 *      否则
 *      case1:当前在整棵树的root(parent=NULL):直接返回自己; 因为后序遍历的最后一个节点,一定是根节点,那既然遍历到了根,直接返回即可
 *      case2:在左节点:依据后序遍历顺序,getNext下一个就是 "右根";
 *            * 有(原生)兄弟右节点(tree->parent->rtag==0): return getFirstPost(tree->parent->rchild);
 *            * 没有的话,那就到"根",也就是parent了: return parent;
 *      case3:在右节点:依据后序遍历顺序,getNext下一个就是 "根";
 *            * 都到根了,那直接返回parent即可: return parent;
 */
TripleTreeNode *getFirstPost(TripleTreeNode *tree) {
    // STEP1:找到最左边
    while (tree->ltag == 0) {
        tree = tree->lchild;
    }
    // STEP2:判断是否有(原生)"右孩子"
    return tree->rtag ? tree : getFirstPost(tree->rchild);
}
TripleTreeNode *getNextPost(TripleTreeNode *tree) {
    if (tree->rtag == 1)  // 线索过了
        return tree->rchild;

    // case1:是整棵树的根节点
    if (tree->parent == NULL)
        return tree;
    // case2:在左节点
    // 看下我是否是"原生的左节点"; 因为在测试树(前) ABD##E##C#F##; C的左孩子是线索的,正好线索的是其右孩子F,所以要判断原生
    else if (tree->parent->ltag == 0 && tree->parent->lchild == tree) {
        if (tree->parent->rtag == 0)  // case2.1:有原生"右孩子"
            return getFirstPost(tree->parent->rchild);

        return tree->parent;  // case2.2:没有就直接返回父亲
    }
    // case3:在右节点
    else {
        return tree->parent;
    }
}
void traversePostThreadTree(TripleTreeNode *tree) {
    for (TripleTreeNode *i = getFirstPost(tree); i; i = getNextPost(i)) {
        printf("%c ", i->data);
        if (i->parent == NULL)
            break;
    }
}