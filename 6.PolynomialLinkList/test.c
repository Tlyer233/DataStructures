#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "polynomial.h"

// 辅助函数：创建指定系数和指数的多项式
LinkListNode* createTestPoly(float* coefs, int* exps, int size) {
    LinkListNode* head = (LinkListNode*)malloc(sizeof(LinkListNode));
    head->exp = head->coef = -1;
    head->next = NULL;
    
    for (int i = 0; i < size; i++) {
        // 跳过系数为0的项
        if (fabs(coefs[i]) < 1e-6) continue;
        
        LinkListNode* newNode = (LinkListNode*)malloc(sizeof(LinkListNode));
        newNode->coef = coefs[i];
        newNode->exp = exps[i];
        newNode->next = NULL;
        
        // 按指数升序插入
        LinkListNode* pmove = head;
        while (pmove->next && newNode->exp > pmove->next->exp) {
            pmove = pmove->next;
        }
        
        // 合并同类项
        if (pmove->next && newNode->exp == pmove->next->exp) {
            pmove->next->coef += newNode->coef;
            // 如果合并后系数为0，删除该节点
            if (fabs(pmove->next->coef) < 1e-6) {
                LinkListNode* temp = pmove->next;
                pmove->next = temp->next;
                free(temp);
            }
            free(newNode);
        } else {
            newNode->next = pmove->next;
            pmove->next = newNode;
        }
    }
    
    return head;
}

