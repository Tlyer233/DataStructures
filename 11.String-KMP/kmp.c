#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

void getNext(int *next, char *moduleS) {
    next[0] = -1;
    for (int i = 1; i < strlen(moduleS); i++) {
        int t = next[i - 1];
        while (t != -1 && moduleS[t] != moduleS[i - 1]) { t = next[t]; }
        next[i] = t + 1;
    }
}
void getNextVal(int *next, int *nextVal, char *moduleS) {
    nextVal[0] = next[0] = -1;  // 无论是next或者nextVal 0号位置,一定是-1
    for (int i = 1; i < strlen(moduleS); i++) {
        int t = next[i];
        nextVal[i] = moduleS[i] == moduleS[t] ? next[t] : next[i];
    }
}

void KMP(int *next, char *aimS, char *moduleS) {
    for (int i = 0, j = 0; i < strlen(aimS); i++) {
        while (j != 0 && aimS[i] != moduleS[j]) j = next[j];
        if (aimS[i] == moduleS[j]) j++;
        if (j == strlen(moduleS)) {
            int begin = i - strlen(moduleS) + 1;
            int end = i;
            printf("%d %d\n", begin, end);
            j = next[j - 1] + 1;
        }
    }
}
void KMPNextVal(int *nextVal, int *next, char *aimS, char *moduleS) {
    for (int i = 0, j = 0; i < strlen(aimS); i++) {
        while (j != 0 && aimS[i] != moduleS[j]) j = nextVal[j];
        if (aimS[i] == moduleS[j]) j++;
        if (j == strlen(moduleS)) {
            int begin = i - strlen(moduleS) + 1;
            int end = i;
            printf("%d %d\n", begin, end);
            j = next[j - 1] + 1;  // 因为nextVal简化了next,所以没有办法准确回退
        }
    }
}

int main() {
    char aimS[N], moduleS[N];
    int next[N], nextVal[N];
    scanf("%s", aimS);
    scanf("%s", moduleS);
    // Next数组
    getNext(next, moduleS);
    printf("Next数组: ");
    for (int i = 0; i < strlen(moduleS); i++) printf("%d ", next[i]);
    puts("");

    // 或者NextVal数组
    getNextVal(next, nextVal, moduleS);
    printf("NextVal数组: ");
    for (int i = 0; i < strlen(moduleS); i++) printf("%d ", nextVal[i]);
    puts("");

    // KMP
    KMP(next, aimS, moduleS);
    puts("=================================");
    KMPNextVal(nextVal, next, aimS, moduleS);
    return 0;
}
