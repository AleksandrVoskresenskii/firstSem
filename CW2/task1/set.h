#ifndef SET_H
#define SET_H

#include <stdbool.h>

// Структура множества строк.
typedef struct {
    char** table;
    bool* occupied;
    int size;
} StringSet;

// Создает множество строк заданного размера.
StringSet* setCreate(int size);

// Освобождает память, занятую множеством.
void setDestroy(StringSet* s);

/**
 * Добавляет строку в множество.
 * Если строка уже есть, повторное добавление не изменяет множество.
 **/
bool setAdd(StringSet* s, const char* str);

// Проверяет, содержится ли строка в множестве.
bool setFind(const StringSet* s, const char* str);

#endif // SET_H