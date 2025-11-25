#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strtok_basic) {
  char str1[] = "hello,world,test";
  char str2[] = "hello,world,test";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_multiple_calls) {
  char str1[] = "hello,world,test";
  char str2[] = "hello,world,test";
  char *token1, *token2;

  token1 = s21_strtok(str1, ",");
  token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_different_delim) {
  char str1[] = "a.b.c";
  char str2[] = "a.b.c";
  char *token1 = s21_strtok(str1, ".");
  char *token2 = strtok(str2, ".");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_multiple_delims) {
  char str1[] = "hello,world.test";
  char str2[] = "hello,world.test";
  char *token1 = s21_strtok(str1, ",.");
  char *token2 = strtok(str2, ",.");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",.");
  token2 = strtok(S21_NULL, ",.");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_no_delim) {
  char str1[] = "hello";
  char str2[] = "hello";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_consecutive_delims) {
  char str1[] = "hello,,world";
  char str2[] = "hello,,world";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_only_delims) {
  char str1[] = ",,,";
  char str2[] = ",,,";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_empty_string) {
  char str1[] = "";
  char str2[] = "";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_null_after_empty) {
  char str1[] = "";
  char str2[] = "";
  s21_strtok(str1, ",");
  strtok(str2, ",");

  char *token1 = s21_strtok(S21_NULL, ",");
  char *token2 = strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_delim_at_start) {
  char str1[] = ",hello,world";
  char str2[] = ",hello,world";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_delim_at_end) {
  char str1[] = "hello,world,";
  char str2[] = "hello,world,";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_multiple_null_calls) {
  char str1[] = "test";
  char str2[] = "test";
  s21_strtok(str1, ",");
  strtok(str2, ",");

  char *token1 = s21_strtok(S21_NULL, ",");
  char *token2 = strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_single_token) {
  char str1[] = "single";
  char str2[] = "single";
  char *token1 = s21_strtok(str1, ",");
  char *token2 = strtok(str2, ",");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, ",");
  token2 = strtok(S21_NULL, ",");
  ck_assert_ptr_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_whitespace_delims) {
  char str1[] = "hello world\ttest";
  char str2[] = "hello world\ttest";
  char *token1 = s21_strtok(str1, " \t");
  char *token2 = strtok(str2, " \t");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, " \t");
  token2 = strtok(S21_NULL, " \t");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, " \t");
  token2 = strtok(S21_NULL, " \t");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_special_chars_delims) {
  char str1[] = "hello|world;test";
  char str2[] = "hello|world;test";
  char *token1 = s21_strtok(str1, "|;");
  char *token2 = strtok(str2, "|;");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, "|;");
  token2 = strtok(S21_NULL, "|;");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(S21_NULL, "|;");
  token2 = strtok(S21_NULL, "|;");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_null_str_after_finished) {
  char str1[] = "one,two";
  char str2[] = "one,two";

  s21_strtok(str1, ",");
  s21_strtok(S21_NULL, ",");
  strtok(str2, ",");
  strtok(S21_NULL, ",");

  char str3[] = "new,token";
  char str4[] = "new,token";
  char *token1 = s21_strtok(str3, ",");
  char *token2 = strtok(str4, ",");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_strtok_empty_delim) {
  char str1[] = "hello";
  char str2[] = "hello";
  char *token1 = s21_strtok(str1, "");
  char *token2 = strtok(str2, "");
  ck_assert_str_eq(token1, token2);
}
END_TEST

TCase *tcase_strtok(void) {
  TCase *tc = tcase_create("s21_strtok");
  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_multiple_calls);
  tcase_add_test(tc, test_strtok_different_delim);
  tcase_add_test(tc, test_strtok_multiple_delims);
  tcase_add_test(tc, test_strtok_no_delim);
  tcase_add_test(tc, test_strtok_consecutive_delims);
  tcase_add_test(tc, test_strtok_only_delims);
  tcase_add_test(tc, test_strtok_empty_string);
  tcase_add_test(tc, test_strtok_null_after_empty);
  tcase_add_test(tc, test_strtok_delim_at_start);
  tcase_add_test(tc, test_strtok_delim_at_end);
  tcase_add_test(tc, test_strtok_multiple_null_calls);
  tcase_add_test(tc, test_strtok_single_token);
  tcase_add_test(tc, test_strtok_whitespace_delims);
  tcase_add_test(tc, test_strtok_special_chars_delims);
  tcase_add_test(tc, test_strtok_null_str_after_finished);
  tcase_add_test(tc, test_strtok_empty_delim);
  return tc;
}