// 辅助函数：检查两个多项式是否相等
bool polyEqual(LinkListNode* poly1, LinkListNode* poly2) {
    LinkListNode* p1 = poly1->next;
    LinkListNode* p2 = poly2->next;
    
    while (p1 && p2) {
        if (p1->exp != p2->exp || fabs(p1->coef - p2->coef) > 1e-6) {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    
    return p1 == NULL && p2 == NULL;
}

// 辅助函数：打印多项式比较结果
void printPolyComparison(LinkListNode* expected, LinkListNode* actual) {
    printf("  预期结果: ");
    traversePolynomial(expected);
    printf("  实际结果: ");
    traversePolynomial(actual);
}

// 测试创建多项式
bool testInitPolynomial() {
    printf("测试创建多项式:\n");
    bool allPassed = true;
    
    // 测试空多项式
    printf("  测试空多项式: ");
    float coefs1[] = {};
    int exps1[] = {};
    LinkListNode* poly1 = createTestPoly(coefs1, exps1, 0);
    bool result = poly1->next == NULL;
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destoryPolynomial(poly1);
    
    // 测试单项多项式
    printf("  测试单项多项式: ");
    float coefs2[] = {2.0};
    int exps2[] = {3};
    LinkListNode* poly2 = createTestPoly(coefs2, exps2, 1);
    result = poly2->next && fabs(poly2->next->coef - 2.0) < 1e-6 && poly2->next->exp == 3;
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destoryPolynomial(poly2);
    
    // 测试多项多项式
    printf("  测试多项多项式: ");
    float coefs3[] = {2.0, 3.0, 1.0};
    int exps3[] = {3, 1, 0};
    LinkListNode* poly3 = createTestPoly(coefs3, exps3, 3);
    LinkListNode* p = poly3->next;
    result = p && fabs(p->coef - 1.0) < 1e-6 && p->exp == 0;
    p = p ? p->next : NULL;
    result &= p && fabs(p->coef - 3.0) < 1e-6 && p->exp == 1;
    p = p ? p->next : NULL;
    result &= p && fabs(p->coef - 2.0) < 1e-6 && p->exp == 3;
    p = p ? p->next : NULL;
    result &= p == NULL;
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destoryPolynomial(poly3);
    
    // 测试合并同类项
    printf("  测试合并同类项: ");
    float coefs4[] = {2.0, 3.0, 4.0};
    int exps4[] = {2, 2, 2};
    LinkListNode* poly4 = createTestPoly(coefs4, exps4, 3);
    result = poly4->next && fabs(poly4->next->coef - 9.0) < 1e-6 && poly4->next->exp == 2;
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destoryPolynomial(poly4);
    
    return allPassed;
}

// 测试多项式加法
bool testAddPoly() {
    printf("测试多项式加法:\n");
    bool allPassed = true;
    
    // 测试不同指数项的合并
    printf("  测试不同指数项的合并: ");
    float coefs1[] = {2.0, 3.0};
    int exps1[] = {3, 1};
    float coefs2[] = {4.0, 5.0};
    int exps2[] = {2, 0};
    
    LinkListNode* poly1 = createTestPoly(coefs1, exps1, 2);
    LinkListNode* poly2 = createTestPoly(coefs2, exps2, 2);
    LinkListNode* result = addPoly(poly1, poly2);
    
    float expectedCoefs[] = {5.0, 3.0, 4.0, 2.0};
    int expectedExps[] = {0, 1, 2, 3};
    LinkListNode* expected = createTestPoly(expectedCoefs, expectedExps, 4);
    
    bool testResult = polyEqual(expected, result);
    printf("%s\n", testResult ? "通过" : "失败");
    if (!testResult) {
        printPolyComparison(expected, result);
    }
    allPassed &= testResult;
    
    destoryPolynomial(poly1);
    destoryPolynomial(poly2);
    destoryPolynomial(result);
    destoryPolynomial(expected);
    
    // 测试相同指数项的合并
    printf("  测试相同指数项的合并: ");
    float coefs3[] = {2.0, 3.0};
    int exps3[] = {3, 1};
    float coefs4[] = {4.0, -3.0};
    int exps4[] = {3, 1};
    
    poly1 = createTestPoly(coefs3, exps3, 2);
    poly2 = createTestPoly(coefs4, exps4, 2);
    result = addPoly(poly1, poly2);
    
    float expectedCoefs2[] = {0.0, 6.0};
    int expectedExps2[] = {1, 3};
    expected = createTestPoly(expectedCoefs2, expectedExps2, 2);
    
    testResult = polyEqual(expected, result);
    printf("%s\n", testResult ? "通过" : "失败");
    if (!testResult) {
        printPolyComparison(expected, result);
    }
    allPassed &= testResult;
    
    destoryPolynomial(poly1);
    destoryPolynomial(poly2);
    destoryPolynomial(result);
    destoryPolynomial(expected);
    
    // 测试一个多项式为空的情况
    printf("  测试一个多项式为空: ");
    float coefs5[] = {2.0, 3.0};
    int exps5[] = {3, 1};
    
    poly1 = createTestPoly(coefs5, exps5, 2);
    poly2 = createTestPoly(NULL, NULL, 0);
    result = addPoly(poly1, poly2);
    
    testResult = polyEqual(poly1, result);
    printf("%s\n", testResult ? "通过" : "失败");
    if (!testResult) {
        printPolyComparison(poly1, result);
    }
    allPassed &= testResult;
    
    destoryPolynomial(poly1);
    destoryPolynomial(poly2);
    destoryPolynomial(result);
    
    return allPassed;
}

// 测试边界情况
bool testEdgeCases() {
    printf("测试边界情况:\n");
    bool allPassed = true;
    
    // 测试系数为0的项
    printf("  测试系数为0的项: ");
    float coefs[] = {0.0, 3.0, 0.0};
    int exps[] = {3, 1, 0};
    LinkListNode* poly = createTestPoly(coefs, exps, 3);
    
    bool result = poly->next && fabs(poly->next->coef - 3.0) < 1e-6 && poly->next->exp == 1;
    result &= poly->next->next == NULL; // 系数为0的项应被忽略
    
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    destoryPolynomial(poly);
    
    // 测试大量项
    printf("  测试大量项: ");
    const int SIZE = 100;
    float* largeCoefs = (float*)malloc(SIZE * sizeof(float));
    int* largeExps = (int*)malloc(SIZE * sizeof(int));
    
    for (int i = 0; i < SIZE; i++) {
        largeCoefs[i] = (float)(i + 1);
        largeExps[i] = i;
    }
    
    poly = createTestPoly(largeCoefs, largeExps, SIZE);
    
    // 检查第一项和最后一项
    result = poly->next && fabs(poly->next->coef - 1.0) < 1e-6 && poly->next->exp == 0;
    LinkListNode* p = poly->next;
    for (int i = 0; i < SIZE-1; i++) {
        p = p->next;
    }
    result &= p && fabs(p->coef - 100.0) < 1e-6 && p->exp == 99;
    
    printf("%s\n", result ? "通过" : "失败");
    allPassed &= result;
    
    free(largeCoefs);
    free(largeExps);
    destoryPolynomial(poly);
    
    return allPassed;
}

// 运行所有测试
void runAllTests() {
    printf("============== 多项式实现测试 ==============\n");
    
    bool initTestPassed = testInitPolynomial();
    bool addTestPassed = testAddPoly();
    bool edgeTestPassed = testEdgeCases();
    
    printf("\n============== 测试结果汇总 ==============\n");
    printf("创建多项式测试: %s\n", initTestPassed ? "通过" : "失败");
    printf("多项式加法测试: %s\n", addTestPassed ? "通过" : "失败");
    printf("边界情况测试: %s\n", edgeTestPassed ? "通过" : "失败");
    printf("总体结果: %s\n", 
           (initTestPassed && addTestPassed && edgeTestPassed) 
           ? "全部通过" : "存在失败");
}
void test01(void) {
    LinkListNode* p1= initPolynomial();
    traversePolynomial(p1);
    LinkListNode* p2= initPolynomial();
    traversePolynomial(p2);
    LinkListNode* ans = addPoly(p1, p2);
    traversePolynomial(ans);

    destoryPolynomial(p1);
    destoryPolynomial(p2);
    destoryPolynomial(ans);
}

int main() {
    // test01();
    runAllTests();
    return 0;
}
/*
9 0
6 1
8 9
3 14
-1 -1

7 1
21 7
-8 9
-1 -1

ans=>9.0x^0+13.0x^1+21.0x^7+0.0x^9+3.0x^14
*/