#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test_to_lower_basic) {
  char *result = s21_to_lower("HELLO");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_to_lower_mixed_case) {
  char *result = s21_to_lower("MiXeD CaSe");
  ck_assert_str_eq(result, "mixed case");
  free(result);
}
END_TEST

START_TEST(test_to_lower_null) {
  ck_assert_ptr_eq(s21_to_lower(S21_NULL), S21_NULL);
}
END_TEST

TCase *tcase_to_lower(void) {
  TCase *tc = tcase_create("s21_to_lower");
  tcase_add_test(tc, test_to_lower_basic);
  tcase_add_test(tc, test_to_lower_mixed_case);
  tcase_add_test(tc, test_to_lower_null);
  return tc;
}