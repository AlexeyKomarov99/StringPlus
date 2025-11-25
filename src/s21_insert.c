#include "s21_string.h"

char *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;

  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);

    if (start_index <= src_len) {
      s21_size_t new_len = src_len + str_len + 1;
      result = (char *)malloc(new_len);

      if (result) {
        s21_size_t i = 0;

        for (; i < start_index; i++) {
          result[i] = src[i];
        }

        for (s21_size_t j = 0; j < str_len; j++, i++) {
          result[i] = str[j];
        }

        for (s21_size_t j = start_index; j < src_len; j++, i++) {
          result[i] = src[j];
        }

        result[i] = '\0';
      }
    }
  }

  return result;
}
