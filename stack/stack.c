#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

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

bool isEmpty(Stack* stack) {
    return stack->head == NULL;
}

int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '{' && close == '}') ||
        (open == '[' && close == ']');
}

bool isBalanced(char* expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(&stack, ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&stack) || !isMatchingPair(pop(&stack), ch)) {
                return false;
            }
        }
    }

    return isEmpty(&stack);
}

bool testInitStack() {
    Stack stack;
    initStack(&stack);
    return isEmpty(&stack);
}

bool testPush() {
    Stack stack;
    initStack(&stack);
    push(&stack, '(');
    return stack.head != NULL && stack.head->data == '(';
}

bool testPop() {
    Stack stack;
    initStack(&stack);
    push(&stack, '(');
    char popped = pop(&stack);
    return popped == '(' && isEmpty(&stack);
}

bool testIsEmpty() {
    Stack stack;
    initStack(&stack);
    bool emptyCheck1 = isEmpty(&stack);
    push(&stack, '(');
    bool emptyCheck2 = !isEmpty(&stack);
    return emptyCheck1 && emptyCheck2;
}

bool testIsMatchingPair() {
    return isMatchingPair('(', ')') && isMatchingPair('{', '}') && isMatchingPair('[', ']') && !isMatchingPair('(', '}');
}

bool testIsBalanced() {
    bool test1 = isBalanced("()");
    bool test2 = isBalanced("({})");
    bool test3 = isBalanced("([])");
    bool test4 = !isBalanced("({[)]}");
    bool test5 = !isBalanced("({)}");
    return test1 && test2 && test3 && test4 && test5;
}

bool allTests() {
    return testInitStack() && testPush() && testPop() && testIsEmpty() && testIsMatchingPair() && testIsBalanced();
}

int main() {
    setlocale(LC_ALL, "Rus");

    if (!allTests()) {
        printf("Тесты не пройдены");
        return 1;
    }

    char expression[100];
    printf("Введите скобочную последовательность: ");
    scanf("%s", expression);

    if (isBalanced(expression)) {
        printf("Вложенность скобок соблюдается\n");
    }
    else {
        printf("Вложенность скобок не соблюдается\n");
    }

    return 0;
}