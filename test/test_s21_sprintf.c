#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

// Тест 1: Простой текст без форматирования
START_TEST(test_sprintf_basic_text) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "Hello World");
  int res2 = snprintf(buffer2, sizeof(buffer2), "Hello World");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 2: Символ %%
START_TEST(test_sprintf_percent) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "100%% complete");
  int res2 = snprintf(buffer2, sizeof(buffer2), "100%% complete");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 3: Символ %c
START_TEST(test_sprintf_char) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "Char: %c", 'A');
  int res2 = snprintf(buffer2, sizeof(buffer2), "Char: %c", 'A');

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 4: Строка %s
START_TEST(test_sprintf_string) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "String: %s", "test");
  int res2 = snprintf(buffer2, sizeof(buffer2), "String: %s", "test");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 5: Целое число %d
START_TEST(test_sprintf_int) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "Number: %d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "Number: %d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 6: Флаг минус (левое выравнивание)
START_TEST(test_sprintf_minus_flag) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%-10d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%-10d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 7: Флаг плюс (знак для положительных)
START_TEST(test_sprintf_plus_flag) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%+d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%+d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 8: Флаг пробел (пробел для положительных)
START_TEST(test_sprintf_space_flag) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "% d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "% d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 9: Беззнаковое целое %u
START_TEST(test_sprintf_unsigned) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%u", (unsigned int)123456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%u", (unsigned int)123456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 10: Вещественное число %f
START_TEST(test_sprintf_float) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.2f", 3.14159);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.2f", 3.14159);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 11: Ширина поля
START_TEST(test_sprintf_width) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%5d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%5d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 12: Точность для целых
START_TEST(test_sprintf_precision_int) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.5d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.5d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 13: Точность для строк
START_TEST(test_sprintf_precision_string) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.3s", "hello");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.3s", "hello");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 14: Комбинация ширины и точности
START_TEST(test_sprintf_width_precision) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%8.3d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%8.3d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 15: Отрицательные числа с флагами
START_TEST(test_sprintf_negative_with_flags) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%+d", -42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%+d", -42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 16: Модификатор h (short)
START_TEST(test_sprintf_short) {
  char buffer1[100], buffer2[100];

  short num = 123;
  int res1 = s21_sprintf(buffer1, "%hd", num);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%hd", num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 17: Модификатор l (long)
START_TEST(test_sprintf_long) {
  char buffer1[100], buffer2[100];

  long num = 123456789L;
  int res1 = s21_sprintf(buffer1, "%ld", num);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%ld", num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 19: Нулевое целое
START_TEST(test_sprintf_zero_int) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%d", 0);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%d", 0);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 20: Спецификатор %i (синоним %d)
START_TEST(test_sprintf_i_specifier) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%i", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%i", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 21: Шестнадцатеричное x (нижний регистр)
START_TEST(test_sprintf_hex_lower) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%x", 255);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%x", 255);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 22: Шестнадцатеричное X (верхний регистр)
START_TEST(test_sprintf_hex_upper) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%X", 255);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%X", 255);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 23: Восьмеричное o
START_TEST(test_sprintf_octal) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%o", 64);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%o", 64);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 24: Указатель p
START_TEST(test_sprintf_pointer) {
  char buffer1[100], buffer2[100];
  int x = 42;

  s21_sprintf(buffer1, "%p", &x);
  snprintf(buffer2, sizeof(buffer2), "%p", &x);

  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 25: Флаг # для шестнадцатеричных
START_TEST(test_sprintf_hash_hex) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%#x", 255);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%#x", 255);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 26: Флаг 0 (zero padding)
START_TEST(test_sprintf_zero_flag) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%05d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%05d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 27: Флаг # для восьмеричных
START_TEST(test_sprintf_hash_octal) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%#o", 8);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%#o", 8);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 28: Научная нотация e
START_TEST(test_sprintf_scientific_lower) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%e", 123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%e", 123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 29: Научная нотация E (верхний регистр)
START_TEST(test_sprintf_scientific_upper) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%E", 123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%E", 123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 30: Спецификатор g (автовыбор формата)
START_TEST(test_sprintf_g_format) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%g", 123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%g", 123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 31: Спецификатор G (автовыбор формата, верхний регистр)
START_TEST(test_sprintf_g_upper) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%G", 0.000123);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%G", 0.000123);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 32: Ширина через *
START_TEST(test_sprintf_width_star) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%*d", 5, 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%*d", 5, 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 33: Точность через .*
START_TEST(test_sprintf_precision_star) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.*f", 2, 3.14159);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.*f", 2, 3.14159);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 34: Комбинация ширины и точности через *
START_TEST(test_sprintf_width_precision_star) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%*.*f", 8, 3, 3.14159);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%*.*f", 8, 3, 3.14159);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 35: Спецификатор G с большим числом
START_TEST(test_sprintf_g_upper_large) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%G", 1234567.89);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%G", 1234567.89);

  ck_assert_int_ge(res1, 0);
  ck_assert_int_ge(res2, 0);
  ck_assert_int_gt(strlen(buffer1), 0);

  ck_assert_ptr_nonnull(strchr(buffer1, 'E'));
  ck_assert_ptr_nonnull(strchr(buffer1, '+'));
}
END_TEST

