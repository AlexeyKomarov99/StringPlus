#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strpbrk_found) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "aeiou"), strpbrk("hello", "aeiou"));
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "xyz"), strpbrk("hello", "xyz"));
}
END_TEST

START_TEST(test_strpbrk_str1_null) {
  ck_assert_ptr_eq(s21_strpbrk(S21_NULL, "abc"), S21_NULL);
}
END_TEST

START_TEST(test_strpbrk_str2_null) {
  ck_assert_ptr_eq(s21_strpbrk("hello", S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_strpbrk_both_null) {
  ck_assert_ptr_eq(s21_strpbrk(S21_NULL, S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_strpbrk_first_char_match) {
  ck_assert_ptr_eq(s21_strpbrk("apple", "a"), strpbrk("apple", "a"));
}
END_TEST

START_TEST(test_strpbrk_last_char_match) {
  ck_assert_ptr_eq(s21_strpbrk("test", "t"), strpbrk("test", "t"));
}
END_TEST

START_TEST(test_strpbrk_middle_char_match) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "l"), strpbrk("hello", "l"));
}
END_TEST

START_TEST(test_strpbrk_multiple_matches) {
  ck_assert_ptr_eq(s21_strpbrk("banana", "na"), strpbrk("banana", "na"));
}
END_TEST

START_TEST(test_strpbrk_empty_string) {
  ck_assert_ptr_eq(s21_strpbrk("", "abc"), strpbrk("", "abc"));
}
END_TEST

START_TEST(test_strpbrk_both_empty) {
  ck_assert_ptr_eq(s21_strpbrk("", ""), strpbrk("", ""));
}
END_TEST

START_TEST(test_strpbrk_single_char_str) {
  ck_assert_ptr_eq(s21_strpbrk("a", "a"), strpbrk("a", "a"));
  ck_assert_ptr_eq(s21_strpbrk("a", "b"), strpbrk("a", "b"));
}
END_TEST

START_TEST(test_strpbrk_reject_all_chars) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "helo"), strpbrk("hello", "helo"));
}
END_TEST

START_TEST(test_strpbrk_no_reject_chars) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "xyz"), strpbrk("hello", "xyz"));
}
END_TEST

START_TEST(test_strpbrk_special_chars) {
  ck_assert_ptr_eq(s21_strpbrk("test!@#string", "!@#"),
                   strpbrk("test!@#string", "!@#"));
}
END_TEST

START_TEST(test_strpbrk_whitespace) {
  ck_assert_ptr_eq(s21_strpbrk("hello world", " "),
                   strpbrk("hello world", " "));
}
END_TEST

START_TEST(test_strpbrk_newline) {
  ck_assert_ptr_eq(s21_strpbrk("hello\nworld", "\n"),
                   strpbrk("hello\nworld", "\n"));
}
END_TEST

START_TEST(test_strpbrk_tab) {
  ck_assert_ptr_eq(s21_strpbrk("hello\tworld", "\t"),
                   strpbrk("hello\tworld", "\t"));
}
END_TEST

START_TEST(test_strpbrk_numbers) {
  ck_assert_ptr_eq(s21_strpbrk("test123", "123"), strpbrk("test123", "123"));
}
END_TEST

START_TEST(test_strpbrk_uppercase_lowercase) {
  ck_assert_ptr_eq(s21_strpbrk("Hello", "H"), strpbrk("Hello", "H"));
  ck_assert_ptr_eq(s21_strpbrk("Hello", "h"), strpbrk("Hello", "h"));
}
END_TEST

START_TEST(test_strpbrk_long_string) {
  char long_str[] = "this is a very long string for testing purposes";
  ck_assert_ptr_eq(s21_strpbrk(long_str, "zqx"), strpbrk(long_str, "zqx"));
}
END_TEST

START_TEST(test_strpbrk_null_in_str) {
  char str[] = "hello\0world";
  ck_assert_ptr_eq(s21_strpbrk(str, "w"), strpbrk(str, "w"));
}
END_TEST

START_TEST(test_strpbrk_reject_single_char) {
  ck_assert_ptr_eq(s21_strpbrk("abcdef", "d"), strpbrk("abcdef", "d"));
}
END_TEST

START_TEST(test_strpbrk_reject_at_start) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "h"), strpbrk("hello", "h"));
}
END_TEST

START_TEST(test_strpbrk_reject_at_end) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "o"), strpbrk("hello", "o"));
}
END_TEST

START_TEST(test_strpbrk_multiple_reject_options) {
  ck_assert_ptr_eq(s21_strpbrk("hello", "lo"), strpbrk("hello", "lo"));
}
END_TEST

START_TEST(test_strpbrk_unicode_safe) {
  ck_assert_ptr_eq(s21_strpbrk("café", "é"), strpbrk("café", "é"));
}
END_TEST

TCase *tcase_strpbrk(void) {
  TCase *tc = tcase_create("s21_strpbrk");
  tcase_add_test(tc, test_strpbrk_found);
  tcase_add_test(tc, test_strpbrk_not_found);
  tcase_add_test(tc, test_strpbrk_str1_null);
  tcase_add_test(tc, test_strpbrk_str2_null);
  tcase_add_test(tc, test_strpbrk_both_null);
  tcase_add_test(tc, test_strpbrk_first_char_match);
  tcase_add_test(tc, test_strpbrk_last_char_match);
  tcase_add_test(tc, test_strpbrk_middle_char_match);
  tcase_add_test(tc, test_strpbrk_multiple_matches);
  tcase_add_test(tc, test_strpbrk_empty_string);
  tcase_add_test(tc, test_strpbrk_both_empty);
  tcase_add_test(tc, test_strpbrk_single_char_str);
  tcase_add_test(tc, test_strpbrk_reject_all_chars);
  tcase_add_test(tc, test_strpbrk_no_reject_chars);
  tcase_add_test(tc, test_strpbrk_special_chars);
  tcase_add_test(tc, test_strpbrk_whitespace);
  tcase_add_test(tc, test_strpbrk_newline);
  tcase_add_test(tc, test_strpbrk_tab);
  tcase_add_test(tc, test_strpbrk_numbers);
  tcase_add_test(tc, test_strpbrk_uppercase_lowercase);
  tcase_add_test(tc, test_strpbrk_long_string);
  tcase_add_test(tc, test_strpbrk_null_in_str);
  tcase_add_test(tc, test_strpbrk_reject_single_char);
  tcase_add_test(tc, test_strpbrk_reject_at_start);
  tcase_add_test(tc, test_strpbrk_reject_at_end);
  tcase_add_test(tc, test_strpbrk_multiple_reject_options);
  tcase_add_test(tc, test_strpbrk_unicode_safe);
  return tc;
}