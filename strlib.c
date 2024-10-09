#include "strlib.h"

#include <stdio.h>
#include <stdlib.h>

// Function to decode a UTF-8 sequence into a Unicode code point
unsigned int decode_utf8(unsigned char* str, int* bytes) {
    // unsigned int decode_utf8(const unsigned char *str, int *bytes) {
    unsigned int code_point = 0;
    *bytes = 0;

    // Normal ascii
    if (str[0] < 0x80) {  // 1-byte sequence
        code_point = str[0];
        *bytes = 1;
    }
    // 0xE0 == 1110 0000
    // 0xC0 == 1100 0000
    // So this is true when str[0] follows the format 110xxxyy,
    // which is the first byte in a 2 byte sequence
    else if ((str[0] & 0xE0) == 0xC0) {  // 2-byte sequence
        // The first 3 bits were control characters, as previously stated
        // So by masking with 0x1F == 0001 1111 we get the last 5 bits, or the ones
        // not used as control characters Since every byte after the first byte is
        // two control characters ("10" followed by 6 bits), we left-shift by 6 bits
        // and let the second byte fill out the first 6 bits Lastly we mask the
        // second byte with 3F == 0011 1111, which is indeed the 6 out of the 8 bits
        // that aren't control characters
        code_point = ((str[0] & 0x1F) << 6) | (str[1] & 0x3F);
        *bytes = 2;
    }
    // Same pattern as above, only we're looking for the first 4 bits,
    // as the control characters 1110wwww
    else if ((str[0] & 0xF0) == 0xE0) {  // 3-byte sequence
        // First 4 characters are control characters, so we look at the last 4 bits
        // 0F == 1111
        // Then we can treat both the 2nd and 3rd byte the same,
        // since every byte after the first share the same pattern:
        // Two first "10" as control bits and the last 6 bits as meaningful data
        code_point =
            ((str[0] & 0x0F) << 12) | ((str[1] & 0x3F) << 6) | (str[2] & 0x3F);
        *bytes = 3;
    }
    // SAME story, only one more control character
    // and hence one less meaningful bit in the first byte
    else if ((str[0] & 0xF8) == 0xF0) {  // 4-byte sequence
        code_point = ((str[0] & 0x07) << 18) | ((str[1] & 0x3F) << 12) |
            ((str[2] & 0x3F) << 6) | (str[3] & 0x3F);
        *bytes = 4;
    }
    else {
        printf("Invalid UTF-8 sequence\n");
        exit(1);
    }

    return code_point;
}

int str_codePointAt(char* str, int index) {
    int length = 0;
    int total_bytes = 0;
    while (str[total_bytes] && length < index) {
        int current_byte = 0;
        decode_utf8((unsigned char*)&str[total_bytes], &current_byte);
        total_bytes += current_byte;
        length++;
    }
    if (length == index) {
        int current_byte = 0;
        return decode_utf8((unsigned char*)&str[total_bytes], &current_byte);
    }
    else {
        return -1;
    }
}

char* str_fromCodePoint(int num_val) {
    char* str = NULL;

    if (num_val < 0) {
        return str;
    }
    // 4 bytes = 32 bits + 1 for terminating 0
    // char* str = malloc(sizeof(char) * 33);
    else if (num_val <= 0x7f) {
        str = malloc(sizeof(char) + 1);
        str[0] = num_val;
        str[1] = 0;
    }
    else if (num_val <= 0x7ff) {
        // 2 bytes + terminating character
        str = malloc(sizeof(char) * 3);
        // Control characters of the first byte, left shifted to make room for the other bits
        char temp = 0b10 << 6;
        // We mask num_val to look at the first 6 bits. Then we "copy" them into temp
        temp |= (num_val & 0x3f);
        str[1] = temp;

        // Shift num_val now, to look at the final bits
        num_val >>= 6;
        // Same procedure, but with one more bit for control
        temp = 0b110 << 5;
        temp |= (num_val & 0x1f);
        str[0] = temp;
        // Terminating null
        str[2] = 0;
    }
    else if (num_val <= 0xffff) {
        str = malloc(sizeof(char) * 4);

    }
    else if (num_val <= 0x10ffff) {


    }
    printf("Final string: %s\n", str);
    return str;
}

