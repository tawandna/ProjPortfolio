#include "s21_string.h"

/*Выполняет поиск первого вхождения символа c (беззнаковый тип)
в первых n байтах строки, на которую указывает аргумент str.*/

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int flag = 0;
  char *p_str = (char *)str;
  char *ptr = (char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    if (p_str[i] == c) {
      ptr = &p_str[i];
      flag = 1;
      break;
    }
  }

  if (flag) {
    return ptr;
  } else {
    return S21_NULL;
  }
}
