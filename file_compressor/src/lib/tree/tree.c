#include <stdlib.h>

#include "tree.h"

TreeNode* createTreeNode(byte c, int frequency, TreeNode* left, TreeNode* right) {
    TreeNode* novo = (TreeNode*) malloc(sizeof(TreeNode));
    if (novo == NULL) return NULL;

    novo->c = c;
    novo->frequency = frequency;
    novo->left = left;
    novo->right = right;

    return novo;
}
