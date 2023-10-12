#include <stdio.h>
#include <stdlib.h>

typedef struct IntArray {
    int lastIndex;
    int size;
    int* array;
} IntArray;

typedef struct PossibilitiesMap {
    int canBeStack;
    int canBeQueue;
} PossibilitiesMap;

void initialize(IntArray* array, int size) {
    array->size = size;
    array->array = (int*) malloc(size * sizeof(int));
    array->lastIndex = -1;
}

void add(IntArray* array, int value) {
    array->array[array->lastIndex + 1] = value;

    array->lastIndex = array->lastIndex + 1;
    array->size = array->size + 1;
}

void removeFirst(IntArray* array) {
    for (int i = 0; i <= array->lastIndex; i++) {
        array->array[i] = array->array[i+1];
    }

    array->lastIndex = array->lastIndex - 1;
    array->size = array->size - 1;
}

void removeLast(IntArray* array) {
    array->array[array->lastIndex] = 0;

    array->lastIndex = array->lastIndex - 1;
    array->size = array->size - 1;
}

void printCharArray(char array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", array[i]);
    }
}

void printIntArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

int main() {
    int numberOfCases;
    scanf("%d", &numberOfCases);

    int numbersOfOperations[numberOfCases];
    char** testCases = (char**) malloc(numberOfCases * sizeof(char*));
    for (int i = 0; i < numberOfCases; i++) {
        scanf("%d", &numbersOfOperations[i]);

        testCases[i] = (char*) malloc((numbersOfOperations[i] * 2)  * sizeof(char));
        for (int j = 0; j < numbersOfOperations[i] * 2; j++) {
            char temp;
            scanf("%c", &temp);

            if (temp == ' ') {
                j--;
            } else  {
                testCases[i][j] = temp;
            }
        }
    }

    for (int i = 0; i < numberOfCases; i++) {
        IntArray insertions;
        initialize(&insertions, numbersOfOperations[i]);
        IntArray deletions;
        initialize(&deletions, numbersOfOperations[i]);

        for (int j = 0; j < numbersOfOperations[i] * 2; j+=2) {
            if (testCases[i][j] == 'i') {
                add(&insertions, testCases[i][j+1] - '0');
            } else {
                add(&deletions, testCases[i][j+1] - '0');
            }
        }

        PossibilitiesMap possibilitiesMap = { 1, 1 };
        for (int j = 0; j <= deletions.lastIndex; j++) {
            if (deletions.array[j] != insertions.array[j]) {
                possibilitiesMap.canBeQueue = 0;
            }

            if (deletions.array[j] != insertions.array[insertions.lastIndex - j]) {
                possibilitiesMap.canBeStack = 0;
            }

            if (possibilitiesMap.canBeStack == 0 && possibilitiesMap.canBeQueue == 0) {
                break;
            }
        }

        if (possibilitiesMap.canBeQueue == 1 && possibilitiesMap.canBeStack == 1) {
            printf("indefinido");
        } else if (possibilitiesMap.canBeQueue == 1) {
            printf("fila");
        } else if (possibilitiesMap.canBeStack == 1) {
            printf("pilha");
        } else {
            printf("impossivel");
        }
        printf("\n");
    }

    return 0;
}