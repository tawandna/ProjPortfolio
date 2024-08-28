#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = S21_NULL;

  if (src != S21_NULL) {
    if (trim_chars == S21_NULL) {
      trim_chars = " \t\n\v\f\r";
    }

    const char *start = src;
    while (*start && s21_strchr(trim_chars, *start)) {
      start++;
    }

    const char *end = src + s21_strlen(src) - 1;
    while (end > start && s21_strchr(trim_chars, *end)) {
      end--;
    }

    s21_size_t new_len = end >= start ? (s21_size_t)(end - start + 1) : 0;

    new_str = (char *)calloc(new_len + 1, sizeof(char));

    if (new_str != S21_NULL && new_len > 0) {
      s21_strncpy(new_str, start, new_len);
    }
  }
  return (void *)new_str;
}