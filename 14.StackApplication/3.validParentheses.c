#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define N 10100
char stack[N];
int top = -1;
char leftParen[] = {'(', '[', '{'};
char rightParen[] = {')', ']', '}'};
/**
 * aim: 栈中弹出的括号
 * x: 右括号
 */
bool isApart(char aim, char x) {
    // 1.如果x是左括号, 一定不对 2.如果x和aim不匹配, 也不对

    for (int i = 0; i < SIZE(leftParen); i++) {
        if (x == rightParen[i] && aim == leftParen[i]) {
            return true;
        }
    }
    return false;
}

bool isValid(char *s) {
    top = -1;
    for (int i = 0; i < strlen(s); i++) {
        // 判断左右括号(没有set数据结构)
        int flag = 0;  // 1表示是左括号, 0表示是右括号
        for (int j = 0; j < SIZE(leftParen); j++) {
            // case1: 左括号
            if (leftParen[j] == s[i]) {
                stack[++top] = s[i];
                flag = 1;
                break;
            }
        }
        // case2: 右括号
        if (top==-1||(!flag && !isApart(stack[top--], s[i])))
            return false;
    }
    return top==-1;
}

int main() {
    char parenthese[100];
    scanf("%s", parenthese);
    printf("%d", isValid(parenthese));
    return 0;
}