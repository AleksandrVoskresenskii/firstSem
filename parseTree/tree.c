#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tree.h"

typedef struct NodeTree {
    char op; // '+', '-', '*', '/' или '\0'
    int value; // Значение для числа
    struct NodeTree* left;
    struct NodeTree* right;
} NodeTree;

NodeTree* createNode(char op, int value) {
    NodeTree* node = (NodeTree*)malloc(sizeof(NodeTree));
    node->op = op;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

NodeTree* parseExpression(FILE* file) {
    int ch = fgetc(file);
    
    // Пропускаем пробелы
    while (isspace(ch)) {
        ch = fgetc(file);
    }

    if (ch == '(') {
        // Читаем операцию
        char op = fgetc(file);
        NodeTree* node = createNode(op, 0);

        // Рекурсивно разбираем левый и правый операнды
        node->left = parseExpression(file);
        node->right = parseExpression(file);

        // Ожидаем закрывающую скобку
        ch = fgetc(file);
        if (ch != ')') {
            printf("Error: Expected ')'\n");
            exit(1);
        }

        return node;
    } else {
        // Возвращаем символ в поток и читаем число
        ungetc(ch, file);
        int value;
        if (fscanf(file, "%d", &value) != 1) {
            printf("Error: Expected number\n");
            exit(1);
        }
        return createNode('\0', value);
    }
}

void printTree(NodeTree* root) {
    if (root->op != '\0') {
        printf("%c ", root->op);
    } else {
        printf("%d ", root->value);
    }
    if (root->left != NULL) {
        printTree(root->left);
    }
    if (root->right != NULL) {
        printTree(root->right);
    }
    return;
}

int resultTree(NodeTree* root)  {
    if (root->op == '\0') {
        return root->value;
    }

    int leftValue = resultTree(root->left);
    int rightValue = resultTree(root->right);

    switch (root->op) {
        case '+': return leftValue + rightValue;
        case '-': return leftValue - rightValue;
        case '*': return leftValue * rightValue;
        case '/':
            if (rightValue == 0) {
                printf("Error: Division by zero\n");
                exit(1);
            }
            return leftValue / rightValue;
        default:
            printf("Error: Unknown operator '%c'\n", root->op);
            exit(1);
    }
}

void freeTree(NodeTree* root) {
    if ((root->left == NULL) && (root->right == NULL)) {
        free(root);
        return;
    }
    if (root->left != NULL) {
        freeTree(root->left);
    }
    if (root->right != NULL) {
        freeTree(root->right);
    }
    free(root);
}