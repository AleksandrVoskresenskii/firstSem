#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

// Внутренняя структура стека
typedef struct Stack {
    int* data;
    int top;
    int capacity;
} Stack;

static Stack* stackCreate(int capacity) {
    Stack* s = malloc(sizeof(Stack));
    s->data = malloc(sizeof(int)*capacity);
    s->top = -1;
    s->capacity = capacity;
    return s;
}

static void stackDestroy(Stack* s) {
    free(s->data);
    free(s);
}

static bool stackIsEmpty(const Stack* s) {
    return s->top == -1;
}

static void stackPush(Stack* s, int value) {
    if (s->top == s->capacity - 1) {
        // при необходимости увеличить размер
        s->capacity *= 2;
        s->data = realloc(s->data, sizeof(int)*s->capacity);
    }
    s->data[++s->top] = value;
}

static int stackPop(Stack* s) {
    return s->data[s->top--];
}

// Структура очереди
struct Queue {
    Stack* stackEnqueue;
    Stack* stackDequeue;
};

Queue* queueCreate(void) {
    Queue* q = malloc(sizeof(Queue));
    q->stackEnqueue = stackCreate(10);
    q->stackDequeue = stackCreate(10);
    return q;
}

void queueDestroy(Queue* q) {
    stackDestroy(q->stackEnqueue);
    stackDestroy(q->stackDequeue);
    free(q);
}

void enqueue(Queue* q, int value) {
    // просто пушим в stackEnqueue
    stackPush(q->stackEnqueue, value);
}

int dequeue(Queue* q) {
    if (stackIsEmpty(q->stackDequeue)) {
        // перекладываем из stackEnqueue в stackDequeue
        while (!stackIsEmpty(q->stackEnqueue)) {
            int val = stackPop(q->stackEnqueue);
            stackPush(q->stackDequeue, val);
        }
    }
    return stackPop(q->stackDequeue);
}

bool queueIsEmpty(const Queue* q) {
    return stackIsEmpty(q->stackEnqueue) && stackIsEmpty(q->stackDequeue);
}