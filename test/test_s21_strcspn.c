#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strcspn_found_at_start) {
  ck_assert_int_eq(s21_strcspn("hello", "h"), strcspn("hello", "h"));
}
END_TEST

START_TEST(test_strcspn_found_in_middle) {
  ck_assert_int_eq(s21_strcspn("hello", "aeiou"), strcspn("hello", "aeiou"));
}
END_TEST

START_TEST(test_strcspn_not_found) {
  ck_assert_int_eq(s21_strcspn("hello", "xyz"), strcspn("hello", "xyz"));
}
END_TEST

START_TEST(test_strcspn_empty_reject) {
  ck_assert_int_eq(s21_strcspn("hello", ""), strcspn("hello", ""));
}
END_TEST

START_TEST(test_strcspn_empty_str) {
  ck_assert_int_eq(s21_strcspn("", "abc"), strcspn("", "abc"));
}
END_TEST

START_TEST(test_strcspn_both_empty) {
  ck_assert_int_eq(s21_strcspn("", ""), strcspn("", ""));
}
END_TEST

START_TEST(test_strcspn_special_chars) {
  ck_assert_int_eq(s21_strcspn("test\nstring", "\n"),
                   strcspn("test\nstring", "\n"));
}
END_TEST

START_TEST(test_strcspn_multiple_reject_chars) {
  ck_assert_int_eq(s21_strcspn("12345", "543"), strcspn("12345", "543"));
}
END_TEST

START_TEST(test_strcspn_found_first_char) {
  ck_assert_int_eq(s21_strcspn("abc", "a"), strcspn("abc", "a"));
}
END_TEST

START_TEST(test_strcspn_found_last_char) {
  ck_assert_int_eq(s21_strcspn("abc", "c"), strcspn("abc", "c"));
}
END_TEST

START_TEST(test_strcspn_reject_whitespace) {
  ck_assert_int_eq(s21_strcspn("hello world", " "),
                   strcspn("hello world", " "));
}
END_TEST

START_TEST(test_strcspn_single_char_str) {
  ck_assert_int_eq(s21_strcspn("a", "a"), strcspn("a", "a"));
  ck_assert_int_eq(s21_strcspn("a", "b"), strcspn("a", "b"));
}
END_TEST

START_TEST(test_strcspn_null_in_str) {
  char str[] = "ab\0cd";
  ck_assert_int_eq(s21_strcspn(str, "c"), strcspn(str, "c"));
}
END_TEST

START_TEST(test_strcspn_reject_all_chars) {
  ck_assert_int_eq(s21_strcspn("hello", "helo"), strcspn("hello", "helo"));
}
END_TEST

START_TEST(test_strcspn_no_reject_chars) {
  ck_assert_int_eq(s21_strcspn("hello", "xyz"), strcspn("hello", "xyz"));
}
END_TEST

START_TEST(test_strcspn_mixed_charset) {
  ck_assert_int_eq(s21_strcspn("test123", "123"), strcspn("test123", "123"));
}
END_TEST

START_TEST(test_strcspn_uppercase_lowercase) {
  ck_assert_int_eq(s21_strcspn("Hello", "H"), strcspn("Hello", "H"));
  ck_assert_int_eq(s21_strcspn("Hello", "h"), strcspn("Hello", "h"));
}
END_TEST

START_TEST(test_strcspn_numbers_only) {
  ck_assert_int_eq(s21_strcspn("123456", "45"), strcspn("123456", "45"));
}
END_TEST

START_TEST(test_strcspn_special_symbols) {
  ck_assert_int_eq(s21_strcspn("test!@#string", "!@#"),
                   strcspn("test!@#string", "!@#"));
}
END_TEST

START_TEST(test_strcspn_long_string) {
  char long_str[] = "this is a very long string for testing purposes";
  ck_assert_int_eq(s21_strcspn(long_str, "zqx"), strcspn(long_str, "zqx"));
}
END_TEST

START_TEST(test_strcspn_reject_at_end) {
  ck_assert_int_eq(s21_strcspn("hello", "o"), strcspn("hello", "o"));
}
END_TEST

START_TEST(test_strcspn_multiple_matches) {
  ck_assert_int_eq(s21_strcspn("banana", "na"), strcspn("banana", "na"));
}
END_TEST

START_TEST(test_strcspn_unicode_safe) {
  ck_assert_int_eq(s21_strcspn("café", "é"), strcspn("café", "é"));
}
END_TEST

