#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Узел дерева
typedef struct NodeTree NodeTree;

// Функция создания узла дерева
NodeTree* createNode(char* value, int key);

// Функция создания пустого дерева, возвращает указатель на дерево
NodeTree* createTree(void);

// Добавляет узел по значению ключа key в дерево root
NodeTree* addElement(char* value, int key, NodeTree* root);

// Проверяет наличие узла с ключем key в дереве root
bool isHaveKey(int key, NodeTree* root);

// Возвращает указатель на значение по ключу key из дерева root или NULL, если ключа нет в дереве
char* getValueKey(int key, NodeTree* root);

// Ищет отца минимального элемента в дереве, если это коркнь, возвращает NULL
NodeTree* searchFatherMinChild(NodeTree* root);

// Удаляет элемент по ключу key из дерева root
NodeTree* deleteElement(int key, NodeTree* root);

// Удаляет дерево
void freeTree(NodeTree* root);

#endif