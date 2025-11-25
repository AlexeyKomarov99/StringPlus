#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strncmp_equal_strings) {
  ck_assert_int_eq(s21_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));
}
END_TEST

START_TEST(test_strncmp_partial_equal) {
  ck_assert_int_eq(s21_strncmp("abc", "abd", 2), strncmp("abc", "abd", 2));
}
END_TEST

START_TEST(test_strncmp_different_lengths) {
  ck_assert_int_eq(s21_strncmp("abc", "abcd", 3), strncmp("abc", "abcd", 3));
}
END_TEST

START_TEST(test_strncmp_zero_size) {
  ck_assert_int_eq(s21_strncmp("abc", "xyz", 0), strncmp("abc", "xyz", 0));
}
END_TEST

START_TEST(test_strncmp_empty_strings) {
  ck_assert_int_eq(s21_strncmp("", "", 1), strncmp("", "", 1));
}
END_TEST

START_TEST(test_strncmp_first_less) {
  int res1 = s21_strncmp("a", "b", 1) < 0;
  int res2 = strncmp("a", "b", 1) < 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_case_sensitive) {
  int res1 = s21_strncmp("hello", "HELLO", 5) > 0;
  int res2 = strncmp("hello", "HELLO", 5) > 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_first_greater) {
  int res1 = s21_strncmp("b", "a", 1) > 0;
  int res2 = strncmp("b", "a", 1) > 0;
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_strncmp_partial_comparison) {
  ck_assert_int_eq(s21_strncmp("abcdef", "abcxyz", 3),
                   strncmp("abcdef", "abcxyz", 3));
}
END_TEST

START_TEST(test_strncmp_single_char_equal) {
  ck_assert_int_eq(s21_strncmp("a", "a", 1), strncmp("a", "a", 1));
}
END_TEST

START_TEST(test_strncmp_single_char_diff) {
  ck_assert_int_eq(s21_strncmp("a", "b", 1), strncmp("a", "b", 1));
}
END_TEST

START_TEST(test_strncmp_with_null_bytes) {
  ck_assert_int_eq(s21_strncmp("a\0b", "a\0c", 3), strncmp("a\0b", "a\0c", 3));
}
END_TEST

START_TEST(test_strncmp_different_sizes) {
  ck_assert_int_eq(s21_strncmp("short", "shorter", 5),
                   strncmp("short", "shorter", 5));
}
END_TEST

START_TEST(test_strncmp_large_n) {
  ck_assert_int_eq(s21_strncmp("hello", "hello", 10),
                   strncmp("hello", "hello", 10));
}
END_TEST

TCase *tcase_strncmp(void) {
  TCase *tc = tcase_create("s21_strncmp");
  tcase_add_test(tc, test_strncmp_equal_strings);
  tcase_add_test(tc, test_strncmp_partial_equal);
  tcase_add_test(tc, test_strncmp_different_lengths);
  tcase_add_test(tc, test_strncmp_zero_size);
  tcase_add_test(tc, test_strncmp_empty_strings);
  tcase_add_test(tc, test_strncmp_first_less);
  tcase_add_test(tc, test_strncmp_case_sensitive);
  tcase_add_test(tc, test_strncmp_first_greater);
  tcase_add_test(tc, test_strncmp_partial_comparison);
  tcase_add_test(tc, test_strncmp_single_char_equal);
  tcase_add_test(tc, test_strncmp_single_char_diff);
  tcase_add_test(tc, test_strncmp_with_null_bytes);
  tcase_add_test(tc, test_strncmp_different_sizes);
  tcase_add_test(tc, test_strncmp_large_n);
  return tc;
}