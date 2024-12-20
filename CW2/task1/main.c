#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

// Тест создания и удаления множества
bool testSetCreateDestroy() {
    StringSet* s = setCreate(10);
    if (s == NULL) {
        return false;
    }
    // Проверим, что после создания поиск любого слова вернет false
    if (setFind(s, "test")) {
        setDestroy(s);
        return false;
    }
    setDestroy(s);
    return true;
}

bool testSetAddFind() {
    StringSet* s = setCreate(10);

    if (!setAdd(s, "math")) {
        setDestroy(s);
        return false;
    }

    if (!setFind(s, "math")) {
        // Должно найти только что добавленное слово
        setDestroy(s);
        return false;
    }

    if (setFind(s, "philosophy")) {
        // Не добавляли "philosophy", зачем ее добавлять, не должно найти
        setDestroy(s);
        return false;
    }

    // Добавляем ещё одно слово
    if (!setAdd(s, "test")) {
        setDestroy(s);
        return false;
    }

    // Проверяем
    if (!setFind(s, "test")) {
        setDestroy(s);
        return false;
    }

    setDestroy(s);
    return true;
}

bool testSetAddExisting() {
    StringSet* s = setCreate(5); // небольшой размер для проверки коллизий
    if (!setAdd(s, "repeat")) {
        setDestroy(s);
        return false;
    }

    // Добавляем то же слово
    bool addedAgain = setAdd(s, "repeat");
    // Если слово уже было, setAdd должно вернуть false
    if (addedAgain) {
        setDestroy(s);
        return false;
    }

    // Проверяем, что слово по-прежнему находится
    if (!setFind(s, "repeat")) {
        setDestroy(s);
        return false;
    }

    setDestroy(s);
    return true;
}

bool runAllTests() {
    bool allPassed = true;

    // Тест создания/удаления
    bool cdt = testSetCreateDestroy();
    printf("testSetCreateDestroy: %s\n", cdt ? "passed" : "failed");
    if (!cdt) allPassed = false;

    // Тест добавления/поиска
    bool af = testSetAddFind();
    printf("testSetAddFind: %s\n", af ? "passed" : "failed");
    if (!af) allPassed = false;

    // Тест добавления существующего
    bool aex = testSetAddExisting();
    printf("testSetAddExisting: %s\n", aex ? "passed" : "failed");
    if (!aex) allPassed = false;

    return allPassed;
}

int main() {
    bool result = runAllTests();
    if (result) {
        printf("All tests passed!\n");
        return 0;
    } else {
        printf("Some tests failed\n");
    }
    return 1;
}