#include "s21_string.h"

/*Выполняет поиск первого вхождения символа
c (беззнаковый тип) в строке, на которую указывает аргумент str.*/

char *s21_strchr(const char *str, int c) {
  char *ptr = S21_NULL;

  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c) {
      ptr = ((char *)str + i);
      break;
    }
  }

  return ptr;
}