#include "strlib.h"

#include <stdio.h>
#include <stdlib.h>


// typedef struct String
// {
//   char* str_start;
//   int byte_length;
//   int length;
//   char* byte_LUT;
// } String;

// Custom struct to return in case of errors
static const String INVALID_STRING = { NULL, 0, 0, NULL };

String* str_construct(char* str) {
  // printf("Constructing\n");
  String* new_string = malloc(sizeof(String));

  int bytes_used = 0;
  int string_length = 0;
  char* byte_length_of_code_points = malloc(sizeof(char) * string_length + 1);
  char* start_byte_of_code_points = malloc(sizeof(char) * string_length + 1);

  // Creates byte index table
  while (str[bytes_used]) {
    // Normal char isn't enough, since we need to look at all 8 bits in the
    // byte, so type-cast to unsigned char pointer
    start_byte_of_code_points[string_length] = bytes_used;
    bytes_used += bytes_in_code_point((unsigned char*)str + bytes_used);
    byte_length_of_code_points[string_length++] = bytes_used;
    // byte_indexes_of_code_points[string_length++] = decode_utf8((unsigned char*) str + bytes_used);
  }

  start_byte_of_code_points[string_length] = 0;
  byte_length_of_code_points[string_length] = 0;

  char* new_char_arr = malloc(sizeof(char) * string_length + 1);

  copy_arr(str, new_char_arr);

  new_string->str_start = new_char_arr;
  // printf("String: %s\n", new_char_arr);

  // printf("==============\n");
  // printf("point_len_LUT:\n");
  // for (int i = 0; i < string_length; i++)
  // {
  //   printf("[%d: %d] ", i, byte_length_of_code_points[i]);
  // }
  // printf("\n\n");

  // printf("byte_start_LUT:\n");
  // for (int i = 0; i < string_length; i++)
  // {
  //   printf("%d: %d ", i, start_byte_of_code_points[i]);
  // }
  // printf("\n\n");
  // printf("==============\n");


  new_string->byte_length = bytes_used;
  new_string->length = string_length;
  new_string->point_lengths = byte_length_of_code_points;
  new_string->byteIndexLookup = start_byte_of_code_points;

  return new_string;
}

void str_destruct(String* str_to_free) {
  if (str_to_free == NULL) {
    return;
  }
  if (str_to_free->str_start != NULL) {
    free(str_to_free->str_start);
    str_to_free->str_start = NULL;
  }
  if (str_to_free->point_lengths != NULL) {
    free(str_to_free->point_lengths);
    str_to_free->point_lengths = NULL;
  }
  if (str_to_free->byteIndexLookup != NULL) {
    free(str_to_free->byteIndexLookup);
    str_to_free->point_lengths = NULL;
  }
  free(str_to_free);

}



// Function to decode a UTF-8 sequence into a Unicode code point
unsigned int decode_utf8(unsigned char* str) {
  // unsigned int decode_utf8(const unsigned char *str, int *bytes) {
  unsigned int code_point = 0;

  // Normal ascii
  if (str[0] < 0x80) {  // 1-byte sequence
    // printf("Issa 1 byte sequence\n");
    code_point = str[0];

  }
  // 0xE0 == 1110 0000
  // 0xC0 == 1100 0000
  // So this is true when str[0] follows the format 110xxxyy,
  // which is the first byte in a 2 byte sequence
  else if ((str[0] & 0xE0) == 0xC0) {  // 2-byte sequence
    // The first 3 bits were control characters, as previously stated
    // So by masking with 0x1F == 0001 1111 we get the last 5 bits, or the ones
    // not used as control characters. Since every byte after the first byte is
    // two control characters ("10" followed by 6 bits), we left-shift by 6 bits
    // and let the second byte fill out the first 6 bits. Lastly we mask the
    // second byte with 3F == 0011 1111, which is indeed the 6 out of the 8 bits
    // that aren't control characters
    code_point = ((str[0] & 0x1F) << 6) | (str[1] & 0x3F);

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

  }
  // SAME story, only one more control character
  // and hence one less meaningful bit in the first byte
  else if ((str[0] & 0xF8) == 0xF0) {  // 4-byte sequence
    code_point = ((str[0] & 0x07) << 18) | ((str[1] & 0x3F) << 12) |
      ((str[2] & 0x3F) << 6) | (str[3] & 0x3F);
  }
  else {
    printf("Invalid UTF-8 sequence\n");
    exit(1);
  }

  return code_point;
}

