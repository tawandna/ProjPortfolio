#include <stdlib.h>

#include "s21_string.h"

/*Возвращает копию строки (str), преобразованной
в верхний регистр. В случае какой-либо ошибки следует вернуть значение NULL.*/

void *s21_to_upper(const char *str) {
  char *up_str = S21_NULL;
  if (str != S21_NULL) {
    up_str = (char *)calloc((s21_strlen(str) + 1), sizeof(char));
    for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        up_str[i] = (str[i] - 'a') + 'A';
      } else
        up_str[i] = str[i];
    }
    // free(up_str);
  }
  return up_str;
}