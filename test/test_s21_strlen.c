#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(test_strlen_basic) {
  ck_assert_int_eq(s21_strlen("hello"), strlen("hello"));
}
END_TEST

START_TEST(test_strlen_empty) { ck_assert_int_eq(s21_strlen(""), strlen("")); }
END_TEST

START_TEST(test_strlen_single_char) {
  ck_assert_int_eq(s21_strlen("a"), strlen("a"));
}
END_TEST

START_TEST(test_strlen_with_spaces) {
  ck_assert_int_eq(s21_strlen("test string"), strlen("test string"));
}
END_TEST

START_TEST(test_strlen_with_special_chars) {
  ck_assert_int_eq(s21_strlen("123\n456"), strlen("123\n456"));
}
END_TEST

START_TEST(test_strlen_single_space) {
  ck_assert_int_eq(s21_strlen(" "), strlen(" "));
}
END_TEST

START_TEST(test_strlen_null_char_in_middle) {
  char str[] = "hello\0world";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_long_string) {
  char long_str[100] = "this is a longer string for testing purposes";
  ck_assert_int_eq(s21_strlen(long_str), strlen(long_str));
}
END_TEST

START_TEST(test_strlen_only_null_term) {
  char str[] = "\0";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_multiple_spaces) {
  ck_assert_int_eq(s21_strlen("   "), strlen("   "));
}
END_TEST

START_TEST(test_strlen_tab_newline) {
  ck_assert_int_eq(s21_strlen("\t\n"), strlen("\t\n"));
}
END_TEST

START_TEST(test_strlen_numbers) {
  ck_assert_int_eq(s21_strlen("1234567890"), strlen("1234567890"));
}
END_TEST

START_TEST(test_strlen_special_symbols) {
  ck_assert_int_eq(s21_strlen("!@#$%^&*()"), strlen("!@#$%^&*()"));
}
END_TEST

START_TEST(test_strlen_mixed_chars) {
  ck_assert_int_eq(s21_strlen("a1!B2@c3#"), strlen("a1!B2@c3#"));
}
END_TEST

START_TEST(test_strlen_very_long_string) {
  int length = 1000;
  char *long_str = (char *)malloc(length + 1);
  for (int i = 0; i < length; i++) {
    long_str[i] = 'A' + (i % 26);
  }
  long_str[length] = '\0';

  ck_assert_int_eq(s21_strlen(long_str), strlen(long_str));
  free(long_str);
}
END_TEST

START_TEST(test_strlen_unicode_safe) {
  ck_assert_int_eq(s21_strlen("café"), strlen("café"));
}
END_TEST

START_TEST(test_strlen_carriage_return) {
  ck_assert_int_eq(s21_strlen("hello\r\nworld"), strlen("hello\r\nworld"));
}
END_TEST

START_TEST(test_strlen_form_feed) {
  ck_assert_int_eq(s21_strlen("hello\fworld"), strlen("hello\fworld"));
}
END_TEST

START_TEST(test_strlen_vertical_tab) {
  ck_assert_int_eq(s21_strlen("hello\vworld"), strlen("hello\vworld"));
}
END_TEST

START_TEST(test_strlen_backspace) {
  ck_assert_int_eq(s21_strlen("hello\bworld"), strlen("hello\bworld"));
}
END_TEST

START_TEST(test_strlen_bell) {
  ck_assert_int_eq(s21_strlen("hello\aworld"), strlen("hello\aworld"));
}
END_TEST

START_TEST(test_strlen_escape) {
  ck_assert_int_eq(s21_strlen("hello\\world"), strlen("hello\\world"));
}
END_TEST

START_TEST(test_strlen_quotes) {
  ck_assert_int_eq(s21_strlen("\"hello\""), strlen("\"hello\""));
}
END_TEST

START_TEST(test_strlen_single_quotes) {
  ck_assert_int_eq(s21_strlen("'hello'"), strlen("'hello'"));
}
END_TEST

START_TEST(test_strlen_question_mark) {
  ck_assert_int_eq(s21_strlen("hello?"), strlen("hello?"));
}
END_TEST

START_TEST(test_strlen_colon_semicolon) {
  ck_assert_int_eq(s21_strlen("hello:world;"), strlen("hello:world;"));
}
END_TEST

START_TEST(test_strlen_brackets) {
  ck_assert_int_eq(s21_strlen("[hello]"), strlen("[hello]"));
}
END_TEST

START_TEST(test_strlen_braces) {
  ck_assert_int_eq(s21_strlen("{hello}"), strlen("{hello}"));
}
END_TEST

START_TEST(test_strlen_parentheses) {
  ck_assert_int_eq(s21_strlen("(hello)"), strlen("(hello)"));
}
END_TEST

START_TEST(test_strlen_angle_brackets) {
  ck_assert_int_eq(s21_strlen("<hello>"), strlen("<hello>"));
}
END_TEST

