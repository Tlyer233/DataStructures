#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "circularDoubleLinkList.h"

// 日志颜色
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

// 全局变量，用于模拟输入
int *testData = NULL;
int testDataSize = 0;
int currentInputIndex = 0;

// 日志函数
void logSuccess(const char* message) {
    printf("%s[✓] %s%s\n", GREEN, message, RESET);
}

void logError(const char* message) {
    printf("%s[✗] %s%s\n", RED, message, RESET);
}

void logInfo(const char* message) {
    printf("%s[i] %s%s\n", YELLOW, message, RESET);
}

// 自定义输入函数，替代scanf
int customInput() {
    if (currentInputIndex < testDataSize) {
        return testData[currentInputIndex++];
    }
    return -1; // 默认结束值
}

// 准备测试数据
void prepareTestData(int *data, int size) {
    testData = data;
    testDataSize = size;
    currentInputIndex = 0;
}

// 修改后的初始化函数，使用自定义输入
CDLNode *customInitCircularDoubleLinkList(void) {
    CDLNode *phead = (CDLNode *)malloc(sizeof(CDLNode));
    phead->data = 0;
    phead->next = phead->prev = phead;

    CDLNode *pmove = phead;

    int input;
    while ((input = customInput()) != -1) {
        CDLNode *newNode = (CDLNode *)malloc(sizeof(CDLNode));
        newNode->data = input;
        // 尾插法
        newNode->prev = pmove;
        pmove->next = newNode;
        newNode->next = phead;
        phead->prev = newNode;

        pmove = pmove->next;

        phead->data++;
    }
    return phead;
}

// 检查链表的完整性
bool checkListIntegrity(CDLNode *cdlist) {
    logInfo("检查链表完整性...");
    
    if (cdlist == NULL) {
        logError("链表头为NULL");
        return false;
    }
    
    int count = 0;
    CDLNode *pmove = cdlist->next;
    
    // 检查前向链接
    while (pmove != cdlist && count < 1000) { // 防止无限循环
        count++;
        
        // 检查前后指针的一致性
        if (pmove->next->prev != pmove) {
            char errorMsg[100];
            sprintf(errorMsg, "节点 %d 的前后指针不一致", pmove->data);
            logError(errorMsg);
            return false;
        }
        
        pmove = pmove->next;
    }
    
    if (count != cdlist->data) {
        char errorMsg[100];
        sprintf(errorMsg, "链表长度不匹配，头节点记录 %d，实际计数 %d", cdlist->data, count);
        logError(errorMsg);
        return false;
    }
    
    // 检查后向链接
    count = 0;
    pmove = cdlist->prev;
    while (pmove != cdlist && count < 1000) {
        count++;
        
        // 检查前后指针的一致性
        if (pmove->prev->next != pmove) {
            char errorMsg[100];
            sprintf(errorMsg, "节点 %d 的前后指针不一致（反向检查）", pmove->data);
            logError(errorMsg);
            return false;
        }
        
        pmove = pmove->prev;
    }
    
    if (count != cdlist->data) {
        char errorMsg[100];
        sprintf(errorMsg, "链表反向长度不匹配，头节点记录 %d，实际计数 %d", cdlist->data, count);
        logError(errorMsg);
        return false;
    }
    
    logSuccess("链表完整性检查通过");
    return true;
}

// 创建一个参考数组，用于验证链表操作
int* createReferenceArray(CDLNode *cdlist, int *size) {
    *size = cdlist->data;
    int *arr = (int*)malloc(sizeof(int) * (*size));
    
    CDLNode *pmove = cdlist->next;
    for (int i = 0; i < *size; i++) {
        arr[i] = pmove->data;
        pmove = pmove->next;
    }
    
    return arr;
}

// 验证链表与参考数组是否一致
bool verifyWithArray(CDLNode *cdlist, int *arr, int size) {
    logInfo("验证链表与参考数组一致性...");
    
    if (cdlist->data != size) {
        char errorMsg[100];
        sprintf(errorMsg, "链表长度 %d 与数组长度 %d 不匹配", cdlist->data, size);
        logError(errorMsg);
        return false;
    }
    
    CDLNode *pmove = cdlist->next;
    for (int i = 0; i < size; i++) {
        if (pmove->data != arr[i]) {
            char errorMsg[100];
            sprintf(errorMsg, "位置 %d 处，链表值 %d 与数组值 %d 不匹配", 
                   i, pmove->data, arr[i]);
            logError(errorMsg);
            return false;
        }
        pmove = pmove->next;
    }
    
    logSuccess("链表与参考数组一致性验证通过");
    return true;
}

// 测试插入操作
bool testInsert(CDLNode *cdlist) {
    printf("\n===== 测试插入操作 =====\n");
    
    int size;
    int *arr = createReferenceArray(cdlist, &size);
    
    // 随机选择插入位置和值
    int pos = rand() % (size + 1); // 可以在0到size之间插入
    int val = rand() % 100;
    
    char infoMsg[100];
    sprintf(infoMsg, "在位置 %d 插入值 %d", pos, val);
    logInfo(infoMsg);
    
    // 更新参考数组
    int *newArr = (int*)malloc(sizeof(int) * (size + 1));
    for (int i = 0; i < pos; i++) {
        newArr[i] = arr[i];
    }
    newArr[pos] = val;
    for (int i = pos; i < size; i++) {
        newArr[i + 1] = arr[i];
    }
    
    // 执行链表插入
    insert(cdlist, val, pos);
    
    // 验证
    bool integrityCheck = checkListIntegrity(cdlist);
    bool arrayCheck = verifyWithArray(cdlist, newArr, size + 1);
    
    free(arr);
    free(newArr);
    
    if (!integrityCheck || !arrayCheck) {
        logError("插入操作测试失败");
        return false;
    } else {
        logSuccess("插入操作测试通过");
        return true;
    }
}

