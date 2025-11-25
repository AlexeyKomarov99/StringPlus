#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    int found = 0;
    for (const char *s1 = str1; *s1 != '\0' && !found; s1++) {
      for (const char *s2 = str2; *s2 != '\0' && !found; s2++) {
        if (*s1 == *s2) {
          result = (char *)s1;
          found = 1;
        }
      }
    }
  }

  return result;
}