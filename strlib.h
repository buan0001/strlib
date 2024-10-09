#ifndef STRLIB_H
#define STRLIB_H

// String functions:
int str_length(char* str);
char* str_at(char* charAdr, int index);
int str_endsWith(char* charAdr, char* end_chars);
int str_startsWith(char* charAdr, char* last_c);
int str_includes(char* org_str, char* searchString);
int str_indexOf(char* searchStr, char* searchVal);
int str_lastIndexOf(char* searchStr, char* searchVal);
void str_padEnd(char* org_str, char* pad_str, int final_len, char* buffer);
void str_padStart(char* org_str, char* pad_str, int final_len, char* buffer);
void str_repeat(char* str_to_repeat, int repeat_amt, char* buffer);
void str_slice(char* org_str, int indexStart, int indexEnd, char* buffer);
void str_substring(char* org_str, int indexStart, int indexEnd, char* buffer);
char* str_trim(char* ws_str);
void str_trimEnd(char* ws_str);
char* str_trimStart(char* ws_str);
void str_toUpperCase(char* str);
void str_toLowerCase(char* str);

int str_codePointAt(char* str, int index);
char* str_fromCodePoint(int num_val);
char* to_code_unit(int num, int initial_size);
int length_and_bytes(char* str, int* byte_count);
int bytes_in_code_point(unsigned char* point);
int bytes_in_string(char* str);

// My own helpers:
void copy_arr(char* org_arr, char* buffer);
int str_searchMatch(char* org_str, char* searchString);
int str_match(char* org_str, char* searchString);
int is_upperCase_letter(char sussy_c);
int is_lowerCase_letter(char sussy_c);

#endif