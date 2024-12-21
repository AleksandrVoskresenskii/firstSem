#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

typedef struct CircularList {
    ListNode* head;
} CircularList;

void initList(CircularList* list) {
    list->head = NULL;
}

void addElement(CircularList* list, int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = newNode;

    if (list->head == NULL) {
        list->head = newNode;
    }
    else {
        ListNode* temp = list->head;
        while (temp->next != list->head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = list->head;
    }
}

void freeList(CircularList* list) {
    if (list->head == NULL) return;

    ListNode* current = list->head;
    ListNode* nextNode;

    do {
        nextNode = current->next;
        free(current);
        current = nextNode;
    } while (current != list->head);

    list->head = NULL;
}

void printList(CircularList* list) {
    if (list->head == NULL) {
        printf("Список пуст\n");
        return;
    }

    ListNode* current = list->head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

int deleteByIndex(CircularList* list, int index) {
    if (list->head == NULL) {
        printf("Список пуст, удаление невозможно\n");
        return -1;
    }

    ListNode* temp = list->head;
    int length = 1;
    while (temp->next != list->head) {
        temp = temp->next;
        length++;
    }

    int actualIndex = index % length;
    if (actualIndex < 0) {
        actualIndex += length;
    }

    if (actualIndex == 0) {
        ListNode* last = list->head;
        while (last->next != list->head) {
            last = last->next;
        }
        ListNode* nodeToDelete = list->head;
        if (list->head->next == list->head) {
            list->head = NULL;
        }
        else {
            list->head = list->head->next;
            last->next = list->head;
        }
        free(nodeToDelete);
        return actualIndex;
    }

    ListNode* current = list->head;
    for (int i = 0; i < actualIndex - 1; i++) {
        current = current->next;
    }

    ListNode* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    free(nodeToDelete);
    return actualIndex;
}

int getValueByIndex(CircularList* list, int index) {
    if (list->head == NULL) {
        printf("Список пуст\n");
        return -1;
    }

    ListNode* temp = list->head;
    int length = 1;
    while (temp->next != list->head) {
        temp = temp->next;
        length++;
    }

    int actualIndex = index % length;
    if (actualIndex < 0) {
        actualIndex += length;
    }

    ListNode* current = list->head;
    for (int i = 0; i < actualIndex; i++) {
        current = current->next;
    }

    return current->data;
}

int counting(CircularList* list, int lengthList, int step) {
    for (int i = 0; i < lengthList; i++) {
        addElement(list, i + 1);
    }
    int deletedElement = -1;
    for (int i = 0; i < lengthList - 1; i++) {
        deletedElement = deleteByIndex(list, deletedElement + step) - 1;
    }
    return getValueByIndex(list, 0);
}

int main(void) {
    setlocale(LC_ALL, "Rus");

    CircularList list;
    initList(&list);

    int lengthList = 0;
    int step = 0;
    printf("Введите количество людей: ");
    scanf("%d", &lengthList);
    printf("Введите шаг счета: ");
    scanf("%d", &step);

    printf("%d", counting(&list, lengthList, step));
}