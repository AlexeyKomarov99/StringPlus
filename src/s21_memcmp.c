#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *b1 = (const unsigned char *)str1;
  const unsigned char *b2 = (const unsigned char *)str2;
  int result = 0;
  s21_size_t i = 0;

  while (i < n && result == 0) {
    if (b1[i] != b2[i]) {
      result = b1[i] - b2[i];
    }
    i++;
  }

  return result;
}