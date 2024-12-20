#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* binaryToDecimalString(const char* binary) {
    int decimal = 0;
    int length = (int)strlen(binary);

    for (int i = 0; i < length; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            char* errorRes = malloc(7);
            strcpy(errorRes, "Error!");
            return errorRes;
        }
        decimal = decimal * 2 + (binary[i] - '0');
    }

    char* result = malloc(32);
    sprintf(result, "%d", decimal);

    return result;
}

void testBinaryToDecimalString() {
    const char* tests[] = {
        "0",
        "1",
        "1011",
        "11111111",
        "010",
        "abc",
        "",
        "101000"
    };

    const char* expected[] = {
        "0",
        "1",
        "11",
        "255",
        "2",
        "Error!",
        "0",
        "40"
    };

    int num_tests = (int)(sizeof(tests) / sizeof(tests[0]));

    for (int i = 0; i < num_tests; i++) {
        char* result = binaryToDecimalString(tests[i]);
        if (strcmp(result, expected[i]) != 0) {
            printf("Test %d failed", i+1);
        }
        free(result);
    }
}

int main() {

    testBinaryToDecimalString();

    char binary[32];
    scanf("%31s", binary);

    char* decimalStr = binaryToDecimalString(binary);
    printf("%s\n", decimalStr);

    free(decimalStr);
    return 0;
}