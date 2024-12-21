#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

typedef struct NodeTree {
    char* value;
    int key;
    struct NodeTree* left;
    struct NodeTree* right;
} NodeTree;

NodeTree* createNode(char* value, int key) {
    NodeTree* node = (NodeTree*)malloc(sizeof(NodeTree));
    char* str = (char*)malloc(strlen(value) + 1);
    strcpy(str, value);
    node->key = key;
    node->value = str;
    node->left = NULL;
    node->right = NULL;
    return node;
}

NodeTree* createTree(void) {
    NodeTree* root = malloc(sizeof(NodeTree*));
    root = NULL;
    return root;
}

NodeTree* addElement(char* value, int key, NodeTree* root) {
    if (root == NULL) {
        return createNode(value, key);
    }

    if (key < root->key) {
        root->left = addElement(value, key, root->left);
    } else if (key > root->key) {
        root->right = addElement(value, key, root->right);
    } else {
        // Если ключ совпадает
        free(root->value);
        char* str = (char*)malloc(strlen(value) + 1);
        strcpy(str, value);
        root->value = str;
    }

    return root;
}

bool isHaveKey(int key, NodeTree* root) {
    if (root->key == key) {
        return true;
    } else if ((root->key > key) && (root->left != NULL)) {
        return isHaveKey(key, root->left);
    } else if ((root->key < key) && (root->right != NULL)) {
        return isHaveKey(key, root->right);
    } else {
        return false;
    }
}

char* getValueKey(int key, NodeTree* root) {
    if (root->key == key) {
        return root->value;
    } else if ((root->key > key) && (root->left != NULL)) {
        return getValueKey(key, root->left);
    } else if ((root->key < key) && (root->right != NULL)) {
        return getValueKey(key, root->right);
    } else {
        return NULL;
    }
}

// NodeTree* searchFatherMinChild(NodeTree* root) {
//     if ((*root).left == NULL) {
//         // Возвращаем NULL, если элемент и так минимальный
//         return NULL;
//     }
//     if (root->left->left == NULL) {
//         // Если следуюший - корень минимального, возвращаем указатель на него
//         return root->left;
//     } else {
//         // проходим дальше по рекурсии
//         return searchFatherMinChild(root->left);
//     }
// }

NodeTree* searchFatherMinChild(NodeTree* root) {
    if (root == NULL || root->left == NULL) {
        return NULL;
    }

    if (root->left->left == NULL) {
        // Возвращаем родителя минимального элемента
        return root;
    } else {
        return searchFatherMinChild(root->left);
    }
}

NodeTree* deleteElement(int key, NodeTree* root) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->key) {
        root->left = deleteElement(key, root->left);
    } else if (key > root->key) {
        root->right = deleteElement(key, root->right);
    } else {
        if (root->left == NULL && root->right == NULL) {
            // Удаляем лист
            free(root->value);
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // Узел с одним потомком (правым)
            NodeTree* temp = root->right;
            free(root->value);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // Узел с одним потомком (левым)
            NodeTree* temp = root->left;
            free(root->value);
            free(root);
            return temp;
        } else {
            // Узел с двумя потомками
            // Ищем минимальный элемент в правом поддереве
            NodeTree* parentMin = searchFatherMinChild(root->right);
            NodeTree* minNode = (parentMin != NULL) ? parentMin->left : root->right;

            // Переносим данные минимального элемента
            free(root->value);
            root->key = minNode->key;

            // Переносим указатель на строку из минимального узла
            root->value = minNode->value;
            minNode->value = NULL;

            // Удаляем минимальный элемент
            if (parentMin) {
                parentMin->left = deleteElement(minNode->key, parentMin->left);
            } else {
                root->right = deleteElement(minNode->key, root->right);
            }
        }
    }

    return root;
}

void freeTree(NodeTree* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);

    if (root->value != NULL) {
        free(root->value);
    }

    free(root);
}