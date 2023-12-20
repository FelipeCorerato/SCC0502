#ifndef SCC0502_TREE_H
#define SCC0502_TREE_H

#include "../byte/byte.h"

typedef struct TreeNode {
    int frequency;
    byte c;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createTreeNode(byte c, int frequency, TreeNode* left, TreeNode* right);

#endif //SCC0502_TREE_H
