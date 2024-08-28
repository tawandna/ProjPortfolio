#include <stdlib.h>

#include "s21_string.h"

/*Возвращает копию строки (str), преобразованной в нижний регистр.
В случае какой-либо ошибки следует вернуть значение NULL.*/

void *s21_to_lower(const char *str) {
  char *low_str = S21_NULL;

  if (str != S21_NULL) {
    low_str = (char *)calloc((s21_strlen(str) + 1), sizeof(char));
    for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        low_str[i] = (str[i] - 'A') + 'a';
      } else {
        low_str[i] = str[i];
      }
    }
    // free(low_str);
  }
  return low_str;
}