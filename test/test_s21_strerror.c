#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strerror_basic) {
  int errnum = 0;
  char *result1 = s21_strerror(errnum);
  char *result2 = strerror(errnum);
  ck_assert_ptr_nonnull(result1);
  ck_assert_ptr_nonnull(result2);
  ck_assert_int_gt(strlen(result1), 0);
  ck_assert_int_gt(strlen(result2), 0);
}
END_TEST

START_TEST(test_strerror_edge_cases) {
#ifdef __linux__
  char *result = s21_strerror(133);
  ck_assert_ptr_nonnull(result);
  result = s21_strerror(0);
  ck_assert_str_eq(result, "Success");
#elif defined(__APPLE__)
  char *result = s21_strerror(69);
  ck_assert_ptr_nonnull(result);
  result = s21_strerror(0);
  ck_assert_str_eq(result, "Undefined error: 0");
#endif
}
END_TEST

START_TEST(test_strerror_unknown) {
  char *result = s21_strerror(999);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Unknown error 999");

  result = s21_strerror(-1);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Unknown error -1");

  result = s21_strerror(1000);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Unknown error 1000");
}
END_TEST

START_TEST(test_strerror_negative) {
  char *result = s21_strerror(-5);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Unknown error -5");
}
END_TEST

START_TEST(test_strerror_large_positive) {
  char *result = s21_strerror(9999);
  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Unknown error 9999");
}
END_TEST

START_TEST(test_strerror_common_errors) {
  char *result1 = s21_strerror(1);
  char *result2 = s21_strerror(2);
  char *result3 = s21_strerror(13);

  ck_assert_ptr_nonnull(result1);
  ck_assert_ptr_nonnull(result2);
  ck_assert_ptr_nonnull(result3);

  ck_assert_int_gt(strlen(result1), 0);
  ck_assert_int_gt(strlen(result2), 0);
  ck_assert_int_gt(strlen(result3), 0);
}
END_TEST

TCase *tcase_strerror(void) {
  TCase *tc = tcase_create("s21_strerror");
  tcase_add_test(tc, test_strerror_basic);
  tcase_add_test(tc, test_strerror_edge_cases);
  tcase_add_test(tc, test_strerror_unknown);
  tcase_add_test(tc, test_strerror_negative);
  tcase_add_test(tc, test_strerror_large_positive);
  tcase_add_test(tc, test_strerror_common_errors);
  return tc;
}