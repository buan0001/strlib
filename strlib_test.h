#ifndef STRLIB_TEST_H
#define STRLIB_TEST_H

void run_tests();

int handle_result_unconditional(int result, int expected, char *func_name);
int handle_result_conditional(int result, int expected, char *critera, char *func_name);
int handle_string_comparison_test(char *actual, char *expected, char *func_name);
int assert_equals(int actual, int expected, char *func_name);
int assert_strings(char* actual, char* expected, char* func_name);
int assert_string_match(char* result, char* expected, char* func_name);

#endif