#ifndef STRLIB_H
#define STRLIB_H

typedef struct String
{
    char* str_start;
    int byte_length;
    int length;
    char* point_lengths;
    char* byteIndexLookup;
} String;

String* str_construct(char* str);
void str_destruct(String* str_to_free);
unsigned int decode_utf8(unsigned char* str);

// String functions:
int str_length(String str);
unsigned int str_at(String string, int index);
int str_endsWith(String string, String end_chars);
int str_startsWith(String charAdr, String last_c);
int str_includes(String org_str, String searchString);
int str_indexOf(String searchStr, String searchVal);
int str_lastIndexOf(String searchStr, String searchVal);
String* str_padEnd(String org_str, String pad_str, int final_len);
String* str_padStart(String org_str, String pad_str, int final_len);
String* str_repeat(String str_to_repeat, int repeat_amt);
String* str_slice(String org_str, int indexStart, int indexEnd);
String* str_substring(String org_str, int indexStart, int indexEnd);
String* str_trim(String ws_str);
String* str_trimEnd(String ws_str);
String* str_trimStart(String ws_str);
String* str_toUpperCase(String str);
String* str_toLowerCase(String str);

unsigned int str_codePointAt(String str, int index);
String* str_fromCodePoint(int num_val);
char* to_code_unit(int num, int initial_size);
int length_and_bytes(String str, int* byte_count);
int bytes_in_code_point(unsigned char* point);
int bytes_in_string(String str);

// My own helpers:
void copy_arr(char* str, char* str2);
int str_searchMatch(String org_str, String searchString);
int str_match(String org_str, String searchString);
int is_upperCase_letter(char sussy_c);
int is_lowerCase_letter(char sussy_c);

#endif