#ifndef STRLIB_TEST_H
#define STRLIB_TEST_H

void run_tests();

int assert_equals(int actual, int expected, char *func_name);
int assert_equals_strings(String actual, String expected, char* func_name);

#endif