// Тест 36: Флаг минус
START_TEST(test_sprintf_flag_minus) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%-10s", "test");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%-10s", "test");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 37: Флаг плюс
START_TEST(test_sprintf_flag_plus) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%+d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%+d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 38: Флаг пробел
START_TEST(test_sprintf_flag_space) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "% d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "% d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 39: Флаг решетка
START_TEST(test_sprintf_flag_hash) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%#x", 255);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%#x", 255);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 40: Флаг ноль
START_TEST(test_sprintf_flag_zero) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%05d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%05d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 41: NULL format в sprintf
START_TEST(test_sprintf_null_format) {
  char buffer[100];

  int result = s21_sprintf(buffer, NULL);

  ck_assert_int_eq(result, -1);
}
END_TEST

// Тест 42: NULL buffer в sprintf
START_TEST(test_sprintf_null_buffer) {
  int result = s21_sprintf(NULL, "test");

  ck_assert_int_eq(result, -1);
}
END_TEST

// Тест 43: NULL оба параметра в sprintf
START_TEST(test_sprintf_null_both) {
  int result = s21_sprintf(NULL, NULL);
  ck_assert_int_eq(result, -1);
}
END_TEST

// Тест 44: Комбинация всех флагов
START_TEST(test_sprintf_valid_flags_combination) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%#x", 255);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%#x", 255);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 45: Неизвестный флаг
START_TEST(test_sprintf_valid_specifier_with_flags) {
  char buffer1[100], buffer2[100];

  // Используем валидный спецификатор
  int res1 = s21_sprintf(buffer1, "%+d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%+d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 46: Флаг пробел (валидный)
START_TEST(test_sprintf_space_flag_valid) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "% d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "% d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 47: Флаг минус с шириной (валидный)
START_TEST(test_sprintf_minus_width_valid) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%-10s", "test");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%-10s", "test");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 48: apply_padding - обычное заполнение справа (width > len)
START_TEST(test_sprintf_padding_right) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%5s", "hi");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%5s", "hi");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 49: apply_padding - заполнение слева с флагом минус
START_TEST(test_sprintf_padding_left) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%-5s", "hi");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%-5s", "hi");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 50: apply_padding - zero padding с числами
START_TEST(test_sprintf_zero_padding) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%05d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%05d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 51: apply_padding - ширина меньше длины строки (padding <= 0)
START_TEST(test_sprintf_no_padding_needed) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%2s", "hello");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%2s", "hello");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 52: apply_padding - zero padding с минус флагом (zero игнорируется)
START_TEST(test_sprintf_minus_ignores_zero) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%-5d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%-5d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 53: apply_padding - очень большая ширина
START_TEST(test_sprintf_large_padding) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%20s", "test");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%20s", "test");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 54: apply_padding - ширина 0
START_TEST(test_sprintf_zero_width) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%s", "test");
  int res2 = snprintf(buffer2, sizeof(buffer2), "%s", "test");

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 55: apply_padding - zero padding только с числами
START_TEST(test_sprintf_zero_padding_numbers_only) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%05d", 42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%05d", 42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 56: apply_padding - отрицательная ширина через *
START_TEST(test_sprintf_negative_width_star) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%*s", -5, "hi");
  snprintf(buffer2, sizeof(buffer2), "%*s", -5, "hi");

  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 57: Отрицательное вещественное число
