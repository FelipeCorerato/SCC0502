#include <stdio.h>

#include "./lib/stack/stack.h"
#include "./lib/queue/queue.h"

struct PossibilitiesMap {
    int canBeStack;
    int canBeQueue;
};

int main() {
    int numberOfCases;
    scanf("%d", &numberOfCases);

    int numbersOfOperations[numberOfCases];
    for (int i = 0; i < numberOfCases; i++) {
        scanf("%d", &numbersOfOperations[i]);

        Stack stack;
        Queue queue;

        initializeStack(&stack, numbersOfOperations[i]);
        initializeQueue(&queue, numbersOfOperations[i]);

        struct PossibilitiesMap possibilitiesMap = { 1, 1 };

        for (int j = 0; j < numbersOfOperations[i]; j++) {
            char temp;
            scanf("%c", &temp);

            if (temp == ' ') {
                j--;
                continue;
            }

            int value;
            scanf("%d", &value);

            if (temp == 'i') {
                push(&stack, value);
                enqueue(&queue, value);
            } else {
                int stackValue = pop(&stack);
                int queueValue = dequeue(&queue);

                if (stackValue != value) {
                    possibilitiesMap.canBeStack = 0;
                }
                if (queueValue != value) {
                    possibilitiesMap.canBeQueue = 0;
                }
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