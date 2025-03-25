#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <setjmp.h>
#include <signal.h>
#include "singleLinkList.h"

// 辅助函数：创建具有特定内容的链表
SingleLinkListNode* createTestList(int* arr, int size) {
    SingleLinkListNode* list = (SingleLinkListNode*)malloc(sizeof(SingleLinkListNode));
    list->data = 0;
    list->next = NULL;
    
    for (int i = 0; i < size; i++) {
        pushBack(list, arr[i]);
    }
    
    return list;
}

// 创建一个空链表
SingleLinkListNode* createEmptyList() {
    SingleLinkListNode* list = (SingleLinkListNode*)malloc(sizeof(SingleLinkListNode));
    list->data = 0;
    list->next = NULL;
    return list;
}

// 辅助函数：检查链表内容是否与数组匹配
bool checkListContent(SingleLinkListNode* list, int* expected, int size) {
    if (list->data != size) {
        printf("    预期长度: %d, 实际长度: %d\n", size, list->data);
        return false;
    }
    
    SingleLinkListNode* pmove = list->next;
    for (int i = 0; i < size; i++) {
        if (!pmove || pmove->data != expected[i]) {
            printf("    索引 %d 处值不匹配: 预期 %d, 实际 ", i, expected[i]);
            if (!pmove) printf("NULL\n");
            else printf("%d\n", pmove->data);
            return false;
        }
        pmove = pmove->next;
    }
    
    if (pmove != NULL) {
        printf("    链表长度超出预期\n");
        return false;
    }
    
    return true;
}

// 测试函数：基本操作
bool testBasicOperations() {
    printf("测试基本操作:\n");
    bool allPassed = true;
    
    // 测试创建和销毁空链表
    printf("  测试创建和销毁空链表: ");
    SingleLinkListNode* list = createEmptyList();
    bool result = (list->data == 0 && list->next == NULL);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(list);
    return allPassed;
}

// 测试函数：插入操作
bool testPushOperations() {
    printf("测试插入操作:\n");
    bool allPassed = true;
    
    // 测试向空链表 pushBack
    printf("  测试向空链表 pushBack: ");
    SingleLinkListNode* list = createEmptyList();
    
    pushBack(list, 10);
    
    int expected1[] = {10};
    bool result = checkListContent(list, expected1, 1);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试多次 pushBack
    printf("  测试多次 pushBack: ");
    pushBack(list, 20);
    pushBack(list, 30);
    
    int expected2[] = {10, 20, 30};
    result = checkListContent(list, expected2, 3);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试向空链表 pushFront
    printf("  测试向空链表 pushFront: ");
    SingleLinkListNode* listEmpty = createEmptyList();
    
    pushFront(listEmpty, 5);
    
    int expected3[] = {5};
    result = checkListContent(listEmpty, expected3, 1);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(listEmpty);
    
    // 测试多次 pushFront
    printf("  测试多次 pushFront: ");
    pushFront(list, 5);
    pushFront(list, 1);
    
    int expected4[] = {1, 5, 10, 20, 30};
    result = checkListContent(list, expected4, 5);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试 insert 在头部
    printf("  测试 insert 在头部: ");
    insert(list, 0, 0);
    
    int expected5[] = {0, 1, 5, 10, 20, 30};
    result = checkListContent(list, expected5, 6);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试 insert 在中间
    printf("  测试 insert 在中间: ");
    insert(list, 15, 4);
    
    int expected6[] = {0, 1, 5, 10, 15, 20, 30};
    result = checkListContent(list, expected6, 7);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试 insert 在尾部
    printf("  测试 insert 在尾部: ");
    insert(list, 40, list->data);
    
    int expected7[] = {0, 1, 5, 10, 15, 20, 30, 40};
    result = checkListContent(list, expected7, 8);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(list);
    return allPassed;
}

