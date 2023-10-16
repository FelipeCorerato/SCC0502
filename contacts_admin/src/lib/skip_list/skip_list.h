#ifndef SCC0502_SKIP_LIST_H
#define SCC0502_SKIP_LIST_H

#define SKIP_LIST_MAX_LEVEL 6

typedef struct Node {
    char key[11];
    char* value;
    struct Node** forward;
} Node;

typedef struct SkipList {
    int level;
    int size;
    Node* header;
} SkipList;

void initializeSkipList(SkipList* list);
Node* search(SkipList* list, char* key);
int exists(SkipList* list, char* key);
static int generateRandomLevel();
void insert(SkipList* list, char* key, char* value);
static void freeNode(Node* x);
void delete(SkipList* list, char* key);
void printList(SkipList* list);

#endif
