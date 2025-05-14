#include <stdio.h>
#include <stdlib.h>

#define N 7    // Hash表的长度
#define MOD 7  // Hash函数需要mod的值
#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 单链表相关实现(有哨兵头, 哨兵头值域没有任何意义)
// 初始化单链表
Node *initLinkList(void);
// 插入(头插)
void insertLinkLIst(Node *link, int x);
// 删除(如果成功删除返回1,否则返回-1,表示hash表中没有该元素)
int deleteLinkList(Node *link, int x);
// 查找(如果在该单链表上找到x, 返回1, 找不到返回-1)
int searchLinkList(Node *link, int x);
// 遍历
void traverseLinkList(Node *link);

typedef struct HashTable {
    Node *place[N];  // 哈希表中每个"坑位"都是一个单链表 (存储的为哨兵头)
    int length;      // 哈希表中值的个数
} HashTable;

// 哈希表相关实现
// 1.初始化哈希表
HashTable *getHashTable(int *input, int len);
// 2.插入元素
void insertVal(HashTable *hashTable, int x);
// 3.查询元素(有返回元素下标, 没找到返回-1)
int searchVal(HashTable *hashTable, int x);
// 4.删除元素(有返回元素下标, 不存在返回-1)
int deleteVal(HashTable *hashTable, int x);
// 5.获取成功ASL的值(打印分数)
void getASLSuccess(HashTable *hashTable);
// 6.获取失败ASL的值(打印分数)
void getASLFail(HashTable *hashTable);
// [for test] 打印哈希表
void printHashTable(HashTable *hashTable);
