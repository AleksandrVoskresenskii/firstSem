#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Структура узла связного списка, содержащая значение int
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Структура списка, содержащая указатель на голову списка
typedef struct List {
    ListNode* head;
} List;

// Функция инициализации списка
void initList(List* list) {
    list->head = NULL;
}

// Функция освобождения памяти всего списка
void freeList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// Функция печати всех значений в списке
void printList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        printf("Значение: %d\n", current->data);
        current = current->next;
    }
}

// Функция добавления элемента в отсортированный список
void addSorted(List* list, int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = value;

    // Если список пустой или элемент должен быть добавлен в начало
    if (list->head == NULL || list->head->data >= value) {
        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        // Найти место для вставки
        ListNode* current = list->head;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }

        // Вставить новый элемент
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Функция удаления элемента по значению
void removeValue(List* list, int value) {
    if (list->head == NULL) {
        printf("Список пуст\n");
        return;
    }

    // Если элемент, который нужно удалить, находится в начале списка
    if (list->head->data == value) {
        ListNode* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    // Поиск элемента в середине или в конце списка
    ListNode* current = list->head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    // Если элемент найден
    if (current->next != NULL) {
        ListNode* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    else {
        printf("Элемент %d не найден в списке\n", value);
    }
}

int main(void) {
    setlocale(LC_ALL, "Rus");

    List* list;
    initList(&list);

    int command = 1;
    printf("Вас привествует пустой отсортированный список!\nСписок возможных команд:\n");
    printf("0 – выйти\n1 – добавить значение в сортированный список\n2 – удалить значение из списка\n3 – распечатать список");

    while (command != 0) {
        printf("\n\nВведите команду: ");
        scanf("%d", &command);
        if (command == 1) {
            int value = 0;
            printf("Введите значение: ");
            scanf("%d", &value);
            addSorted(&list, value);
            printf("Значение добавленно в список!");
        }
        else if (command == 2) {
            int value = 0;
            printf("Введите значение: ");
            scanf("%d", &value);
            removeValue(&list, value);
            printf("Значение удалено!");
        }
        else if (command == 3) {
            printList(&list);
        }
        else if (command == 0) {
            freeList(&list);
            printf("Ну и пожалуйста.");
            break;
        }
        else {
            printf("Такой команды нет.");
        }
    }
}