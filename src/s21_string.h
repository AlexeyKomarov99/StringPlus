#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>
#include <stdlib.h>

#define S21_NULL ((void *)0)
typedef unsigned long s21_size_t;

typedef struct {
  int minus, plus, space, hash, zero;
  int width, precision, is_precision_set;
  int width_star, precision_star;
  char length, specifier;
} FormatFlags;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

const char *s21_parse_format(const char *format, FormatFlags *flags);
void s21_itoa(int value, char *buffer, int base);
void s21_utoa(unsigned int value, char *buffer, int base);
void s21_ftoa(double value, char *buffer, int precision);
void s21_reverse(char *str);

char *s21_to_upper(const char *str);
char *s21_to_lower(const char *str);
char *s21_insert(const char *src, const char *str, s21_size_t start_index);
char *s21_trim(const char *src, const char *trim_chars);

#endif