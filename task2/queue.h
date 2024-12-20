#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Структура очереди, реализованной на двух стеках
typedef struct Queue Queue;

// Создает и инициализирует новую пустую очередь
Queue* queueCreate(void);

// Освобождает память, занятую очередью
void queueDestroy(Queue* q);

// Добавляет элемент в очередь
void enqueue(Queue* q, int value);

// Удаляет элемент из очереди и возвращает его значение
int dequeue(Queue* q);

// Проверяет, пуста ли очередь
bool queueIsEmpty(const Queue* q);

#endif // QUEUE_H