// 测试函数：删除操作
bool testPopOperations() {
    printf("测试删除操作:\n");
    bool allPassed = true;
    
    // 测试单元素链表 popBack
    printf("  测试单元素链表 popBack: ");
    SingleLinkListNode* singleList = createEmptyList();
    pushBack(singleList, 10);
    popBack(singleList);
    
    bool result = (singleList->data == 0 && singleList->next == NULL);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(singleList);
    
    // 测试单元素链表 popFront
    printf("  测试单元素链表 popFront: ");
    singleList = createEmptyList();
    pushBack(singleList, 10);
    popFront(singleList);
    
    result = (singleList->data == 0 && singleList->next == NULL);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(singleList);
    
    // 测试多元素链表的删除操作
    int initial[] = {10, 20, 30, 40, 50};
    SingleLinkListNode* list = createTestList(initial, 5);
    
    // 测试 popBack
    printf("  测试多元素链表 popBack: ");
    popBack(list);
    
    int expected1[] = {10, 20, 30, 40};
    result = checkListContent(list, expected1, 4);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试 popFront
    printf("  测试多元素链表 popFront: ");
    popFront(list);
    
    int expected2[] = {20, 30, 40};
    result = checkListContent(list, expected2, 3);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试 erase 头部
    printf("  测试 erase 头部: ");
    list = createTestList(initial, 5); // 重新创建链表
    erase(list, 0);
    
    int expected3[] = {20, 30, 40, 50};
    result = checkListContent(list, expected3, 4);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试 erase 中间
    printf("  测试 erase 中间: ");
    erase(list, 1);
    
    int expected4[] = {20, 40, 50};
    result = checkListContent(list, expected4, 3);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试 erase 尾部
    printf("  测试 erase 尾部: ");
    erase(list, list->data - 1);
    
    int expected5[] = {20, 40};
    result = checkListContent(list, expected5, 2);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(list);
    return allPassed;
}

// 测试函数：特殊边界情况
bool testEdgeCases() {
    printf("测试特殊边界情况:\n");
    bool allPassed = true;
    
    // 测试空链表基本属性
    printf("  测试空链表基本属性: ");
    SingleLinkListNode* list = createEmptyList();
    
    bool result = (list->data == 0 && list->next == NULL);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试插入后再全部删除
    printf("  测试插入后全部删除: ");
    pushBack(list, 10);
    pushBack(list, 20);
    pushBack(list, 30);
    popBack(list);
    popBack(list);
    popBack(list);
    
    result = (list->data == 0 && list->next == NULL);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试大量元素操作
    printf("  测试大量元素操作: ");
    const int LARGE_SIZE = 1000;
    for (int i = 0; i < LARGE_SIZE; i++) {
        pushBack(list, i);
    }
    
    result = (list->data == LARGE_SIZE);
    printf("%s (链表长度: %d)\n", result ? "通过" : "失败", list->data);
    allPassed &= result;
    
    destorySingleLinkList(list);
    
    printf("  注意：以下边界情况会触发断言，仅记录不执行：\n");
    printf("    - 对空链表执行删除操作\n");
    printf("    - 插入/删除索引超出范围\n");
    
    return allPassed;
}

// 综合测试
void runAllTests() {
    printf("============== 单链表实现测试 ==============\n");
    
    bool basicTestPassed = testBasicOperations();
    bool pushTestPassed = testPushOperations();
    bool popTestPassed = testPopOperations();
    bool edgeTestPassed = testEdgeCases();
    
    printf("\n============== 测试结果汇总 ==============\n");
    printf("基本操作测试: %s\n", basicTestPassed ? "通过" : "失败");
    printf("插入操作测试: %s\n", pushTestPassed ? "通过" : "失败");
    printf("删除操作测试: %s\n", popTestPassed ? "通过" : "失败");
    printf("边界情况测试: %s\n", edgeTestPassed ? "通过" : "失败");
    printf("总体结果: %s\n", 
           (basicTestPassed && pushTestPassed && popTestPassed && edgeTestPassed) 
           ? "全部通过" : "存在失败");
}

int main() {
    // 设置随机种子
    srand((unsigned int)time(NULL));
    
    // 运行所有测试
    runAllTests();
    
    return 0;
}