#include <stdint.h>
#include <stdio.h>

#include "math.h"
#include "s21_string.h"

static int s21_isdigit(char c) { return (c >= '0' && c <= '9'); }

static char *s21_strcpy(char *dest, const char *src) {
  char *ptr = dest;
  while (*src != '\0') {
    *ptr++ = *src++;
  }
  *ptr = '\0';
  return dest;
}

static int is_flag_char(char c) {
  int result = 0;

  if (c == '-' || c == '+' || c == ' ' || c == '#' || c == '0') {
    result = 1;
  }

  return result;
}

static void set_flag(char flag_char, FormatFlags *flags) {
  if (flags != S21_NULL) {
    switch (flag_char) {
      case '-':
        flags->minus = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
      case '#':
        flags->hash = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
      default:
        break;
    }
  }
}

static const char *parse_flags(const char *format, FormatFlags *flags) {
  const char *result = format;

  if (format != S21_NULL && flags != S21_NULL) {
    while (is_flag_char(*result)) {
      set_flag(*result, flags);
      result++;
    }
  }

  return result;
}

static char *fill_padding(char *str, char fill_char, int count) {
  for (int i = 0; i < count; i++) {
    *str++ = fill_char;
  }
  return str;
}

static char *copy_buffer_content(char *str, const char *buffer, int len) {
  for (int i = 0; i < len; i++) {
    *str++ = buffer[i];
  }
  return str;
}

static char get_fill_char(const FormatFlags *flags) {
  char fill_char = ' ';
  if (flags->zero && !flags->minus) {
    fill_char = '0';
  }
  return fill_char;
}

static char *apply_padding(char *str, const char *buffer,
                           const FormatFlags *flags) {
  char *result = str;

  if (str != S21_NULL && buffer != S21_NULL && flags != S21_NULL) {
    int len = 0;
    while (buffer[len] != '\0') len++;

    int padding = flags->width - len;

    if (padding > 0) {
      if (flags->minus) {
        result = copy_buffer_content(result, buffer, len);
        result = fill_padding(result, ' ', padding);
      } else {
        char fill_char = get_fill_char(flags);
        result = fill_padding(result, fill_char, padding);
        result = copy_buffer_content(result, buffer, len);
      }
    } else {
      result = copy_buffer_content(result, buffer, len);
    }
  }

  return result;
}

static char digit_to_char_unsigned(unsigned int digit) {
  char result;
  if (digit < 10) {
    result = digit + '0';
  } else {
    result = digit - 10 + 'a';
  }
  return result;
}

static char *write_digits_reverse_unsigned(unsigned int value, int base,
                                           char *buffer) {
  char *p = buffer;

  do {
    unsigned int digit = value % base;
    *p++ = digit_to_char_unsigned(digit);
    value /= base;
  } while (value > 0);

  return p;
}

static void terminate_string(char *buffer_pos) { *buffer_pos = '\0'; }

void s21_utoa(unsigned int value, char *buffer, int base) {
  if (buffer != S21_NULL) {
    char *buffer_end = write_digits_reverse_unsigned(value, base, buffer);
    terminate_string(buffer_end);
    s21_reverse(buffer);
  }
}

static void handle_negative_float(double *value, int *negative) {
  *negative = 0;
  if (*value < 0) {
    *negative = 1;
    *value = -(*value);
  }
}

static void process_integer_part(double value, char *buffer, int negative) {
  int int_part = (int)value;
  s21_itoa(int_part, buffer, 10);

  if (negative) {
    char temp[64];
    temp[0] = '-';
    s21_strcpy(temp + 1, buffer);
    s21_strcpy(buffer, temp);
  }
}

