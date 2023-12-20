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

    if (inputFile != NULL) {
        // Move o cursor para o início do arquivo
        fseek(inputFile, 0, SEEK_SET);

        // Escreve na primeira linha do arquivo
        fprintf(inputFile, "Nova primeira linha\n");

        // Fecha o arquivo
        fclose(inputFile);

        printf("Conteúdo do arquivo foi atualizado.\n");
    } else {
        printf("Erro ao abrir o arquivo.\n");
    }
}

void removeFilenameFromFile(char* inputFilePath) {
    char tempFilename[FILENAME_MAX];
    tmpnam(tempFilename);

    FILE* inputFile = fopen(inputFilePath, "r");

    if (inputFile != NULL) {
        FILE* tempFile = fopen(tempFilename, "w");

        if (tempFile != NULL) {
            int c;
            while ((c = fgetc(inputFile)) != EOF && c != '\n') {  }

            while ((c = fgetc(inputFile)) != EOF) {
                fputc(c, tempFile);
            }

            fclose(inputFile);
            fclose(tempFile);

            remove(inputFilePath);
            rename(tempFilename, inputFilePath);

            printf("Primeira linha removida com sucesso.\n");
        } else {
            printf("Erro ao abrir o arquivo temporário.\n");
            fclose(inputFile);
        }
    } else {
        printf("Erro ao abrir o arquivo original.\n");
    }
}

void compressFile(char* inputFilePath) {
    clock_t start, finish;
    start = clock();

//    addFilenameInFile(inputFilePath);

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

    finish = clock();
    double spentTime = (double)(finish - start) / CLOCKS_PER_SEC;

    fseek(inputFile, 0L, SEEK_END);
    double inputFileSize = ftell(inputFile);

    fseek(outputFile, 0L, SEEK_END);
    double outputFileSize = ftell(outputFile);

    freeHuffmanTree(root);

    printf("Arquivo de entrada: %s (%g bytes)\nArquivo de saida: %s (%g bytes)\nTempo gasto: %gs\n", inputFilePath, inputFileSize / 1000, outputFilename, outputFileSize / 1000, spentTime);
    printf("Taxa de compressao: %d%%\n", (int) ((100 * outputFileSize) / inputFileSize));

//    char tempFilename[256];
//    char* inputFilename = getInputFilename(inputFilePath);
//    snprintf(tempFilename, sizeof(tempFilename), "%.*s-temp%s", (int)(strrchr(inputFilename, '.') - inputFilename), inputFilename, strrchr(inputFilename, '.'));
//    FILE *tempFile = fopen(tempFilename, "w");

    fclose(inputFile);
    fclose(outputFile);

    removeFilenameFromFile(inputFilePath);
}

int main(int _, char *argv[]) {
    compressFile(argv[1]);
}
