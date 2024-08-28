#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *current_char_str1 = S21_NULL;
  const char *searched_char_str2 = S21_NULL;
  char *result = S21_NULL;

  for (current_char_str1 = str1;
       *current_char_str1 != '\0' && result == S21_NULL; ++current_char_str1) {
    for (searched_char_str2 = str2; *searched_char_str2 != '\0';
         ++searched_char_str2) {
      if (*current_char_str1 == *searched_char_str2) {
        result = (char *)current_char_str1;
        break;
      }
    }
  }

  return result;
}