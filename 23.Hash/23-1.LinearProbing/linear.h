#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 7    // 数组长度 (装填因子=表中元素/表长N)
#define MOD 7  // H(key)=key%MOD
#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct HashTable {
    int *hash;
    int *aslSuccess;  // 每个值的, 成功的拼接查找长度 [命名不严谨]
    int length;       // 关键字个数
} HashTable;

// 1.初始化Hash表
HashTable *initHashTable(int *input, int len);
// 2.向哈希表中插入元素
void insertVal(HashTable *hashTable, int x);

// 2-1.平方探测法
void quadraticInsert(HashTable *hashTable, int x);
int quadraticSearch(HashTable *hashTable, int x);

// 3.查找指定值x是否在哈希表中, 在返回下标, 不在返回-1
int search(HashTable *hashTable, int x);
// 4.删除制定值x, 返回下标, 如果目标删除值不在返回-1
int deleteVal(HashTable *hashTable, int x);
// 5.获取平均成功查找长度(不返回了)
void getASLSuccess(HashTable *hashTable);
// 6.获取平均失败查找长度(不返回了)
void getASLFail(HashTable *hashTable);

// [for test] 打印哈希表
void printHashTable(HashTable *HashTable);
