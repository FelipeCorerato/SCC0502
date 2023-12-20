#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef unsigned char byte;

typedef struct TreeNode {
    int frequency;
    byte c;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct ListNode {
    TreeNode* n;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* head;
    int count;
} List;

ListNode* createListNode(TreeNode* treeNode) {
    ListNode* novo = (ListNode*) malloc(sizeof(ListNode));
    if (novo == NULL) return NULL;

    novo->n = treeNode;
    novo->next = NULL;

    return novo;
}

TreeNode* createTreeNode(byte c, int frequency, TreeNode* left, TreeNode* right) {
    TreeNode* novo = (TreeNode*) malloc(sizeof(TreeNode));
    if (novo == NULL) return NULL;

    novo->c = c;
    novo->frequency = frequency;
    novo->left = left;
    novo->right = right;

    return novo;
}

void insertList(ListNode* node, List* list) {
    if (!list->head) {
        list->head = node;
    } else if (node->n->frequency < list->head->n->frequency) {
        node->next = list->head;
        list->head = node;
    } else {
        ListNode* aux = list->head->next;
        ListNode* aux2 = list->head;

        while (aux && aux->n->frequency <= node->n->frequency) {
            aux2 = aux;
            aux = aux2->next;
        }

        aux2->next = node;
        node->next = aux;
    }

    list->count++;
}

TreeNode* popMinList(List* list) {
    ListNode* aux = list->head;
    TreeNode* aux2 = aux->n;

    list->head = aux->next;

    free(aux);
    aux = NULL;

    list->count--;

    return aux2;
}

void getByteFrequency(FILE* stream, unsigned int* bytesList) {
    byte c;

    while (fread(&c, 1, 1, stream) >= 1) {
        bytesList[(byte)c]++;
    }

    rewind(stream);
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

int generateBit(FILE* stream, int position, byte* aux) {
    if (position % 8 == 0) {
        fread(aux, 1, 1, stream);
    }

    return !!(*aux & 1 << position % 8);
}

void fileError() {
    printf("Arquivo nao encontrado\n");
    exit(0);
}

void compressFile(const char* inputFilename, const char* outputFilename) {
    clock_t start, finish;
    start = clock();

    unsigned bytesList[256] = {0};

    FILE* inputFile = fopen(inputFilename, "rb");
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

    printf("Arquivo de entrada: %s (%g bytes)\nArquivo de saida: %s (%g bytes)\nTempo gasto: %gs\n", inputFilename, inputFileSize / 1000, outputFilename, outputFileSize / 1000, spentTime);
    printf("Taxa de compressao: %d%%\n", (int) ((100 * outputFileSize) / inputFileSize));

    fclose(inputFile);
    fclose(outputFile);
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

void instrucoes() {
    printf("Uso: main [OPCAO] [ARQUIVO] [ARQUIVO]\n\n");
    printf("Opcoes:\n");
    printf("\t-c\t\tComprime\n");
    printf("\tExemplo: \t./main -c comprima.isso nisso.pd\n");
    printf("\n\t-x\t\tDescomprime\n");
    printf("\tExemplo: \t./main -x descomprima-isso.pd nisso.extensao\n");
    printf("\n\t-h, --help\tInformacoes de ajuda\n");
}

int main(int argc, char *argv[]) {
    if (argc < 4 && strcmp("-h", argv[1]) != 0 && strcmp("--help", argv[1]) != 0) {
        printf("Erro uso inadequado do programa.\n\n");

        instrucoes();

        return 0;
    }

    if (strcmp("-c", argv[1]) == 0) {
        if (strstr(argv[3], ".pd")) {
            compressFile(argv[2], argv[3]);
        } else {
            printf("O arquivo resultante da compressao deve ter a extensao '.pd'.\n");
            printf("Exemplo: \n\t./main -c comprima.isso nisso.pd\n");

            return 0;
        }
    } else if (strcmp("-x", argv[1]) == 0) {
        if (strstr(argv[2], ".pd")) {
            decompressFile(argv[2], argv[3]);
        } else {
            printf("O arquivo a ser descomprimido deve ter a extensao '.pd'.\n");
            printf("Exemplo: \n\t./main -x descomprime.pd nisso.extensao\n");

            return 0;
        }
    } else if (strcmp("-h", argv[1]) == 0 || strcmp("--help", argv[1]) == 0) {
        instrucoes();
        return 0;
    } else {
        instrucoes();
        return 0;
    }

    return 0;
}