static void process_fractional_part(double value, int int_part, char *buffer,
                                    int precision) {
  char *p = buffer;
  while (*p) p++;

  *p++ = '.';

  double frac = value - int_part;
  if (frac < 0) frac = -frac;

  double round_adj = 0.5;
  for (int i = 0; i < precision; i++) {
    round_adj /= 10.0;
  }
  frac += round_adj;

  for (int i = 0; i < precision; i++) {
    frac *= 10;
    int digit = (int)frac;
    *p++ = digit + '0';
    frac -= digit;
  }
  *p = '\0';
}

void s21_ftoa(double value, char *buffer, int precision) {
  int negative = 0;

  if (buffer != S21_NULL) {
    int int_part = 0;

    if (precision < 0) {
      precision = 6;
    }

    handle_negative_float(&value, &negative);
    int_part = (int)value;
    process_integer_part(value, buffer, negative);
    process_fractional_part(value, int_part, buffer, precision);
  }
}

static const char *parse_width(const char *format, FormatFlags *flags) {
  if (*format == '*') {
    flags->width_star = 1;
    format++;
  } else {
    int width = 0;
    while (s21_isdigit(*format)) {
      width = width * 10 + (*format - '0');
      format++;
    }
    flags->width = width;
  }
  return format;
}

static const char *parse_precision(const char *format, FormatFlags *flags) {
  if (*format == '.') {
    format++;
    flags->is_precision_set = 1;

    if (*format == '*') {
      flags->precision_star = 1;
      format++;
    } else {
      int precision = 0;
      while (s21_isdigit(*format)) {
        precision = precision * 10 + (*format - '0');
        format++;
      }
      flags->precision = precision;
    }
  }
  return format;
}

static const char *parse_length(const char *format, FormatFlags *flags) {
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    flags->length = *format;
    format++;
  }
  return format;
}

static const char *parse_specifier(const char *format, FormatFlags *flags) {
  flags->specifier = *format;
  return format + 1;
}

const char *s21_parse_format(const char *format, FormatFlags *flags) {
  format = parse_flags(format, flags);
  format = parse_width(format, flags);
  format = parse_precision(format, flags);
  format = parse_length(format, flags);
  format = parse_specifier(format, flags);
  return format;
}

void s21_reverse(char *str) {
  if (str == S21_NULL) return;

  char *end = str;
  while (*end != '\0') end++;
  end--;

  while (str < end) {
    char temp = *str;
    *str = *end;
    *end = temp;
    str++;
    end--;
  }
}

static int handle_negative_number(int *value, int base) {
  int negative = 0;
  if (*value < 0 && base == 10) {
    negative = 1;
    *value = -(*value);
  }
  return negative;
}

static char digit_to_char(int digit) {
  char result;
  if (digit < 10) {
    result = digit + '0';
  } else {
    result = digit - 10 + 'a';
  }
  return result;
}

static char *write_digits_reverse(int value, int base, char *buffer) {
  char *p = buffer;

  do {
    int digit = value % base;
    *p++ = digit_to_char(digit);
    value /= base;
  } while (value > 0);

  return p;
}

static char *add_negative_sign(char *buffer_pos, int negative) {
  if (negative) {
    *buffer_pos++ = '-';
  }
  *buffer_pos = '\0';
  return buffer_pos;
}

void s21_itoa(int value, char *buffer, int base) {
  if (buffer != S21_NULL) {
    int negative = handle_negative_number(&value, base);
    char *buffer_end = write_digits_reverse(value, base, buffer);
    add_negative_sign(buffer_end, negative);
    s21_reverse(buffer);
  }
}

static char *process_string(char *str, FormatFlags *flags, va_list args) {
  const char *s = va_arg(args, char *);
  if (s == S21_NULL) {
    s = "(null)";
  }

  char buffer[1024];
  char *p = buffer;

  int max_chars = flags->is_precision_set ? flags->precision : 1023;
  while (*s && max_chars > 0) {
    *p++ = *s++;
    max_chars--;
  }
  *p = '\0';

  if (flags->width > 0) {
    str = apply_padding(str, buffer, flags);
  } else {
    p = buffer;
    while (*p) {
      *str++ = *p++;
    }
  }

  return str;
}

