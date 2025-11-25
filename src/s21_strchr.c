#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  const char *ptr = str;
  char *result = S21_NULL;
  int found = 0;

  while (*ptr != '\0' && !found) {
    if (*ptr == c) {
      result = (char *)ptr;
      found = 1;
    }
    ptr++;
  }

  if (!found && c == '\0') {
    result = (char *)ptr;
  }

  return result;
}