// Returns the bytes of a code point
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

// Returns the code point at a given index
unsigned int str_codePointAt(String str, int index) {
  if (str.length > index && index >= 0)
  {

    char byteToStartAt = str.byteIndexLookup[index];
    // printf("Byte to start at: %d\n", str.byteIndexLookup[index]);
    // printf("Byte to start at: %d\n", str.point_lengths[index]);
    unsigned int codePoint = decode_utf8((unsigned char*)(str.str_start + byteToStartAt));
    // printf("Code point at %d: %d\n", index, codePoint);
    return codePoint;
  }
  return -1;

  // }
}

String* str_fromCodePoint(int num_val) {
  int amount_of_bytes = 0;
  if (num_val < 0 || num_val > 0x10ffff) {
    return NULL;
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

  char* code_unit = to_code_unit(num_val, amount_of_bytes);
  return str_construct(code_unit);

}

char* to_code_unit(int num, int initial_size) {
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

    while (size > 0) {
      // "10" is the start of every trailing byte.
      // So append the 10, shift them to the front of the byte,
      // Mask the last 6 bits of the number and "add" them together
      string[size] = (0b10 << 6) | (num & 0b111111);

      // Finally right shift the number in preperation for the next byte
      num >>= 6;
      size--;
    }

    // Handling the "first" control byte (we could also do this before the while loop)
    // We dont shift for 4 byters, but the rest get right shifted and then set their first bit to 0 
    char final_byte_start = (0b11110 >> (4 - initial_size)) & 0b11110;
    // Set the "header" of the byte, shift it "7 - initial size" spots to the left,
    // since the larger the header, the smaller the shift.
    // No masking required in this case
    string[0] = (final_byte_start << (0b111 - initial_size)) | num;
  }

  // printf("Final string: %s\n", string);
  return string;
}

// Returns the length of the given string
int str_length(String str) {
  return str.length;
}

// Copies the contents of one array into another. USE WITH CAUTION.
// Has no guard against overflow
void copy_arr(char* org_arr, char* buffer) { while ((*buffer++ = *org_arr++)); }

// // Checks if the search string matches (part of) the org str
int str_searchMatch(String org_str, String searchString) {
  if (org_str.str_start == NULL && searchString.str_start == NULL) {
    return 1;
  }
  else if (org_str.str_start == NULL || searchString.str_start == NULL) {
    return 0;
  }

  // Keep going until '\0' is met.
  do {
    if (*org_str.str_start++ != *searchString.str_start++) {
      return 0;
    }
  } while (*searchString.str_start);
  return 1;
}

// // ONLY returns true if the two strings are identical
int str_match(String org_str, String searchString) {
  // If both are null, they are technically a match?
  if (org_str.str_start == NULL && searchString.str_start == NULL) {
    return 1;
  }
  // If only one is null, it's clearly not a match
  else if (org_str.str_start == NULL || searchString.str_start == NULL) {
    return 0;
  }
  while (*searchString.str_start || *org_str.str_start) {
    if (*org_str.str_start++ != *searchString.str_start++) {
      return 0;
    }
  }
  return 1;
}

int is_lowerCase_letter(char sussy_c) { return 96 < sussy_c && sussy_c < 123; }

int is_upperCase_letter(char sussy_c) { return 64 < sussy_c && sussy_c < 91; }

// /* Returns the character (exactly one UTF-16 code unit) at the specified index.
//  * Accepts negative integers, which count back from the last string character.*/
unsigned int str_at(String charAdr, int index) {
  if (index < 0) {
    index += charAdr.length;
  }
  if (index >= 0 && index < charAdr.length)
  {
    return str_codePointAt(charAdr, index);
  }
  return -1;
}

