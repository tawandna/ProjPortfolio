#include "s21_string.h"

//Копирует до n символов из строки, на которую указывает src, в dest.

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i] = '\0';
  // printf("%s\n||\n", dest);

  return dest;
}

/*int main(void) {
    char str[100] = "ssssssssssssssss";
    printf("%s\n", s21_strncpy(str, "aaa", 5));
    printf("%s\n", strncpy(str, "aaa", 5));
    return 0;
}*/
