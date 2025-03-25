#include "doubleLinkList.h"
#include <stdbool.h>
#include <string.h>
#include <time.h>

// 辅助函数：创建指定数组内容的链表
DListNode *createTestList(int *arr, int size) {
    DListNode *head = (DListNode *)malloc(sizeof(DListNode));
    head->data = 0;
    head->prev = NULL;
    head->next = NULL;

    DListNode *pmove = head;
    for (int i = 0; i < size; i++) {
        DListNode *newNode = (DListNode *)malloc(sizeof(DListNode));
        newNode->data = arr[i];
        newNode->prev = pmove;
        newNode->next = NULL;
        pmove->next = newNode;
        pmove = newNode;
        head->data++;
    }

    return head;
}

// 辅助函数：验证链表的双向性
bool verifyDoubleLinkList(DListNode *list) {
    if (!list) return false;

    // 正向遍历检查prev指针
    DListNode *pmove = list->next;
    while (pmove) {
        if (pmove->prev->next != pmove) return false;
        pmove = pmove->next;
    }

    // 反向遍历检查next指针
    pmove = list;
    while (pmove->next) pmove = pmove->next;
    while (pmove != list) {
        if (pmove->prev->next != pmove) return false;
        pmove = pmove->prev;
    }

    return true;
}

// 测试初始化功能
bool testInit() {
    printf("测试初始化功能:\n");
    bool allPassed = true;

    // 测试空链表
    printf("  测试创建空链表: ");
    DListNode *list = createTestList(NULL, 0);
    bool result = (list->data == 0 && list->next == NULL);
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destoryDoubleLinkList(list);

    // 测试单节点链表
    printf("  测试创建单节点链表: ");
    int arr[] = {1};
    list = createTestList(arr, 1);
    result = (list->data == 1 && verifyDoubleLinkList(list));
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destoryDoubleLinkList(list);

    return allPassed;
}

// 测试插入功能
bool testInsert() {
    printf("测试插入功能:\n");
    bool allPassed = true;

    // 创建测试链表
    int arr[] = {1, 2, 3};
    DListNode *list = createTestList(arr, 3);

    // 测试头部插入
    printf("  测试头部插入: ");
    insert(list, 0, 0);
    bool result = (list->next->data == 0 && verifyDoubleLinkList(list));
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;

    // 测试尾部插入
    printf("  测试尾部插入: ");
    insert(list, 4, list->data);
    result = (list->data == 5 && verifyDoubleLinkList(list));
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;

    destoryDoubleLinkList(list);
    return allPassed;
}

// 测试删除功能
bool testErase() {
    printf("测试删除功能:\n");
    bool allPassed = true;

    // 创建测试链表
    int arr[] = {1, 2, 3, 4};
    DListNode *list = createTestList(arr, 4);

    // 测试头部删除
    printf("  测试头部删除: ");
    earse(list, 0);
    bool result = (list->next->data == 2 && verifyDoubleLinkList(list));
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;

    // 测试尾部删除
    printf("  测试尾部删除: ");
    earse(list, list->data - 1);
    result = (list->data == 2 && verifyDoubleLinkList(list));
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;

    destoryDoubleLinkList(list);
    return allPassed;
}

// 运行所有测试
void runAllTests() {
    printf("============== 双向链表测试 ==============\n");

    bool initTestPassed = testInit();
    bool insertTestPassed = testInsert();
    bool eraseTestPassed = testErase();

    printf("\n============== 测试结果汇总 ==============\n");
    printf("初始化测试: %s\n", initTestPassed ? "通过" : "失败");
    printf("插入操作测试: %s\n", insertTestPassed ? "通过" : "失败");
    printf("删除操作测试: %s\n", eraseTestPassed ? "通过" : "失败");
    printf("总体结果: %s\n",
           (initTestPassed && insertTestPassed && eraseTestPassed) ? "全部通过" : "存在失败");
}

void test01() {
    DListNode *dlist = initDoubleLinkList();
    traverseDoubleLinkeList(dlist);

    earse(dlist, -7);
    traverseDoubleLinkeList(dlist);

    destoryDoubleLinkList(dlist);
}

int main() {
    runAllTests();
    return 0;
}
