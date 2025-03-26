/** 约瑟夫环问题 (无头双向循环链表)
 * 输入样例: 10, 4
 *   第一个参数表示有10个人参加, 每个人的编号为1~10;
 *   第二个参数表示有数到4的人就退出;
 * 返回: 5
 *   返回最后一个人的编号
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;
    struct Node *prev;
    struct Node *next;
} Node;

/** 初始化链表
 * nums:有几个人参与
 * 每个人的编号为1~nums
 */
Node *initJonsephRing(int nums) {
    assert(nums && "No one is playing!");
    Node *phead = (Node *)malloc(sizeof(Node));
    phead->num = nums--;
    phead->next = phead;
    phead->prev = phead;
    while (nums > 0) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->num = nums--;
        // 头插法`
        newNode->next = phead;
        phead->prev->next = newNode;
        newNode->prev = phead->prev;
        phead->prev = newNode;

        phead = newNode;
    }
    return phead;
}
// 遍历
void traverseJonsephRing(Node *jring) {
    Node *pmove = jring;
    int flag = 1;  // 控制第一个输出
    while (pmove != jring || flag) {
        printf("%d->", pmove->num);
        pmove = pmove->next;
        flag = 0;
    }
    puts("NULL");
}

/**删除节点
 * count: 删除数到count的人
 * 人不够就来回数
 */
int delete(Node *jring, int count) {
    while (jring != jring->next) {
        for (int i = 0; i < count - 1; i++) jring = jring->next;
        Node *temp = jring;  // 准备释放
        jring->prev->next = jring->next;
        jring->next->prev = jring->prev;
        jring = jring->next;
        traverseJonsephRing(temp->next);  // 打印每次结果
        free(temp);
    }
    return jring->num;
}

int josephRingProblem(int nums, int count) {
    Node *jring = initJonsephRing(nums);
    traverseJonsephRing(jring);
    return delete (jring, count);
}
int main() {
    int ans = josephRingProblem(10, 4);
    printf("%d", ans);
    return 0;
}