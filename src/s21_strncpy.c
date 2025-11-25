#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;
  s21_size_t i = 0;

  for (; i < n && s[i] != '\0'; i++) d[i] = s[i];
  for (; i < n; i++) d[i] = '\0';

  return dest;
}