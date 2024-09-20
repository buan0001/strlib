#ifndef STRLIB_H
#define STRLIB_H

// String functions:
char str_at(int index, char *charAdr);
int endsWith(char last_c, char *charAdr);


// Tests and other
void run_tests();

int run_at_like_test(int index, char *string, int expected, char (*str_f)(int, char *));
int run_endsWith_like_test(char ending_c, char *string, int expected, int (*str_f)(char, char *));

#endif