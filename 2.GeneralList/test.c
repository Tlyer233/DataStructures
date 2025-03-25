#include "generalList.h"

void test01(void) {
    // A = (a,(b,c),y)
    // B = (((a,b,(#),c),d),e,((f),g))
    GeneralListNode *glist = (GeneralListNode *)malloc(sizeof(GeneralListNode));
    initGeneralList(&glist);

    traverseGeneralList(glist);
    printf("\n");
    printf("Length: %d\n", getLength(glist));
    printf("Depth: %d\n", getDepth(glist));
    GeneralListNode *ghead = getHead(glist);

    printf("Head: ");
    if (ghead == NULL)  // 不存在
        printf("不存在");
    else if (ghead->tag == 0)  //  是一个元素(原子)
        printf("%c", ghead->data);
    else  // 是一个字表
        traverseGeneralList(ghead);

    printf("\n");

    GeneralListNode *gtail = getTail(glist);
    printf("Tail: ");
    if (gtail == NULL)  // 不存在
        printf("不存在");
    else
        traverseGeneralList(gtail);
    printf("\n");
}

void linkModifyTest() {
    GeneralListNode *glist = (GeneralListNode *)malloc(sizeof(GeneralListNode));
    initGeneralList(&glist); // (((a,b,(#),c),d),e,((f),g))
    traverseGeneralList(glist);
    puts("");

    // ((a,b,(#),c),d)
    // (a,b,(#),c)
    // (b,(#),c)
    // ((#),c)
    // ()
    // GeneralListNode* ans = getTail(getTail(getHead(getHead(glist))));
    // 不存在该表
    GeneralListNode* ans = getHead(getHead(getTail(getTail(getHead(getHead(glist))))));
    traverseGeneralList(ans);
}

int main() {
    // test01();
    linkModifyTest();
    return 0;
}

// init+traverse=45min