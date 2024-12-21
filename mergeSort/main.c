#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>


typedef struct Record {
    char name[50];
    char phone[20];
} Record;

typedef struct ListNode {
    Record data;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* head;
} List;

// Инициализация пустого списка
void initList(List* list) {
    list->head = NULL;
}

// Функция для добавления записи в начало списка
void addRecord(List* list, const char* name, const char* phone) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    strcpy(newNode->data.name, name);
    strcpy(newNode->data.phone, phone);
    newNode->next = list->head;
    list->head = newNode;
}

// Функция для освобождения памяти списка
void freeList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// Слияние двух отсортированных подсписков
ListNode* sortedMerge(ListNode* a, ListNode* b, bool (*comparator)(Record, Record)) {
    if (!a) return b;
    if (!b) return a;

    ListNode* result = NULL;
    if (comparator(a->data, b->data)) {
        result = a;
        result->next = sortedMerge(a->next, b, comparator);
    }
    else {
        result = b;
        result->next = sortedMerge(a, b->next, comparator);
    }
    return result;
}

// Разделение списка на две половины
void splitList(ListNode* source, ListNode** frontRef, ListNode** backRef) {
    ListNode* fast;
    ListNode* slow;
    if (source == NULL || source->next == NULL) {
        *frontRef = source;
        *backRef = NULL;
    }
    else {
        slow = source;
        fast = source->next;

        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}

// Функция сортировки слиянием
void mergeSort(ListNode** headRef, bool (*comparator)(Record, Record)) {
    if (*headRef == NULL || (*headRef)->next == NULL)
        return;

    ListNode* head = *headRef;
    ListNode* a;
    ListNode* b;

    splitList(head, &a, &b);
    mergeSort(&a, comparator);
    mergeSort(&b, comparator);

    *headRef = sortedMerge(a, b, comparator);
}

// Компаратор для сортировки по имени
bool compareByName(Record a, Record b) {
    return strcmp(a.name, b.name) < 0;
}

// Компаратор для сортировки по телефону
bool compareByPhone(Record a, Record b) {
    return strcmp(a.phone, b.phone) < 0;
}

// Функция для печати списка
void printList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        printf("%s %s\n", current->data.name, current->data.phone);
        current = current->next;
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Rus");
    List contactList;
    initList(&contactList);

    // Чтение данных из файла (пример)
    FILE* file = fopen("contacts.txt", "r");
    if (!file) {
        printf("Ошибка открытия файла\n");
        return 1;
    }

    char name[50], phone[20];
    while (fscanf(file, "%49s %19s", name, phone) != EOF) {
        addRecord(&contactList, name, phone);
    }
    fclose(file);

    // Выбор критерия сортировки
    int choice;
    printf("Выберите критерий сортировки:\n1 - По имени\n2 - По номеру телефона\n");
    scanf("%d", &choice);

    // Выполнение сортировки на основе выбора пользователя
    if (choice == 1) {
        mergeSort(&contactList.head, compareByName);
    }
    else if (choice == 2) {
        mergeSort(&contactList.head, compareByPhone);
    }
    else {
        printf("Неверный выбор\n");
        freeList(&contactList);
        return 1;
    }

    // Вывод отсортированного списка
    printf("Отсортированные записи:\n");
    printList(&contactList);

    // Очистка памяти
    freeList(&contactList);

    return 0;
}