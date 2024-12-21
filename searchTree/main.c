#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

void printMenu() {
    printf("\nКоманды:\n");
    printf("1 - Добавить элемент\n");
    printf("2 - Получить значение по ключу\n");
    printf("3 - Проверить наличие ключа\n");
    printf("4 - Удалить элемент\n");
    printf("5 - Выйти\n");
}

int main() {
    NodeTree* tree = createTree();

    printMenu();
    int command = 0;
    while (true) {
        printf("\nВведите команду: ");
        if (scanf("%d", &command) != 1) {
            printf("Ошибка ввода\n");
            break;
        }

        if (command == 1) {
            int key;
            char value[100];
            printf("Введите ключ (int): ");
            scanf("%d", &key);
            printf("Введите значение (строка): ");
            scanf("%s", value);
            tree = addElement(value, key, tree);
            printf("Элемент добавлен\n");

        } else if (command == 2) {
            int key;
            printf("Введите ключ для поиска: ");
            scanf("%d", &key);
            char* result = getValueKey(key, tree);
            if (result != NULL) {
                printf("Значение для ключа %d: %s\n", key, result);
            } else {
                printf("Ключ %d не найден\n", key);
            }

        } else if (command == 3) {
            int key;
            printf("Введите ключ для проверки: ");
            scanf("%d", &key);
            if (isHaveKey(key, tree)) {
                printf("Ключ %d найден\n", key);
            } else {
                printf("Ключ %d отсутствует в словаре\n", key);
            }

        } else if (command == 4) {
            int key;
            printf("Введите ключ для удаления: ");
            scanf("%d", &key);
            tree = deleteElement(key, tree);
            printf("Ключ %d удален\n", key);

        } else if (command == 5) {
            freeTree(tree);
            printf("Завершение работы программы\n");
            break;

        } else {
            printf("Неизвестная команда. Попробуйте снова\n");
        }
    }

    return 0;
}