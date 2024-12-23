#include "hash.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOAD_FACTOR 0.75

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->segments = (List**)malloc(size * sizeof(List*));
    table->size = size;
    table->count = 0;

    for (int i = 0; i < size; i++) {
        table->segments[i] = createList(2); // начальная вместимость списка
    }
    return table;
}

int hashFunction(const char* key, int size) {
    unsigned long hash = 0;
    while (*key) {
        hash = (hash * 31 + (unsigned char)*key) % size;
        key++;
    }
    return (int)(hash % size);
}

void rehashTable(HashTable* table, int newSize) {
    List** oldSegments = table->segments;
    int oldSize = table->size;

    table->segments = (List**)malloc(newSize * sizeof(List*));
    table->size = newSize;
    int oldCount = table->count;
    table->count = 0;

    for (int i = 0; i < newSize; i++) {
        table->segments[i] = createList(2);
    }

    // Переносим все элементы
    for (int i = 0; i < oldSize; i++) {
        List* list = oldSegments[i];
        for (int j = 0; j < list->size; j++) {
            const char* key = list->items[j].key;
            int value = list->items[j].value;

            int index = hashFunction(key, table->size);
            // Добавим с учетом value
            addToList(table->segments[index], key, value);
            table->count += value; 
        }
        freeList(list);
    }

    free(oldSegments);
}

void addToHashTable(HashTable* table, const char* key) {
    int index = hashFunction(key, table->size);
    List* list = table->segments[index];

    ListItem* item = findInList(list, key);
    if (!item) {
        table->count++;
        addToList(list, key, 1);
    } else {
        item->value++;
    }

    double loadFactor = (double)table->count / table->size;
    if (loadFactor > LOAD_FACTOR) {
        rehashTable(table, table->size * 2);
    }
}

void printHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        List* list = table->segments[i];
        if (list->size > 0) {
            for (int j = 0; j < list->size; j++) {
                printf("  %s: %d\n", list->items[j].key, list->items[j].value);
            }
        }
    }
}

void printStatistics(HashTable* table) {
    int nonEmptySegments = 0;
    int maxListLength = 0;
    double totalLength = 0;

    for (int i = 0; i < table->size; i++) {
        int length = getListLength(table->segments[i]);
        if (length > 0) {
            nonEmptySegments++;
            totalLength += length;
            if (length > maxListLength) {
                maxListLength = length;
            }
        }
    }

    double loadFactor = (double)table->count / table->size;
    double averageListLength = (nonEmptySegments > 0) ? (totalLength / nonEmptySegments) : 0.0;

    printf("Коэффициент заполнения: %.2f\n", loadFactor);
    printf("Максимальная длина списка: %d\n", maxListLength);
    printf("Средняя длина списка: %.2f\n", averageListLength);
}

void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        freeList(table->segments[i]);
    }
    free(table->segments);
    free(table);
}