static char *process_char(char *str, const FormatFlags *flags, va_list args) {
  char c = (char)va_arg(args, int);
  const char buffer[2] = {c, '\0'};

  if (flags->width > 1) {
    str = apply_padding(str, buffer, flags);
  } else {
    *str++ = c;
  }

  return str;
}

static void format_integer_number(int num, const FormatFlags *flags,
                                  char *output_buffer) {
  char buffer[32];
  int negative = 0;

  if (num < 0) {
    negative = 1;
    num = -num;
  }

  s21_itoa(num, buffer, 10);

  char padded_buffer[32] = {0};
  int len = s21_strlen(buffer);
  int precision = flags->is_precision_set ? flags->precision : 0;

  if (precision > len) {
    int zeros_to_add = precision - len;
    for (int i = 0; i < zeros_to_add; i++) {
      padded_buffer[i] = '0';
    }
    s21_strcpy(padded_buffer + zeros_to_add, buffer);
  } else {
    s21_strcpy(padded_buffer, buffer);
  }

  char *p = output_buffer;

  if (negative) {
    *p++ = '-';
  } else if (flags->plus) {
    *p++ = '+';
  } else if (flags->space) {
    *p++ = ' ';
  }

  const char *num_ptr = (precision > len) ? padded_buffer : buffer;
  while (*num_ptr) {
    *p++ = *num_ptr++;
  }
  *p = '\0';
}

static char *apply_integer_formatting(char *str, const char *formatted_num,
                                      const FormatFlags *flags) {
  char *result = str;

  if (flags->width > 0) {
    result = apply_padding(str, formatted_num, flags);
  } else {
    const char *p = formatted_num;
    while (*p) {
      *result++ = *p++;
    }
  }

  return result;
}

static char *process_int(char *str, const FormatFlags *flags, va_list args) {
  char *result = str;

  if (str != S21_NULL && flags != S21_NULL) {
    int num = va_arg(args, int);
    char signed_buffer[34];

    format_integer_number(num, flags, signed_buffer);
    result = apply_integer_formatting(str, signed_buffer, flags);
  }

  return result;
}

static char *process_unsigned(char *str, const FormatFlags *flags,
                              va_list args) {
  unsigned int num;

  if (flags->length == 'l') {
    num = (unsigned long)va_arg(args, unsigned long);
  } else {
    num = va_arg(args, unsigned int);
  }

  char buffer[32];
  s21_utoa(num, buffer, 10);

  if (flags->width > 0) {
    str = apply_padding(str, buffer, flags);
  } else {
    const char *p = buffer;
    while (*p) *str++ = *p++;
  }

  return str;
}

static char *process_float(char *str, FormatFlags *flags, va_list args) {
  double num;

  if (flags->length == 'L') {
    num = (double)va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }

  char buffer[64];
  int precision = flags->is_precision_set ? flags->precision : 6;
  s21_ftoa(num, buffer, precision);

  if (flags->width > 0) {
    str = apply_padding(str, buffer, flags);
  } else {
    const char *p = buffer;
    while (*p) *str++ = *p++;
  }

  return str;
}

