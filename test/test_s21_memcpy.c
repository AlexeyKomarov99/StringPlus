#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_memcpy_full_string) {
  char src[] = "Hello";
  char dest1[10], dest2[10];
  s21_memcpy(dest1, src, 6);
  memcpy(dest2, src, 6);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_partial) {
  char src[] = "Hello";
  char dest1[10], dest2[10];
  s21_memcpy(dest1, src, 3);
  memcpy(dest2, src, 3);
  dest1[3] = '\0';
  dest2[3] = '\0';
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_memcpy_zero_size) {
  char src[] = "Hello";
  char dest1[10] = "test", dest2[10] = "test";
  s21_memcpy(dest1, src, 0);
  memcpy(dest2, src, 0);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

TCase *tcase_memcpy(void) {
  TCase *tc = tcase_create("s21_memcpy");
  tcase_add_test(tc, test_memcpy_full_string);
  tcase_add_test(tc, test_memcpy_partial);
  tcase_add_test(tc, test_memcpy_zero_size);
  return tc;
}