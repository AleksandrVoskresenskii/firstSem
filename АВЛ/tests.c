#include <stdio.h>
#include <assert.h>

#include "tree.h"

typedef struct NodeTree {

    int height;
    int key;
    char *value;

    struct NodeTree *father;
    struct NodeTree *left;
    struct NodeTree *right;
} NodeTree;

void testCreateTree() {
    NodeTree* tree = createTree();
    assert(tree == NULL); // Дерево должно быть пустым
    printf("[PASSED] testCreateTree\n");
}

void testAddElement() {
    NodeTree* tree = createTree();

    tree = addElement("Value1", 10, tree); // Корневой элемент
    assert(tree != NULL);
    assert(tree->key == 10);
    assert(strcmp(tree->value, "Value1") == 0);

    tree = addElement("Value2", 5, tree); // Левый элемент
    assert(tree->left != NULL);
    assert(tree->left->key == 5);
    assert(strcmp(tree->left->value, "Value2") == 0);

    tree = addElement("Value3", 15, tree); // Правый элемент
    assert(tree->right != NULL);
    assert(tree->right->key == 15);
    assert(strcmp(tree->right->value, "Value3") == 0);

    printf("[PASSED] testAddElement\n");
}

void testGetValueKey() {
    NodeTree* tree = createTree();
    tree = addElement("Value1", 10, tree);
    tree = addElement("Value2", 5, tree);
    tree = addElement("Value3", 15, tree);

    char* value = getValueKey(10, tree);
    assert(value != NULL && strcmp(value, "Value1") == 0);

    value = getValueKey(5, tree);
    assert(value != NULL && strcmp(value, "Value2") == 0);

    value = getValueKey(15, tree);
    assert(value != NULL && strcmp(value, "Value3") == 0);

    value = getValueKey(20, tree); // Несуществующий ключ
    assert(value == NULL);

    printf("[PASSED] testGetValueKey\n");
}

void testDeleteElement() {
    NodeTree* tree = createTree();
    tree = addElement("Value1", 10, tree);
    tree = addElement("Value2", 5, tree);
    tree = addElement("Value3", 15, tree);

    tree = deleteElement(5, tree); // Удаление левого элемента
    assert(tree->left == NULL);

    tree = deleteElement(15, tree); // Удаление правого элемента
    assert(tree->right == NULL);

    tree = deleteElement(10, tree); // Удаление корневого элемента
    assert(tree == NULL);

    printf("[PASSED] testDeleteElement\n");
}

void testIsHaveKey() {
    NodeTree* tree = createTree();
    tree = addElement("Value1", 10, tree);
    tree = addElement("Value2", 5, tree);

    assert(isHaveKey(10, tree) == true);
    assert(isHaveKey(5, tree) == true);
    assert(isHaveKey(15, tree) == false);

    printf("[PASSED] testIsHaveKey\n");
}

void testBalanceTree() {
    NodeTree* tree = createTree();

    // Добавляем элементы в порядке, нарушающем баланс
    tree = addElement("Value1", 10, tree);
    tree = addElement("Value2", 5, tree);
    tree = addElement("Value3", 3, tree); // Левое поддерево становится несбалансированным

    assert(tree->key == 5); // Должен произойти правый поворот

    printf("[PASSED] testBalanceTree\n");
}

void testFreeTree() {
    NodeTree* tree = createTree();
    tree = addElement("Value1", 10, tree);
    tree = addElement("Value2", 5, tree);

    freeTree(tree);

    printf("[PASSED] testFreeTree\n");
}

int main(void) {
    testCreateTree();
    testAddElement();
    testGetValueKey();
    testDeleteElement();
    testIsHaveKey();
    testBalanceTree();
    testFreeTree();

    printf("Все тесты пройдены успешно!\n");
    return 0;
}