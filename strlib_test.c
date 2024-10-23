#include <stdio.h>
#include <stdlib.h>

#include "strlib.h"

#include "strlib_test.h"

int main() { run_tests(); }

void run_tests() {
    int wrongs_corrects[] = { 0, 0 };
    // char* someString = malloc(sizeof("halløj"));
    String* strTest1 = str_construct("🍎halløj");
    String* strTest2 = str_construct("🍎halløj");
    String* strTest3 = str_construct("ne😁j");
    String* searchTest1 = str_construct("j");

    wrongs_corrects[assert_equals(str_codePointAt(*strTest1, 0), 127822, "string match")]++;
    wrongs_corrects[assert_equals(str_codePointAt(*strTest1, 1), 104, "string match")]++;
    wrongs_corrects[assert_equals(str_codePointAt(*strTest1, 13), -1, "string match")]++;


    wrongs_corrects[assert_equals(str_match(*strTest1, *strTest2), 1, "string match")]++;
    wrongs_corrects[assert_equals(str_match(*strTest1, *strTest3), 0, "string match")]++;

    wrongs_corrects[assert_equals(str_indexOf(*strTest1, *searchTest1), 10, "index of")]++;

    String* slice_test = str_construct("🍎h");
    String* slice_str = str_slice(*strTest1, 0, 2);

    wrongs_corrects[assert_equals_strings(*slice_str, *slice_test, "slice")]++;

    printf("All tests have run\n");
    str_destruct(strTest1);
    str_destruct(strTest2);
    str_destruct(strTest3);
    printf("Managed to free all\n");
    // printf("Test 1 after freeing: %d,%d, %p,  %p\n", strTest1.length, strTest1.byte_length, strTest1.byte_LUT, strTest1.str_start);



    printf("\nRan %d tests:\n",
        (wrongs_corrects[0] +
            wrongs_corrects[1]));
    printf("Passed: %d\n", wrongs_corrects[1]);
    printf("Failed: %d\n", wrongs_corrects[0]);
}


int assert_equals(int actual, int expected, char* func_name) {
    if (actual == expected)
        return 1;
    else {
        printf("Error in %s. Expected: %d. Got: %d\n", func_name, expected, actual);
        return 0;
    }
}

int assert_equals_strings(String actual, String expected, char* func_name) {
    if (str_match(actual, expected))
        return 1;
    else {
        printf("Error in %s. Expected: %s. Got: %s\n", func_name, expected.str_start, actual.str_start);
        return 0;
    }
}