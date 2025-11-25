#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test_insert_at_end) {
  char *result = s21_insert("Hello", " world", 5);
  ck_assert_str_eq(result, "Hello world");
  free(result);
}
END_TEST

START_TEST(test_insert_at_start) {
  char *result = s21_insert("Hello", " world", 0);
  ck_assert_str_eq(result, " worldHello");
  free(result);
}
END_TEST

START_TEST(test_insert_in_middle) {
  char *result = s21_insert("Hello", " world", 3);
  ck_assert_str_eq(result, "Hel worldlo");
  free(result);
}
END_TEST

START_TEST(test_insert_null_src) {
  ck_assert_ptr_eq(s21_insert(S21_NULL, "test", 0), S21_NULL);
}
END_TEST

START_TEST(test_insert_str_null) {
  ck_assert_ptr_eq(s21_insert("Hello", S21_NULL, 0), S21_NULL);
}
END_TEST

START_TEST(test_insert_index_greater_than_length) {
  ck_assert_ptr_eq(s21_insert("Hello", "test", 10), S21_NULL);
}
END_TEST

START_TEST(test_insert_index_equal_to_length) {
  char *result = s21_insert("Hello", " world", 5);
  ck_assert_str_eq(result, "Hello world");
  free(result);
}
END_TEST

START_TEST(test_insert_malloc_failure_case) {
  char *result = s21_insert("test", "insert", 2);
  ck_assert_ptr_nonnull(result);
  if (result) {
    ck_assert_str_eq(result, "teinsertst");
    free(result);
  }
}
END_TEST

START_TEST(test_insert_empty_str) {
  char *result = s21_insert("Hello", "", 2);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(test_insert_into_empty_src) {
  char *result = s21_insert("", "test", 0);
  ck_assert_str_eq(result, "test");
  free(result);
}
END_TEST

START_TEST(test_insert_at_negative_index) {
  ck_assert_ptr_eq(s21_insert("Hello", "test", -1), S21_NULL);
}
END_TEST

START_TEST(test_insert_single_char) {
  char *result = s21_insert("abc", "d", 1);
  ck_assert_str_eq(result, "adbc");
  free(result);
}
END_TEST

START_TEST(test_insert_at_zero_index) {
  char *result = s21_insert("Hello", "Prefix ", 0);
  ck_assert_str_eq(result, "Prefix Hello");
  free(result);
}
END_TEST

START_TEST(test_insert_large_index) {
  ck_assert_ptr_eq(s21_insert("short", "test", 100), S21_NULL);
}
END_TEST

START_TEST(test_insert_null_src_with_valid_str) {
  ck_assert_ptr_eq(s21_insert(S21_NULL, "test", 0), S21_NULL);
}
END_TEST

START_TEST(test_insert_both_null) {
  ck_assert_ptr_eq(s21_insert(S21_NULL, S21_NULL, 0), S21_NULL);
}
END_TEST

START_TEST(test_insert_empty_src_empty_str) {
  char *result = s21_insert("", "", 0);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

TCase *tcase_insert(void) {
  TCase *tc = tcase_create("s21_insert");
  tcase_add_test(tc, test_insert_at_end);
  tcase_add_test(tc, test_insert_at_start);
  tcase_add_test(tc, test_insert_in_middle);
  tcase_add_test(tc, test_insert_null_src);
  tcase_add_test(tc, test_insert_str_null);
  tcase_add_test(tc, test_insert_index_greater_than_length);
  tcase_add_test(tc, test_insert_index_equal_to_length);
  tcase_add_test(tc, test_insert_malloc_failure_case);
  tcase_add_test(tc, test_insert_empty_str);
  tcase_add_test(tc, test_insert_into_empty_src);
  tcase_add_test(tc, test_insert_at_negative_index);
  tcase_add_test(tc, test_insert_single_char);
  tcase_add_test(tc, test_insert_at_zero_index);
  tcase_add_test(tc, test_insert_large_index);
  tcase_add_test(tc, test_insert_null_src_with_valid_str);
  tcase_add_test(tc, test_insert_both_null);
  tcase_add_test(tc, test_insert_empty_src_empty_str);
  return tc;
}