#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* head;
} Stack;

void initStack(Stack* stack) {
    stack->head = NULL;
}

void push(Stack* stack, int data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = stack->head;
    stack->head = newNode;
}

int pop(Stack* stack) {
    if (stack->head == NULL) {
        printf("Ошибка: стек пуст\n");
        return '\0';
    }
    StackNode* temp = stack->head;
    int data = temp->data;
    stack->head = stack->head->next;
    free(temp);
    return data;
}

bool isEmpty(Stack* stack) {
    return stack->head == NULL;
}

bool isNumber(char value) {
    return ((value == '0') || (value == '1') ||
        (value == '2') || (value == '3') ||
        (value == '4') || (value == '5') ||
        (value == '6') || (value == '7') ||
        (value == '8') || (value == '9'));
}

int postSum(char* expression) {
    int i = 0;
    int summ = 0;
    Stack stack;
    initStack(&stack);

    while (expression[i] != '\0') {
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        if (isNumber(expression[i])) {
            push(&stack, expression[i] - '0');
        }
        else if (expression[i] == '*') {
            int a = pop(&stack);
            int b = pop(&stack);
            int c = b * a;
            push(&stack, c);
        }
        else if (expression[i] == '/') {
            int a = pop(&stack);
            int b = pop(&stack);
            int c = b / a;
            push(&stack, c);
        }
        else if (expression[i] == '+') {
            int a = pop(&stack);
            int b = pop(&stack);
            int c = b + a;
            push(&stack, c);
        }
        else if (expression[i] == '-') {
            int a = pop(&stack);
            int b = pop(&stack);
            int c = b - a;
            push(&stack, c);
        }
        i++;
    }
    summ = pop(&stack);
    if (isEmpty(&stack)) {
        return summ;
    }
    printf("Выражение введено неверно");
    return NULL;
}

bool testIsNumber() {
    if (!isNumber('0')) return false;
    if (!isNumber('5')) return false;
    if (!isNumber('9')) return false;
    if (isNumber('a')) return false;
    if (isNumber(' ')) return false;
    return true;
}

bool testPostSum() {
    char expression1[] = "4 2 - 1 2 + *";
    if (postSum(expression1) != 6) return false;

    char expression2[] = "9 6 - 1 2 + *";
    if (postSum(expression2) != 9) return false;

    char expression3[] = "3 5 + 8 2 / *";
    if (postSum(expression3) != 32) return false;

    return true;
}

int main() {
    setlocale(LC_ALL, "Rus");

    if (!(testPostSum() && testIsNumber())) {
        printf("Ошибка: тесты не прошли");
        return 1;
    }

    char expression[100];
    printf("Введите выражение в постфиксном виде: ");
    scanf("%s", expression);
    printf("%d", postSum(expression));



    return 0;
}