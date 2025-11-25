#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (haystack != S21_NULL && needle != S21_NULL) {
    if (*needle == '\0') {
      result = (char *)haystack;
    } else {
      for (const char *h = haystack; *h != '\0' && result == S21_NULL; h++) {
        const char *n = needle;
        const char *h_temp = h;

        while (*n != '\0' && *h_temp != '\0' && *h_temp == *n) {
          h_temp++;
          n++;
        }

        if (*n == '\0') {
          result = (char *)h;
        }
      }
    }
  }

  return result;
}