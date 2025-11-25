#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test_trim_default_whitespace) {
  char *result = s21_trim("   hello   ", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_explicit_whitespace) {
  char *result = s21_trim("   hello   ", " ");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_multiple_chars) {
  char *result = s21_trim("xyxhelloxyx", "xy");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_only_whitespace) {
  char *result = s21_trim("   ", S21_NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_only_custom_chars) {
  char *result = s21_trim("xxx", "x");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_mixed_chars) {
  char *result = s21_trim(" \t\nhello \t\n", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_left_only) {
  char *result = s21_trim("   hello", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_right_only) {
  char *result = s21_trim("hello   ", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_string) {
  char *result = s21_trim("", S21_NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_null_with_chars) {
  ck_assert_ptr_eq(s21_trim(S21_NULL, "abc"), S21_NULL);
}
END_TEST

START_TEST(test_trim_empty_trim_chars) {
  char *result = s21_trim("hello", "");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_special_chars) {
  char *result = s21_trim("\r\n\thello\r\n\t", "\r\n\t");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_string_malloc_failure) {
  char *result = s21_trim("", S21_NULL);
  ck_assert_ptr_nonnull(result);
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }
}
END_TEST

START_TEST(test_trim_single_char_trimmed) {
  char *result = s21_trim("x", "x");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_all_chars_trimmed) {
  char *result = s21_trim("xxx", "x");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_only_left_trim) {
  char *result = s21_trim("   hello", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_only_right_trim) {
  char *result = s21_trim("hello   ", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_end_equals_zero_case) {
  char *result = s21_trim("x", "x");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_malloc_failure_case) {
  char *result = s21_trim("test", S21_NULL);
  ck_assert_ptr_nonnull(result);
  if (result) {
    ck_assert_str_eq(result, "test");
    free(result);
  }
}
END_TEST

START_TEST(test_trim_single_space) {
  char *result = s21_trim(" ", S21_NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_multiple_spaces_both_sides) {
  char *result = s21_trim("   hello   ", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_custom_chars_both_sides) {
  char *result = s21_trim("xyxhelloxyx", "xy");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_no_trim_needed) {
  char *result = s21_trim("hello", "xyz");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_null_trim_chars) {
  char *result = s21_trim("  hello  ", S21_NULL);
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

START_TEST(test_trim_null_src) {
  char *result = s21_trim(S21_NULL, S21_NULL);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST

START_TEST(test_trim_end_zero_case) {
  char *result = s21_trim("x", "x");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_empty_result_malloc) {
  char *result = s21_trim("   ", " ");
  ck_assert_ptr_nonnull(result);
  if (result) {
    ck_assert_str_eq(result, "");
    free(result);
  }
}
END_TEST

START_TEST(test_trim_single_char_no_trim) {
  char *result = s21_trim("a", "b");
  ck_assert_str_eq(result, "a");
  free(result);
}
END_TEST

START_TEST(test_trim_two_chars_both_trimmed) {
  char *result = s21_trim("xx", "x");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_trim_whitespace_tab_only) {
  char *result = s21_trim("\thello\t", "\t");
  ck_assert_str_eq(result, "hello");
  free(result);
}
END_TEST

#ifdef TEST_MALLOC_FAIL
START_TEST(test_trim_malloc_fails) {
  char *result = s21_trim("test", S21_NULL);
  ck_assert_ptr_eq(result, S21_NULL);
}
END_TEST
#endif

TCase *tcase_trim(void) {
  TCase *tc = tcase_create("s21_trim");
  tcase_add_test(tc, test_trim_default_whitespace);
  tcase_add_test(tc, test_trim_explicit_whitespace);
  tcase_add_test(tc, test_trim_multiple_chars);
  tcase_add_test(tc, test_trim_only_whitespace);
  tcase_add_test(tc, test_trim_only_custom_chars);
  tcase_add_test(tc, test_trim_mixed_chars);
  tcase_add_test(tc, test_trim_left_only);
  tcase_add_test(tc, test_trim_right_only);
  tcase_add_test(tc, test_trim_empty_string);
  tcase_add_test(tc, test_trim_null_with_chars);
  tcase_add_test(tc, test_trim_special_chars);
  tcase_add_test(tc, test_trim_empty_string_malloc_failure);
  tcase_add_test(tc, test_trim_single_char_trimmed);
  tcase_add_test(tc, test_trim_all_chars_trimmed);
  tcase_add_test(tc, test_trim_only_left_trim);
  tcase_add_test(tc, test_trim_only_right_trim);
  tcase_add_test(tc, test_trim_end_equals_zero_case);
  tcase_add_test(tc, test_trim_malloc_failure_case);
  tcase_add_test(tc, test_trim_single_space);
  tcase_add_test(tc, test_trim_multiple_spaces_both_sides);
  tcase_add_test(tc, test_trim_custom_chars_both_sides);
  tcase_add_test(tc, test_trim_no_trim_needed);
  tcase_add_test(tc, test_trim_empty_trim_chars);
  tcase_add_test(tc, test_trim_null_trim_chars);
  tcase_add_test(tc, test_trim_null_src);
  tcase_add_test(tc, test_trim_end_zero_case);
  tcase_add_test(tc, test_trim_empty_result_malloc);
  tcase_add_test(tc, test_trim_single_char_no_trim);
  tcase_add_test(tc, test_trim_two_chars_both_trimmed);
  tcase_add_test(tc, test_trim_whitespace_tab_only);
#ifdef TEST_MALLOC_FAIL
  tcase_add_test(tc, test_trim_malloc_fails);
#endif
  return tc;
}