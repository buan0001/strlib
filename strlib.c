#include <stdio.h>
#include "strlib.h"

char str_at(int index, char *charAdr)
{
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
        return '\0';
    }
}

int endsWith(char last_c, char *charAdr)
{
    // Keep going until '\0' is met.
    while (*(++charAdr))
        ;
    // At this point *charAdr will be the null character. So go one back and compare it to the desired check char
    return last_c == *(--charAdr);
}

int includes(char *org_str, char* comp_str)
{
    char* temp_ptr = comp_str;
    // Keep going until '\0' is met.
    while (*(++org_str));
}

/*


includes()
indexOf()
lastIndexOf()
localeCompare()
padEnd()
padStart()
repeat()
slice()
startsWith()
substring()
toLocaleLowerCase() <- wtf?
toLocaleUpperCase() <- wtf?
toString()
toUpperCase()
toLowerCase()
trim()
trimEnd()
trimStart()
valueOf()
*/

/* REGEX METHODS:
match()
mastchAll()
replace()
replaceAll()
search()
split()
*/