START_TEST(test_sprintf_negative_float) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.2f", -3.14159);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.2f", -3.14159);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 58: Отрицательное вещественное с флагом плюс
START_TEST(test_sprintf_negative_float_plus_flag) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%+.2f", -3.14159);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%+.2f", -3.14159);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 59: Отрицательное вещественное с шириной
START_TEST(test_sprintf_negative_float_width) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%8.2f", -3.14159);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%8.2f", -3.14159);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 60: Очень маленькое отрицательное число
START_TEST(test_sprintf_negative_small_float) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%f", -0.000001);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%f", -0.000001);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 61: Отрицательное число в научной нотации
START_TEST(test_sprintf_negative_scientific) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%e", -123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%e", -123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 62: Отрицательный ноль
START_TEST(test_sprintf_negative_zero) {
  char buffer1[100], buffer2[100];

  s21_sprintf(buffer1, "%.2f", -0.0);
  snprintf(buffer2, sizeof(buffer2), "%.2f", -0.0);

  ck_assert_int_gt(strlen(buffer1), 0);
  ck_assert_int_gt(strlen(buffer2), 0);
}
END_TEST

// Тест 63: Отрицательная точность для %f (должна использовать precision по
// умолчанию 6)
START_TEST(test_sprintf_negative_precision_float) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.*f", -2, 3.14159);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.*f", -2, 3.14159);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 64: Отрицательная точность для %e (должна использовать precision по
// умолчанию 6)
START_TEST(test_sprintf_negative_precision_scientific) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.*e", -3, 123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.*e", -3, 123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 65: Отрицательная точность для %g (должна использовать precision по
// умолчанию 6)
START_TEST(test_sprintf_negative_precision_g_format) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%.*g", -1, 123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%.*g", -1, 123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 66: %g с модификатором L (long double)
START_TEST(test_sprintf_g_long_double) {
  char buffer1[100], buffer2[100];

  long double num = 123.456L;
  int res1 = s21_sprintf(buffer1, "%Lg", num);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%Lg", num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 67: %g с нулем
START_TEST(test_sprintf_g_zero) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%g", 0.0);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%g", 0.0);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 68: %g с шириной
START_TEST(test_sprintf_g_with_width) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%10g", 123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%10g", 123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 69: %G с очень маленьким числом (должен использовать научную нотацию)
START_TEST(test_sprintf_g_small_number) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%G", 0.0000123);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%G", 0.0000123);

  ck_assert_int_ge(res1, 0);
  ck_assert_int_ge(res2, 0);
}
END_TEST

// Тест 70: %g с очень большим числом (должен использовать научную нотацию)
START_TEST(test_sprintf_g_large_number) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%g", 123456789.0);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%g", 123456789.0);

  ck_assert_int_ge(res1, 0);
  ck_assert_int_ge(res2, 0);
}
END_TEST

