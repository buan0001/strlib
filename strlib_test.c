#include <stdio.h>
#include "strlib.h"

int main()
{
    run_tests();
}

void run_tests()
{
    int wrongs_corrects[] = {0, 0};

    wrongs_corrects[run_length_like_test("nan", 3, str_length)]++;
    wrongs_corrects[run_length_like_test("", 0, str_length)]++;
    wrongs_corrects[run_length_like_test("nanu babu", 9, str_length)]++;

    wrongs_corrects[run_at_like_test(0, "nanubabu", 'n', str_at)]++;
    wrongs_corrects[run_at_like_test(4, "nanubabu", 'b', str_at)]++;
    wrongs_corrects[run_at_like_test(20, "nanubabu", 0, str_at)]++;
    wrongs_corrects[run_at_like_test(-1, "nanubabu", 'u', str_at)]++;
    wrongs_corrects[run_at_like_test(-8, "nanubabu", 'n', str_at)]++;
    wrongs_corrects[run_at_like_test(-9, "nanubabu", 0, str_at)]++;

    wrongs_corrects[run_endsWith_like_test("u", "nanubabu", 1, str_endsWith)]++;
    wrongs_corrects[run_endsWith_like_test("babu", "nanubabu", 1, str_endsWith)]++;
    wrongs_corrects[run_endsWith_like_test("q", "nanubabu", 0, str_endsWith)]++;

    wrongs_corrects[run_endsWith_like_test("na", "nanubabu", 1, str_startsWith)]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 1, str_startsWith)]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", 0, str_startsWith)]++;
    wrongs_corrects[run_endsWith_like_test("q", "nanubabu", 0, str_startsWith)]++;

    wrongs_corrects[run_endsWith_like_test("ba", "nanubabu", 1, str_includes)]++;
    wrongs_corrects[run_endsWith_like_test("q", "nanubabu", 0, str_includes)]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 1, str_includes)]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", 0, str_includes)]++;
    wrongs_corrects[run_endsWith_like_test("nanubabu", "nanubabu", 1, str_includes)]++;

    wrongs_corrects[run_endsWith_like_test("anu", "nanubabu", 1, str_indexOf)]++;
    wrongs_corrects[run_endsWith_like_test("nanubabu", "nanubabu", 0, str_indexOf)]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 0, str_indexOf)]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", -1, str_indexOf)]++;
    wrongs_corrects[run_endsWith_like_test("nanubabububu", "nanubabu", -1, str_indexOf)]++;
    wrongs_corrects[run_endsWith_like_test("abu", "nanubabu", 5, str_indexOf)]++;
    wrongs_corrects[run_endsWith_like_test("bu", "nanubabu", 6, str_indexOf)]++;

    wrongs_corrects[run_endsWith_like_test("anu", "nanubabu", 1, str_lastIndexOf)]++;
    wrongs_corrects[run_endsWith_like_test("nanubabu", "nanubabu", 0, str_lastIndexOf)]++;
    wrongs_corrects[run_endsWith_like_test("n", "nanubabu", 2, str_lastIndexOf)]++;
    wrongs_corrects[run_endsWith_like_test("", "nanubabu", -1, str_lastIndexOf)]++;
    wrongs_corrects[run_endsWith_like_test("nanubabububu", "nanubabu", -1, str_lastIndexOf)]++;
    wrongs_corrects[run_endsWith_like_test("abu", "nanubabu", 5, str_lastIndexOf)]++;
    wrongs_corrects[run_endsWith_like_test("u", "nanubabu", 7, str_lastIndexOf)]++;

    wrongs_corrects[run_pad_like_test("nanubabu", "la", 10, "nanubabul", str_padEnd)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", "la", 11, "nanubabula", str_padEnd)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 11, "nanubabu..", str_padEnd)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", " ", 11, "nanubabu  ", str_padEnd)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 4, "nanubabu", str_padEnd)]++;


    wrongs_corrects[run_pad_like_test("nanubabu", "la", 10, "lnanubabu", str_padStart)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", "la", 10, "lananubabu", str_padStart)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 10, "..nanubabu", str_padStart)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", " ", 10, "  nanubabu", str_padStart)]++;
    wrongs_corrects[run_pad_like_test("nanubabu", ".", 4, "nanubabu", str_padStart)]++;

    printf("\nRan %d tests:\n", (wrongs_corrects[0] + wrongs_corrects[1]));
    printf("Passed: %d\n", wrongs_corrects[1]);
    printf("Failed: %d\n", wrongs_corrects[0]);
}

int run_at_like_test(int index, char *string, int expected, char (*str_f)(char *, int))
{
    return handle_result_unconditional((*str_f)(string, index), string, expected);
}

int run_endsWith_like_test(char *comp_str, char *org_str, int expected, int (*str_f)(char *, char *))
{
    return handle_result_conditional((*str_f)(org_str, comp_str), org_str, expected, comp_str);
}

int run_length_like_test(char *string, int expected, int (*str_f)(char *))
{
    return handle_result_unconditional((*str_f)(string), string, expected);
}

int run_pad_like_test(char *string, char *pad_str, int desired_length, char *expected, void (*str_f)(char *, char *, int, char *))
{
    char padded_array[500];
    (*str_f)(string, pad_str, desired_length, padded_array);
    return handle_string_comparison_test(string, padded_array, expected);
}

int handle_result_unconditional(int result, char *string, int expected)
{
    if (result != expected)
    {
        printf("Test FAILED for %s. Expected: %d. Actual: %d. \n", string, expected, result);
        return 0;
    }
    return 1;
}

int handle_result_conditional(int result, char *string, int expected, char *critera)
{
    if (result != expected)
    {
        printf("Test FAILED for %s. Testing for: %s. Expected: %d. Actual: %d. \n", string, critera, expected, result);
        return 0;
    }
    return 1;
}

int handle_string_comparison_test( char* original, char* actual, char* expected)
{
    if (!str_match(actual, expected)){
        printf("Test FAILED for %s. Expected: %s. Actual: %s\n", original, expected, actual);
        return 0;
    }
    return 1;
}