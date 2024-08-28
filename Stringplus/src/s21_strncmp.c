#include <stdio.h>

#include "s21_string.h"

//Сравнивает не более первых n байтов str1 и str2

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res_val = 0;
  for (s21_size_t i = 0; i < n && (str1[i] || str2[i]); i++) {
    if (str1[i] != str2[i]) {
      if (str1[i] > str2[i]) {
        res_val = 1;
      } else {
        res_val = -1;
      }
      break;
    }
  }
  return res_val;
}
