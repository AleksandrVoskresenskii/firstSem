#ifndef LIST_H
#define LIST_H

typedef struct {
    char* key;   // слово
    int value;   // частота
} ListItem;

typedef struct {
    ListItem* items;  // динамический массив элементов
    int size;         // текущее количество элементов
    int capacity;     // текущая вместимость
} List;

// Создает список с начальной вместимостью initialCapacity
List* createList(int initialCapacity);

// Добавляет слово с частотой freq (по умолчанию freq=1) или увеличивает частоту, если слово уже есть
void addToList(List* list, const char* key, int freq);

// Ищет слово в списке, возвращает указатель на элемент или NULL
ListItem* findInList(List* list, const char* key);

// Возвращает длину списка
int getListLength(List* list);

// Освобождает память списка
void freeList(List* list);

#endif