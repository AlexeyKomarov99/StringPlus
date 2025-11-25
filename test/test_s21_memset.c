#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_memset_basic_fill) {
  char str1[10], str2[10];
  strcpy(str1, "abcdefghi");
  strcpy(str2, "abcdefghi");
  s21_memset(str1, 'X', 5);
  memset(str2, 'X', 5);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_memset_zero_fill) {
  char str1[10], str2[10];
  strcpy(str1, "abcdefghi");
  strcpy(str2, "abcdefghi");
  s21_memset(str1, 0, 5);
  memset(str2, 0, 5);
  ck_assert_mem_eq(str1, str2, 5);
}
END_TEST

TCase *tcase_memset(void) {
  TCase *tc = tcase_create("s21_memset");
  tcase_add_test(tc, test_memset_basic_fill);
  tcase_add_test(tc, test_memset_zero_fill);
  return tc;
}