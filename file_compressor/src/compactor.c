#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./lib/huffman/huffman.h"

char* getInputFilename(char* filePath) {
    char* filename = strrchr(filePath, '/');
    if (filename == NULL) {
        filename = strrchr(filePath, '\\');
    }

    return (filename != NULL) ? filename + 1 : filePath;
}

char* getFilenameExtension(char* filename) {
    char* extension = strrchr(filename, '.');

    if (extension != NULL && extension != filename + strlen(filename) - 1) {
        return extension;
    }

    return "";
}

char* getTempFilename(char* filename) {
    char* tempFilename = (char*) malloc(FILENAME_MAX);
    char* extension = getFilenameExtension(filename);

    strcat(tempFilename, "temp_filename_");

    time_t timestamp = time(NULL);
    struct tm *tm_info = localtime(&timestamp);
    char timestampStr[20];
    strftime(timestampStr, sizeof(timestampStr), "%Y%m%d%H%M%S", tm_info);

    strcat(tempFilename, timestampStr);
    strcat(tempFilename, extension);

    return tempFilename;
}

char* getOutputFilename(char* filePath) {
    char* slash = strrchr(filePath, '/');
    char* filenameStartInPath = slash ? slash + 1 : filePath;
    char* dot = strrchr(filenameStartInPath, '.');

    if (dot) {
        size_t filenameSize = dot - filenameStartInPath;
        char* filename = malloc(filenameSize + 1);

        strncpy(filename, filenameStartInPath, filenameSize);
        filename[filenameSize] = '\0';
        strcat(filename, ".comp");

        return filename;
    } else {
        char* filename = malloc(strlen(filenameStartInPath) + 6);
        strcpy(filename, filenameStartInPath);
        strcat(filename, ".comp");

        return filename;
    }
}

int getCode(TreeNode* n, byte c, char* buffer, int size) {
    if (!(n->left || n->right) && n->c == c) {
        buffer[size] = '\0';
        return 1;
    }

    int found = 0;

    if (n->left) {
        buffer[size] = '0';
        found = getCode(n->left, c, buffer, size + 1);
    }

    if (!found && n->right) {
        buffer[size] = '1';
        found = getCode(n->right, c, buffer, size + 1);
    }

    if (!found) {
        buffer[size] = '\0';
    }

    return found;
}

void fileError() {
    printf("Arquivo nao encontrado\n");
    exit(0);
}

void addFilenameInFile(char* inputFilePath) {
    FILE* inputFile = fopen(inputFilePath, "r+");

    char* inputFilename = getInputFilename(inputFilePath);
    char* tempFilename = getTempFilename(inputFilename);

    FILE* tempFile = fopen(tempFilename, "w");
    fprintf(tempFile, "%s\n", inputFilename);

    char line[FILENAME_MAX];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        fprintf(tempFile, "%s", line);
    }

    fclose(inputFile);
    fclose(tempFile);

    remove(inputFilePath);
    rename(tempFilename, inputFilePath);
}

void removeFilenameFromFile(char* inputFilePath) {
    FILE* inputFile = fopen(inputFilePath, "r");

    char* tempFilename = getTempFilename(getInputFilename(inputFilePath));
    FILE* tempFile = fopen(tempFilename, "w");

    int c;
    while ((c = fgetc(inputFile)) != EOF && c != '\n') {  }

    while ((c = fgetc(inputFile)) != EOF) {
        fputc(c, tempFile);
    }

    fclose(inputFile);
    fclose(tempFile);

    remove(inputFilePath);
    rename(tempFilename, inputFilePath);
}

void compressFile(char* inputFilePath) {
    addFilenameInFile(inputFilePath);

    char* outputFilename = getOutputFilename(inputFilePath);

    unsigned bytesList[256] = {0};

    FILE* inputFile = fopen(inputFilePath, "rb");
    FILE* outputFile = fopen(outputFilename, "wb");

    if (!inputFile || !outputFile) {
        fileError();
    }

    getByteFrequency(inputFile, bytesList);

    TreeNode* root = buildHuffmanTree(bytesList);

    fwrite(bytesList, 256, sizeof(bytesList[0]), outputFile);

    fseek(outputFile, sizeof(unsigned int), SEEK_CUR);

    byte c;
    unsigned size = 0;
    byte aux = 0;

    while (fread(&c, 1, 1, inputFile) >= 1) {
        char buffer[1024] = {0};

        getCode(root, c, buffer, 0);

        for (char* i = buffer; *i; i++) {
            if (*i == '1') {
                aux = aux | (1 << (size % 8));
            }

            size++;

            if (size % 8 == 0) {
                fwrite(&aux, 1, 1, outputFile);
                aux = 0;
            }
        }
    }

    fwrite(&aux, 1, 1, outputFile);

    fseek(outputFile, 256 * sizeof(unsigned int), SEEK_SET);

    fwrite(&size, 1, sizeof(unsigned), outputFile);

    fseek(inputFile, 0L, SEEK_END);
    fseek(outputFile, 0L, SEEK_END);

    freeHuffmanTree(root);

    fclose(inputFile);
    fclose(outputFile);

    removeFilenameFromFile(inputFilePath);
}

int main(int _, char *argv[]) {
    compressFile(argv[1]);
}
