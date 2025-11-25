#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strncpy_full_string) {
  char dest1[50], dest2[50];
  char src[] = "Hello world";
  s21_strncpy(dest1, src, 11);
  strncpy(dest2, src, 11);
  ck_assert_mem_eq(dest1, dest2, 11);
}
END_TEST

START_TEST(test_strncpy_partial) {
  char dest1[50], dest2[50];
  char src[] = "Hello world";
  s21_strncpy(dest1, src, 5);
  strncpy(dest2, src, 5);
  ck_assert_mem_eq(dest1, dest2, 5);
}
END_TEST

START_TEST(test_strncpy_empty_src) {
  char dest1[50], dest2[50];
  char empty[] = "";
  s21_strncpy(dest1, empty, 3);
  strncpy(dest2, empty, 3);
  ck_assert_mem_eq(dest1, dest2, 3);
}
END_TEST

TCase *tcase_strncpy(void) {
  TCase *tc = tcase_create("s21_strncpy");
  tcase_add_test(tc, test_strncpy_full_string);
  tcase_add_test(tc, test_strncpy_partial);
  tcase_add_test(tc, test_strncpy_empty_src);
  return tc;
}