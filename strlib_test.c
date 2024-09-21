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
    return handle_result_condition((*str_f)(org_str, comp_str), org_str, expected, comp_str);
}

int run_length_like_test(char *string, int expected, int (*str_f)(char *))
{
    return handle_result_unconditional((*str_f)(string), string, expected);
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

int handle_result_condition(int result, char *string, int expected, char *critera)
{
    if (result != expected)
    {
        printf("Test FAILED for %s. Testing for: %s. Expected: %d. Actual: %d. \n", string, critera, expected, result);
        return 0;
    }
    return 1;
}