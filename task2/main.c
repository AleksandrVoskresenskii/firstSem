#include <stdio.h>
#include "queue.h"

int main() {
    Queue* q = queueCreate();
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    printf("%d\n", dequeue(q)); // ожидаем 10
    printf("%d\n", dequeue(q)); // ожидаем 20

    enqueue(q, 40);
    enqueue(q, 50);

    while (!queueIsEmpty(q)) {
        printf("%d\n", dequeue(q));
    }

    queueDestroy(q);
    return 0;
}