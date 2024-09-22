#ifndef STRLIB_TEST_H
#define STRLIB_TEST_H

void run_tests();

int run_at_like_test(int index, char *string, int expected, char (*str_f)(char *, int), char *func_name);
int run_endsWith_like_test(char *ending_str, char *string, int expected, int (*str_f)(char *, char *), char *func_name);
int run_length_like_test(char *string, int expected, int (*str_f)(char *), char *func_name);
int run_pad_like_test(char *string, char *pad_str, int desired_length, char *expected, void (*str_f)(char *, char *, int, char *), char *func_name);
int run_trimEnd_like_test(char *string, char *expected, void (*str_f)(char *), char *func_name);
int run_trimStart_like_test(char *string, char *expected, char *(*str_f)(char *), char *func_name);
int run_repeat_like_test(char *str_to_repeat, int repeat_amt, char *expected, void (*str_f)(char *, int, char *), char *func_name);
int run_substring_like_test(char *org_str, int start_index, int end_index, char *expected, void (*str_f)(char *, int, int, char *), char *func_name);

int handle_result_unconditional(int result, int expected, char *func_name);
int handle_result_conditional(int result, int expected, char *critera, char *func_name);
int handle_string_comparison_test(char *actual, char *expected, char *func_name);

#endif