START_TEST(test_strlen_pipe) {
  ck_assert_int_eq(s21_strlen("hello|world"), strlen("hello|world"));
}
END_TEST

START_TEST(test_strlen_tilde) {
  ck_assert_int_eq(s21_strlen("hello~world"), strlen("hello~world"));
}
END_TEST

START_TEST(test_strlen_grave) {
  ck_assert_int_eq(s21_strlen("hello`world"), strlen("hello`world"));
}
END_TEST

START_TEST(test_strlen_dollar) {
  ck_assert_int_eq(s21_strlen("hello$world"), strlen("hello$world"));
}
END_TEST

START_TEST(test_strlen_percent) {
  ck_assert_int_eq(s21_strlen("hello%world"), strlen("hello%world"));
}
END_TEST

START_TEST(test_strlen_ampersand) {
  ck_assert_int_eq(s21_strlen("hello&world"), strlen("hello&world"));
}
END_TEST

START_TEST(test_strlen_asterisk) {
  ck_assert_int_eq(s21_strlen("hello*world"), strlen("hello*world"));
}
END_TEST

START_TEST(test_strlen_plus) {
  ck_assert_int_eq(s21_strlen("hello+world"), strlen("hello+world"));
}
END_TEST

START_TEST(test_strlen_comma) {
  ck_assert_int_eq(s21_strlen("hello,world"), strlen("hello,world"));
}
END_TEST

START_TEST(test_strlen_dash) {
  ck_assert_int_eq(s21_strlen("hello-world"), strlen("hello-world"));
}
END_TEST

START_TEST(test_strlen_dot) {
  ck_assert_int_eq(s21_strlen("hello.world"), strlen("hello.world"));
}
END_TEST

START_TEST(test_strlen_slash) {
  ck_assert_int_eq(s21_strlen("hello/world"), strlen("hello/world"));
}
END_TEST

START_TEST(test_strlen_equal) {
  ck_assert_int_eq(s21_strlen("hello=world"), strlen("hello=world"));
}
END_TEST

START_TEST(test_strlen_underscore) {
  ck_assert_int_eq(s21_strlen("hello_world"), strlen("hello_world"));
}
END_TEST

START_TEST(test_strlen_null_pointer) {
  ck_assert_int_eq(s21_strlen(S21_NULL), 0);
}
END_TEST

TCase *tcase_strlen(void) {
  TCase *tc = tcase_create("s21_strlen");
  tcase_add_test(tc, test_strlen_basic);
  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_single_char);
  tcase_add_test(tc, test_strlen_with_spaces);
  tcase_add_test(tc, test_strlen_with_special_chars);
  tcase_add_test(tc, test_strlen_single_space);
  tcase_add_test(tc, test_strlen_null_char_in_middle);
  tcase_add_test(tc, test_strlen_long_string);
  tcase_add_test(tc, test_strlen_only_null_term);
  tcase_add_test(tc, test_strlen_multiple_spaces);
  tcase_add_test(tc, test_strlen_tab_newline);
  tcase_add_test(tc, test_strlen_numbers);
  tcase_add_test(tc, test_strlen_special_symbols);
  tcase_add_test(tc, test_strlen_mixed_chars);
  tcase_add_test(tc, test_strlen_very_long_string);
  tcase_add_test(tc, test_strlen_unicode_safe);
  tcase_add_test(tc, test_strlen_carriage_return);
  tcase_add_test(tc, test_strlen_form_feed);
  tcase_add_test(tc, test_strlen_vertical_tab);
  tcase_add_test(tc, test_strlen_backspace);
  tcase_add_test(tc, test_strlen_bell);
  tcase_add_test(tc, test_strlen_escape);
  tcase_add_test(tc, test_strlen_quotes);
  tcase_add_test(tc, test_strlen_single_quotes);
  tcase_add_test(tc, test_strlen_question_mark);
  tcase_add_test(tc, test_strlen_colon_semicolon);
  tcase_add_test(tc, test_strlen_brackets);
  tcase_add_test(tc, test_strlen_braces);
  tcase_add_test(tc, test_strlen_parentheses);
  tcase_add_test(tc, test_strlen_angle_brackets);
  tcase_add_test(tc, test_strlen_pipe);
  tcase_add_test(tc, test_strlen_tilde);
  tcase_add_test(tc, test_strlen_grave);
  tcase_add_test(tc, test_strlen_dollar);
  tcase_add_test(tc, test_strlen_percent);
  tcase_add_test(tc, test_strlen_ampersand);
  tcase_add_test(tc, test_strlen_asterisk);
  tcase_add_test(tc, test_strlen_plus);
  tcase_add_test(tc, test_strlen_comma);
  tcase_add_test(tc, test_strlen_dash);
  tcase_add_test(tc, test_strlen_dot);
  tcase_add_test(tc, test_strlen_slash);
  tcase_add_test(tc, test_strlen_equal);
  tcase_add_test(tc, test_strlen_underscore);
  tcase_add_test(tc, test_strlen_null_pointer);

  return tc;
}