void s21_ftoa_scientific(double value, char *buffer, int precision,
                         int uppercase) {
  if (buffer == S21_NULL) return;

  if (precision < 0) precision = 6;

  int negative = 0;
  if (value < 0) {
    negative = 1;
    value = -value;
  }

  int exponent = 0;
  if (value != 0.0) {
    while (value >= 10.0) {
      value /= 10.0;
      exponent++;
    }
    while (value < 1.0 && value > 0.0) {
      value *= 10.0;
      exponent--;
    }
  }

  double multiplier = 1.0;
  for (int i = 0; i < precision; i++) {
    multiplier *= 10.0;
  }

  value = round(value * multiplier) / multiplier;

  if (value >= 10.0 - 1e-12) {
    value /= 10.0;
    exponent++;
  }

  char *p = buffer;

  if (negative) *p++ = '-';

  int int_part = (int)value;
  *p++ = int_part + '0';
  *p++ = '.';

  double frac = value - int_part;

  for (int i = 0; i < precision; i++) {
    frac *= 10.0;
    int digit = (int)frac;

    if (i == precision - 1) {
      double remainder = frac - digit;
      if (remainder >= 0.5) {
        digit++;
        if (digit == 10) {
          digit = 0;
        }
      }
    }

    *p++ = digit + '0';
    frac -= (int)frac;
  }

  *p++ = uppercase ? 'E' : 'e';
  *p++ = exponent >= 0 ? '+' : '-';

  int exp_abs = exponent >= 0 ? exponent : -exponent;
  if (exp_abs < 10) {
    *p++ = '0';
    *p++ = exp_abs + '0';
  } else {
    *p++ = (exp_abs / 10) + '0';
    *p++ = (exp_abs % 10) + '0';
  }

  *p = '\0';
}

static char *process_scientific(char *str, FormatFlags *flags, va_list args) {
  double num;

  if (flags->length == 'L') {
    num = (double)va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }

  char buffer[64];
  int precision = flags->is_precision_set ? flags->precision : 6;
  int uppercase = (flags->specifier == 'E');

  s21_ftoa_scientific(num, buffer, precision, uppercase);

  if (flags->width > 0) {
    str = apply_padding(str, buffer, flags);
  } else {
    const char *p = buffer;
    while (*p) *str++ = *p++;
  }

  return str;
}

static char *process_percent(char *str, const FormatFlags *flags) {
  const char buffer[2] = {'%', '\0'};

  if (flags->width > 1) {
    str = apply_padding(str, buffer, flags);
  } else {
    *str++ = '%';
  }

  return str;
}

static char *process_hex(char *str, const FormatFlags *flags, va_list args) {
  unsigned int num = va_arg(args, unsigned int);
  char buffer[32];
  char final_buffer[36] = {0};

  s21_utoa(num, buffer, 16);

  if (flags->specifier == 'X') {
    for (char *p = buffer; *p; p++) {
      if (*p >= 'a' && *p <= 'f') *p = *p - 'a' + 'A';
    }
  }

  char *output = buffer;
  if (flags->hash && num != 0) {
    final_buffer[0] = '0';
    final_buffer[1] = (flags->specifier == 'X') ? 'X' : 'x';
    s21_strcpy(final_buffer + 2, buffer);
    output = final_buffer;
  }

  if (flags->width > 0) {
    str = apply_padding(str, output, flags);
  } else {
    const char *p = output;
    while (*p) *str++ = *p++;
  }

  return str;
}

static char *process_octal(char *str, const FormatFlags *flags, va_list args) {
  unsigned int num = va_arg(args, unsigned int);
  char buffer[32];
  char final_buffer[36] = {0};

  s21_utoa(num, buffer, 8);

  char *output = buffer;
  if (flags->hash && num != 0) {
    final_buffer[0] = '0';
    s21_strcpy(final_buffer + 1, buffer);
    output = final_buffer;
  }

  if (flags->width > 0) {
    str = apply_padding(str, output, flags);
  } else {
    const char *p = output;
    while (*p) *str++ = *p++;
  }

  return str;
}

static char *process_pointer(char *str, FormatFlags *flags, va_list args) {
  (void)flags;
  void *ptr = va_arg(args, void *);

  if (ptr == S21_NULL) {
    const char *null_str = "0x0";
    while (*null_str) *str++ = *null_str++;
  } else {
    uintptr_t addr = (uintptr_t)ptr;
    char buffer[20];

    char *p = buffer;
    uintptr_t temp = addr;

    int digits = 0;
    do {
      digits++;
      temp /= 16;
    } while (temp > 0);

    p += digits;
    *p = '\0';

    temp = addr;
    do {
      *--p = "0123456789abcdef"[temp % 16];
      temp /= 16;
    } while (temp > 0);

    *str++ = '0';
    *str++ = 'x';

    const char *src = p;
    while (*src) *str++ = *src++;
  }
  return str;
}

