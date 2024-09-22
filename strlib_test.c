#include <stdio.h>
#include "strlib.h"

int main()
{
    run_tests();
}

void run_tests()
{
    int wrongs_corrects[] = {0, 0};

    wrongs_corrects[run_length_like_test("nan", 3, str_length, "str_length")]++;
    wrongs_corrects[run_length_like_test("", 0, str_length, "str_length")]++;
    wrongs_corrects[run_length_like_test("nanu babu", 9, str_length, "str_length")]++;

    wrongs_corrects[run_at_like_test(0, "nanubabu", 'n', str_at, "str_at")]++;
    wrongs_corrects[run_at_like_test(4, "nanubabu", 'b', str_at, "str_at")]++;
    wrongs_corrects[run_at_like_test(20, "nanubabu", 0, str_at, "str_at")]++;
    wrongs_corrects[run_at_like_test(-1, "nanubabu", 'u', str_at, "str_at")]++;
    wrongs_corrects[run_at_like_test(-8, "nanubabu", 'n', str_at, "str_at")]++;
    wrongs_corrects[run_at_like_test(-9, "nanubabu", 0, str_at, "str_at")]++;

    wrongs_corrects[run_endsWith_like_test("u", "nanubabu", 1, str_endsWith, "str_endsWith")]++;
    wrongs_corrects[run_endsWith_like_test("babu", "nanubabu", 1, str_endsWith, "str_endsWith")]++;
    wrongs_corrects[run_endsWith_like_test("q", "nanubabu", 0, str_endsWith, "str_endsWith")]++;

    wrongs_corrects[run_endsWith_like_test("na", "nanubabu", 1, str_startsWith, "startsWith")]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 1, str_startsWith, "startsWith")]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", 0, str_startsWith, "startsWith")]++;
    wrongs_corrects[run_endsWith_like_test("q", "nanubabu", 0, str_startsWith, "startsWith")]++;

    wrongs_corrects[run_endsWith_like_test("ba", "nanubabu", 1, str_includes, "includes")]++;
    wrongs_corrects[run_endsWith_like_test("q", "nanubabu", 0, str_includes, "includes")]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 1, str_includes, "includes")]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", 0, str_includes, "includes")]++;
    wrongs_corrects[run_endsWith_like_test("nanubabu", "nanubabu", 1, str_includes, "includes")]++;

    wrongs_corrects[run_endsWith_like_test("anu", "nanubabu", 1, str_indexOf, "indexOf")]++;
    wrongs_corrects[run_endsWith_like_test("nanubabu", "nanubabu", 0, str_indexOf, "indexOf")]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 0, str_indexOf, "indexOf")]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", -1, str_indexOf, "indexOf")]++;
    wrongs_corrects[run_endsWith_like_test("nanubabububu", "nanubabu", -1, str_indexOf, "indexOf")]++;
    wrongs_corrects[run_endsWith_like_test("abu", "nanubabu", 5, str_indexOf, "indexOf")]++;
    wrongs_corrects[run_endsWith_like_test("bu", "nanubabu", 6, str_indexOf, "indexOf")]++;

    wrongs_corrects[run_endsWith_like_test("anu", "nanubabu", 1, str_lastIndexOf, "lastIndexOf")]++;
    wrongs_corrects[run_endsWith_like_test("nanubabu", "nanubabu", 0, str_lastIndexOf, "lastIndexOf")]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 2, str_lastIndexOf, "lastIndexOf")]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", -1, str_lastIndexOf, "lastIndexOf")]++;
    wrongs_corrects[run_endsWith_like_test("nanubabububu", "nanubabu", -1, str_lastIndexOf, "lastIndexOf")]++;
    wrongs_corrects[run_endsWith_like_test("abu", "nanubabu", 5, str_lastIndexOf, "lastIndexOf")]++;
    wrongs_corrects[run_endsWith_like_test("u", "nanubabu", 7, str_lastIndexOf, "lastIndexOf")]++;

    wrongs_corrects[run_pad_like_test("nanubabu", "la", 12, "nanubabulala", str_padEnd, "padEnd")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", "la", 11, "nanubabulal", str_padEnd, "padEnd")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 11, "nanubabu...", str_padEnd, "padEnd")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", " ", 11, "nanubabu   ", str_padEnd, "padEnd")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 4, "nanubabu", str_padEnd, "padEnd")]++;

    wrongs_corrects[run_pad_like_test("nanubabu", "la", 12, "lalananubabu", str_padStart, "padStart")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", "la", 11, "lalnanubabu", str_padStart, "padStart")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 11, "...nanubabu", str_padStart, "padStart")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", " ", 11, "   nanubabu", str_padStart, "padStart")]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 4, "nanubabu", str_padStart, "padStart")]++;

    wrongs_corrects[run_repeat_like_test("na", 4, "nananana", str_repeat, "repeat")]++;
    wrongs_corrects[run_repeat_like_test("k", 1, "k", str_repeat, "repeat")]++;
    wrongs_corrects[run_repeat_like_test("k h", 3, "k hk hk h", str_repeat, "repeat")]++;
    wrongs_corrects[run_repeat_like_test("k h", 0, "\0", str_repeat, "repeat")]++;

    char trim_array1[] = "nanu  ";
    char trim_array2[] = "     nanu  ";
    char trim_array3[] = "      ";
    char trim_array4[] = "   nanu";

    wrongs_corrects[run_trimEnd_like_test(trim_array1, "nanu", str_trimEnd, "trimEnd")]++;
    wrongs_corrects[run_trimEnd_like_test("nanu", "nanu", str_trimEnd, "trimEnd")]++;
    wrongs_corrects[run_trimEnd_like_test(trim_array2, "     nanu", str_trimEnd, "trimEnd")]++;
    wrongs_corrects[run_trimEnd_like_test(trim_array3, "", str_trimEnd, "trimEnd")]++;

    wrongs_corrects[run_trimStart_like_test(trim_array4, "nanu", str_trimStart, "trimStart")]++;
    wrongs_corrects[run_trimStart_like_test("nanu", "nanu", str_trimStart, "trimStart")]++;
    wrongs_corrects[run_trimStart_like_test(trim_array2, "nanu  ", str_trimStart, "trimStart")]++;
    wrongs_corrects[run_trimStart_like_test(trim_array3, "", str_trimStart, "trimStart")]++;

    wrongs_corrects[run_trimStart_like_test(trim_array1, "nanu", str_trim, "trim")]++;
    wrongs_corrects[run_trimStart_like_test(trim_array2, "nanu", str_trim, "trim")]++;
    wrongs_corrects[run_trimStart_like_test(trim_array3, "", str_trim, "trim")]++;
    wrongs_corrects[run_trimStart_like_test(trim_array4, "nanu", str_trim, "trim")]++;

    char case_array1[] = "nanu";
    char case_array2[] = " ._`| nanu  ";
    char case_array3[] = "nAnU";
    // char case_array[] = "nanu";
    wrongs_corrects[run_trimEnd_like_test(case_array1, "NANU", str_toUpperCase, "toUpperCase")]++;
    wrongs_corrects[run_trimEnd_like_test(case_array2, " ._`| NANU  ", str_toUpperCase, "toUpperCase")]++;
    wrongs_corrects[run_trimEnd_like_test(case_array3, "NANU", str_toUpperCase, "toUpperCase")]++;

    wrongs_corrects[run_trimEnd_like_test(case_array1, "nanu", str_toLowerCase, "toLowerCase")]++;
    wrongs_corrects[run_trimEnd_like_test(case_array2, " ._`| nanu  ", str_toLowerCase, "toLowerCase")]++;
    wrongs_corrects[run_trimEnd_like_test(case_array3, "nanu", str_toLowerCase, "toLowerCase")]++;

    printf("\nRan %d tests:\n", (wrongs_corrects[0] + wrongs_corrects[1]));
    printf("Passed: %d\n", wrongs_corrects[1]);
    printf("Failed: %d\n", wrongs_corrects[0]);
}

