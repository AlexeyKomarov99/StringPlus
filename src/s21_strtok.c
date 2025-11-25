#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last_token = S21_NULL;
  char *token_start = S21_NULL;
  int found = 0;

  if (str != S21_NULL) {
    last_token = str;
  }

  if (last_token != S21_NULL && *last_token != '\0') {
    while (*last_token != '\0' && s21_strchr(delim, *last_token) != S21_NULL) {
      last_token++;
    }

    if (*last_token != '\0') {
      token_start = last_token;

      while (*last_token != '\0' &&
             s21_strchr(delim, *last_token) == S21_NULL) {
        last_token++;
      }

      if (*last_token != '\0') {
        *last_token = '\0';
        last_token++;
      } else {
        last_token = S21_NULL;
      }
      found = 1;
    }
  }

  return found ? token_start : S21_NULL;
}