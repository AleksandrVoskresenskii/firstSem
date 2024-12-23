#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"

typedef struct NodeTree {

    int height;
    int key;
    char *value;

    struct NodeTree *father;
    struct NodeTree *left;
    struct NodeTree *right;
} NodeTree;

int max(int a, int b) {
    return (a > b) ? a : b;
}

NodeTree* createTree(void) {
    NodeTree* root = malloc(sizeof(NodeTree*));
    root = NULL;
    return root;
}

NodeTree* createNode(char* value, int key, NodeTree *root) {
    // Выделение памяти на value
    NodeTree* node = (NodeTree*)malloc(sizeof(NodeTree));
    char* str = (char*)malloc(strlen(value) + 1);
    strcpy(str, value);

    // Копирование ключа и значения в новый узел
    node->key = key;
    node->value = str;

    node->height = 1;

    // Присваивание указателей новому узлу
    node->father = root;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int newHeit(NodeTree *root) {
    if ((root->right != NULL) && (root->left != NULL)) {
        return max(root->left->height, root->right->height) + 1;
    } else if (root->left != 0) {
        return root->left->height + 1;
    } else if (root->right != 0) {
        return root->right->height + 1;
    } else {
        return 1;
    }
}

NodeTree *rightRotate(NodeTree *root) {
    void *leftSubtree = root->left;
    void *leftRightSudtree = root->left->right;

    if (root->father == NULL) {
        // Если это корень всего дерева
        root->father = leftSubtree;
        root->left->father = NULL;

        root->left->right = root;
        root->left = leftRightSudtree;
    } else if (root->father->left == root) {
        root->father->left = leftSubtree;

        root->left->father = root->father;
        root->father = leftSubtree;

        root->left->right = root;
        root->left = leftRightSudtree;
    } else if (root->father->right == root) {
        root->father->right = leftSubtree;

        root->left->father = root->father;
        root->father = leftSubtree;

        root->left->right = root;
        root->left = leftRightSudtree;
    }

    root = leftSubtree;
    root->left->height = newHeit(root->left);
    root->right->height = newHeit(root->right);
    root->height = newHeit(root);

    return root;
}

NodeTree *leftRotate(NodeTree *root) {
    NodeTree *rightSubtree = root->right;
    NodeTree *rightLeftSudtree = root->right->left;

    if (root->father == NULL) {
        // Если это корень всего дерева
        root->father = rightSubtree;
        root->right->father = NULL;

        root->right->left = root;
        root->right = rightLeftSudtree;
    } else if (root->father->left == root) {
        root->father->left = rightSubtree;

        root->right->father = root->father;
        root->father = rightSubtree;

        root->right->left = root;
        root->right = rightLeftSudtree;
    } else if (root->father->right == root) {
        root->father->right = rightLeftSudtree;

        root->right->father = root->father;
        root->father = rightSubtree;

        root->right->left = root;
        root->right = rightLeftSudtree;
    }

    root = rightSubtree;
    root->left->height = newHeit(root->left);
    root->right->height = newHeit(root->right);
    root->height = newHeit(root);

    return root;
}

NodeTree* balanceTree(NodeTree* root, int key) {
    int leftHeight = 0;
    int rightHeight = 0;

    if (root->left == NULL) {
        leftHeight = 0;
    } else {
        leftHeight = root->left->height;
    }

    if (root->right == NULL) {
        rightHeight = 0;
    } else {
        rightHeight = root->right->height;
    }

    int balance = leftHeight - rightHeight;

    if (balance > 1) {
        // Левый большой поворот
        if (key > root->left->key) {
            root->left = leftRotate(root->left);
        }
        // Левый малый поворот
        root = rightRotate(root);
    } else if (balance < -1) {
        // Правый большой поворот
        if (key < root->right->key) {
            root->right = rightRotate(root->right);
        }
        // Правый малый поворот
        root = leftRotate(root);
    }

    return root;
}

NodeTree* addElement(char* value, int key, NodeTree* root) {
    if (root == NULL) {
        return createNode(value, key, root);
    }

    int rotate = 0; // -1 если вставка была в левом поддереве, 1, если в правом

    if (key < root->key) {
        root->left = addElement(value, key, root->left);
        rotate = -1;
        root->height = newHeit(root);
    } else if (key > root->key) {
        root->right = addElement(value, key, root->right);
        rotate = 1;
        root->height = newHeit(root);
    } else {
        // Если ключ совпадает
        free(root->value);
        char* str = (char*)malloc(strlen(value) + 1);
        strcpy(str, value);
        root->value = str;
        return root;
    }

    root->height = newHeit(root);

    // Балансировка
    root = balanceTree(root, key);

    return root;
}

NodeTree* findMin(NodeTree* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

NodeTree* deleteElement(int key, NodeTree* root) {
    if (root == NULL) {
        return NULL;
    }

    // Ищем узел
    if (key < root->key) {
        root->left = deleteElement(key, root->left);
    } else if (key > root->key) {
        root->right = deleteElement(key, root->right);
    } else {
        // Узел найден
        if (root->left == NULL && root->right == NULL) {
            // Удаляем лист
            free(root->value);
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            // Один потомок (правый)
            NodeTree* temp = root->right;
            temp->father = root->father;
            free(root->value);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            // Один потомок (левый)
            NodeTree* temp = root->left;
            temp->father = root->father;
            free(root->value);
            free(root);
            return temp;
        } else {
            // Два потомка
            NodeTree* minNode = findMin(root->right);
            root->key = minNode->key;

            free(root->value);

            root->value = minNode->value;
            minNode->value = NULL;

            root->right = deleteElement(minNode->key, root->right);
        }
    }

    // Обновляем высоту текущего узла
    root->height = newHeit(root);

    // Балансировка
    root = balanceTree(root, key);

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