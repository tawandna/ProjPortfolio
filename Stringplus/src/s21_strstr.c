#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *result = S21_NULL;

  if (*needle == '\0') {
    result = haystack;
  } else {
    const char *hs_start = haystack;

    while (*hs_start != '\0' && result == S21_NULL) {
      const char *hs_iter = hs_start;
      const char *n_iter = needle;

      while (*hs_iter == *n_iter && *n_iter != '\0') {
        ++hs_iter;
        ++n_iter;
      }

      if (*n_iter == '\0') {
        result = hs_start;
      } else {
        ++hs_start;
      }
    }
  }

  return (char *)result;
}