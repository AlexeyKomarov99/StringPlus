#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  void *result = S21_NULL;
  s21_size_t i = 0;

  while (i < n && result == S21_NULL) {
    if (s[i] == c) {
      result = (void *)(s + i);
    }
    i++;
  }

  return result;
}