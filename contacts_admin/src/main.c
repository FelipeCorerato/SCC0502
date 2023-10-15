#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lib/skip_list/skip_list.h"

int main() {
    char operation;

    SkipList list;
    initializeSkipList(&list);

    for (;;) {
        scanf("%c", &operation);

        if (operation == '0') {
            break;
        }

        int name;
        char* number;

        switch (operation) {
            case 'I':
                scanf("%d ", &name);
                number = (char*) malloc(9 * sizeof(char));
                fgets(number, 10, stdin);
                number[strcspn(number, "\n")] = '\0';

                if (exists(&list, name)) {
                    printf("Contatinho ja inserido\n");
                    break;
                }

                insert(&list, name, number);
            break;
            case 'P':
                scanf("%d", &name);

                Node* n = search(&list, name);
                if (n == NULL) {
                    printf("Operacao invalida: contatinho nao encontrado\n");
                    break;
                }

                printf("Contatinho encontrado: telefone %s\n", n->value);
            break;
            case 'A':
                scanf("%d ", &name);
                number = (char*) malloc(9 * sizeof(char));
                fgets(number, 10, stdin);
                number[strcspn(number, "\n")] = '\0';

                if (!exists(&list, name)) {
                    printf("Operacao invalida: contatinho nao encontrado\n");
                    break;
                }

                insert(&list, name, number);
            break;
            case 'R':
                scanf("%d", &name);

                if (!exists(&list, name)) {
                    printf("Operacao invalida: contatinho nao encontrado\n");
                    break;
                }

                delete(&list, name);
            break;
            default:
                insert(&list, 123, "felipe");
                insert(&list, 456, "catarina");
                printList(&list);

                insert(&list, 456, "hannah");
                printList(&list);
            break;
        }
    }

    return 0;
}