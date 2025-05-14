#include "zipHash.h"

// 单链表相关实现
// 初始化单链表
Node *initLinkList(void) {
    Node *head = (Node *)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}
// 插入(头插)
void insertLinkLIst(Node *link, int x) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = link->next;  // 头插法
    link->next = newNode;
}
// 删除
int deleteLinkList(Node *link, int x) {
    Node *pmove = link->next;
    Node *pre = link;
    while (pmove) {
        if (pmove->data == x) {
            pre->next = pmove->next;
            free(pmove);  // 释放
            pmove = NULL;
            return 1;
        }
        pre = pmove;
        pmove = pmove->next;
    }
    return -1;  // 该值不在该单链表中
}
// 查找(如果在该单链表上找到x, 返回1, 找不到返回0)
int searchLinkList(Node *link, int x) {
    link = link->next;
    while (link) {
        if (link->data == x)
            return 1;
        link = link->next;
    }
    return -1;  // 该值不在该单链表中
}
// 遍历
void traverseLinkList(Node *link) {
    link = link->next;
    while (link) {
        printf("%d->", link->data);
        link = link->next;
    }
    printf("NULL\n");
}

// 哈希表相关实现
// 1.初始化哈希表
HashTable *getHashTable(int *input, int len) {

    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->length = len;
    // 初始化每个坑位
    for (int i = 0; i < N; i++) {
        hashTable->place[i] = initLinkList();
    }
    // 插入初始化的值
    for (int i = 0; i < len; i++) {
        insertVal(hashTable, *(input + i));
    }
    return hashTable;
}
// 2.插入元素
void insertVal(HashTable *hashTable, int x) {
    int pos = x % MOD;
    insertLinkLIst(hashTable->place[pos], x);  // 向哈希表中, 第pos位置的单链表插入x值(头插)
}
// 3.查询元素(有返回元素下标, 没找到返回-1)
int searchVal(HashTable *hashTable, int x) {
    int pos = x % MOD;
    return searchLinkList(hashTable->place[pos], x) == 1 ? pos : -1;  // pos就是这个pos,找到就是有,否则就没有
}
// 4.删除元素(有返回元素下标, 不存在返回-1)
int deleteVal(HashTable *hashTable, int x) {
    int pos = x % MOD;
    return deleteLinkList(hashTable->place[pos], x) == 1 ? pos : -1;
}
// 5.获取成功ASL的值(打印分数)
void getASLSuccess(HashTable *hashTable) {
    int ASLSuccessSum = 0;
    for (int i = 0; i < N; i++) {
        Node *pmove = hashTable->place[i]->next;
        int count = 0;  // 比较NULL不算做一次比较(所以初始化为0)
        int level = 1;  // 层数
        while (pmove) {
            count = count + (count + 1);
            pmove = pmove->next;
        }
        printf("i:%d ->%d\n", i, count);
        ASLSuccessSum += count;
    }
    printf("ASL Success: %d/%d\n", ASLSuccessSum, hashTable->length);
}
// 6.获取失败ASL的值(打印分数)
void getASLFail(HashTable *hashTable) {
    // 计算每个单链表, 比较到NULL需要的次数, 注意与NULL比较不算一次
    int ASLFailSum = 0;
    for (int i = 0; i < MOD; i++) {  // !注意这里是MOD, 只能到MOD!!!
        Node *pmove = hashTable->place[i]->next;
        while (pmove) {
            ASLFailSum++;
            pmove = pmove->next;
        }
    }
    printf("ASL Fail: %d/%d\n", ASLFailSum, MOD);
}
// [for test] 打印哈希表
void printHashTable(HashTable *hashTable) {
    for (int i = 0; i < N; i++) {
        printf("%d: ", i);
        traverseLinkList(hashTable->place[i]);
    }
}
