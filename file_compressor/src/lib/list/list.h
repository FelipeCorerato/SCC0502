#ifndef SCC0502_LIST_H
#define SCC0502_LIST_H

#include "../tree/tree.h"

typedef struct ListNode {
    TreeNode* n;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* head;
    int count;
} List;

ListNode* createListNode(TreeNode* treeNode);
void insertList(ListNode* node, List* list);
TreeNode* popMinList(List* list);

#endif //SCC0502_LIST_H
