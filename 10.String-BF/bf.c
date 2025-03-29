#include <stdio.h>
#include <string.h>

#define N 1000

void BF(char *aimS, char *moduleS) {
    for (int index = 0; index < strlen(aimS); index++) {
        for (int i = index, j = 0; j < strlen(moduleS); i++, j++) {
            if (aimS[i] != moduleS[j]) break;
            if (j == strlen(moduleS) - 1) { // 成功匹配
                int begin = index;
                int end = i ;
                printf("%d %d\n", begin, end);
                break;
            }
        }
    }
}

int main() {
    char aimS[N], moduleS[N];
    scanf("%s", aimS);
    scanf("%s", moduleS);
    BF(aimS, moduleS);
    return 0;
}