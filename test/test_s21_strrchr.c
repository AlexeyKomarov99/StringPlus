#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strrchr_found_middle) {
  ck_assert_ptr_eq(s21_strrchr("hello", 'l'), strrchr("hello", 'l'));
}
END_TEST

START_TEST(test_strrchr_found_first) {
  ck_assert_ptr_eq(s21_strrchr("hello", 'h'), strrchr("hello", 'h'));
}
END_TEST

START_TEST(test_strrchr_found_last) {
  ck_assert_ptr_eq(s21_strrchr("hello", 'o'), strrchr("hello", 'o'));
}
END_TEST

START_TEST(test_strrchr_not_found) {
  ck_assert_ptr_eq(s21_strrchr("hello", 'x'), strrchr("hello", 'x'));
}
END_TEST

START_TEST(test_strrchr_null_term) {
  ck_assert_ptr_eq(s21_strrchr("hello", '\0'), strrchr("hello", '\0'));
}
END_TEST

START_TEST(test_strrchr_empty_str) {
  ck_assert_ptr_eq(s21_strrchr("", 'a'), strrchr("", 'a'));
}
END_TEST

START_TEST(test_strrchr_empty_null_term) {
  ck_assert_ptr_eq(s21_strrchr("", '\0'), strrchr("", '\0'));
}
END_TEST

START_TEST(test_strrchr_after_null) {
  char str[] = "test\0test";
  ck_assert_ptr_eq(s21_strrchr(str, 't'), strrchr(str, 't'));
}
END_TEST

START_TEST(test_strrchr_multiple_occurrences) {
  ck_assert_ptr_eq(s21_strrchr("mississippi", 'i'),
                   strrchr("mississippi", 'i'));
}
END_TEST

START_TEST(test_strrchr_single_char) {
  ck_assert_ptr_eq(s21_strrchr("a", 'a'), strrchr("a", 'a'));
  ck_assert_ptr_eq(s21_strrchr("a", 'b'), strrchr("a", 'b'));
}
END_TEST

START_TEST(test_strrchr_repeated_chars) {
  ck_assert_ptr_eq(s21_strrchr("aaaa", 'a'), strrchr("aaaa", 'a'));
}
END_TEST

START_TEST(test_strrchr_null_str) {
  ck_assert_ptr_eq(s21_strrchr(S21_NULL, 'a'), NULL);
}
END_TEST

TCase *tcase_strrchr(void) {
  TCase *tc = tcase_create("s21_strrchr");
  tcase_add_test(tc, test_strrchr_found_middle);
  tcase_add_test(tc, test_strrchr_found_first);
  tcase_add_test(tc, test_strrchr_found_last);
  tcase_add_test(tc, test_strrchr_not_found);
  tcase_add_test(tc, test_strrchr_null_term);
  tcase_add_test(tc, test_strrchr_empty_str);
  tcase_add_test(tc, test_strrchr_empty_null_term);
  tcase_add_test(tc, test_strrchr_after_null);
  tcase_add_test(tc, test_strrchr_multiple_occurrences);
  tcase_add_test(tc, test_strrchr_single_char);
  tcase_add_test(tc, test_strrchr_repeated_chars);
  tcase_add_test(tc, test_strrchr_null_str);
  return tc;
}