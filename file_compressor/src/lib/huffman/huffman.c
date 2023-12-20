#include <stdlib.h>

#include "huffman.h"

TreeNode* buildHuffmanTree(unsigned* bytesList) {
    List list = {NULL, 0};

    for (int i = 0; i < 256; i++) {
        if (bytesList[i]) {
            insertList(createListNode(createTreeNode(i, bytesList[i], NULL, NULL)), &list);
        }
    }

    while (list.count > 1) {
        TreeNode* leftNode = popMinList(&list);
        TreeNode* rightNode = popMinList(&list);

        TreeNode* soma = createTreeNode('#',leftNode->frequency + rightNode->frequency, leftNode, rightNode);
        insertList(createListNode(soma), &list);
    }

    return popMinList(&list);
}

void freeHuffmanTree(TreeNode* treeNode) {
    if (!treeNode) return;

    TreeNode* left = treeNode->left;
    TreeNode* right = treeNode->right;

    free(treeNode);
    freeHuffmanTree(left);
    freeHuffmanTree(right);
}
