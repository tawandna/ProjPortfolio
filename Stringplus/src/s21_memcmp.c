#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;

  const unsigned char *s2 = (const unsigned char *)str2;
  int a = 0;
  for (s21_size_t i = 0; i < n; i++) {
    a = s1[i] - s2[i];
    if (a != 0) {
      break;
    }
  }
  return a;
}

// int main() {
//     char str1[] = "Hel";
//     char str2[] = "He";

//     int result = s21_memcmp(str1, str2, 5);

//     if (result < 0) {
//         printf("str1 is less than str2\n");
//     } else if (result > 0) {
//         printf("str1 is greater than str2\n");
//     } else {
//         printf("str1 is equal to str2\n");
//     }
//     printf("%d\n", result);
//     return 0;
// }
