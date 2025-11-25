#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_memcmp_equal_strings) {
  ck_assert_int_eq(s21_memcmp("Hello", "Hello", 5),
                   memcmp("Hello", "Hello", 5));
}
END_TEST

START_TEST(test_memcmp_first_greater) {
  ck_assert_int_eq(s21_memcmp("Hello", "Helln", 5) > 0,
                   memcmp("Hello", "Helln", 5) > 0);
}
END_TEST

START_TEST(test_memcmp_first_less) {
  ck_assert_int_eq(s21_memcmp("Helln", "Hello", 5) < 0,
                   memcmp("Helln", "Hello", 5) < 0);
}
END_TEST

START_TEST(test_memcmp_partial_equal) {
  ck_assert_int_eq(s21_memcmp("abcx", "abcy", 3), memcmp("abcx", "abcy", 3));
}
END_TEST

START_TEST(test_memcmp_zero_size) {
  ck_assert_int_eq(s21_memcmp("abc", "xyz", 0), memcmp("abc", "xyz", 0));
}
END_TEST

START_TEST(test_memcmp_with_null_bytes) {
  ck_assert_int_eq(s21_memcmp("a\0b", "a\0c", 3), memcmp("a\0b", "a\0c", 3));
}
END_TEST

TCase *tcase_memcmp(void) {
  TCase *tc = tcase_create("s21_memcmp");

  tcase_add_test(tc, test_memcmp_equal_strings);
  tcase_add_test(tc, test_memcmp_first_greater);
  tcase_add_test(tc, test_memcmp_first_less);
  tcase_add_test(tc, test_memcmp_partial_equal);
  tcase_add_test(tc, test_memcmp_zero_size);
  tcase_add_test(tc, test_memcmp_with_null_bytes);

  return tc;
}