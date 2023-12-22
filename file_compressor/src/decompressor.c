#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./lib/huffman/huffman.h"

char* getTempFilename(char* prefix) {
    char* tempFilename = (char*) malloc(FILENAME_MAX);

    strcat(tempFilename, prefix);
    strcat(tempFilename, "_temp_filename_");

    time_t timestamp = time(NULL);
    struct tm *tm_info = localtime(&timestamp);
    char timestampStr[20];
    strftime(timestampStr, sizeof(timestampStr), "%Y%m%d%H%M%S", tm_info);

    strcat(tempFilename, timestampStr);
    strcat(tempFilename, ".txt");

    return tempFilename;
}

void fileError() {
    printf("Arquivo nao encontrado\n");
    exit(0);
}

char* getOutputFilename(const char* filename) {
    FILE* file = fopen(filename, "r");

    char line[1000];
    if (fgets(line, sizeof(line), file) != NULL) {
        char* lineBreaker = strchr(line, '\n');
        if (lineBreaker != NULL) {
            *lineBreaker = '\0';
        }

        char* firstLine = strdup(line);

        fclose(file);

        return firstLine;
    }

    fclose(file);

    return NULL;
}

void deleteFirstLine(const char* filename) {
    FILE* originalFile = fopen(filename, "r");

    char* tempFilename = getTempFilename("deleteFirstLine");
    FILE* tempFile = fopen(tempFilename, "w");

    int character;
    while ((character = fgetc(originalFile)) != EOF && character != '\n');

    while ((character = fgetc(originalFile)) != EOF) {
        fputc(character, tempFile);
    }

    fclose(originalFile);
    fclose(tempFile);

    remove(filename);
    rename(tempFilename, filename);
}

void decompressFile(const char* inputFilename) {
    unsigned bytesList[256] = {0};

    char* tempFilename = getTempFilename("decompressFile");

    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(tempFilename, "wb");

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

    fseek(inputFile, 0L, SEEK_END);
    fseek(outputFile, 0L, SEEK_END);

    char* outputFilename = getOutputFilename(tempFilename);

    fclose(inputFile);
    fclose(outputFile);

    deleteFirstLine(tempFilename);
    rename(tempFilename, outputFilename);
}

int main(int _, char *argv[]) {
    decompressFile(argv[1]);
}
