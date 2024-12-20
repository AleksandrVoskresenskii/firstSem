#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Хеш-функция для строк
static unsigned hashString(const char* str) {
    unsigned hash = 34756;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

StringSet* setCreate(int size) {
    StringSet* set = malloc(sizeof(StringSet));
    set->size = size;
    set->table = calloc(size, sizeof(char*));
    set->occupied = calloc(size, sizeof(bool));
    return set;
}

void setDestroy(StringSet* set) {
    for (int i = 0; i < set->size; i++) {
        if (set->occupied[i]) {
            free(set->table[i]);
        }
    }
    free(set->table);
    free(set->occupied);
    free(set);
}

// Линейное пробирование: начинаем с позиции hash = hashString() % size и двигаемся дальше
// до пустой ячейки или совпадения
bool setAdd(StringSet* set, const char* str) {
    unsigned hash = hashString(str);
    int start = (int)(hash % set->size);

    for (int i = 0; i < set->size; i++) {
        int pos = (start + i) % set->size;
        if (!set->occupied[pos]) {
            // свободно, добавляем
            set->table[pos] = strdup(str);
            set->occupied[pos] = true;
            return true;
        } else {
            // занято, проверим, совпадает ли строка
            if (strcmp(set->table[pos], str) == 0) {
                // уже существует
                return false;
            }
        }
    }
    // Если мы прошли весь цикл и не нашли места - таблица переполнена, я просто возвращаю false
    return false;
}

bool setFind(const StringSet* set, const char* str) {
    unsigned hash = hashString(str);
    int start = (int)(hash % set->size);

    for (int i = 0; i < set->size; i++) {
        int pos = (start + i) % set->size;
        if (!set->occupied[pos]) {
            // встретили пустую ячейку - значит, слова точно нет
            return false;
        }
        if (strcmp(set->table[pos], str) == 0) {
            return true;
        }
    }
    return false;
}