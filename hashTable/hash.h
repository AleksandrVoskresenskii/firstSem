#ifndef HASH_H
#define HASH_H

#include "list.h"

typedef struct {
    List** segments;
    int size;   // количество сегментов
    int count;  // общее количество элементов (слов)
} HashTable;

// Создает хеш-таблицу
HashTable* createHashTable(int size);

// Добавляет слово в хэш-таблицу
void addToHashTable(HashTable* table, const char* key);

// Хеш-функция
int hashFunction(const char* key, int size);

// Печатает таблицу
void printHashTable(HashTable* table);

// Печатает статистику
void printStatistics(HashTable* table);

// Освобождает память хэш-таблицы
void freeHashTable(HashTable* table);

// Увеличение размера таблицы и перераспределение элементов
void rehashTable(HashTable* table, int newSize);

#endif