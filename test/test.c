#include <stdio.h>
#include <stdlib.h>

// Function to decode a UTF-8 sequence into a Unicode code point
unsigned int decode_utf8(unsigned char *str, int *bytes) {
  // unsigned int decode_utf8(const unsigned char *str, int *bytes) {
  printf("Converting string: %s\n", str);
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
  } else {
    printf("Invalid UTF-8 sequence\n");
    exit(1);
  }

  return code_point;
}

int main() {
  char final_mask = (0b11110 >> (0b100 - 2)) & 0b11110;
  printf("thing: %x\n", final_mask);
  // Normal char isn't enough, since we need to look at all 8 bits in the byte,
  // not just 7
  // char *list = "ab";
  // // unsigned char *list = "🍎aæ";
  // // char* list = "bær";
  // // char list[] = "aæøå";
  // // printf("printing for %s\n", list);

  // int index = 0;
  // while (list[index]) {
  //   int bytes = 0;
  //   unsigned int code_point = decode_utf8("a", &bytes);
  //   // unsigned int code_point = decode_utf8((unsigned char*)&list[index], &bytes);
  //   printf("Code point: U+%04X, Bytes: %d\n", code_point, bytes);
  //   index += bytes;
  // }

  return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// void int_to_bin(unsigned int num, char str[]);

// int main() {
//     char buffer[50];
// //   char* list = "bær";
// //   char* test = "æ";
// //   int_to_bin((unsigned int)test[0], buffer);
// //   int index = 0;
// //   printf("s\n", buffer);
// //   printf("\n");
// //   char* list = "🍎aæ";
//   char list[] = "å";
//   printf("printing for %s\n", list);
// //   int test = 0xc3a6;
// //   printf("æ == test: %d\n", test == ("æ"[0] + "æ"[1]));
//   int index = 0;
//   printf("\n");
//   int new_buff[20];
//   while (list[index])
//   {
//       printf("%x\n", list[index]);
//       int masked_val = list[index] & 0xff;
//       new_buff[index] = masked_val;
//       printf("%x\n\n", masked_val);
//       index++;
//   }
//   printf("new buff: %s\n", *new_buff);
//   return 0;
// }

// void int_to_bin(unsigned int num, char str[]) {
//     printf("converting %x (%d)\n", num, num);
//   int index = 0;
//   char temp_array[33];
//   do {
//     // 0b110000 == 48
//     // Difference between 0 and '0' is 48 in ascii decimal
//     // (num & 1) will be either 0 or 1
//     // 48 is then "added"
//     temp_array[index++] = (num & 0b1) | 0b110000;
//     num >>= 1;
//   } while (num);

//   // Reverse array
//   for (size_t i = 0; i < index; i++) {
//     str[index - i - 1] = temp_array[i];
//   }
//   str[index] = '\0';
// }