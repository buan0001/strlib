#include <stdio.h>
#include "strlib.h"

// Returns the length of the given string
int str_length(char* str)
{
    int length = 0;
    while(*str++){
        length++;
    }
    return length;
}

// TODO: Accept negative values in order to take the the index from the end/right
/* Returns the character (exactly one UTF-16 code unit) at the specified index. Accepts negative integers, which count back from the last string character.*/
char str_at(char *charAdr, int index)
{
    if (index < 0){
        index += str_length(charAdr);
    }
    int moves = 0;
    while (*charAdr != '\0' && index != moves)
    {
        moves++;
        charAdr++;
    }
    if (index == moves)
    {
        return *charAdr;
    }
    else
    {
        return 0;
    }
}

/* Determines whether a string ends with the characters of the string searchString. */
int str_endsWith(char *charAdr, char* end_chars)
{
    int length_org = str_length(charAdr);
    int length_check = str_length(end_chars);
    int length_dif = length_org - length_check;

    if (length_dif < 0) return 0;

    // Move the string pointer
    charAdr += length_dif;
    for (int i = 0; i < length_check; i++)
    {
        if (*charAdr++ != *end_chars++)
        {
            return 0;
        }
    }
    return 1;
    

    // // Keep going until '\0' is met.
    // while (*(++charAdr))
    //     ;
    // // At this point *charAdr will be the null character. So go one back and compare it to the desired check char
    // return last_c == *(--charAdr);
}

// Determines whether the calling string begins with the characters of string searchString
int str_startsWith(char *charAdr, char* last_c)
{
}

/* Determines whether the calling string contains searchString. */
int str_includes(char *org_str, char *searchString)
{
    char *temp_ptr = searchString;
    // Keep going until '\0' is met.
    while (*(++org_str))
        ;
}

/*Returns the index within this string of the first occurrence of searchValue, or -1 if not found.*/
int str_indexOf(char *searchStr, char *searchVal)
{
}

/* Returns the index within this string of the last occurrence of searchValue, or -1 if not found. */
int str_lastIndexOf(char *searchStr, char *searchVal)
{
}

// Pads the current string from the end with a given string and returns a new string of the length targetLength.
void str_padEnd(char *org_str, char *pad_str, int final_len, char *buffer)
{
}
// Pads the current string from the end with a given string and returns a new string of the length targetLength
void str_padStart(char *org_str, char *pad_str, int final_len, char *buffer)
{
}

// Returns a string consisting of the elements of the object repeated count times.
void str_repeat(char *str_to_repeat, int repeat_amt, char *buffer)
{
}

// SUBTLE DIFFERENCES BETWEEN SUBSTRING AND SLICE

// Extracts a section of a string and returns a new string.
void str_slice(char *org_str, int indexStart, int indexEnd, char *buffer)
{
}

// Returns a new string containing characters of the calling string from (or between) the specified index (or indices).
void str_substring(char *org_str, int indexStart, int indexEnd, char *buffer)
{
}

// Trims whitespace from the beginning and end of the string.
void str_trim(char* ws_str)
{}

// Trims whitespace from the end of the string.
void str_trimEnd(char* ws_str)
{
}

// Trims whitespace from the beginning of the string.
void str_trimStart(char *ws_str)
{
}

// Returns the calling string value converted to uppercase.
void str_toUpperCase(char* str)
{}

// Returns the calling string value converted to lowercase.
void str_toLowerCase(char *str)
{}



    /*
    No idea how to handle locales:

    localeCompare()
    toLocaleLowerCase() <- wtf?
    toLocaleUpperCase() <- wtf?
    */

    /* REGEX METHODS - maybe do them with just strings
    match()
    mastchAll()
    replace()
    replaceAll()
    search()
    split()
    */