void s21_ftoa_remove_zeros(double value, char *buffer, int precision) {
  if (buffer == S21_NULL) return;

  char temp_buffer[64];
  s21_ftoa(value, temp_buffer, precision);

  char *p = temp_buffer;
  while (*p) p++;

  if (s21_strchr(temp_buffer, '.')) {
    p--;
    while (p > temp_buffer && *p == '0') {
      *p = '\0';
      p--;
    }
    if (p > temp_buffer && *p == '.') {
      *p = '\0';
    }
  }

  s21_strcpy(buffer, temp_buffer);
}

static char *process_g_format(char *str, FormatFlags *flags, va_list args) {
  double num;

  if (flags->length == 'L') {
    num = (double)va_arg(args, long double);
  } else {
    num = va_arg(args, double);
  }

  char buffer[64] = {0};
  int precision = flags->is_precision_set ? flags->precision : 6;
  int uppercase = (flags->specifier == 'G');

  double abs_num = (num < 0) ? -num : num;

  if (abs_num == 0.0) {
    s21_strcpy(buffer, "0");
  } else if (abs_num >= 1e-4 && abs_num < 1e6) {
    s21_ftoa_remove_zeros(num, buffer, precision);
  } else {
    s21_ftoa_scientific(num, buffer, precision, uppercase);
  }

  if (flags->width > 0) {
    str = apply_padding(str, buffer, flags);
  } else {
    const char *p = buffer;
    while (*p) *str++ = *p++;
  }

  return str;
}

static char *process_known_specifier(char *str, FormatFlags *flags,
                                     va_list args) {
  char *result = S21_NULL;

  if (flags != S21_NULL) {
    switch (flags->specifier) {
      case 'c':
        result = process_char(str, flags, args);
        break;
      case 's':
        result = process_string(str, flags, args);
        break;
      case 'd':
      case 'i':
        result = process_int(str, flags, args);
        break;
      case 'u':
        result = process_unsigned(str, flags, args);
        break;
      case 'f':
        result = process_float(str, flags, args);
        break;
      case 'e':
      case 'E':
        result = process_scientific(str, flags, args);
        break;
      case 'g':
      case 'G':
        result = process_g_format(str, flags, args);
        break;
      case 'x':
      case 'X':
        result = process_hex(str, flags, args);
        break;
      case 'o':
        result = process_octal(str, flags, args);
        break;
      case 'p':
        result = process_pointer(str, flags, args);
        break;
      case '%':
        result = process_percent(str, flags);
        break;
      default:
        break;
    }
  }

  return result;
}

static char *process_specifier(char *str, FormatFlags *flags, va_list args) {
  char *result = str;

  if (str != S21_NULL && flags != S21_NULL) {
    if (flags->width_star) {
      flags->width = va_arg(args, int);
      if (flags->width < 0) {
        flags->minus = 1;
        flags->width = -flags->width;
      }
    }
    if (flags->precision_star) {
      flags->precision = va_arg(args, int);
    }

    char *temp_result = process_known_specifier(str, flags, args);
    if (temp_result != S21_NULL) {
      result = temp_result;
    }
  }

  return result;
}

int s21_sprintf(char *str, const char *format, ...) {
  int result = -1;

  if (str != S21_NULL && format != S21_NULL) {
    va_list args;
    va_start(args, format);

    const char *start = str;

    while (*format) {
      if (*format != '%') {
        *str++ = *format++;
      } else {
        FormatFlags flags = {0};

        format = s21_parse_format(format + 1, &flags);

        str = process_specifier(str, &flags, args);
      }
    }

    *str = '\0';
    va_end(args);
    result = str - start;
  }

  return result;
}