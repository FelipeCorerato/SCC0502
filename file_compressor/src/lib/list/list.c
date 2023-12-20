#include <stdlib.h>

#include "list.h"

ListNode* createListNode(TreeNode* treeNode) {
    ListNode* novo = (ListNode*) malloc(sizeof(ListNode));
    if (novo == NULL) return NULL;

    novo->n = treeNode;
    novo->next = NULL;

    return novo;
}

void insertList(ListNode* node, List* list) {
    if (!list->head) {
        list->head = node;
    } else if (node->n->frequency < list->head->n->frequency) {
        node->next = list->head;
        list->head = node;
    } else {
        ListNode* aux = list->head->next;
        ListNode* aux2 = list->head;

        while (aux && aux->n->frequency <= node->n->frequency) {
            aux2 = aux;
            aux = aux2->next;
        }

        aux2->next = node;
        node->next = aux;
    }

    list->count++;
}

TreeNode* popMinList(List* list) {
    ListNode* aux = list->head;
    TreeNode* aux2 = aux->n;

    list->head = aux->next;

    free(aux);
    aux = NULL;

    list->count--;

    return aux2;
}