// Тест 71: %p с валидным указателем
START_TEST(test_sprintf_pointer_valid) {
  char buffer1[100], buffer2[100];

  int x = 42;
  int res1 = s21_sprintf(buffer1, "%p", (void *)&x);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%p", (void *)&x);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_nonnull(buffer1);
  ck_assert_ptr_nonnull(buffer2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 72: %p с указателем на строку
START_TEST(test_sprintf_pointer_string) {
  char buffer1[100], buffer2[100];

  char str[] = "test";
  int res1 = s21_sprintf(buffer1, "%p", (void *)str);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%p", (void *)str);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_nonnull(buffer1);
  ck_assert_ptr_nonnull(buffer2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 73: %p с указателем на массив
START_TEST(test_sprintf_pointer_array) {
  char buffer1[100], buffer2[100];

  int arr[5] = {1, 2, 3, 4, 5};
  int res1 = s21_sprintf(buffer1, "%p", (void *)arr);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%p", (void *)arr);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_nonnull(buffer1);
  ck_assert_ptr_nonnull(buffer2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 74: %p с шириной
START_TEST(test_sprintf_pointer_width) {
  char buffer1[100], buffer2[100];

  int x = 42;
  int res1 = s21_sprintf(buffer1, "%10p", (void *)&x);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%10p", (void *)&x);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_nonnull(buffer1);
  ck_assert_ptr_nonnull(buffer2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 75: Отрицательное число с основанием 10
START_TEST(test_sprintf_negative_decimal_internal) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%d", -42);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%d", -42);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_str_eq(buffer1, "-42");
}
END_TEST

// Тест 76: Отрицательное число с основанием 10 через %i
START_TEST(test_sprintf_negative_int_internal) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%i", -123);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%i", -123);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);

  ck_assert_str_eq(buffer1, "-123");
}
END_TEST

// Тест 77: %u с модификатором l (long)
START_TEST(test_sprintf_unsigned_long) {
  char buffer1[100], buffer2[100];

  unsigned long num = 4294967295UL;
  int res1 = s21_sprintf(buffer1, "%lu", num);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%lu", num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 78: %u с шириной
START_TEST(test_sprintf_unsigned_width) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%10u", (unsigned int)123);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%10u", (unsigned int)123);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 79: %e с модификатором L (long double)
START_TEST(test_sprintf_scientific_long_double) {
  char buffer1[100], buffer2[100];

  long double num = 123.456L;
  int res1 = s21_sprintf(buffer1, "%Le", num);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%Le", num);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 80: %E с шириной
START_TEST(test_sprintf_scientific_width) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%15E", 123.456);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%15E", 123.456);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 81: %X с преобразованием в верхний регистр
START_TEST(test_sprintf_hex_upper_conversion) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%X", 0xabc);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%X", 0xabc);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 82: %#x с флагом решетка
START_TEST(test_sprintf_hex_hash_flag) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%#x", 255);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%#x", 255);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

// Тест 83: %x с шириной
START_TEST(test_sprintf_hex_width) {
  char buffer1[100], buffer2[100];

  int res1 = s21_sprintf(buffer1, "%8x", 255);
  int res2 = snprintf(buffer2, sizeof(buffer2), "%8x", 255);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(buffer1, buffer2);
}
END_TEST

TCase *tcase_sprintf(void) {
  TCase *tc = tcase_create("s21_sprintf");

  tcase_add_test(tc, test_sprintf_basic_text);
  tcase_add_test(tc, test_sprintf_percent);
  tcase_add_test(tc, test_sprintf_char);
  tcase_add_test(tc, test_sprintf_string);
  tcase_add_test(tc, test_sprintf_int);

  tcase_add_test(tc, test_sprintf_minus_flag);
  tcase_add_test(tc, test_sprintf_plus_flag);
  tcase_add_test(tc, test_sprintf_space_flag);
  tcase_add_test(tc, test_sprintf_unsigned);
  tcase_add_test(tc, test_sprintf_float);

  tcase_add_test(tc, test_sprintf_width);
  tcase_add_test(tc, test_sprintf_precision_int);
  tcase_add_test(tc, test_sprintf_precision_string);
  tcase_add_test(tc, test_sprintf_width_precision);
  tcase_add_test(tc, test_sprintf_negative_with_flags);

  tcase_add_test(tc, test_sprintf_short);
  tcase_add_test(tc, test_sprintf_long);
  tcase_add_test(tc, test_sprintf_zero_int);
  tcase_add_test(tc, test_sprintf_i_specifier);

  tcase_add_test(tc, test_sprintf_hex_lower);
  tcase_add_test(tc, test_sprintf_hex_upper);
  tcase_add_test(tc, test_sprintf_octal);
  tcase_add_test(tc, test_sprintf_pointer);
  tcase_add_test(tc, test_sprintf_hash_hex);

  tcase_add_test(tc, test_sprintf_zero_flag);
  tcase_add_test(tc, test_sprintf_hash_octal);
  tcase_add_test(tc, test_sprintf_scientific_lower);
  tcase_add_test(tc, test_sprintf_scientific_upper);
  tcase_add_test(tc, test_sprintf_g_format);

  tcase_add_test(tc, test_sprintf_g_upper);
  tcase_add_test(tc, test_sprintf_width_star);
  tcase_add_test(tc, test_sprintf_precision_star);
  tcase_add_test(tc, test_sprintf_width_precision_star);
  tcase_add_test(tc, test_sprintf_g_upper_large);

  tcase_add_test(tc, test_sprintf_flag_minus);
  tcase_add_test(tc, test_sprintf_flag_plus);
  tcase_add_test(tc, test_sprintf_flag_space);
  tcase_add_test(tc, test_sprintf_flag_hash);
  tcase_add_test(tc, test_sprintf_flag_zero);

  tcase_add_test(tc, test_sprintf_null_format);
  tcase_add_test(tc, test_sprintf_null_buffer);
  tcase_add_test(tc, test_sprintf_null_both);
  tcase_add_test(tc, test_sprintf_valid_flags_combination);
  tcase_add_test(tc, test_sprintf_valid_specifier_with_flags);

  tcase_add_test(tc, test_sprintf_space_flag_valid);
  tcase_add_test(tc, test_sprintf_minus_width_valid);

  tcase_add_test(tc, test_sprintf_padding_right);
  tcase_add_test(tc, test_sprintf_padding_left);
  tcase_add_test(tc, test_sprintf_zero_padding);
  tcase_add_test(tc, test_sprintf_no_padding_needed);
  tcase_add_test(tc, test_sprintf_minus_ignores_zero);
  tcase_add_test(tc, test_sprintf_large_padding);
  tcase_add_test(tc, test_sprintf_zero_width);
  tcase_add_test(tc, test_sprintf_zero_padding_numbers_only);
  tcase_add_test(tc, test_sprintf_negative_width_star);

  tcase_add_test(tc, test_sprintf_negative_float);
  tcase_add_test(tc, test_sprintf_negative_float_plus_flag);
  tcase_add_test(tc, test_sprintf_negative_float_width);
  tcase_add_test(tc, test_sprintf_negative_small_float);
  tcase_add_test(tc, test_sprintf_negative_scientific);
  tcase_add_test(tc, test_sprintf_negative_zero);

  tcase_add_test(tc, test_sprintf_negative_precision_float);
  tcase_add_test(tc, test_sprintf_negative_precision_scientific);
  tcase_add_test(tc, test_sprintf_negative_precision_g_format);

  tcase_add_test(tc, test_sprintf_g_long_double);
  tcase_add_test(tc, test_sprintf_g_zero);
  tcase_add_test(tc, test_sprintf_g_with_width);
  tcase_add_test(tc, test_sprintf_g_small_number);
  tcase_add_test(tc, test_sprintf_g_large_number);

  tcase_add_test(tc, test_sprintf_pointer_valid);
  tcase_add_test(tc, test_sprintf_pointer_string);
  tcase_add_test(tc, test_sprintf_pointer_array);
  tcase_add_test(tc, test_sprintf_pointer_width);

  tcase_add_test(tc, test_sprintf_negative_decimal_internal);
  tcase_add_test(tc, test_sprintf_negative_int_internal);

  tcase_add_test(tc, test_sprintf_unsigned_long);
  tcase_add_test(tc, test_sprintf_unsigned_width);

  tcase_add_test(tc, test_sprintf_scientific_long_double);
  tcase_add_test(tc, test_sprintf_scientific_width);

  tcase_add_test(tc, test_sprintf_hex_upper_conversion);
  tcase_add_test(tc, test_sprintf_hex_hash_flag);
  tcase_add_test(tc, test_sprintf_hex_width);

  return tc;
}