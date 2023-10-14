#include <stdio.h>

#include "./lib/skip_list/skip_list.h"

typedef struct Contact {
    char name [10];
    char number [9];
} Contact;

int main() {
    char operation;

    int arr[] = { 3, 6, 9, 2, 11, 1, 4 };
    SkipList list;
    initializeSkipList(&list);

    printf("Insert:--------------------\n");
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        insert(&list, arr[i], arr[i]);
    }
    dump(&list);

    printf("Search:--------------------\n");
    int keys[] = { 3, 4, 7, 10, 111 };

    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        Node* x = search(&list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not found\n", keys[i]);
        }
    }

    printf("Search:--------------------\n");
    delete(&list, 3);
    delete(&list, 9);
    dump(&list);

//    for (;;) {
//        scanf("%c", &operation);
//
//        if (operation == '0') {
//            break;
//        }
//
//        Contact contact;
//        switch (operation) {
//            case 'I':
//                scanf("%s", &contact.name);
//                scanf("%s", &contact.number);
//
//                printf("name: %s.\n", contact.name);
//                printf("number: %s.\n", contact.number);
//            case 'P':
//                scanf("%s", &contact.name);
//                printf("name: %s.\n", contact.name);
//            case 'A':
//                scanf("%s", &contact.name);
//                scanf("%s", &contact.number);
//
//                printf("name: %s.\n", contact.name);
//                printf("number: %s.\n", contact.number);
//            case 'R':
//                scanf("%s", &contact.name);
//                printf("name: %s.\n", contact.name);
//        }
//    }

    return 0;
}