char* to_code_unit(int num, int initial_size) {
    // Make room for all the bytes + 1 for terminating 0
    char* string = malloc(sizeof(char) * initial_size + 1);
    // No reason to loop if we're just dealing with ascii
    if (initial_size == 1) {
        string[0] = num;
    }

    else {
        // The difference between the 3 first bytes is 8 then 16
        // So for 2 byte value we dotn want to add anything
        // 
        char final_mask = 0b110 | (0b1000 |initial_size) ;
        if (initial_size == 2) {
            // Shift the 3 control bits, then mask the last 5
            string[0] = (0b110 << 5) | (num & 0b11111);
        }
        else if (initial_size == 3) {
            // Dec = 14
            string[0] = (0b1110 << 4) | (num & 0b1111);
        }
        else if (initial_size == 4) {
            // Dec = 30
            string[0] = (0b11110 << 3) | (num & 0b111);
        }
        // Next would theoretically be 62
        else {
            printf("Invalid UTF-8\n");
            free(string);
            return NULL;
        }

        int current_size = initial_size - 1;
        // 6 bits is the most we mask with at a time
        int mask_bits = 0b00111111;
        // We stop 1 iteration "earlier", since that's our initial control byte
        while (current_size > 1) {
            // The final control byte
            string[current_size] = (0b10 << 6) | (num & 0b111111);
            num >>= 6;

            current_size--;
        }
    }

    string[initial_size] = '\0';
}

// Returns the length of the given string
int str_length(char* str) {
    int length = 0;
    int total_bytes = 0;
    while (str[total_bytes]) {
        int current_byte = 0;
        // Normal char isn't enough, since we need to look at all 8 bits in the
        // byte, so type-cast to unsigned char pointer
        decode_utf8((unsigned char*)&str[total_bytes], &current_byte);
        // unsigned int code_point = decode_utf8(&str[total_bytes], &bytes);
        // printf("Code point: U+%04X, Bytes: %d\n", code_point, bytes);
        total_bytes += current_byte;
        length++;
    }
    return length;
}

// Copies the contents of one array into another. USE WITH CAUTION.
// Has no guard against overflow
void copy_arr(char* org_arr, char* buffer) { while (*buffer++ = *org_arr++); }

// Checks if the search string matches (part of) the org str
int str_searchMatch(char* org_str, char* searchString) {
    // Keep going until '\0' is met.
    do {
        if (*org_str++ != *searchString++) {
            return 0;
        }
    } while (*searchString);
    // } while (*searchString && *org_str);
    return 1;
}

// ONLY returns true if the two strings are identical
int str_match(char* org_str, char* searchString) {
    while (*searchString || *org_str) {
        // printf("Iteration: %d\n", iteration);
        if (*org_str++ != *searchString++) {
            return 0;
        }
    }
    return 1;
}

int is_lowerCase_letter(char sussy_c) { return 96 < sussy_c && sussy_c < 123; }

int is_upperCase_letter(char sussy_c) { return 64 < sussy_c && sussy_c < 91; }

/* Returns the character (exactly one UTF-16 code unit) at the specified index.
 * Accepts negative integers, which count back from the last string character.*/
char str_at(char* charAdr, int index) {
    if (index < 0) {
        index += str_length(charAdr);
    }
    int moves = 0;
    while (*charAdr != '\0' && index != moves) {
        moves++;
        charAdr++;
    }
    if (index == moves) {
        return *charAdr;
    }
    else {
        return 0;
    }
}

/* Determines whether a string ends with the characters of the string
 * searchString. */
