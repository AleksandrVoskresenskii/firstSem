#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void resizeList(List* list) {
    int newCapacity = (list->capacity == 0) ? 2 : list->capacity * 2;
    ListItem* newItems = (ListItem*)malloc(sizeof(ListItem) * newCapacity);

    for (int i = 0; i < list->size; i++) {
        newItems[i] = list->items[i];
    }

    free(list->items);
    list->items = newItems;
    list->capacity = newCapacity;
}

List* createList(int initialCapacity) {
    List* list = (List*)malloc(sizeof(List));
    list->size = 0;
    list->capacity = (initialCapacity > 0) ? initialCapacity : 2;
    list->items = (ListItem*)malloc(sizeof(ListItem) * list->capacity);
    return list;
}

ListItem* findInList(List* list, const char* key) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->items[i].key, key) == 0) {
            return &list->items[i];
        }
    }
    return NULL;
}

void addToList(List* list, const char* key, int freq) {
    ListItem* item = findInList(list, key);
    if (item) {
        item->value += freq;
        return;
    }

    if (list->size == list->capacity) {
        resizeList(list);
    }

    list->items[list->size].key = strdup(key);
    list->items[list->size].value = freq;
    list->size++;
}

int getListLength(List* list) {
    return list->size;
}

void freeList(List* list) {
    for (int i = 0; i < list->size; i++) {
        free(list->items[i].key);
    }
    free(list->items);
    free(list);
}