#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tree.h"

int main() {
    FILE* file = fopen("file.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    NodeTree* root = parseExpression(file);

    printTree(root);
    printf("\n");
    printf("%d\n", resultTree(root));

    freeTree(root);

    return 0;
}