#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    const char *ptr = str;

    while (*ptr != '\0') {
      if (*ptr == c) {
        result = (char *)ptr;
      }
      ptr++;
    }

    if (c == '\0') {
      result = (char *)ptr;
    }
  }

  return result;
}