START_TEST(test_strcspn_reject_single_char) {
  ck_assert_int_eq(s21_strcspn("abcdef", "d"), strcspn("abcdef", "d"));
}
END_TEST

START_TEST(test_strcspn_empty_after_null) {
  char str[] = "test\0hidden";
  ck_assert_int_eq(s21_strcspn(str, "x"), strcspn(str, "x"));
}
END_TEST

START_TEST(test_strcspn_all_reject_chars) {
  ck_assert_int_eq(s21_strcspn("abc", "abc"), strcspn("abc", "abc"));
}
END_TEST

START_TEST(test_strcspn_partial_reject) {
  ck_assert_int_eq(s21_strcspn("hello world", " w"),
                   strcspn("hello world", " w"));
}
END_TEST

START_TEST(test_strcspn_digits_and_letters) {
  ck_assert_int_eq(s21_strcspn("test123abc", "123"),
                   strcspn("test123abc", "123"));
}
END_TEST

START_TEST(test_strcspn_reject_newline) {
  ck_assert_int_eq(s21_strcspn("line1\nline2", "\n"),
                   strcspn("line1\nline2", "\n"));
}
END_TEST

START_TEST(test_strcspn_tab_character) {
  ck_assert_int_eq(s21_strcspn("hello\tworld", "\t"),
                   strcspn("hello\tworld", "\t"));
}
END_TEST

START_TEST(test_strcspn_carriage_return) {
  ck_assert_int_eq(s21_strcspn("hello\rworld", "\r"),
                   strcspn("hello\rworld", "\r"));
}
END_TEST

START_TEST(test_strcspn_null_str1) {
  ck_assert_int_eq(s21_strcspn(S21_NULL, "abc"), 0);
}
END_TEST

START_TEST(test_strcspn_null_str2) {
  ck_assert_int_eq(s21_strcspn("hello", S21_NULL), 0);
}
END_TEST

START_TEST(test_strcspn_both_null) {
  ck_assert_int_eq(s21_strcspn(S21_NULL, S21_NULL), 0);
}
END_TEST

TCase *tcase_strcspn(void) {
  TCase *tc = tcase_create("s21_strcspn");
  tcase_add_test(tc, test_strcspn_found_at_start);
  tcase_add_test(tc, test_strcspn_found_in_middle);
  tcase_add_test(tc, test_strcspn_not_found);
  tcase_add_test(tc, test_strcspn_empty_reject);
  tcase_add_test(tc, test_strcspn_empty_str);
  tcase_add_test(tc, test_strcspn_both_empty);
  tcase_add_test(tc, test_strcspn_special_chars);
  tcase_add_test(tc, test_strcspn_multiple_reject_chars);
  tcase_add_test(tc, test_strcspn_found_first_char);
  tcase_add_test(tc, test_strcspn_found_last_char);
  tcase_add_test(tc, test_strcspn_reject_whitespace);
  tcase_add_test(tc, test_strcspn_single_char_str);
  tcase_add_test(tc, test_strcspn_null_in_str);
  tcase_add_test(tc, test_strcspn_reject_all_chars);
  tcase_add_test(tc, test_strcspn_no_reject_chars);
  tcase_add_test(tc, test_strcspn_mixed_charset);
  tcase_add_test(tc, test_strcspn_uppercase_lowercase);
  tcase_add_test(tc, test_strcspn_numbers_only);
  tcase_add_test(tc, test_strcspn_special_symbols);
  tcase_add_test(tc, test_strcspn_long_string);
  tcase_add_test(tc, test_strcspn_reject_at_end);
  tcase_add_test(tc, test_strcspn_multiple_matches);
  tcase_add_test(tc, test_strcspn_unicode_safe);
  tcase_add_test(tc, test_strcspn_reject_single_char);
  tcase_add_test(tc, test_strcspn_empty_after_null);
  tcase_add_test(tc, test_strcspn_all_reject_chars);
  tcase_add_test(tc, test_strcspn_partial_reject);
  tcase_add_test(tc, test_strcspn_digits_and_letters);
  tcase_add_test(tc, test_strcspn_reject_newline);
  tcase_add_test(tc, test_strcspn_tab_character);
  tcase_add_test(tc, test_strcspn_carriage_return);
  tcase_add_test(tc, test_strcspn_null_str1);
  tcase_add_test(tc, test_strcspn_null_str2);
  tcase_add_test(tc, test_strcspn_both_null);
  return tc;
}