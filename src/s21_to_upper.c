#include "s21_string.h"

char *s21_to_upper(const char *str) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    result = (char *)malloc(len + 1);

    if (result) {
      for (s21_size_t i = 0; i <= len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          result[i] = str[i] - 32;
        } else {
          result[i] = str[i];
        }
      }
    }
  }

  return result;
}