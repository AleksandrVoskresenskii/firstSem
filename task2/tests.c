#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

static void testEmptyQueue() {
    Queue* q = queueCreate();
    if (queueIsEmpty(q)) {
        printf("testEmptyQueue passed: очередь пуста после создания\n");
    } else {
        printf("testEmptyQueue failed: очередь не пуста после создания\n");
    }
    queueDestroy(q);
}

static void testEnqueueDequeue() {
    Queue* q = queueCreate();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    int val = dequeue(q);
    if (val == 10) {
        printf("testEnqueueDequeue step1 passed\n");
    } else {
        printf("testEnqueueDequeue step1 failed: ожидали 10, получили %d\n", val);
    }

    val = dequeue(q);
    if (val == 20) {
        printf("testEnqueueDequeue step2 passed\n");
    } else {
        printf("testEnqueueDequeue step2 failed: ожидали 20, получили %d\n", val);
    }

    val = dequeue(q);
    if (val == 30) {
        printf("testEnqueueDequeue step3 passed\n");
    } else {
        printf("testEnqueueDequeue step3 failed: ожидали 30, получили %d\n", val);
    }

    if (queueIsEmpty(q)) {
        printf("testEnqueueDequeue final passed: очередь пуста в конце\n");
    } else {
        printf("testEnqueueDequeue final failed: очередь не пуста\n");
    }

    queueDestroy(q);
}

static void testMultipleEnqueueDequeue() {
    Queue* q = queueCreate();
    // Добавляем несколько элементов
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);

    // Удаляем два
    int val1 = dequeue(q); // ожидаем 1
    int val2 = dequeue(q); // ожидаем 2

    if (val1 == 1 && val2 == 2) {
        printf("testMultipleEnqueueDequeue step1 passed\n");
    } else {
        printf("testMultipleEnqueueDequeue step1 failed: ожидали 1,2 получили %d,%d\n", val1, val2);
    }

    // Добавляем еще два
    enqueue(q, 5);
    enqueue(q, 6);

    // Теперь вынимаем остаток: должно быть 3,4,5,6
    int vals[4];
    for (int i = 0; i < 4; i++) {
        vals[i] = dequeue(q);
    }

    int expected[] = {3,4,5,6};
    bool passed = true;
    for (int i = 0; i < 4; i++) {
        if (vals[i] != expected[i]) {
            passed = false;
            break;
        }
    }

    if (passed) {
        printf("testMultipleEnqueueDequeue step2 passed\n");
    } else {
        printf("testMultipleEnqueueDequeue step2 failed\n");
    }

    if (queueIsEmpty(q)) {
        printf("testMultipleEnqueueDequeue final passed\n");
    } else {
        printf("testMultipleEnqueueDequeue final failed\n");
    }

    queueDestroy(q);
}

int main() {
    testEmptyQueue();
    testEnqueueDequeue();
    testMultipleEnqueueDequeue();

    return 0;
}