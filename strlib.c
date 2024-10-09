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
        // printf("Issa 1 byte sequence\n");
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

int bytes_in_code_point(unsigned char* point) {
    int bytes = 0;
    if (point[0] < 0x80) {
        bytes = 1;
    }
    else if ((point[0] & 0xE0) == 0xC0) {
        bytes = 2;
    }
    else if ((point[0] & 0xF0) == 0xE0) {
        bytes = 3;
    }
    else if ((point[0] & 0xF8) == 0xF0) {
        bytes = 4;
    }
    else {
        printf("Invalid UTF-8 sequence\n");
        exit(1);
    }

    return bytes;
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
    int amount_of_bytes = 0;
    if (num_val < 0) {
        return str;
    }
    else if (num_val <= 0x7f) {
        amount_of_bytes = 1;
    }
    else if (num_val <= 0x7ff) {
        amount_of_bytes = 2;
    }
    else if (num_val <= 0xffff) {
        amount_of_bytes = 3;
    }
    else if (num_val <= 0x10ffff) {
        amount_of_bytes = 4;
    }
    str = to_code_unit(num_val, amount_of_bytes);
    // printf("Final string: %s\n", str);
    return str;
}

char* to_code_unit(int num, int initial_size) {
    // printf("Number: %d, bytes used: %d\n", num, initial_size);
    // Make room for all the bytes + 1 for terminating 0
    char* string = malloc(sizeof(char) * (initial_size + 1));
    string[initial_size] = '\0';
    // No reason to loop if we're just dealing with ascii
    if (initial_size == 1) {
        string[0] = num;
    }
    else if (initial_size > 4) {
        printf("Invalid UTF-8\n");
        free(string);
        return NULL;
    }
    else {
        // -1 from initial size, since the last array spot is reserved for terminating 0
        int size = initial_size - 1;

        // We stop 1 iteration "earlier", since that's our initial control byte
        while (size > 0) {
            // "10" is the start of every trailing byte.
            // So append the 10, shift them to the front of the byte,
            // Mask the last 6 bits of the number and "add" them together
            string[size] = (0b10 << 6) | (num & 0b111111);

            // Finally right shift the number in preperation for the next byte
            num >>= 6;
            size--;
        }

        // We dont shift for 4 byters, but the rest get right shifted and then set their first bit to 0 
        char final_byte_start = (0b11110 >> (4 - initial_size)) & 0b11110;
        // Set the "header" of the byte, shift it "7 - initial size" spots to the left,
        // since the larger the header, the smaller the shift
        // Finally we can mask the number according to how many bits are left over from the "header"
        // No masking required in this case
        string[0] = (final_byte_start << (0b111 - initial_size)) | num;
    }

    // printf("Final string: %s\n", string);
    return string;
}

// Returns the length of the given string
int str_length(char* str) {
    int trash;
    return length_and_bytes(str, &trash);
}

int length_and_bytes(char* str, int* byte_count) {
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
    *byte_count = total_bytes;
    return length;
}

// Copies the contents of one array into another. USE WITH CAUTION.
// Has no guard against overflow
void copy_arr(char* org_arr, char* buffer) { while (*buffer++ = *org_arr++); }

// Checks if the search string matches (part of) the org str
int str_searchMatch(char* org_str, char* searchString) {
    if (org_str == NULL && searchString == NULL) {
        return 1;
    }
    else if (org_str == NULL || searchString == NULL) {
        return 0;
    }

    // Keep going until '\0' is met.
    do {
        if (*org_str++ != *searchString++) {
            return 0;
        }
    } while (*searchString);
    return 1;
}

// ONLY returns true if the two strings are identical
int str_match(char* org_str, char* searchString) {
    // printf("Org str: %s. Compare string: %s\n", org_str, searchString);
    if (org_str == NULL && searchString == NULL) {
        return 1;
    }
    else if (org_str == NULL || searchString == NULL) {
        return 0;
    }
    while (*searchString || *org_str) {
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
char* str_at(char* charAdr, int index) {

    int length = 0;
    int total_bytes = 0;
    // Make index not negative
    // printf("Looking for value at %d in string: %s\n", index, charAdr);
    if (index < 0) {
        int temp = str_length(charAdr);
        // printf("Length: %d\n",temp);
        index += temp;
    }
    // printf("Looking for value at %d in string: %s\n", index, charAdr);
    // printf("New while loop\n");
    while (charAdr[total_bytes] && length < index) {
        // printf("Totalt bytes: %d\n", total_bytes);
        int current_byte = 0;
        // We just ignore the return value since we only care about the byte length
        decode_utf8((unsigned char*)&charAdr[total_bytes], &current_byte);
        // unsigned int code_point = decode_utf8(&str[total_bytes], &bytes);
        // printf("Code point: U+%04X, Bytes: %d\n", code_point, bytes);
        total_bytes += current_byte;
        length++;
        // printf("Finished loop sucessfully\n");
    }
    // printf("Right after loop\n");
    if (index > length || index < 0) {
        printf("Index out of bounds\n");
        return NULL;
    }
    else {
        // printf("decoding to code unit\n");
        int byte_size = 0;
        unsigned int num_version = decode_utf8((unsigned char*)&charAdr[total_bytes], &byte_size);
        return to_code_unit(num_version, byte_size);
    }
}

/* Determines whether a string ends with the characters of the string
 * searchString. */

 // TODO: UTF-8-ify
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
    do {
        if (str_searchMatch(org_str++, searchString)) {
            return 1;
        }
    } while (*org_str);
    return 0;
}

/*Returns the index within this string of the first occurrence of searchValue,
 * or -1 if not found.*/

 // TODO: UTF-8-ify
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
 // TODO: UTF-8-ify
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
 // TODO: UTF-8-ify
void str_padEnd(char* org_str, char* pad_str, int final_len, char* buffer) {
    int byte_size = 0;
    int actual_length = length_and_bytes(org_str, &byte_size);
    char* buffer_start = buffer;
    // Make a copy of the start adress for the pad str so we can use it multiple
    // times
    char* pad_pointer_copy = pad_str;

    copy_arr(org_str, buffer);

    // Start the pointer at the end of the pre-existing string
    buffer += byte_size;
    while (actual_length++ < final_len) {
        // Reset the pointer of pad_str every time it reaches the end
        if (!*pad_pointer_copy) {
            pad_pointer_copy = pad_str;
        }
        int byte_amount = 0;
        decode_utf8(*pad_pointer_copy, &byte_amount);
        while (byte_amount > 1) {
            *buffer++ = *pad_pointer_copy++;
            byte_amount--;
        }
        // *buffer++ = *pad_pointer_copy++;
    }
    // Terminating 0
    *(buffer) = 0;
    // printf("Buffer: %s\n", buffer - final_len);
}

// Pads the current string from the end with a given string and returns a new
// string of the length targetLength
 // TODO: UTF-8-ify
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
 // TODO: UTF-8-ify
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
 // TODO: UTF-8-ify
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
 // TODO: UTF-8-ify
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
    int byte_length = bytes_in_code_point((unsigned char*)ws_str);
    // Start from the end of the string
    ws_str += byte_length - 1;
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