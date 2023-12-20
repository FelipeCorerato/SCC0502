#ifndef SCC0502_HUFFMAN_H
#define SCC0502_HUFFMAN_H

#include "../list/list.h"

TreeNode* buildHuffmanTree(unsigned* bytesList);
void freeHuffmanTree(TreeNode* treeNode);

#endif //SCC0502_HUFFMAN_H
