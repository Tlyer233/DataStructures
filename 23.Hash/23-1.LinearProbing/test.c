#include "linear.h"

void test(void) {
    int input[] = {10, 25, 17, 6, 24};
    HashTable *hashTable = initHashTable(input, SIZE(input));
    printHashTable(hashTable);
    // deleteVal(hashTable, 25);
    // for (int i = 0; i < hashTable->length; i++) {
    //     printf("%d=>%d\n", input[i], search(hashTable, input[i]));
    // }

    getASLSuccess(hashTable);
    getASLFail(hashTable);
}

int main() {
    test();
    return 0;
}