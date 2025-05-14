#include "quadratic.h"

// 1.初始化Hash表
HashTable *initHashTable(int *input, int len) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->hash = (int *)malloc(N * sizeof(int));
    hashTable->aslSuccess = (int *)malloc(N * sizeof(int));
    hashTable->length = len;

    memset(hashTable->hash, 0, N * sizeof(int));
    memset(hashTable->aslSuccess, 0, N * sizeof(int));

    // 插入初始值
    for (int i = 0; i < len; i++) {
        insertVal(hashTable, *(input + i));
        // quadraticInsert(hashTable, *(input + i));
    }

    return hashTable;
}
// 2.向哈希表中插入元素
void insertVal(HashTable *hashTable, int x) {
    int pos = x % MOD;
    int successCount = 1;                                         // 经过多少次才找到坑位
    while (hashTable->hash[pos] && hashTable->hash[pos] != -1) {  //! -1表示删除,可以插入新值
        pos = (pos + 1) % N;
        successCount++;
    }
    hashTable->hash[pos] = x;
    hashTable->aslSuccess[pos] = successCount;  // 这样分开写直观
}

// 2-1.平方探测法
void quadraticInsert(HashTable *hashTable, int x) {
    int step[] = {1, -1, 4, -4, 9, -9};
    int indexStep = 0;
    int initPos = x % MOD;  // ! 要在原始基础上变动

    int pos = initPos;
    int successCount = 1;  // 经过多少次才找到坑位
    while (hashTable->hash[pos] != 0 && hashTable->hash[pos] != -1) {
        pos = (initPos + step[indexStep++]) % N;
        successCount++;
    }
    hashTable->hash[pos] = x;
    hashTable->aslSuccess[pos] = successCount;
}
// 3-1
int quadraticSearch(HashTable *hashTable, int x) {
    int step[] = {1, -1, 4, -4, 9, -9};
    int indexStep = 0;
    int pos = x % MOD;
    while (hashTable->hash[pos] != x && hashTable->hash[pos] != -1 && hashTable->hash[pos] != 0) {
        pos = (pos + step[indexStep++]) % N;
    }
    return hashTable->hash[pos] == x ? pos : -1;
}

// 3.查找指定值x是否在哈希表中, 在返回下标, 不在返回-1
int search(HashTable *hashTable, int x) {
    int pos = x % MOD;
    //! 删除置为-1的意义在这里, 如果直接置为0,那这里就不会继续向后找了
    // 比如MOD=7, 7,14,21都映射到0位置,因为冲突,0:7; 1:14; 2:21
    // 现在把14删除了,如果置为0, 那找21的时候,碰到1位置的0,就停止寻找了
    // 但是如果置为-1, 寻找停止的条件为0, 那就会继续向后, 正确找到21.
    while (hashTable->hash[pos] != x && hashTable->hash[pos] != 0) {
        pos = (pos + 1) % N;
    }
    return hashTable->hash[pos] == x ? pos : -1;
}

// 4.删除指定值x, 返回下标, 如果目标删除值不在返回-1
int deleteVal(HashTable *hashTable, int x) {
    int pos = search(hashTable, x);
    if (pos == -1)  // 删除的值, 置为-1;
        return -1;
    hashTable->hash[pos] = -1;
    return pos;
}

// 5.获取平均成功查找长度
void getASLSuccess(HashTable *hashTable) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += hashTable->aslSuccess[i];
    }
    printf("%d/%d\n", sum, hashTable->length);
}

// 6.获取平均失败查找长度
void getASLFail(HashTable *hashTable) {
    int ASLFail[N];
    memset(ASLFail, 1, N);           // 和空气也比较也算一次
    int count = 1;                   // 什么情况count为1? case1:刚开始 case2:经过了"空坑位"
    for (int i = 0; i < MOD; i++) {  // !坑 因为查找不可能到MOD
        // 过空气归零
        if (hashTable->hash[i] == -1 || hashTable->hash[i] == 0) {
            ASLFail[i] = 1;
            count = 1;  //! 归零
            continue;
        }
        // 重算逻辑
        if (count == 1) {
            int j = i;
            while (hashTable->hash[j] != 0 && hashTable->hash[j] != -1) {
                count++;
                j = (j + 1) % N;
                // printf("%d\n", count);
            }
            ASLFail[i] = count;
            count--;
        }
        // 连续直接等与前一个-1(当然每次获取完-1, 下一个直接等就是-1 的值了)
        else {
            ASLFail[i] = count;
            count--;
        }
    }

    int sum = 0;
    for (int i = 0; i < MOD; i++) {
        sum += ASLFail[i];
    }
    printf("%d/%d\n", sum, MOD);
}

// [for test] 打印哈希表
void printHashTable(HashTable *hashTable) {
    for (int i = 0; i < N; i++)
        printf("%d ", i);
    puts("");
    for (int i = 0; i < N; i++) {
        printf("%d ", hashTable->hash[i]);
    }
    puts("");
}