// /* Determines whether a string ends with the characters of the string
//  * searchString. */

int str_endsWith(String str, String compStr) {
  int length_dif = str.byte_length - compStr.byte_length;

  if (length_dif < 0) return 0;

  // Move the string pointer to match the end string
  str.str_start += length_dif;

  return str_searchMatch(str, compStr);
}

// // Determines whether the calling string begins with the characters of string
int str_startsWith(String charAdr, String start_str) {
  return str_searchMatch(charAdr, start_str);
}

// /* Determines whether the calling string contains searchString. */
int str_includes(String org_str, String searchString) {
  // We need to check for every character in the org_str if it and the following
  // charcters match the search string If we find a match, we stop. 
  // Otherwise we increment the org_str and continue until 0 is met
  do {
    if (str_searchMatch(org_str, searchString)) {
      return 1;
    }
    org_str.str_start++;
    searchString.str_start++;
  } while (*(org_str.str_start));
  return 0;
}

// /*Returns the index within this string of the first occurrence of searchValue,
//  * or -1 if not found.*/
int str_indexOf(String strToSearch, String searchVal) {
  if (searchVal.byte_length <= 0) {
    printf("Search val has no length\n");
    return -1;
  }

  int index = 0;
  int passed_bytes = 0;
  char* LUT_ptr_copy = searchVal.point_lengths;
  do {
    // Much like str_includes we must check with every character of strToSearch being the first one
    //  And iterate for the full search value
    int matches = 0;
    for (int i = 0; i < searchVal.byte_length; i++) {
      if (strToSearch.str_start[passed_bytes + i] != searchVal.str_start[i]) {
        break;
      }
      matches++;
    }
    if (matches == searchVal.byte_length) {
      return index;
    }
    else {
      if (!(*LUT_ptr_copy)) {
        // printf("Reseting the pointer\n");
        LUT_ptr_copy = searchVal.point_lengths;
      }
      // printf("Bytes here: %d\n", *LUT_ptr_copy);
      passed_bytes += *LUT_ptr_copy;
      LUT_ptr_copy++;
      index++;
    }
    // printf("Passed bytes: %d\n", passed_bytes);
    // Continue as long as there is a value on the index
    // AND as long as there's enough room to fit the search string in the
    // original value
  } while (strToSearch.str_start[passed_bytes + searchVal.byte_length - 1]);
  return -1;
}

// /* Returns the index within this string of the last occurrence of searchValue,
//  * or -1 if not found. */
int str_lastIndexOf(String strToSearch, String searchVal) {

  if (searchVal.byte_length <= 0 || searchVal.byte_length > strToSearch.byte_length) {
    return -1;
  }

  int index = 0;
  int passed_bytes = 0;
  int last_correct_index = -1;
  do {
    int matches = 0;
    for (int i = 0; i < searchVal.byte_length; i++) {
      if (strToSearch.str_start[passed_bytes + i] != searchVal.str_start[i]) {
        break;
      }
      matches++;
    }
    if (matches == searchVal.byte_length) {
      last_correct_index = index;
    }

    passed_bytes += searchVal.point_lengths[index];
    index++;

  } while (strToSearch.str_start[passed_bytes + searchVal.byte_length - 1]);
  return last_correct_index;
}

