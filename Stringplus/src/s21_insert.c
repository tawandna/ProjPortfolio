#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = S21_NULL;

  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);

    if (start_index <= src_len) {
      new_str = (char *)calloc(src_len + str_len + 1, sizeof(char));
      if (new_str != S21_NULL) {
        s21_strncpy(new_str, src, start_index);
        s21_strncpy(new_str + start_index, str, str_len);
        s21_strncpy(new_str + start_index + str_len, src + start_index,
                    src_len - start_index);
      }
    }
  }
  return (void *)new_str;
}