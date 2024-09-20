#include <stdio.h>
#include "strlib.h"

int main()
{
    run_tests();
}

void run_tests()
{
    int wrongs_corrects[] = {0, 0};

    wrongs_corrects[run_at_like_test(0, "nanubabu", 'n', str_at)]++;
    wrongs_corrects[run_at_like_test(4, "nanubabu", 'b', str_at)]++;
    wrongs_corrects[run_at_like_test(20, "nanubabu", '\0', str_at)]++;

    wrongs_corrects[run_endsWith_like_test('u', "nanubabu", 1, endsWith)]++;
    wrongs_corrects[run_endsWith_like_test('n', "nanubabu", 0, endsWith)]++;
    wrongs_corrects[run_endsWith_like_test('q', "nanubabu", 0, endsWith)]++;

    printf("\nRan %d tests:\n", (wrongs_corrects[0] + wrongs_corrects[1]));
    printf("Passed: %d\n", wrongs_corrects[1]);
    printf("Failed: %d\n", wrongs_corrects[0]);
}

int run_at_like_test(int index, char *string, int expected, char (*str_f)(int, char *))
{
    int result = (*str_f)(index, string);
    if (result != expected)
    {
        printf("Test FAILED for %s. Expected: %d. Actual: %d. \n", string, expected, result);
        return 0;
    }
    return 1;
}

int run_endsWith_like_test(char ending_c, char *string, int expected, int (*str_f)(char, char *))
{
    int result = (*str_f)(ending_c, string);
    if (result != expected)
    {
        printf("Test FAILED for %s ends with %c. Expected: %d. Actual: %d. \n", string, ending_c, expected, result);
        return 0;
    }
    return 1;
}