// // Pads the current string from the end with a given string and returns a new
// // string of the length targetLength.
String* str_padEnd(String org_str, String pad_str, int final_len) {

  // Return a copy of the original if the length is already met
  if (org_str.length >= final_len) {
    return str_construct(org_str.str_start);
  }
  // Make a copy of the start adress for the pad str so we can use it multiple
  // times
  char* pad_pointer_copy = pad_str.str_start;
  char* LUT_copy = pad_str.point_lengths;
  int code_points_needed = final_len - org_str.length;
  int bytes_needed = 0;
  // Since there's no guarantee that the padding string will end on the last index,
  // we can't just take the byte length of the padding string.
  // Instead we need to count the amount of bytes needed, given the amount of pad_str code points we'll be using
  for (int i = 0; i < code_points_needed; i++)
  {
    if (!*LUT_copy) {
      LUT_copy = pad_str.point_lengths;
    }
    // We need to prefix the ++, since the next value in the LUT reveals how long the current code point is
    bytes_needed += *(++LUT_copy);
  }

  char* temp_arr = malloc(sizeof(char) * bytes_needed + 1);
  copy_arr(org_str.str_start, temp_arr);

  int total_itearations = final_len - org_str.length;
  for (int i = 0; i < total_itearations; i++)
  {
    // Reset the pointer of pad_str every time it reaches the end
    if (!*pad_pointer_copy) {
      pad_pointer_copy = pad_str.str_start;
    }
    // We need to prefix the ++, since the next value in the LUT reveals how long the current code point is
    for (int j = 0; j < *(++pad_str.point_lengths); j++)
    {
      *temp_arr++ = *pad_pointer_copy++;
    }
  }
  *temp_arr = '\0';
  String* string_struct = str_construct(temp_arr);
  free(temp_arr);
  return string_struct;
}

// // Pads the current string from the end with a given string and returns a new
// // string of the length targetLength
String* str_padStart(String org_str, String pad_str, int final_len) {

  // Make a copy of the start adress for the pad str so we can use it multiple
  // times
  char* pad_pointer_copy = pad_str.str_start;
  char* temp_arr = malloc(sizeof(char) * final_len + 1);


  int total_itearations = final_len - org_str.length;
  for (int i = 0; i < total_itearations; i++)
  {
    // Reset the pointer of pad_str every time it reaches the end
    if (!*pad_pointer_copy) {
      pad_pointer_copy = pad_str.str_start;
    }
    // We need to prefix the ++, since we're actually interested in the byte length of the upcoming code point, not this
    for (int j = 0; j < *(++pad_str.point_lengths); j++)
    {
      *temp_arr++ = *pad_pointer_copy++;
    }
  }
  copy_arr(org_str.str_start, temp_arr);
  *temp_arr = '\0';
  String* string_struct = str_construct(temp_arr);
  free(temp_arr);
  return string_struct;

  // Pad nothing if the string already exceeds the desired length
  // if ((final_len - string_length) * bytes_in_pad < 0) {
  //   copy_arr(org_str, buffer);
  // }
  // else {
  //   // Make a copy of the start adress for the pad str so we can use it multiple times
  //   char* pad_pointer_copy = pad_str;
  //   while (string_length++ < final_len) {
  //     // Reset the pointer of pad_str every time it reaches the end
  //     if (!*pad_pointer_copy) {
  //       pad_pointer_copy = pad_str;
  //     }
  //     int byte_amount = bytes_in_code_point((unsigned char*)pad_pointer_copy);
  //     while (byte_amount > 0) {
  //       *buffer++ = *pad_pointer_copy++;
  //       byte_amount--;
  //     }
  //   }
  //   // Can just copy last - buffer should be pointing to the end of the string anyway
  //   copy_arr(org_str, buffer);
  // }
}

// // Returns a string consisting of the elements of the object repeated count
// // times.
String* str_repeat(String str_to_repeat, int repeat_amt) {
  char* buffer = malloc(sizeof(char) * str_to_repeat.byte_length * repeat_amt + 1);
  char* repeat_pointer_copy = str_to_repeat.str_start;
  int lut_index = 0;
  for (int i = 0; i < repeat_amt; i++) {
    while (*repeat_pointer_copy) {
      int byte_amount = str_to_repeat.point_lengths[lut_index++];
      while (byte_amount > 0) {
        *buffer++ = *repeat_pointer_copy++;
        byte_amount--;
      }
      // Wrap around if the index exceeds the length
      lut_index %= str_to_repeat.length;
      // lut_index = lut_index % str_to_repeat.length;
    }
    repeat_pointer_copy = str_to_repeat.str_start;
  }
  *buffer = '\0';

  String* string_ptr = str_construct(buffer);
  free(buffer);
  return string_ptr;
}

// SUBTLE DIFFERENCES BETWEEN SUBSTRING AND SLICE

