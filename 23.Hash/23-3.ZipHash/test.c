#include "zipHash.h"

void test(void) {
    int input[] = {10, 25, 17, 6, 24};
    HashTable *hashTable = getHashTable(input, SIZE(input));
    printHashTable(hashTable);
    getASLSuccess(hashTable);
    getASLFail(hashTable);
}

int main() {
    test();
    return 0;
}