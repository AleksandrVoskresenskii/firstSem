#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* head;
} Stack;

void initStack(Stack* stack) {
    stack->head = NULL;
}

void push(Stack* stack, char data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = stack->head;
    stack->head = newNode;
}

char pop(Stack* stack) {
    if (stack->head == NULL) {
        printf("Ошибка: стек пуст\n");
        return '\0';
    }
    StackNode* temp = stack->head;
    char data = temp->data;
    stack->head = stack->head->next;
    free(temp);
    return data;
}

char peek(Stack* stack) {
    if (stack->head == NULL) {
        return '\0';
    }
    return stack->head->data;
}

bool isEmpty(Stack* stack) {
    return stack->head == NULL;
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else {
        return 0;
    }
}

bool isOperator(char letter) {
    return letter == '+' || letter == '-' || letter == '*' || letter == '/';
}

void infixToPostfix(const char* expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char letter = expression[i];

        if (isdigit(letter)) {
            printf("%c ", letter);
        }
        else if (letter == '(') {
            push(&stack, letter);
        }
        else if (letter == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                printf("%c ", pop(&stack));
            }
            pop(&stack);
        }
        else if (isOperator(letter)) {
            while (!isEmpty(&stack) && precedence(peek(&stack)) >= precedence(letter)) {
                printf("%c ", pop(&stack));
            }
            push(&stack, letter);
        }
    }

    while (!isEmpty(&stack)) {
        printf("%c ", pop(&stack));
    }

    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Rus");
    const char* expression = "(1+2)*2";
    printf("Инфиксное выражение: %s\n", expression);
    printf("Постфиксное выражение: ");
    infixToPostfix(expression);
    return 0;
}