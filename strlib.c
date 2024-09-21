#include <stdio.h>
#include "strlib.h"

// Returns the length of the given string
int str_length(char *str)
{
    int length = 0;
    while (*str++)
    {
        length++;
    }
    return length;
}

/* Returns the character (exactly one UTF-16 code unit) at the specified index. Accepts negative integers, which count back from the last string character.*/
char str_at(char *charAdr, int index)
{
    if (index < 0)
    {
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
int str_endsWith(char *charAdr, char *end_chars)
{
    int length_org = str_length(charAdr);
    int length_check = str_length(end_chars);
    int length_dif = length_org - length_check;

    if (length_dif < 0)
        return 0;

    // Move the string pointer to match the end string
    charAdr += length_dif;

    return str_match(charAdr, end_chars);
}

// Determines whether the calling string begins with the characters of string searchString
int str_startsWith(char *charAdr, char *start_str)
{
    return str_match(charAdr, start_str);
}

/* Determines whether the calling string contains searchString. */
int str_includes(char *org_str, char *searchString)
{
    // We need to check for every character in the org_str if it and the following charcters match the search string
    // If we find a match, we stop. Otherwise we increment the org_str and continue until 0 is met
    do
    {
        if (str_match(org_str++, searchString))
        {
            return 1;
        }
    } while (*org_str);
    return 0;
}

// Checks if two strings are equal
int str_match(char *org_str, char *searchString)
{
    // char *temp_ptr = searchString;
    // Keep going until '\0' is met.
    do
    {
        if (*org_str++ != *searchString++)
        {
            return 0;
        }
    } while (*searchString);
    return 1;
}

/*Returns the index within this string of the first occurrence of searchValue, or -1 if not found.*/
int str_indexOf(char *strToSearch, char *searchVal)
{
    int length_search = str_length(searchVal);
    if ( length_search == 0 )
    {
        return -1;
    }

    int index = 0;
    char *copy = strToSearch;
    do
    {
        // Much like str_includes we must check with every character of strToSearch being the first one
        // And iterate for the full search value
        int matches = 0;
        for (int i = 0; i < length_search; i++)
        {
            if (strToSearch[index + i] != searchVal[i])
            {
                break;
            }
           matches++;
        }
        if (matches == length_search)
        {
            return index;
        }
        else
        {
            index++;
        }
        // Continue as long as there is a value on the index
        // AND as long as there's enough room to fit the search string in the original value
    } while (strToSearch[index + length_search - 1]);
    return -1;
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
void str_trim(char *ws_str)
{
}

// Trims whitespace from the end of the string.
void str_trimEnd(char *ws_str)
{
}

// Trims whitespace from the beginning of the string.
void str_trimStart(char *ws_str)
{
}

// Returns the calling string value converted to uppercase.
void str_toUpperCase(char *str)
{
}

// Returns the calling string value converted to lowercase.
void str_toLowerCase(char *str)
{
}

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