#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  int result = 0;
  s21_size_t i = 0;

  while (i < n && result == 0) {
    if (s1[i] != s2[i]) {
      result = s1[i] - s2[i];
    } else if (s1[i] == '\0') {
      break;
    }
    i++;
  }

  return result;
}