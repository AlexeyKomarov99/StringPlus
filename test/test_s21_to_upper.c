#include <check.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(test_to_upper_basic) {
  char *result = s21_to_upper("hello");
  ck_assert_str_eq(result, "HELLO");
  free(result);
}
END_TEST

START_TEST(test_to_upper_with_spaces) {
  char *result = s21_to_upper("Hello World");
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

START_TEST(test_to_upper_with_numbers) {
  char *result = s21_to_upper("123abc");
  ck_assert_str_eq(result, "123ABC");
  free(result);
}
END_TEST

START_TEST(test_to_upper_empty) {
  char *result = s21_to_upper("");
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_to_upper_already_upper) {
  char *result = s21_to_upper("ALREADY UPPER");
  ck_assert_str_eq(result, "ALREADY UPPER");
  free(result);
}
END_TEST

START_TEST(test_to_upper_mixed_case) {
  char *result = s21_to_upper("MiXeD CaSe");
  ck_assert_str_eq(result, "MIXED CASE");
  free(result);
}
END_TEST

START_TEST(test_to_upper_null) {
  ck_assert_ptr_eq(s21_to_upper(S21_NULL), S21_NULL);
}
END_TEST

START_TEST(test_to_upper_special_chars) {
  char *result = s21_to_upper("!@#$%123ABC");
  ck_assert_str_eq(result, "!@#$%123ABC");
  free(result);
}
END_TEST

START_TEST(test_to_upper_uppercase_letters) {
  char *result = s21_to_upper("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  ck_assert_str_eq(result, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  free(result);
}
END_TEST

START_TEST(test_to_upper_lowercase_boundary) {
  char *result = s21_to_upper("az");
  ck_assert_str_eq(result, "AZ");
  free(result);
}
END_TEST

START_TEST(test_to_upper_non_alpha_chars) {
  char *result = s21_to_upper("!a@b#c$");
  ck_assert_str_eq(result, "!A@B#C$");
  free(result);
}
END_TEST

START_TEST(test_to_upper_memory_allocation_failure) {
  char *result = s21_to_upper("test");
  ck_assert_ptr_nonnull(result);
  if (result) {
    ck_assert_str_eq(result, "TEST");
    free(result);
  }
}
END_TEST

START_TEST(test_to_upper_single_char_lower) {
  char *result = s21_to_upper("a");
  ck_assert_str_eq(result, "A");
  free(result);
}
END_TEST

START_TEST(test_to_upper_single_char_upper) {
  char *result = s21_to_upper("A");
  ck_assert_str_eq(result, "A");
  free(result);
}
END_TEST

START_TEST(test_to_upper_single_char_non_alpha) {
  char *result = s21_to_upper("!");
  ck_assert_str_eq(result, "!");
  free(result);
}
END_TEST

START_TEST(test_to_upper_mixed_with_numbers) {
  char *result = s21_to_upper("a1b2c3");
  ck_assert_str_eq(result, "A1B2C3");
  free(result);
}
END_TEST

START_TEST(test_to_upper_with_newline) {
  char *result = s21_to_upper("hello\nworld");
  ck_assert_str_eq(result, "HELLO\nWORLD");
  free(result);
}
END_TEST

START_TEST(test_to_upper_with_tab) {
  char *result = s21_to_upper("hello\tworld");
  ck_assert_str_eq(result, "HELLO\tWORLD");
  free(result);
}
END_TEST

START_TEST(test_to_upper_only_special_chars) {
  char *result = s21_to_upper("!@#$%^&*()");
  ck_assert_str_eq(result, "!@#$%^&*()");
  free(result);
}
END_TEST

START_TEST(test_to_upper_whitespace_only) {
  char *result = s21_to_upper("   ");
  ck_assert_str_eq(result, "   ");
  free(result);
}
END_TEST

START_TEST(test_to_upper_malloc_failure_simulation) {
  char test_str[] = "test";
  char *result = s21_to_upper(test_str);
  ck_assert_ptr_nonnull(result);
  if (result) {
    ck_assert_str_eq(result, "TEST");
    free(result);
  }
}
END_TEST

START_TEST(test_to_upper_chars_below_lowercase_a) {
  char *result = s21_to_upper("0123456789");
  ck_assert_str_eq(result, "0123456789");
  free(result);

  result = s21_to_upper("@ABCDEFGHI");
  ck_assert_str_eq(result, "@ABCDEFGHI");
  free(result);

  result = s21_to_upper(" !\"#$%&'()*+,-./");
  ck_assert_str_eq(result, " !\"#$%&'()*+,-./");
  free(result);
}
END_TEST

START_TEST(test_to_upper_control_chars) {
  char control_chars[] = {1, 2, 3, 10, 13, 0};
  char *result = s21_to_upper(control_chars);
  ck_assert_mem_eq(result, control_chars, 6);
  free(result);
}
END_TEST

START_TEST(test_to_upper_chars_above_lowercase_z) {
  char *result = s21_to_upper("{|}~");
  ck_assert_str_eq(result, "{|}~");
  free(result);
}
END_TEST

TCase *tcase_to_upper(void) {
  TCase *tc = tcase_create("s21_to_upper");
  tcase_add_test(tc, test_to_upper_basic);
  tcase_add_test(tc, test_to_upper_with_spaces);
  tcase_add_test(tc, test_to_upper_with_numbers);
  tcase_add_test(tc, test_to_upper_empty);
  tcase_add_test(tc, test_to_upper_already_upper);
  tcase_add_test(tc, test_to_upper_mixed_case);
  tcase_add_test(tc, test_to_upper_null);
  tcase_add_test(tc, test_to_upper_special_chars);
  tcase_add_test(tc, test_to_upper_uppercase_letters);
  tcase_add_test(tc, test_to_upper_lowercase_boundary);
  tcase_add_test(tc, test_to_upper_non_alpha_chars);
  tcase_add_test(tc, test_to_upper_memory_allocation_failure);
  tcase_add_test(tc, test_to_upper_single_char_lower);
  tcase_add_test(tc, test_to_upper_single_char_upper);
  tcase_add_test(tc, test_to_upper_single_char_non_alpha);
  tcase_add_test(tc, test_to_upper_mixed_with_numbers);
  tcase_add_test(tc, test_to_upper_with_newline);
  tcase_add_test(tc, test_to_upper_with_tab);
  tcase_add_test(tc, test_to_upper_only_special_chars);
  tcase_add_test(tc, test_to_upper_whitespace_only);
  tcase_add_test(tc, test_to_upper_malloc_failure_simulation);
  tcase_add_test(tc, test_to_upper_chars_below_lowercase_a);
  tcase_add_test(tc, test_to_upper_control_chars);
  tcase_add_test(tc, test_to_upper_chars_above_lowercase_z);
  return tc;
}