#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *current_position = S21_NULL;
  char *token = S21_NULL;

  if (str != S21_NULL) {
    current_position = str;
  }

  if (current_position != S21_NULL) {
    while (*current_position && s21_strchr(delim, *current_position)) {
      current_position++;
    }

    if (*current_position != '\0') {
      token = current_position;
      while (*current_position && !s21_strchr(delim, *current_position)) {
        current_position++;
      }

      if (*current_position != '\0') {
        *current_position = '\0';
        current_position++;
      } else {
        current_position = S21_NULL;
      }
    }
  }
  return (token);
}
