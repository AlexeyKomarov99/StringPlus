#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_memchr_basic) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'w', 11), memchr(str, 'w', 11));
}
END_TEST

START_TEST(test_memchr_first_char) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'H', 11), memchr(str, 'H', 11));
}
END_TEST

START_TEST(test_memchr_last_char) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'd', 11), memchr(str, 'd', 11));
}
END_TEST

START_TEST(test_memchr_not_found) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'x', 11), memchr(str, 'x', 11));
}
END_TEST

START_TEST(test_memchr_zero_length) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'H', 0), memchr(str, 'H', 0));
}
END_TEST

START_TEST(test_memchr_null_terminator) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_memchr(str, '\0', 12), memchr(str, '\0', 12));
}
END_TEST

START_TEST(test_memchr_partial_search) {
  char str[] = "Hello world";
  ck_assert_ptr_eq(s21_memchr(str, 'o', 5), memchr(str, 'o', 5));
}
END_TEST

START_TEST(test_memchr_empty_string) {
  char empty[] = "";
  ck_assert_ptr_eq(s21_memchr(empty, 'a', 1), memchr(empty, 'a', 1));
}
END_TEST

START_TEST(test_memchr_binary_data) {
  char numbers[] = {1, 2, 3, 4, 5};
  ck_assert_ptr_eq(s21_memchr(numbers, 3, 5), memchr(numbers, 3, 5));
}
END_TEST

START_TEST(test_memchr_binary_not_found) {
  char numbers[] = {1, 2, 3, 4, 5};
  ck_assert_ptr_eq(s21_memchr(numbers, 6, 5), memchr(numbers, 6, 5));
}
END_TEST

START_TEST(test_memchr_negative_char) {
  char data[] = {'a', 'b', -1, 'd', 'e'};
  unsigned char search = (unsigned char)-1;
  ck_assert_ptr_eq(s21_memchr(data, search, 5), memchr(data, search, 5));
}
END_TEST

TCase *tcase_memchr(void) {
  TCase *tc = tcase_create("s21_memchr");

  tcase_add_test(tc, test_memchr_basic);
  tcase_add_test(tc, test_memchr_first_char);
  tcase_add_test(tc, test_memchr_last_char);
  tcase_add_test(tc, test_memchr_not_found);
  tcase_add_test(tc, test_memchr_zero_length);
  tcase_add_test(tc, test_memchr_null_terminator);
  tcase_add_test(tc, test_memchr_partial_search);
  tcase_add_test(tc, test_memchr_empty_string);
  tcase_add_test(tc, test_memchr_binary_data);
  tcase_add_test(tc, test_memchr_binary_not_found);
  tcase_add_test(tc, test_memchr_negative_char);

  return tc;
}