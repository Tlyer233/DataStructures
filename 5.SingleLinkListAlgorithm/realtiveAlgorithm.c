#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SingleLinkListNode {
    int data;
    struct SingleLinkListNode *next;
} Node;
// 全都带有头节点!!!
void traverseLinkList(Node *list) {
    Node *pmove = list->next;
    while (pmove) {
        printf("%d->", pmove->data);
        pmove = pmove->next;
    }
    puts("NULL");
}

// 1.创建有序链表
Node *createSortedLinkList(void) {
    Node *phead = (Node *)malloc(sizeof(Node));
    phead->next = NULL;
    int input;

    while (scanf("%d", &input) == 1 && input != -1) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = input;
        newNode->next = NULL;
        // 找到 xNode->next->data>input;
        Node *pmove = phead;
        while (pmove->next != NULL && pmove->next->data <= input) { pmove = pmove->next; }
        //  插入进去
        newNode->next = pmove->next;
        pmove->next = newNode;
    }
    return phead;
}

// 2.翻转链表
void reverseLinkList(Node *phead) {
    if (phead->next == NULL || phead->next->next == NULL)
        return;  // 只有一个元素 or 没有元素, 就直接返回

    Node *pre = NULL;
    Node *cur = phead->next;
    while (cur) {
        Node *temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    phead->next = pre;
}

// 3.链表归并
Node *mergeLinkList(Node *phead1, Node *phead2) {
    Node *newHead = (Node *)malloc(sizeof(Node));
    newHead->next = NULL;
    Node *pmove = newHead;

    Node *l = phead1->next, *r = phead2->next;  // 左右指针
    while (l && r) {
        if (l->data < r->data)
            pmove->next = l, l = l->next;
        else
            pmove->next = r, r = r->next;
        pmove = pmove->next;
    }
    while (l) pmove->next = l, l = l->next, pmove = pmove->next;
    while (r) pmove->next = r, r = r->next, pmove = pmove->next;
    return newHead;
}

// 4.链表冒泡
void bubbleLinkList(Node *list) {
    for (Node *i = list->next; i; i = i->next) {
        for (Node *j = list->next; j; j = j->next) {
            if (j->next && j->data > j->next->data) {
                j->data = j->data ^ j->next->data;
                j->next->data = j->data ^ j->next->data;
                j->data = j->data ^ j->next->data;
            }
        }
    }
}

void test01() {
    Node *list1 = createSortedLinkList();
    traverseLinkList(list1);

    Node *list2 = createSortedLinkList();
    traverseLinkList(list2);

    Node *list3 = mergeLinkList(list1, list2);
    traverseLinkList(list3);

    reverseLinkList(list3);
    traverseLinkList(list3);
    bubbleLinkList(list3);
    traverseLinkList(list3);
}

int main() {
    test01();
    return 0;
}

// 1h:15min