// Extracts a section of a string and returns a new string
// Same behaviour as substring, only it doesn't swap end and start if: end <
// start
String* str_slice(String org_str, int indexStart, int indexEnd) {

  // If they are negative, we count from the end
  if (indexEnd < 0) {
    indexEnd += org_str.length;
  }
  if (indexStart < 0) {
    indexStart += org_str.length;
  }
  if (indexEnd > indexStart && indexStart >= 0 && indexEnd < org_str.byte_length) {
    int startByte = org_str.byteIndexLookup[indexStart];
    int endByte = org_str.byteIndexLookup[indexEnd];
    char* buffer = malloc(sizeof(char) * (endByte - startByte) + 1);
    unsigned char* buffer_ptr = buffer;
    for (int i = startByte; i < endByte; i++) {
      *buffer_ptr++ = org_str.str_start[i];
    }
    *buffer_ptr = 0;
    String* string_ptr = str_construct(buffer);
    free(buffer);
    return string_ptr;
  }
  printf("Returning null because badd indexes\n");
  return NULL;
}

// // Returns a new string containing characters of the calling string from (or
// // between) the specified index (or indices).
String* str_substring(String org_str, int indexStart, int indexEnd) {
  // If they are negative, we count from the end
  if (indexEnd < 0) {
    indexEnd += org_str.length;
  }
  if (indexStart < 0) {
    indexStart += org_str.length;
  }

  // If we're supposed to start after the final index, we simply swap the two.
  // You will get a return value!! (unless out of bounds)
  if (indexEnd < indexStart) {
    int temp = indexEnd;
    indexEnd = indexStart;
    indexStart = temp;
  }

  if (indexStart >= 0 && indexEnd < org_str.byte_length) {
    int startByte = org_str.byteIndexLookup[indexStart];
    int endByte = org_str.byteIndexLookup[indexEnd];
    char* buffer = malloc(sizeof(char) * (endByte - startByte) + 1);
    char* buffer_ptr = buffer;

    for (int i = startByte; i < endByte; i++) {
      *buffer_ptr++ = org_str.str_start[i];
    }

    *buffer_ptr = 0;
    String* string_ptr = str_construct(buffer);
    free(buffer);
    return string_ptr;
  }
  printf("Returning null because badd indexes\n");
  return NULL;
}

// // Trims whitespace from the beginning and end of the string.
String* str_trim(String ws_str) {
  String* start_trimmed = str_trimStart(ws_str);
  String* fully_trimmed = str_trimEnd(*start_trimmed);
  str_destruct(start_trimmed);
  return fully_trimmed;
}

//  Trims whitespace from the end of the string.
String* str_trimEnd(String ws_str) {
  ws_str.str_start += ws_str.byte_length - 1;
  // Replacing any spaces with a terminating 0
  while (*ws_str.str_start == ' ') {
    *ws_str.str_start-- = 0;
  }
  return str_construct(ws_str.str_start);
}

// // Trims whitespace from the beginning of the string.
String* str_trimStart(String ws_str) {
  // Simply move the pointer one spot as long as it finds a space
  while (*ws_str.str_start == ' ') {
    ws_str.str_start++;
  }
  return str_construct(ws_str.str_start);
}

// // Returns the calling string value converted to uppercase.
String* str_toUpperCase(String str) {
  for (int i = 0; i < str.length; i++)
  {
    if (is_lowerCase_letter(str.str_start[str.byteIndexLookup[i]])) {
      str.str_start[str.byteIndexLookup[i]] -= 32;
    }
  }

  return str_construct(str.str_start);
}

// // Returns the calling string value converted to lowercase.
String* str_toLowerCase(String str) {
  for (int i = 0; i < str.length; i++)
  {
    if (is_upperCase_letter(str.str_start[str.byteIndexLookup[i]])) {
      str.str_start[str.byteIndexLookup[i]] -= 32;
    }
  }

  return str_construct(str.str_start);
}


// /* REGEX METHODS - maybe do them with just strings
// match()
// mastchAll()
// replace()
// replaceAll()
// search()
// split()
// */