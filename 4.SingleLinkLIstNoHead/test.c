#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "singleLinkList.h"

// 创建测试链表（手动创建，不使用initSingleLinkList避免需要用户输入）
SingleLinkListNode* createTestList(int* arr, int size) {
    if (size == 0) return NULL;
    
    SingleLinkListNode* head = (SingleLinkListNode*)malloc(sizeof(SingleLinkListNode));
    head->data = arr[0];
    head->next = NULL;
    
    SingleLinkListNode* pmove = head;
    for (int i = 1; i < size; i++) {
        SingleLinkListNode* newNode = (SingleLinkListNode*)malloc(sizeof(SingleLinkListNode));
        newNode->data = arr[i];
        newNode->next = NULL;
        
        pmove->next = newNode;
        pmove = pmove->next;
    }
    
    return head;
}

// 检查链表内容是否与数组匹配
bool checkListContent(SingleLinkListNode* list, int* expected, int size) {
    if ((list == NULL) && (size == 0)) return true;
    if ((list == NULL) || (size == 0)) return false;
    
    SingleLinkListNode* pmove = list;
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

// 计算链表长度
int getListLength(SingleLinkListNode* list) {
    int length = 0;
    SingleLinkListNode* pmove = list;
    while (pmove) {
        length++;
        pmove = pmove->next;
    }
    return length;
}

// 测试销毁函数
bool testDestroy() {
    printf("测试销毁链表:\n");
    
    // 创建测试链表
    int arr[] = {1, 2, 3, 4, 5};
    SingleLinkListNode* list = createTestList(arr, 5);
    
    // 调用销毁函数
    printf("  调用destorySingleLinkList: ");
    destorySingleLinkList(list);
    printf("通过 (无法检查内存是否正确释放)\n");
    
    return true;
}

// 测试插入操作
bool testInsert() {
    printf("测试插入操作:\n");
    bool allPassed = true;
    
    // 测试向空链表插入
    printf("  测试向空链表插入: ");
    SingleLinkListNode* emptyList = NULL;
    insert(&emptyList, 100, 0);
    
    int expected1[] = {100};
    bool result = checkListContent(emptyList, expected1, 1);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(emptyList);
    
    // 测试向链表头插入
    printf("  测试向链表头插入: ");
    int arr[] = {20, 30, 40};
    SingleLinkListNode* list = createTestList(arr, 3);
    
    insert(&list, 10, 0);
    
    int expected2[] = {10, 20, 30, 40};
    result = checkListContent(list, expected2, 4);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试向链表中间插入
    printf("  测试向链表中间插入: ");
    insert(&list, 25, 2);
    
    int expected3[] = {10, 20, 25, 30, 40};
    result = checkListContent(list, expected3, 5);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试向链表尾部插入
    printf("  测试向链表尾部插入: ");
    insert(&list, 50, 5);
    
    int expected4[] = {10, 20, 25, 30, 40, 50};
    result = checkListContent(list, expected4, 6);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(list);
    return allPassed;
}

// 测试删除操作
bool testErase() {
    printf("测试删除操作:\n");
    bool allPassed = true;
    
    // 测试单节点链表删除
    printf("  测试单节点链表删除: ");
    SingleLinkListNode* singleList = createTestList((int[]){100}, 1);
    erase(&singleList, 0);
    
    bool result = (singleList == NULL);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试删除链表头
    printf("  测试删除链表头: ");
    int arr[] = {10, 20, 30, 40, 50};
    SingleLinkListNode* list = createTestList(arr, 5);
    
    erase(&list, 0);
    
    int expected1[] = {20, 30, 40, 50};
    result = checkListContent(list, expected1, 4);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试删除链表中间节点
    printf("  测试删除链表中间节点: ");
    erase(&list, 1);
    
    int expected2[] = {20, 40, 50};
    result = checkListContent(list, expected2, 3);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试删除链表尾节点
    printf("  测试删除链表尾节点: ");
    erase(&list, 2);
    
    int expected3[] = {20, 40};
    result = checkListContent(list, expected3, 2);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    destorySingleLinkList(list);
    return allPassed;
}

// 测试边界情况
bool testEdgeCases() {
    printf("测试边界情况:\n");
    
    // 测试空链表
    printf("  测试空链表创建和检查: ");
    SingleLinkListNode* emptyList = NULL;
    bool result = (emptyList == NULL);
    printf("%s\n", result ? "通过" : "失败");
    
    printf("  注意：以下边界情况会触发断言，仅记录不执行：\n");
    printf("    - 对空链表执行删除操作\n");
    printf("    - 对空链表非0位置插入\n");
    printf("    - 插入/删除索引超出范围\n");
    
    return true;
}

// 测试链表长度计算
bool testLength() {
    printf("测试链表长度计算:\n");
    bool allPassed = true;
    
    // 测试空链表
    printf("  测试空链表长度: ");
    SingleLinkListNode* emptyList = NULL;
    bool result = (getListLength(emptyList) == 0);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    // 测试单节点链表
    printf("  测试单节点链表长度: ");
    SingleLinkListNode* singleList = createTestList((int[]){100}, 1);
    result = (getListLength(singleList) == 1);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destorySingleLinkList(singleList);
    
    // 测试多节点链表
    printf("  测试多节点链表长度: ");
    int arr[] = {10, 20, 30, 40, 50};
    SingleLinkListNode* list = createTestList(arr, 5);
    result = (getListLength(list) == 5);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destorySingleLinkList(list);
    
    return allPassed;
}

// 运行所有测试
void runAllTests() {
    printf("============== 不带头节点单链表实现测试 ==============\n");
    
    bool lengthTestPassed = testLength();
    bool destroyTestPassed = testDestroy();
    bool insertTestPassed = testInsert();
    bool eraseTestPassed = testErase();
    bool edgeTestPassed = testEdgeCases();
    
    printf("\n============== 测试结果汇总 ==============\n");
    printf("长度计算测试: %s\n", lengthTestPassed ? "通过" : "失败");
    printf("销毁链表测试: %s\n", destroyTestPassed ? "通过" : "失败");
    printf("插入操作测试: %s\n", insertTestPassed ? "通过" : "失败");
    printf("删除操作测试: %s\n", eraseTestPassed ? "通过" : "失败");
    printf("边界情况测试: %s\n", edgeTestPassed ? "通过" : "失败");
    printf("总体结果: %s\n", 
           (lengthTestPassed && destroyTestPassed && insertTestPassed && eraseTestPassed && edgeTestPassed) 
           ? "全部通过" : "存在失败");
}


void test01(void) {
    SingleLinkListNode* list = initSingleLinkList();
    traverseSingleLinkList(list);
    erase(&list, 0);
    traverseSingleLinkList(list);
}

int main() {
    srand((unsigned int)time(NULL));
    runAllTests();
    // test01();
    
    return 0;
}