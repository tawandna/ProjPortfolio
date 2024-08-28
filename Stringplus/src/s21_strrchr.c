#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *current_char_str = S21_NULL;
  const char *last_occurence = S21_NULL;

  for (current_char_str = str; *current_char_str != '\0'; ++current_char_str) {
    if (*current_char_str == (char)c) {
      last_occurence = current_char_str;
    }
  }

  if (*current_char_str == (char)c) {
    last_occurence = current_char_str;
  }

  return (char *)last_occurence;
}