/**在"栈"的应用中,都用数组栈,简单封装 */
// 1. 计算算术表达式
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define N 1000

char stack[N];      // 中=>后的栈
int calcuStack[N];  // 计算"后缀表达式"的栈
int head = -1;

// 获取"操作符"优先级; 如果不是字符返回-1
int isOperator(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;  // 1级操作符
        case '*':
        case '/':
            return 2;  // 2级操作符
        default:
            return -1;  // 不是操作符
    }
}

// 1.中缀表达式=>后缀表达式 (抽象版)
char *convertInfix2Postfix(char *infixExpression) {
    head = -1;
    char *postfixExpression = (char *)malloc(sizeof(char) * N);
    char *pmove = postfixExpression;

    int i = 0;
    while (i < strlen(infixExpression)) {
        // case1:如果是数字,直接写入"后缀表达式"
        if (isdigit(infixExpression[i])) {
            // STEP1:读取完整数字
            while (isdigit(infixExpression[i])) {
                *pmove++ = infixExpression[i++];  // 等价于先赋值, 后将pmove++==>*pmove = infixExpression[i++]; pmove++;
            }
            // STEP2:添加空格
            *pmove++ = ' ';
            i++;  // 跳过(读取)空格
        } else {
            switch (infixExpression[i]) {
                case '(':  // case2:是(括号
                    stack[++head] = infixExpression[i];
                    break;
                case ')':  // case3:是)括号
                    while (stack[head] != '(') {
                        *pmove++ = stack[head--];
                        *pmove++ = ' ';  // 补空格
                    }
                    head--;  // 弹出'(',但不写入"后缀表达式"
                    break;
                default:  // case4:如果是操作符
                    // 请大哥出来(如果有); 否则就不会执行while,相当于自己直接进去
                    while (head != -1 && isOperator(stack[head]) >= isOperator(infixExpression[i])) {
                        *pmove++ = stack[head--];  // 读操作符
                        *pmove++ = ' ';            // 补空格
                    }
                    // 自己再进去
                    stack[++head] = infixExpression[i];
            }
            i += 2;  // 略过当前操作符及其后面的空格
        }
    }

    // 剩余的依次弹出,并写入
    while (head != -1) {
        *pmove++ = stack[head--];
        *pmove++ = ' ';  // 补空格
    }

    *pmove = '\0';  // 手动补一个\0

    return postfixExpression;
}

// 计算指定"操作符"计算后的结果
int calculate(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
    }
}
// 2.计算后缀表达式 (9 3 1 - 3 * + 10 2 / +)
int executePostfixExp(char *postfixExpress) {
    head = -1;  // 清空栈
    int i = 0;
    while (i < strlen(postfixExpress)) {
        // case1:如果是数字
        if (isdigit(postfixExpress[i])) {
            char temp[100] = "";
            while (isdigit(postfixExpress[i])) {
                char partNum[2];
                partNum[0] = postfixExpress[i++];
                partNum[1] = '\0';  // 这样转为字符串
                strcat(temp, partNum);
            }
            calcuStack[++head] = atoi(temp);
            i++;  // 跳过空格
        } else {
            int b = calcuStack[head--];  // 注意次序(是反的)
            int a = calcuStack[head--];
            char op = postfixExpress[i];
            calcuStack[++head] = calculate(a, b, op);
            i += 2;  // 跳过"操作符"和"空格"
        }
    }
    return calcuStack[head--];
}

void test01() {
    char *infixExpression = "9 + ( 3 - 1 ) * 3 + 10 / 2";
    char *postfixExpression = convertInfix2Postfix(infixExpression);
    printf("%s\n", postfixExpression);
    int ans = executePostfixExp(postfixExpression);
    printf("%d", ans);
}

int main() {
    test01();
    return 0;
}
