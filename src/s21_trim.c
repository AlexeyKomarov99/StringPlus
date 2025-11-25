#include "s21_string.h"

char *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;

  if (src != S21_NULL) {
    const char *default_trim = " \t\n\r\f\v";
    const char *trim_set = (trim_chars == S21_NULL || *trim_chars == '\0')
                               ? default_trim
                               : trim_chars;

    s21_size_t src_len = s21_strlen(src);

    if (src_len == 0) {
      result = (char *)malloc(1);
      if (result) result[0] = '\0';
    } else {
      s21_size_t start = 0;
      while (start < src_len && s21_strchr(trim_set, src[start])) {
        start++;
      }

      s21_size_t end = src_len - 1;
      while (end >= start && end > 0 && s21_strchr(trim_set, src[end])) {
        end--;
      }

      s21_size_t result_len = (end >= start) ? (end - start + 1) : 0;
      result = (char *)malloc(result_len + 1);

      if (result) {
        for (s21_size_t i = 0; i < result_len; i++) {
          result[i] = src[start + i];
        }
        result[result_len] = '\0';
      }
    }
  }

  return result;
}