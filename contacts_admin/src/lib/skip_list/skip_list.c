#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./skip_list.h"

void initializeSkipList(SkipList* list) {
    Node* header = (Node*) malloc(sizeof(Node));

    list->header = header;
    header->key = INT_MAX;

    header->forward = (Node**) malloc((SKIP_LIST_MAX_LEVEL + 1) * sizeof(Node*));
    for (int i = 0; i <= SKIP_LIST_MAX_LEVEL; i++) {
        header->forward[i] = list->header;
    }

    list->level = 1;
    list->size = 0;
}

Node* search(SkipList* list, int key) {
    Node* x = list->header;

    for (int i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }

    if (x->forward[1]->key == key) {
        return x->forward[1];
    } else {
        return NULL;
    }
}

int exists(SkipList* list, int key) {
    Node* n = search(list, key);
    return n != NULL;
}

static int generateRandomLevel() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < SKIP_LIST_MAX_LEVEL) {
        level++;
    }

    return level;
}

void insert(SkipList* list, int key, char* value) {
    Node* update[SKIP_LIST_MAX_LEVEL + 1];
    Node* x = list->header;
    int level;

    for (int i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }

        update[i] = x;
    }
    x = x->forward[1];

    if (key == x->key) {
        x->value = value;
        return;
    } else {
        level = generateRandomLevel();

        if (level > list->level) {
            for (int i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }

            list->level = level;
        }

        x = (Node*) malloc(sizeof(Node));
        x->key = key;
        x->value = value;
        x->forward = (Node**) malloc(sizeof(Node*) * (level + 1));

        for (int i = 1; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }

        list->size = list->size + 1;
    }
}

static void freeNode(Node* x) {
    if (x) {
        free(x->forward);
        free(x);
    }
}

void delete(SkipList* list, int key) {
    Node* update[SKIP_LIST_MAX_LEVEL + 1];
    Node* x = list->header;

    for (int i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }

        update[i] = x;
    }

    x = x->forward[1];

    if (x->key == key) {
        for (int i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x) {
                break;
            }

            update[i]->forward[i] = x->forward[i];
        }

        freeNode(x);

        while (list->level > 1 && list->header->forward[list->level] == list->header) {
            list->level--;
        }

        list->size = list->size - 1;
    }
}

void printList(SkipList* list) {
    Node* x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%s]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }

    printf("NIL\n");
}