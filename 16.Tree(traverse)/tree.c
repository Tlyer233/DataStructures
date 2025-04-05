#include "tree.h"

// 1.创建树(前序序列的顺序)
void createTree(TreeNode **tree) {
    char input;
    while (scanf("%c", &input) == 1 && input != '\n') {
        if (input == '#') {
            *tree = NULL;  // 当前节点是空的
            return;
        } else {
            // 创建节点
            TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
            newNode->data = input;
            newNode->lchild = NULL;
            newNode->rchild = NULL;
            *tree = newNode;
            createTree(&(*tree)->lchild);
            createTree(&(*tree)->rchild);
            return;  // 在循环里面,所以要显式return
        }
    }
}
// 2.前序遍历
void preOrder(TreeNode *tree) {
    if (tree != NULL) {
        printf("%c ", tree->data);
        preOrder(tree->lchild);
        preOrder(tree->rchild);
    }
}
// 3.中序遍历
void inOrder(TreeNode *tree) {
    if (tree != NULL) {
        inOrder(tree->lchild);
        printf("%c ", tree->data);
        inOrder(tree->rchild);
    }
}
// 4.后序遍历
void postOrder(TreeNode *tree) {
    if (tree != NULL) {
        postOrder(tree->lchild);
        postOrder(tree->rchild);
        printf("%c ", tree->data);
    }
}
TreeNode *stack[SIZE];
int top = -1;
// 5.[栈]前序遍历
void preOrderWithStack(TreeNode *tree) {
    top = -1;
    TreeNode *pmove = tree;
    while (top != -1 || pmove != NULL) {
        if (pmove == NULL) {
            pmove = stack[top--]->rchild;  // 没左了,取栈顶的右边孩子(开始向右走)
        }
        // 还有左
        else {
            printf("%c ", pmove->data);
            stack[++top] = pmove;   //  入栈当前节点
            pmove = pmove->lchild;  // 继续往左
        }
    }
}
// 6.[栈]中序遍历
void inOrderWithStack(TreeNode *tree) {
    top = -1;
    TreeNode *pmove = tree;
    while (top != -1 || pmove != NULL) {
        if (pmove == NULL) {
            printf("%c ", stack[top]->data);  // 没有左了,pmove已经到NULL了,说明栈顶(上一个入的)就是最左的,打印他
            pmove = stack[top--]->rchild;     // 没有左,就只能向右了;
        }
        // 还有左
        else {
            stack[++top] = pmove;
            pmove = pmove->lchild;
        }
    }
}
// 7.[栈]后续遍历
void postOrderWithStack(TreeNode *tree) {
    top = -1;
    TreeNode *pmove = tree;
    char printStack[100];
    int pTop = -1;
    while (top != -1 || pmove != NULL) {
        if (pmove == NULL) {
            pmove = stack[top--]->lchild;
        } else {
            printStack[++pTop] = pmove->data;  // 打印位置同"前序"
            stack[++top] = pmove;
            pmove = pmove->rchild;  // 一直找右
        }
    }
    // 翻转打印
    while (pTop != -1) {
        printf("%c ", printStack[pTop--]);
    }
}

TreeNode *queue[SIZE];
int hh = 0, tt = -1;  // 这里我们采用普通队列
// 回顾下:hh = 0, tt = 0; 循环队列=>空?hh==tt; 满?(tt+1)%SIZE==hh; 出入队:(tt/hh+1)%SIZE
// 8.层次遍历
void levelOrder(TreeNode *tree) {
    hh = 0, tt = -1;  // 初始化队列
    queue[++tt] = tree;
    while (hh <= tt) {
        TreeNode *temp = queue[hh++];  // 出队
        printf("%c ", temp->data);
        if (temp->lchild != NULL) {
            queue[++tt] = temp->lchild;
        }
        if (temp->rchild != NULL) {
            queue[++tt] = temp->rchild;
        }
    }
}