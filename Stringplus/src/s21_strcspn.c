#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  const char *current_char_str1 = S21_NULL;
  const char *searched_char_str2 = S21_NULL;
  s21_size_t index = 0;
  bool found = false;

  for (current_char_str1 = str1; *current_char_str1 != false && !found;
       ++current_char_str1) {
    for (searched_char_str2 = str2; *searched_char_str2 != false && !found;
         ++searched_char_str2) {
      if (*current_char_str1 == *searched_char_str2) {
        index = current_char_str1 - str1;
        found = true;
      }
    }
  }
  if (!found) {
    index = current_char_str1 - str1;
  }
  return index;
}