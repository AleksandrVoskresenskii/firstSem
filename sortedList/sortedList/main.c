#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// ��������� ���� �������� ������, ���������� �������� int
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// ��������� ������, ���������� ��������� �� ������ ������
typedef struct List {
    ListNode* head;
} List;

// ������� ������������� ������
void initList(List* list) {
    list->head = NULL;
}

// ������� ������������ ������ ����� ������
void freeList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// ������� ������ ���� �������� � ������
void printList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        printf("��������: %d\n", current->data);
        current = current->next;
    }
}

// ������� ���������� �������� � ��������������� ������
void addSorted(List* list, int value) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("������ ��������� ������\n");
        exit(1);
    }
    newNode->data = value;

    // ���� ������ ������ ��� ������� ������ ���� �������� � ������
    if (list->head == NULL || list->head->data >= value) {
        newNode->next = list->head;
        list->head = newNode;
    }
    else {
        // ����� ����� ��� �������
        ListNode* current = list->head;
        while (current->next != NULL && current->next->data < value) {
            current = current->next;
        }

        // �������� ����� �������
        newNode->next = current->next;
        current->next = newNode;
    }
}

// ������� �������� �������� �� ��������
void removeValue(List* list, int value) {
    if (list->head == NULL) {
        printf("������ ����\n");
        return;
    }

    // ���� �������, ������� ����� �������, ��������� � ������ ������
    if (list->head->data == value) {
        ListNode* temp = list->head;
        list->head = list->head->next;
        free(temp);
        return;
    }

    // ����� �������� � �������� ��� � ����� ������
    ListNode* current = list->head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }

    // ���� ������� ������
    if (current->next != NULL) {
        ListNode* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    else {
        printf("������� %d �� ������ � ������\n", value);
    }
}

int main(void) {
    setlocale(LC_ALL, "Rus");

    List* list;
    initList(&list);

    int command = 1;
    printf("��� ����������� ������ ��������������� ������!\n������ ��������� ������:\n");
    printf("0 � �����\n1 � �������� �������� � ������������� ������\n2 � ������� �������� �� ������\n3 � ����������� ������");

    while (command != 0) {
        printf("\n\n������� �������: ");
        scanf("%d", &command);
        if (command == 1) {
            int value = 0;
            printf("������� ��������: ");
            scanf("%d", &value);
            addSorted(&list, value);
            printf("�������� ���������� � ������!");
        }
        else if (command == 2) {
            int value = 0;
            printf("������� ��������: ");
            scanf("%d", &value);
            removeValue(&list, value);
            printf("�������� �������!");
        }
        else if (command == 3) {
            printList(&list);
        }
        else if (command == 0) {
            freeList(&list);
            printf("�� � ����������.");
            break;
        }
        else {
            printf("����� ������� ���.");
        }
    }
}