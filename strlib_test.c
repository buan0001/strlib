#include <stdio.h>
#include <stdlib.h>

#include "strlib.h"

#include "strlib_test.h"

int main() { run_tests(); }

void run_tests() {
    // char* someString = malloc(sizeof("halløj"));
    char* someString = "halløj";
    String* strTest = str_construct(someString);
    printf("Adress in test: %p\n", strTest);
    printf("String: %s. Length: %d. Bytes: %d\n", strTest->str_start, strTest->length, strTest->byte_length);
    str_destruct(strTest);
    

    int wrongs_corrects[] = { 0, 0 };

    printf("\nRan %d tests:\n",
        (wrongs_corrects[0] +
            wrongs_corrects[1]));
    printf("Passed: %d\n", wrongs_corrects[1]);
    printf("Failed: %d\n", wrongs_corrects[0]);
}

// Run the tests

int assert_equals(int actual, int expected, char* func_name) {
    if (actual == expected)
        return 1;
    else {
        printf("Error in %s. Expected: %d. Got: %d\n", func_name, expected, actual);
        return 0;
    }
}