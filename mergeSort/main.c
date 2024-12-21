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

// ������������� ������� ������
void initList(List* list) {
    list->head = NULL;
}

// ������� ��� ���������� ������ � ������ ������
void addRecord(List* list, const char* name, const char* phone) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("������ ��������� ������\n");
        exit(1);
    }
    strcpy(newNode->data.name, name);
    strcpy(newNode->data.phone, phone);
    newNode->next = list->head;
    list->head = newNode;
}

// ������� ��� ������������ ������ ������
void freeList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

// ������� ���� ��������������� ����������
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

// ���������� ������ �� ��� ��������
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

// ������� ���������� ��������
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

// ���������� ��� ���������� �� �����
bool compareByName(Record a, Record b) {
    return strcmp(a.name, b.name) < 0;
}

// ���������� ��� ���������� �� ��������
bool compareByPhone(Record a, Record b) {
    return strcmp(a.phone, b.phone) < 0;
}

// ������� ��� ������ ������
void printList(List* list) {
    ListNode* current = list->head;
    while (current != NULL) {
        printf("%s %s\n", current->data.name, current->data.phone);
        current = current->next;
    }
}

// �������� �������
int main() {
    setlocale(LC_ALL, "Rus");
    List contactList;
    initList(&contactList);

    // ������ ������ �� ����� (������)
    FILE* file = fopen("contacts.txt", "r");
    if (!file) {
        printf("������ �������� �����\n");
        return 1;
    }

    char name[50], phone[20];
    while (fscanf(file, "%49s %19s", name, phone) != EOF) {
        addRecord(&contactList, name, phone);
    }
    fclose(file);

    // ����� �������� ����������
    int choice;
    printf("�������� �������� ����������:\n1 - �� �����\n2 - �� ������ ��������\n");
    scanf("%d", &choice);

    // ���������� ���������� �� ������ ������ ������������
    if (choice == 1) {
        mergeSort(&contactList.head, compareByName);
    }
    else if (choice == 2) {
        mergeSort(&contactList.head, compareByPhone);
    }
    else {
        printf("�������� �����\n");
        freeList(&contactList);
        return 1;
    }

    // ����� ���������������� ������
    printf("��������������� ������:\n");
    printList(&contactList);

    // ������� ������
    freeList(&contactList);

    return 0;
}