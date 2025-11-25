#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    int found = 0;
    for (const char *ptr1 = str1; *ptr1 != '\0' && !found; ptr1++) {
      for (const char *check = str2; *check != '\0' && !found; check++) {
        if (*ptr1 == *check) {
          found = 1;
        }
      }
      if (!found) {
        result++;
      }
    }
  }

  return result;
}