int str_endsWith(char* charAdr, char* end_chars) {
    int length_org = str_length(charAdr);
    int length_check = str_length(end_chars);
    int length_dif = length_org - length_check;

    if (length_dif < 0) return 0;

    // Move the string pointer to match the end string
    charAdr += length_dif;

    return str_searchMatch(charAdr, end_chars);
}

// Determines whether the calling string begins with the characters of string
// searchString
int str_startsWith(char* charAdr, char* start_str) {
    return str_searchMatch(charAdr, start_str);
}

/* Determines whether the calling string contains searchString. */
int str_includes(char* org_str, char* searchString) {
    // We need to check for every character in the org_str if it and the following
    // charcters match the search string If we find a match, we stop. Otherwise we
    // increment the org_str and continue until 0 is met
    char* org_copy = org_str;
    char* search_copy = searchString;
    do {
        if (str_searchMatch(org_str++, searchString)) {
            return 1;
        }
    } while (*org_str);
    return 0;
}

/*Returns the index within this string of the first occurrence of searchValue,
 * or -1 if not found.*/
int str_indexOf(char* strToSearch, char* searchVal) {
    int length_search = str_length(searchVal);
    if (length_search == 0) {
        return -1;
    }

    int index = 0;
    char* copy = strToSearch;
    do {
        // Much like str_includes we must check with every character of strToSearch
        // being the first one And iterate for the full search value
        int matches = 0;
        for (int i = 0; i < length_search; i++) {
            if (strToSearch[index + i] != searchVal[i]) {
                break;
            }
            matches++;
        }
        if (matches == length_search) {
            return index;
        }
        else {
            index++;
        }
        // Continue as long as there is a value on the index
        // AND as long as there's enough room to fit the search string in the
        // original value
    } while (strToSearch[index + length_search - 1]);
    return -1;
}

/* Returns the index within this string of the last occurrence of searchValue,
 * or -1 if not found. */
int str_lastIndexOf(char* strToSearch, char* searchVal) {
    int length_org_str = str_length(strToSearch);
    int length_search = str_length(searchVal);
    if (length_search == 0) {
        return -1;
    }

    int index = length_org_str - 1;
    char* copy = strToSearch;
    do {
        int matches = 0;
        for (int i = 0; i < length_search; i++) {
            if (strToSearch[index + i] != searchVal[i]) {
                break;
            }
            matches++;
        }
        if (matches == length_search) {
            return index;
        }
        else {
            index--;
        }
        // Continue as long as there is a value on the index
        // AND as long as there's enough room to fit the search string in the
        // original value
    } while (strToSearch[index]);
    return -1;
}

// Pads the current string from the end with a given string and returns a new
// string of the length targetLength.
void str_padEnd(char* org_str, char* pad_str, int final_len, char* buffer) {
    int string_length = str_length(org_str);
    char* buffer_start = buffer;
    // Make a copy of the start adress for the pad str so we can use it multiple
    // times
    char* pad_pointer_copy = pad_str;

    copy_arr(org_str, buffer);

    // Start the pointer at the end of the pre-existing string
    buffer += string_length;
    while (string_length++ < final_len) {
        // Reset the pointer of pad_str every time it reaches the end
        if (!*pad_pointer_copy) {
            pad_pointer_copy = pad_str;
        }
        *buffer++ = *pad_pointer_copy++;
    }
    // Terminating 0
    *(buffer) = 0;
    // printf("Buffer: %s\n", buffer - final_len);
}

// Pads the current string from the end with a given string and returns a new
// string of the length targetLength
void str_padStart(char* org_str, char* pad_str, int final_len, char* buffer) {
    int string_length = str_length(org_str);
    int additional_spots_needed = final_len - string_length;

    if (additional_spots_needed < 0) {
        copy_arr(org_str, buffer);
    }
    else {
        // Make a copy of the start adress for the pad str so we can use it multiple
        // times
        char* pad_pointer_copy = pad_str;
        // Dont fill the buffer from the start - we want to leave room for the
        // padding in the begginning
        copy_arr(org_str, buffer + additional_spots_needed);

        while (string_length++ < final_len) {
            // Reset the pointer of pad_str every time it reaches the end
            if (!*pad_pointer_copy) {
                pad_pointer_copy = pad_str;
            }
            *buffer++ = *pad_pointer_copy++;
        }
        // Add a terminating 0 at the end of the string full length
        // *(buffer + final_len) = 0;
    }
}

