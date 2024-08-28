#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  /* cppcheck-suppress cstyleCast */
  unsigned char *d = (unsigned char *)dest;
  /* cppcheck-suppress cstyleCast */
  const unsigned char *s = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

// int main () {
//     int a[2] = {1,2};

//     int b[2];
//     s21_memcpy(&b, &a, 2* sizeof(int));

//     printf("%d %d\n", b[0], b[1]);
//     return 0;

// }
