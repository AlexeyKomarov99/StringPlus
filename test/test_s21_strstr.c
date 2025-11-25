#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strstr_found_end) {
  ck_assert_ptr_eq(s21_strstr("hello world", "world"),
                   strstr("hello world", "world"));
}
END_TEST

START_TEST(test_strstr_found_start) {
  ck_assert_ptr_eq(s21_strstr("hello world", "hello"),
                   strstr("hello world", "hello"));
}
END_TEST

START_TEST(test_strstr_found_middle) {
  ck_assert_ptr_eq(s21_strstr("hello world", "o w"),
                   strstr("hello world", "o w"));
}
END_TEST

START_TEST(test_strstr_not_found) {
  ck_assert_ptr_eq(s21_strstr("hello world", "xyz"),
                   strstr("hello world", "xyz"));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  ck_assert_ptr_eq(s21_strstr("hello world", ""), strstr("hello world", ""));
}
END_TEST

START_TEST(test_strstr_empty_haystack) {
  ck_assert_ptr_eq(s21_strstr("", "abc"), strstr("", "abc"));
}
END_TEST

START_TEST(test_strstr_both_empty) {
  ck_assert_ptr_eq(s21_strstr("", ""), strstr("", ""));
}
END_TEST

START_TEST(test_strstr_after_null) {
  char str[] = "test\0string";
  ck_assert_ptr_eq(s21_strstr(str, "string"), strstr(str, "string"));
}
END_TEST

START_TEST(test_strstr_exact_match) {
  ck_assert_ptr_eq(s21_strstr("hello", "hello"), strstr("hello", "hello"));
}
END_TEST

START_TEST(test_strstr_partial_match) {
  ck_assert_ptr_eq(s21_strstr("hello", "hell"), strstr("hello", "hell"));
}
END_TEST

START_TEST(test_strstr_single_char_needle) {
  ck_assert_ptr_eq(s21_strstr("hello", "e"), strstr("hello", "e"));
}
END_TEST

START_TEST(test_strstr_repeated_pattern) {
  ck_assert_ptr_eq(s21_strstr("ababab", "abab"), strstr("ababab", "abab"));
}
END_TEST

START_TEST(test_strstr_null_haystack) {
  ck_assert_ptr_eq(s21_strstr(S21_NULL, "needle"), NULL);
}
END_TEST

START_TEST(test_strstr_null_needle) {
  ck_assert_ptr_eq(s21_strstr("haystack", S21_NULL), NULL);
}
END_TEST

START_TEST(test_strstr_both_null) {
  ck_assert_ptr_eq(s21_strstr(S21_NULL, S21_NULL), NULL);
}
END_TEST

TCase *tcase_strstr(void) {
  TCase *tc = tcase_create("s21_strstr");
  tcase_add_test(tc, test_strstr_found_end);
  tcase_add_test(tc, test_strstr_found_start);
  tcase_add_test(tc, test_strstr_found_middle);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_empty_haystack);
  tcase_add_test(tc, test_strstr_both_empty);
  tcase_add_test(tc, test_strstr_after_null);
  tcase_add_test(tc, test_strstr_exact_match);
  tcase_add_test(tc, test_strstr_partial_match);
  tcase_add_test(tc, test_strstr_single_char_needle);
  tcase_add_test(tc, test_strstr_repeated_pattern);
  tcase_add_test(tc, test_strstr_null_haystack);
  tcase_add_test(tc, test_strstr_null_needle);
  tcase_add_test(tc, test_strstr_both_null);
  return tc;
}