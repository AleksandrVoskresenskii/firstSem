#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Узел дерева
typedef struct NodeTree NodeTree;

// Функция создания узла дерева
NodeTree* createNode(char op, int value);

// Функция разбора узла из файла
NodeTree* parseExpression(FILE* file);

// Функция печати дерева
void printTree(NodeTree* root);

// Функция вычисления значения дерева
int resultTree(NodeTree* root);

// Очистка памяти дерева
void freeTree(NodeTree* root);
