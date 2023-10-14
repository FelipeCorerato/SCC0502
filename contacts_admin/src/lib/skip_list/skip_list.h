#ifndef SCC0502_SKIP_LIST_H
#define SCC0502_SKIP_LIST_H

#define SKIP_LIST_MAX_LEVEL 6

typedef struct Node {
    int key;
    int value;
    struct Node** forward;
} Node;

typedef struct SkipList {
    int level;
    int size;
    Node* header;
} SkipList;

void initializeSkipList(SkipList* list);
Node* search(SkipList* list, int key);
static int generateRandomLevel();
void insert(SkipList* list, int key, int value);
static void freeNode(Node* x);
void delete(SkipList* list, int key);
void dump(SkipList* list);

#endif
