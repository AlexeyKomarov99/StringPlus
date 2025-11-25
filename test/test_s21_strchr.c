#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strchr_basic) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'w'), strchr(str, 'w'));
}
END_TEST

START_TEST(test_strchr_first_char) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'H'), strchr(str, 'H'));
}
END_TEST

START_TEST(test_strchr_not_found) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_strchr(str, 'x'), strchr(str, 'x'));
}
END_TEST

START_TEST(test_strchr_null_terminator) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

TCase *tcase_strchr(void) {
  TCase *tc = tcase_create("s21_strchr");
  tcase_add_test(tc, test_strchr_basic);
  tcase_add_test(tc, test_strchr_first_char);
  tcase_add_test(tc, test_strchr_not_found);
  tcase_add_test(tc, test_strchr_null_terminator);
  return tc;
}