// Run the tests

int run_at_like_test(int index, char *string, int expected, char (*str_f)(char *, int), char *func_name)
{
    return handle_result_unconditional((*str_f)(string, index), expected, func_name);
}

int run_endsWith_like_test(char *comp_str, char *org_str, int expected, int (*str_f)(char *, char *), char *func_name)
{
    return handle_result_conditional((*str_f)(org_str, comp_str), expected, comp_str, func_name);
}

int run_length_like_test(char *string, int expected, int (*str_f)(char *), char *func_name)
{
    return handle_result_unconditional((*str_f)(string), expected, func_name);
}

int run_trimEnd_like_test(char *string, char *expected, void (*str_f)(char *), char *func_name)
{
    (*str_f)(string), expected, func_name;
    return handle_string_comparison_test(string, expected, func_name);
}

int run_trimStart_like_test(char *string, char *expected, char* (*str_f)(char *), char *func_name)
{
    char* trimmed = (*str_f)(string);
    return handle_string_comparison_test(trimmed, expected, func_name);
}

int run_pad_like_test(char *string, char *pad_str, int desired_length, char *expected, void (*str_f)(char *, char *, int, char *), char *func_name)
{
    char padded_array[500];
    (*str_f)(string, pad_str, desired_length, padded_array);
    return handle_string_comparison_test(padded_array, expected, func_name);
}

int run_repeat_like_test(char *str_to_repeat, int repeat_amt, char *expected, void (*str_f)(char *, int, char *), char *func_name)
{
    char repeated_array[500];
    (*str_f)(str_to_repeat, repeat_amt, repeated_array);
    // printf("expected: %d. actual: %d\n", *expected, *repeated_array);
    return handle_string_comparison_test(repeated_array, expected, func_name);
}

// Assert results

int handle_result_unconditional(int result, int expected, char *func_name)
{
    if (result != expected)
    {
        printf("Test FAILED for %s. Expected: '%d' Actual: '%d'. \n", func_name, expected, result);
        return 0;
    }
    return 1;
}

int handle_result_conditional(int result, int expected, char *critera, char *func_name)
{
    if (result != expected)
    {
        printf("Test FAILED for %s. Testing for: %s. Expected: '%d' Actual: '%d' \n", func_name, critera, expected, result);
        return 0;
    }
    return 1;
}

int handle_string_comparison_test(char *actual, char *expected, char *func_name)
{
    // printf("Expected: %s. Actual: %s. Match: %d\n", expected, actual, str_match(expected, actual));
    if (!str_match(expected, actual))
    {
        printf("Test FAILED for %s.\nExpected: '%s'\nActual: '%s'\n", func_name, expected, actual);
        return 0;
    }
    return 1;
}
