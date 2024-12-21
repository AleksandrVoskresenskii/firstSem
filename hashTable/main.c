#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

#define HASH_TABLE_SIZE 128

void processTextFile(const char* filename, HashTable* table) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть файл");
        exit(1);
    }

    char word[256];
    while (fscanf(file, "%255s", word) == 1) {
        addToHashTable(table, word);
    }

    fclose(file);
}

int main(void) {
    const char* filename = "text.txt";

    HashTable* table = createHashTable(HASH_TABLE_SIZE);
    processTextFile(filename, table);

    printf("Частоты слов:\n");
    printHashTable(table);

    printf("\nСтатистика хеш-таблицы:\n");
    printStatistics(table);

    freeHashTable(table);
    return 0;
}