// 测试删除操作
bool testErase(CDLNode *cdlist) {
    printf("\n===== 测试删除操作 =====\n");
    
    if (cdlist->data == 0) {
        logInfo("链表为空，跳过删除测试");
        return true;
    }
    
    int size;
    int *arr = createReferenceArray(cdlist, &size);
    
    // 随机选择删除位置
    int pos = rand() % size;
    
    char infoMsg[100];
    sprintf(infoMsg, "删除位置 %d 的元素（值为 %d）", pos, arr[pos]);
    logInfo(infoMsg);
    
    // 更新参考数组
    int *newArr = (int*)malloc(sizeof(int) * (size - 1));
    for (int i = 0; i < pos; i++) {
        newArr[i] = arr[i];
    }
    for (int i = pos + 1; i < size; i++) {
        newArr[i - 1] = arr[i];
    }
    
    // 执行链表删除
    erase(cdlist, pos);
    
    // 验证
    bool integrityCheck = checkListIntegrity(cdlist);
    bool arrayCheck = verifyWithArray(cdlist, newArr, size - 1);
    
    free(arr);
    free(newArr);
    
    if (!integrityCheck || !arrayCheck) {
        logError("删除操作测试失败");
        return false;
    } else {
        logSuccess("删除操作测试通过");
        return true;
    }
}

// 测试初始化函数
bool testInitialization() {
    printf("\n===== 测试初始化函数 =====\n");
    
    // 生成随机测试数据
    int testSize = 5 + rand() % 10; // 5-14个元素
    int *initData = (int*)malloc(sizeof(int) * (testSize + 1));
    
    logInfo("使用以下数据测试初始化函数：");
    printf("  ");
    for (int i = 0; i < testSize; i++) {
        initData[i] = rand() % 100;
        printf("%d ", initData[i]);
    }
    initData[testSize] = -1; // 结束标记
    printf("-1\n");
    
    // 准备测试数据
    prepareTestData(initData, testSize + 1);
    
    // 调用自定义初始化函数
    CDLNode *list = customInitCircularDoubleLinkList();
    
    // 验证初始化结果
    bool result = checkListIntegrity(list);
    
    if (result) {
        char successMsg[100];
        sprintf(successMsg, "初始化函数测试通过，创建了包含 %d 个元素的链表", list->data);
        logSuccess(successMsg);
    } else {
        logError("初始化函数测试失败");
    }
    
    // 清理
    destory(list);
    free(initData);
    return result;
}

// 主测试函数
void testCircularDoubleLinkList() {
    srand(time(NULL));
    
    printf("===== 循环双向链表测试开始 =====\n\n");
    
    // 测试初始化
    if (!testInitialization()) {
        logError("初始化测试失败，终止后续测试");
        return;
    }
    
    // 创建一个新的链表用于后续测试
    logInfo("准备初始链表数据：");
    
    // 自动生成测试数据
    int testSize = 5 + rand() % 5; // 5-9个元素
    int *mainTestData = (int*)malloc(sizeof(int) * (testSize + 1));
    
    printf("  ");
    for (int i = 0; i < testSize; i++) {
        mainTestData[i] = rand() % 100;
        printf("%d ", mainTestData[i]);
    }
    mainTestData[testSize] = -1; // 结束标记
    printf("-1\n");
    
    // 准备测试数据
    prepareTestData(mainTestData, testSize + 1);
    
    CDLNode *list = customInitCircularDoubleLinkList();
    
    logInfo("初始链表：");
    traverse(list);
    
    if (!checkListIntegrity(list)) {
        logError("初始链表完整性检查失败，终止后续测试");
        destory(list);
        free(mainTestData);
        return;
    }
    
    // 执行多次随机插入和删除操作
    int numTests = 5;
    int passedTests = 0;
    int totalTests = numTests * 2; // 每轮测试包含一次插入和一次删除
    
    for (int i = 0; i < numTests; i++) {
        printf("\n----- 测试轮次 %d/%d -----\n", i+1, numTests);
        
        if (testInsert(list)) passedTests++;
        logInfo("插入后的链表：");
        traverse(list);
        
        if (testErase(list)) passedTests++;
        logInfo("删除后的链表：");
        traverse(list);
    }
    
    printf("\n===== 测试结果汇总 =====\n");
    char summaryMsg[100];
    sprintf(summaryMsg, "总共执行 %d 项测试，通过 %d 项，通过率: %.1f%%", 
           totalTests, passedTests, (float)passedTests/totalTests*100);
    
    if (passedTests == totalTests) {
        logSuccess(summaryMsg);
        logSuccess("所有测试通过，循环双向链表实现正确！");
    } else {
        logError(summaryMsg);
        logError("部分测试未通过，请检查实现！");
    }
    
    destory(list);
    free(mainTestData);
}

int main() {
    testCircularDoubleLinkList();
    return 0;
}