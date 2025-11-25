#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strncat_basic) {
  char dest1[20] = {0}, dest2[20] = {0};
  strcpy(dest1, "Hello");
  strcpy(dest2, "Hello");
  s21_strncat(dest1, "World", 5);
  strncat(dest2, "World", 5);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(test_strncat_zero_count) {
  char dest1[20] = {0}, dest2[20] = {0};
  strcpy(dest1, "Hello");
  strcpy(dest2, "Hello");
  s21_strncat(dest1, "World", 0);
  strncat(dest2, "World", 0);
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

TCase *tcase_strncat(void) {
  TCase *tc = tcase_create("s21_strncat");
  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strncat_zero_count);
  return tc;
}