#ifndef STRLIB_H
#define STRLIB_H

// String functions:
int str_length(char *str);
char str_at(char *charAdr, int index);
int str_endsWith(char *charAdr, char *end_chars);
int str_startsWith(char *charAdr, char *last_c);
int str_includes(char *org_str, char *searchString);
int str_indexOf(char *searchStr, char *searchVal);
int str_lastIndexOf(char *searchStr, char *searchVal);
void str_padEnd(char *org_str, char *pad_str, int final_len, char *buffer);
void str_padStart(char *org_str, char *pad_str, int final_len, char *buffer);
void str_repeat(char *str_to_repeat, int repeat_amt, char *buffer);
void str_slice(char *org_str, int indexStart, int indexEnd, char *buffer);
void str_substring(char *org_str, int indexStart, int indexEnd, char *buffer);
void str_trim(char *ws_str);
void str_trimEnd(char *ws_str);
void str_trimStart(char *ws_str);
void str_toUpperCase(char *str);
void str_toLowerCase(char *str);

// Tests and other
void run_tests();

int run_at_like_test(int index, char *string, int expected, char (*str_f)(char *, int));
int run_endsWith_like_test(char *ending_str, char *string, int expected, int (*str_f)(char *, char *));
int run_length_like_test(char *string, int expected, int (*str_f)(char *));
int handle_result(int result, char *string, int expected);

#endif