// Returns a string consisting of the elements of the object repeated count
// times.
void str_repeat(char* str_to_repeat, int repeat_amt, char* buffer) {
    char* repeat_pointer_copy = str_to_repeat;
    for (int i = 0; i < repeat_amt; i++) {
        while (*repeat_pointer_copy) {
            *buffer++ = *repeat_pointer_copy++;
        }
        repeat_pointer_copy = str_to_repeat;
    }
    *buffer = '\0';
}

// SUBTLE DIFFERENCES BETWEEN SUBSTRING AND SLICE

// Extracts a section of a string and returns a new string
// Same behaviour as substring, only it doesn't swap end and start if: end <
// start
void str_slice(char* org_str, int indexStart, int indexEnd, char* buffer) {
    int length = str_length(org_str);

    // If they are negative, we count from the end
    if (indexEnd < 0) {
        indexEnd += length;
    }
    if (indexStart < 0) {
        indexStart += length;
    }
    if (indexEnd > indexStart) {
        for (int i = indexStart; i < indexEnd; i++) {
            // STOP if we're at an invalid index
            if (i < 0 || i >= length) {
                break;
            }
            *buffer++ = *(org_str + i);
        }
    }
    *buffer = 0;
}

// Returns a new string containing characters of the calling string from (or
// between) the specified index (or indices).
void str_substring(char* org_str, int indexStart, int indexEnd, char* buffer) {
    int length = str_length(org_str);

    // If they are negative, we count from the end
    if (indexEnd < 0) {
        indexEnd += length;
    }
    if (indexStart < 0) {
        indexStart += length;
    }

    // If we're supposed to start after the final index, we simply swap the two.
    // You will get a return value!!
    if (indexEnd < indexStart) {
        int temp = indexEnd;
        indexEnd = indexStart;
        indexStart = temp;
    }

    for (int i = indexStart; i < indexEnd; i++) {
        // STOP if we're at an invalid index
        if (i < 0 || i >= length) {
            break;
        }
        *buffer++ = *(org_str + i);
    }
    *buffer = 0;
}

// Trims whitespace from the beginning and end of the string.
char* str_trim(char* ws_str) {
    char* start_trimmed = str_trimStart(ws_str);
    str_trimEnd(start_trimmed);
    return start_trimmed;
}

// Trims whitespace from the end of the string.
void str_trimEnd(char* ws_str) {
    int length = str_length(ws_str);
    // Start from the end of the string
    ws_str += length - 1;
    // Replacing any spaces with a terminating 0
    while (*ws_str == ' ') {
        *ws_str-- = 0;
    }
}

// Trims whitespace from the beginning of the string.
char* str_trimStart(char* ws_str) {
    // Simply move the pointer one spot as long as it finds a space
    while (*ws_str == ' ') {
        ws_str++;
    }
    // Return the pointer - we now ignore the previous white spaces
    return ws_str;
}

// Returns the calling string value converted to uppercase.
void str_toUpperCase(char* str) {
    while (*str) {
        if (is_lowerCase_letter(*str)) {
            *str -= 32;
        }
        str++;
    }
}

// Returns the calling string value converted to lowercase.
void str_toLowerCase(char* str) {
    while (*str) {
        if (is_upperCase_letter(*str)) {
            *str += 32;
        }
        str++;
    }
}


/* REGEX METHODS - maybe do them with just strings
match()
mastchAll()
replace()
replaceAll()
search()
split()
*/