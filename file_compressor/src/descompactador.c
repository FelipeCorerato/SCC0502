#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./lib/huffman/huffman.h"

void fileError() {
    printf("Arquivo nao encontrado\n");
    exit(0);
}

void decompressFile(const char* inputFilename, const char* outputFilename) {
    clock_t start, finish;
    start = clock();

    unsigned bytesList[256] = {0};

    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile) {
        fileError();
    }

    fread(bytesList, 256, sizeof(bytesList[0]), inputFile);

    TreeNode* root = buildHuffmanTree(bytesList);

    unsigned size;
    fread(&size, 1, sizeof(size), inputFile);

    unsigned pos = 0;
    byte aux = 0;

    while (pos < size) {
        TreeNode* currentNode = root;

        while (currentNode->left || currentNode->right) {
            currentNode = generateBit(inputFile, pos++, &aux) ? currentNode->right : currentNode->left;
        }

        fwrite(&(currentNode->c), 1, 1, outputFile);
    }

    freeHuffmanTree(root);

    finish = clock();
    double spentTime = (double)(finish - start) / CLOCKS_PER_SEC;

    fseek(inputFile, 0L, SEEK_END);
    double inputFileSize = ftell(inputFile);

    fseek(outputFile, 0L, SEEK_END);
    double outputFileSize = ftell(outputFile);

    printf("Arquivo de entrada: %s (%g bytes)\nArquivo de saida: %s (%g bytes)\nTempo gasto: %gs\n", inputFilename, inputFileSize / 1000, outputFilename, outputFileSize / 1000, spentTime);
    printf("Taxa de descompressao: %d%%\n", (int)((100 * outputFileSize) / inputFileSize));

    fclose(inputFile);
    fclose(outputFile);
}

int main(int _, char *argv[]) {
    decompressFile(argv[1], "input.c");
}
