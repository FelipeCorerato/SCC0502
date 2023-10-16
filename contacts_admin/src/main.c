#include <stdio.h>
#include <string.h>

#include "./lib/skip_list/skip_list.h"

int main() {
    char operation;

    SkipList list;
    initializeSkipList(&list);

    for (;;) {
        scanf(" %c", &operation);

        if (operation == '0') {
            break;
        }

        char name[11];
        char number[10];

        switch (operation) {
            case 'I':
                scanf("%s %s", name, number);

                if (exists(&list, name)) {
                    printf("Contatinho ja inserido\n");
                    break;
                }

                insert(&list, name, number);
            break;
            case 'P':
                scanf("%s", name);

                Node* n = search(&list, name);
                if (n == NULL) {
                    printf("Contatinho nao encontrado\n");
                    break;
                }

                printf("Contatinho encontrado: telefone %s\n", n->value);
            break;
            case 'A':
                scanf("%s %s", name, number);

                if (!exists(&list, name)) {
                    printf("Operacao invalida: contatinho nao encontrado\n");
                    break;
                }

                insert(&list, name, number);
            break;
            case 'R':
                scanf("%s", name);

                if (!exists(&list, name)) {
                    printf("Operacao invalida: contatinho nao encontrado\n");
                    break;
                }

                delete(&list, name);
            break;
            default: break;
        }
    }

    return 0;
}