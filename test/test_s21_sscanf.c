#include <check.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define ASSERT_SCANF_EQ(fmt, input, ...)                 \
  do {                                                   \
    int std_r = sscanf((input), (fmt), __VA_ARGS__);     \
    int s21_r = s21_sscanf((input), (fmt), __VA_ARGS__); \
    ck_assert_int_eq(s21_r, std_r);                      \
  } while (0)

#define ASSERT_SCANF_EQ_UNSAFE(fmt_lit, input, ...)         \
  do {                                                      \
    const char *fmtv__ = (fmt_lit);                         \
    int std_r__ = sscanf((input), fmtv__, __VA_ARGS__);     \
    int s21_r__ = s21_sscanf((input), fmtv__, __VA_ARGS__); \
    ck_assert_int_eq(s21_r__, std_r__);                     \
  } while (0)

START_TEST(test_float_basic) {
  float f1;
  double f2;
  long double f3;
  ASSERT_SCANF_EQ("%f %lf %Lf", "3.14 2.71828 6.022e23", &f1, &f2, &f3);
}
END_TEST

START_TEST(test_sscanf_multiple_ints) {
  int a1, a2, b1, b2, c1, c2;
  ck_assert_int_eq(s21_sscanf("123 -456 +789", "%d %d %d", &a1, &b1, &c1),
                   sscanf("123 -456 +789", "%d %d %d", &a2, &b2, &c2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_width_ints) {
  int a1, a2, b1, b2;
  ck_assert_int_eq(s21_sscanf("123456", "%3d%3d", &a1, &b1),
                   sscanf("123456", "%3d%3d", &a2, &b2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_sscanf_floats) {
  float f1, f2, f3, f4, f5, f6;
  ck_assert_int_eq(s21_sscanf("3.14 -2.5 .75", "%f %f %f", &f1, &f2, &f3),
                   sscanf("3.14 -2.5 .75", "%f %f %f", &f4, &f5, &f6));
  ck_assert_int_eq(f1 == f4, 1);
  ck_assert_int_eq(f2 == f5, 1);
  ck_assert_int_eq(f3 == f6, 1);
}
END_TEST

START_TEST(test_sscanf_doubles) {
  double d1, d2, d3, d4;
  ck_assert_int_eq(s21_sscanf("1.5e2 3e-1", "%lf %lf", &d1, &d2),
                   sscanf("1.5e2 3e-1", "%lf %lf", &d3, &d4));
  ck_assert_int_eq(d1 == d3, 1);
  ck_assert_int_eq(d2 == d4, 1);
}
END_TEST

START_TEST(test_sscanf_string_width) {
  char s1[50] = {0}, s2[50] = {0};
  ck_assert_int_eq(s21_sscanf("hello", "%3s", s1), sscanf("hello", "%3s", s2));
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_chars) {
  char ch1[3] = {0}, ch2[3] = {0};
  ck_assert_int_eq(s21_sscanf("abc", "%2c", ch1), sscanf("abc", "%2c", ch2));
  ck_assert_str_eq(ch1, ch2);
}
END_TEST

START_TEST(test_sscanf_scanset) {
  char s1[50] = {0}, s2[50] = {0};
  ck_assert_int_eq(s21_sscanf("hello123", "%49[a-z]", s1),
                   sscanf("hello123", "%49[a-z]", s2));
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_negated_scanset) {
  char s1[50] = {0}, s2[50] = {0};
  ck_assert_int_eq(s21_sscanf("hello world", "%49[^ ]", s1),
                   sscanf("hello world", "%49[^ ]", s2));
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_suppress_assignment) {
  char s1[50] = {0}, s2[50] = {0};
  ck_assert_int_eq(s21_sscanf("123 abc", "%*d %49s", s1),
                   sscanf("123 abc", "%*d %49s", s2));
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_mixed_types) {
  int a1, a2;
  float f1, f2;
  char s1[50] = {0}, s2[50] = {0};
  ck_assert_int_eq(s21_sscanf("42 3.14 test", "%d %f %49s", &a1, &f1, s1),
                   sscanf("42 3.14 test", "%d %f %49s", &a2, &f2, s2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(f1 == f2, 1);
  ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(test_sscanf_octal_hex) {
  unsigned int o1, o2, x1, x2;
  ck_assert_int_eq(s21_sscanf("777 0xFF", "%o %x", &o1, &x1),
                   sscanf("777 0xFF", "%o %x", &o2, &x2));
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(x1, x2);
}
END_TEST

START_TEST(test_sscanf_n_specifier) {
  int a1, a2, n1, n2;
  ck_assert_int_eq(s21_sscanf("test 123", "test %d%n", &a1, &n1),
                   sscanf("test 123", "test %d%n", &a2, &n2));
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_sscanf_percent) {
  ck_assert_int_eq(s21_sscanf("%%", "%%"), sscanf("%%", "%%"));
}
END_TEST

START_TEST(test_int_conversions_basic) {
  int a, b;
  unsigned int c, d, e, f;

  ASSERT_SCANF_EQ("%d %i %u %o %x %X", "42 42 42 52 2A 2A", &a, &b, &c, &d, &e,
                  &f);
}
END_TEST

START_TEST(test_int_prefix_and_signs) {
  int a, b, c;
  ASSERT_SCANF_EQ("%i %i %i", "-10 0x10 010", &a, &b, &c);
}
END_TEST

START_TEST(test_int_width_limit) {
  int a = 0;
  ASSERT_SCANF_EQ("%2d", "12345", &a);
}
END_TEST

START_TEST(test_int_suppress_assignment) {
  int a = 999;
  ASSERT_SCANF_EQ("%*d %d", "123 456", &a);
}
END_TEST

START_TEST(test_int_length_modifiers) {
  long l;
  short s;
  long long ll;
  signed char hh;
  ASSERT_SCANF_EQ("%ld %hd %lld %hhd", "12345 12 99999 42", &l, &s, &ll, &hh);
}
END_TEST

START_TEST(test_float_exponent) {
  float f;
  ASSERT_SCANF_EQ("%f", "1.23e-3", &f);
}
END_TEST

START_TEST(test_float_specials) {
  double a, b, c;
  ASSERT_SCANF_EQ("%lf %lf %lf", "inf infinity nan", &a, &b, &c);
}
END_TEST

START_TEST(test_float_negative) {
  float f;
  ASSERT_SCANF_EQ("%f", "-123.45", &f);
}
END_TEST

START_TEST(test_char_and_string_basic) {
  char c1, c2;
  char s[20];
  ASSERT_SCANF_EQ("%c %c %19s", "A B Hello", &c1, &c2, s);
}
END_TEST

START_TEST(test_char_with_width) {
  char buf[10];
  ASSERT_SCANF_EQ("%3c", "XYZ123", buf);
}
END_TEST

START_TEST(test_string_with_width) {
  char s[10];
  ASSERT_SCANF_EQ("%4s", "HelloWorld", s);
}
END_TEST

START_TEST(test_string_suppress) {
  char s[10] = "xxx";
  ASSERT_SCANF_EQ("%*s %9s", "Skip This", s);
}
END_TEST

START_TEST(test_string_empty_input) {
  char s[10] = "abc";
  ASSERT_SCANF_EQ("%9s", "", s);
}
END_TEST

START_TEST(test_scanset_basic) {
  char b[10];
  ASSERT_SCANF_EQ("%9[abc]", "aaabbbxyz", b);
}
END_TEST

START_TEST(test_scanset_negate) {
  char b[10];
  ASSERT_SCANF_EQ("%9[^0-9]", "Hello123", b);
}
END_TEST

START_TEST(test_scanset_range) {
  char b[20];
  ASSERT_SCANF_EQ("%19[a-z]", "helloWORLD", b);
}
END_TEST

START_TEST(test_scanset_with_bracket) {
  char b[10];
  ASSERT_SCANF_EQ("%9[]]", "]]]]abc", b);
}
END_TEST

START_TEST(test_pointer_basic) {
  void *p = NULL;
  ASSERT_SCANF_EQ("%p", "0x7fffabcd", &p);
}
END_TEST

START_TEST(test_percent_literal) {
  int rs, r21;
  rs = sscanf("%", "%%");
  r21 = s21_sscanf("%", "%%");
  ck_assert_int_eq(rs, r21);
}
END_TEST

START_TEST(test_n_specifier_basic) {
  int a, n;
  ASSERT_SCANF_EQ("%d%n", "12345", &a, &n);
}
END_TEST

START_TEST(test_n_specifier_lengths) {
  int d = 0;
  short hs = 0;
  long l = 0;
  long long ll = 0;
  ASSERT_SCANF_EQ("%d%hn%ln%lln", "42", &d, &hs, &l, &ll);
}
END_TEST

START_TEST(test_whitespace_handling) {
  int a, b;
  ASSERT_SCANF_EQ("%d %d", "   42   99", &a, &b);
}
END_TEST

START_TEST(test_invalid_input_non_digit) {
  int a = 111;
  ASSERT_SCANF_EQ("%d", "ABC", &a);
}
END_TEST

START_TEST(test_invalid_literal_mismatch) {
  int rs = sscanf("Hello", "World");
  int r21 = s21_sscanf("Hello", "World");
  ck_assert_int_eq(rs, r21);
}
END_TEST

START_TEST(test_null_format_or_src) {
  ck_assert_int_eq(s21_sscanf(NULL, "%d", 0), -1);
  ck_assert_int_eq(s21_sscanf("123", NULL, 0), -1);
}
END_TEST

START_TEST(test_unsigned_modifiers) {
  unsigned short hs;
  unsigned long hl;
  unsigned long long hll;
  unsigned char hh;
  ASSERT_SCANF_EQ("%hu %lu %llu %hhu", "42 12345 999999 12", &hs, &hl, &hll,
                  &hh);
}
END_TEST

START_TEST(test_base_prefix_16) {
  unsigned x;
  ASSERT_SCANF_EQ("%x", "0xFF", &x);
}
END_TEST

START_TEST(test_base_prefix_8) {
  int x;
  ASSERT_SCANF_EQ("%i", "0777", &x);
}
END_TEST

START_TEST(test_base_prefix_10) {
  int x;
  ASSERT_SCANF_EQ("%i", "123", &x);
}
END_TEST

START_TEST(test_float_nan_inf_mixed_case) {
  double a, b;
  ASSERT_SCANF_EQ("%lf %lf", "NaN InFiNiTy", &a, &b);
}
END_TEST
START_TEST(test_float_zero_and_negative_exp) {
  double a;
  ASSERT_SCANF_EQ("%lf", "1.23E-2", &a);
}
END_TEST

START_TEST(test_mixed_formats_all) {
  int a;
  float f;
  char s[10];
  char c;
  ASSERT_SCANF_EQ("%d %f %9s %c", "42 3.14 hello X", &a, &f, s, &c);
}
END_TEST

START_TEST(test_multiple_literals) {
  int a;
  ASSERT_SCANF_EQ("num:%d;end", "num:99;end", &a);
}
END_TEST

START_TEST(test_literal_mismatch_early_stop) {
  int a = 0;
  int rs = sscanf("num:99x", "num:%d;end", &a);
  int r21 = s21_sscanf("num:99x", "num:%d;end", &a);
  ck_assert_int_eq(rs, r21);
}
END_TEST

START_TEST(test_extreme_values) {
  long long big;
  ASSERT_SCANF_EQ("%lld", "9223372036854775807", &big);
}
END_TEST
START_TEST(test_extreme_negative_values) {
  long long big;
  ASSERT_SCANF_EQ("%lld", "-9223372036854775808", &big);
}
END_TEST
START_TEST(test_unsigned_overflow) {
  unsigned long long big;
  ASSERT_SCANF_EQ("%llu", "18446744073709551615", &big);
}
END_TEST

START_TEST(test_zero_width_behavior) {
  int a = 0;
  ASSERT_SCANF_EQ_UNSAFE("%1d", "42", &a);
}
END_TEST

END_TEST

START_TEST(test_extra_spaces_in_format) {
  int a, b;
  ASSERT_SCANF_EQ(" %d  %d ", " 1 2 ", &a, &b);
}
END_TEST
START_TEST(test_trailing_chars) {
  int a;
  ASSERT_SCANF_EQ("%d", "42xyz", &a);
}
END_TEST

START_TEST(test_all_length_modifiers_parse) {
  const char *fmt[] = {"%hhx", "%hx", "%llx", "%lx", "%jx",
                       "%zx",  "%tx", "%Lx",  "%x"};
  for (int i = 0; i < 9; i++) {
    unsigned long long x = 0;
    s21_sscanf("7B", fmt[i], &x);
  }
}
END_TEST

START_TEST(test_read_base_prefix_variants) {
  unsigned x;
  s21_sscanf("0x1F", "%i", &x);
  s21_sscanf("075", "%i", &x);
  s21_sscanf("9", "%i", &x);
  s21_sscanf("0x", "%x", &x);
}
END_TEST

START_TEST(test_unsigned_integer_invalid_digit) {
  unsigned x;
  s21_sscanf("12Z", "%u", &x);
  s21_sscanf("777", "%2u", &x);
}
END_TEST

START_TEST(test_integer_overflow_signs) {
  long long x;
  s21_sscanf("999999999999999999999", "%lld", &x);
  s21_sscanf("-999999999999999999999", "%lld", &x);
}
END_TEST

START_TEST(test_float_exponent_variants) {
  double x;
  s21_sscanf("1.23e+4", "%lf", &x);
  s21_sscanf("1.23e-4", "%lf", &x);
  s21_sscanf("1.23e", "%lf", &x);
  s21_sscanf("1.23", "%lf", &x);
}
END_TEST

START_TEST(test_float_parts_variants) {
  double x;
  s21_sscanf(".25", "%lf", &x);
  s21_sscanf("42.", "%lf", &x);
  s21_sscanf(".", "%lf", &x);
}
END_TEST

START_TEST(test_pointer_edge_cases) {
  void *p = NULL;
  s21_sscanf("0x", "%p", &p);
  s21_sscanf("123ABC", "%p", &p);
}
END_TEST

START_TEST(test_conv_char_edge_cases) {
  char c = 'X';
  s21_sscanf("", "%c", &c);
  s21_sscanf("AB", "%*c%c", &c);
}
END_TEST

START_TEST(test_scanset_corner_cases) {
  char b[10];
  s21_sscanf("abc", "%[^]", b);
  s21_sscanf("zxy", "%[z-a]", b);
  s21_sscanf("hello", "%[^h]", b);
}
END_TEST

START_TEST(test_handle_specifier_edges) {
  int x;
  s21_sscanf("", "%d", &x);
  s21_sscanf("%%", "%%");
  s21_sscanf("abc", "%*", &x);
}
END_TEST

START_TEST(test_parse_spec_incomplete) {
  int x;
  s21_sscanf("42", "%", &x);
  s21_sscanf("abc", "%[", &x);
  s21_sscanf("abc", "%[^", &x);
}
END_TEST

START_TEST(test_process_literal_mismatch) {
  int x;
  s21_sscanf("Hello", "World%d", &x);
}
END_TEST

START_TEST(test_skip_format_whitespace_variants) {
  int x;
  s21_sscanf("    123", "   %d", &x);
  s21_sscanf("123", "   %d", &x);
}
END_TEST

START_TEST(test_handle_n_all_lengths) {
  int a;
  short hs;
  long l;
  long long ll;
  signed char hh;
  s21_sscanf("abcd", "%n", &a);
  s21_sscanf("abcd", "%hn", &hs);
  s21_sscanf("abcd", "%ln", &l);
  s21_sscanf("abcd", "%lln", &ll);
  s21_sscanf("abcd", "%hhn", &hh);
}
END_TEST

START_TEST(test_finalize_processing_variants) {
  int x;
  s21_sscanf("a", "%d", &x);
  s21_sscanf("123", "%*d", &x);
}
END_TEST

START_TEST(test_float_special_values_extra) {
  double a, b, c;
  s21_sscanf("INF", "%lf", &a);
  s21_sscanf("infinity", "%lf", &b);
  s21_sscanf("NAN(extra)", "%lf", &c);
}
END_TEST

START_TEST(test_float_exponent_missing_digits) {
  double a;
  s21_sscanf("1.0e+", "%lf", &a);
  s21_sscanf("1.0e-", "%lf", &a);
  s21_sscanf("1.0eA", "%lf", &a);
}
END_TEST

START_TEST(test_unsigned_integer_zero_and_invalid) {
  unsigned long long u;
  s21_sscanf("GHI", "%x", &u);
  s21_sscanf("8", "%0u", &u);
}
END_TEST

START_TEST(test_pointer_odd_cases) {
  void *p = NULL;
  s21_sscanf("-0x123", "%p", &p);
  s21_sscanf("0XABCD", "%p", &p);
  s21_sscanf("0x", "%p", &p);
}
END_TEST

START_TEST(test_scanset_degenerate_inputs) {
  char b[10];
  s21_sscanf("", "%[a-z]", b);
  s21_sscanf("abc", "%0[a-z]", b);
  s21_sscanf("xyz", "%[^xyz]", b);
}
END_TEST

START_TEST(test_string_weird_widths) {
  char b[10];
  s21_sscanf("abc def", "%0s", b);
  s21_sscanf("abc def", "%3s", b);
}
END_TEST

START_TEST(test_handle_specifier_suppress_and_n) {
  int n1, n2;
  s21_sscanf("abc", "%*n%n", &n1, &n2);
}
END_TEST

START_TEST(test_parse_spec_malformed) {
  int x;
  s21_sscanf("99", "%**d", &x);
  s21_sscanf("10", "%10hhq", &x);
  s21_sscanf("5", "%%", &x);
}
END_TEST

START_TEST(test_store_variants_all) {
  signed char a;
  short b;
  int c;
  long d;
  long long e;
  intmax_t j;
  size_t z;
  ptrdiff_t t;
  long double L;
  a = b = c = d = e = j = z = t = 0;
  L = 0;
  s21_sscanf("127", "%hhd", &a);
  s21_sscanf("32767", "%hd", &b);
  s21_sscanf("999", "%d", &c);
  s21_sscanf("123456", "%ld", &d);
  s21_sscanf("9999999999", "%lld", &e);
  s21_sscanf("1", "%jd", &j);
  s21_sscanf("2", "%zd", &z);
  s21_sscanf("3", "%td", &t);
  s21_sscanf("1.2345", "%Lf", &L);
}
END_TEST

START_TEST(test_calculate_float_exponent_cases) {
  double f;
  s21_sscanf("1.0e0", "%lf", &f);
  s21_sscanf("1.0e5", "%lf", &f);
  s21_sscanf("1.0e-5", "%lf", &f);
}
END_TEST

START_TEST(test_match_literal_cases) {
  int x;
  s21_sscanf("A", "A%d", &x);
  s21_sscanf("B", "A%d", &x);
}
END_TEST

START_TEST(test_skip_ws_branches) {
  int x;
  s21_sscanf("   42", "%d", &x);
  s21_sscanf("\n\t\r", "%d", &x);
  s21_sscanf("", "%d", &x);
}
END_TEST

START_TEST(test_parse_loop_early_exit) {
  int x;
  s21_sscanf("hello", "world%d", &x);
}
END_TEST

START_TEST(test_sscanf_empty_fmt_and_percent) {
  int x;
  s21_sscanf("123", "", &x);
  s21_sscanf("abc", "%", &x);
}
END_TEST

Suite *s21_sscanf_suite(void) {
  Suite *s = suite_create("s21_sscanf_full_branch_only");
  TCase *tc = tcase_create("core");

  suite_add_tcase(s, tc);
  return s;
}

TCase *tcase_sscanf(void) {
  TCase *tc = tcase_create("s21_sscanf");
  tcase_add_test(tc, test_sscanf_multiple_ints);
  tcase_add_test(tc, test_sscanf_width_ints);
  tcase_add_test(tc, test_sscanf_floats);
  tcase_add_test(tc, test_sscanf_doubles);
  tcase_add_test(tc, test_sscanf_string_width);
  tcase_add_test(tc, test_sscanf_chars);
  tcase_add_test(tc, test_sscanf_scanset);
  tcase_add_test(tc, test_sscanf_negated_scanset);
  tcase_add_test(tc, test_sscanf_suppress_assignment);
  tcase_add_test(tc, test_sscanf_mixed_types);
  tcase_add_test(tc, test_sscanf_octal_hex);
  tcase_add_test(tc, test_sscanf_n_specifier);
  tcase_add_test(tc, test_sscanf_percent);
  tcase_add_test(tc, test_int_conversions_basic);
  tcase_add_test(tc, test_int_prefix_and_signs);
  tcase_add_test(tc, test_int_width_limit);
  tcase_add_test(tc, test_int_suppress_assignment);
  tcase_add_test(tc, test_int_length_modifiers);
  tcase_add_test(tc, test_float_exponent);
  tcase_add_test(tc, test_float_specials);
  tcase_add_test(tc, test_float_negative);
  tcase_add_test(tc, test_char_and_string_basic);
  tcase_add_test(tc, test_char_with_width);
  tcase_add_test(tc, test_string_with_width);
  tcase_add_test(tc, test_string_suppress);
  tcase_add_test(tc, test_string_empty_input);
  tcase_add_test(tc, test_scanset_basic);
  tcase_add_test(tc, test_scanset_negate);
  tcase_add_test(tc, test_scanset_range);
  tcase_add_test(tc, test_scanset_with_bracket);
  tcase_add_test(tc, test_pointer_basic);
  tcase_add_test(tc, test_percent_literal);
  tcase_add_test(tc, test_n_specifier_basic);
  tcase_add_test(tc, test_n_specifier_lengths);
  tcase_add_test(tc, test_whitespace_handling);
  tcase_add_test(tc, test_invalid_input_non_digit);
  tcase_add_test(tc, test_invalid_literal_mismatch);
  tcase_add_test(tc, test_null_format_or_src);
  tcase_add_test(tc, test_unsigned_modifiers);
  tcase_add_test(tc, test_base_prefix_16);
  tcase_add_test(tc, test_base_prefix_8);
  tcase_add_test(tc, test_base_prefix_10);
  tcase_add_test(tc, test_float_nan_inf_mixed_case);
  tcase_add_test(tc, test_float_zero_and_negative_exp);
  tcase_add_test(tc, test_mixed_formats_all);
  tcase_add_test(tc, test_multiple_literals);
  tcase_add_test(tc, test_literal_mismatch_early_stop);
  tcase_add_test(tc, test_extreme_values);
  tcase_add_test(tc, test_extreme_negative_values);
  tcase_add_test(tc, test_unsigned_overflow);
  tcase_add_test(tc, test_zero_width_behavior);
  tcase_add_test(tc, test_extra_spaces_in_format);
  tcase_add_test(tc, test_trailing_chars);
  tcase_add_test(tc, test_float_basic);
  tcase_add_test(tc, test_all_length_modifiers_parse);
  tcase_add_test(tc, test_read_base_prefix_variants);
  tcase_add_test(tc, test_unsigned_integer_invalid_digit);
  tcase_add_test(tc, test_integer_overflow_signs);
  tcase_add_test(tc, test_float_exponent_variants);
  tcase_add_test(tc, test_float_parts_variants);
  tcase_add_test(tc, test_pointer_edge_cases);
  tcase_add_test(tc, test_conv_char_edge_cases);
  tcase_add_test(tc, test_scanset_corner_cases);
  tcase_add_test(tc, test_handle_specifier_edges);
  tcase_add_test(tc, test_parse_spec_incomplete);
  tcase_add_test(tc, test_process_literal_mismatch);
  tcase_add_test(tc, test_skip_format_whitespace_variants);
  tcase_add_test(tc, test_handle_n_all_lengths);
  tcase_add_test(tc, test_finalize_processing_variants);
  tcase_add_test(tc, test_float_special_values_extra);
  tcase_add_test(tc, test_float_exponent_missing_digits);
  tcase_add_test(tc, test_unsigned_integer_zero_and_invalid);
  tcase_add_test(tc, test_pointer_odd_cases);
  tcase_add_test(tc, test_scanset_degenerate_inputs);
  tcase_add_test(tc, test_string_weird_widths);
  tcase_add_test(tc, test_handle_specifier_suppress_and_n);
  tcase_add_test(tc, test_parse_spec_malformed);
  tcase_add_test(tc, test_store_variants_all);
  tcase_add_test(tc, test_calculate_float_exponent_cases);
  tcase_add_test(tc, test_match_literal_cases);
  tcase_add_test(tc, test_skip_ws_branches);
  tcase_add_test(tc, test_parse_loop_early_exit);
  tcase_add_test(tc, test_sscanf_empty_fmt_and_percent);

  return tc;
}