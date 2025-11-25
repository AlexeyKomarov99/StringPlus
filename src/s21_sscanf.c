#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "s21_string.h"

typedef enum {
  LEN_NONE,
  LEN_HH,
  LEN_H,
  LEN_L,
  LEN_LL,
  LEN_J,
  LEN_Z,
  LEN_T,
  LEN_BIGL
} length_t;

typedef struct {
  int suppress;
  int width;
  length_t len;
  char conv;
  unsigned char set[256];
  int set_negate;
  int needs_skip_ws;
} spec_t;

int handle_specifier(const char **f, const char **p, va_list *ap, int *assigned,
                     const char *src);
int handle_n_specifier(const spec_t *sp, va_list *ap, const char *src,
                       const char *p);

static void s21_memzero(void *p, size_t n) { s21_memset(p, 0, n); }

static int s21_isspace(unsigned char c) {
  return (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' ||
          c == '\f');
}

static void skip_ws(const char **p) {
  while (**p && s21_isspace((unsigned char)**p)) (*p)++;
}

static int match_literal(const char **p, char want) {
  int result = 0;

  if (**p == want) {
    (*p)++;
    result = 1;
  }

  return result;
}

static int is_dec_digit(int c) { return c >= '0' && c <= '9'; }
static int is_oct_digit(int c) { return c >= '0' && c <= '7'; }
static int is_hex_digit(int c) {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
         (c >= 'A' && c <= 'F');
}
static int hex_val(int c) {
  int result = 0;

  if (c >= '0' && c <= '9') {
    result = c - '0';
  } else if (c >= 'a' && c <= 'f') {
    result = 10 + (c - 'a');
  } else if (c >= 'A' && c <= 'F') {
    result = 10 + (c - 'A');
  }

  return result;
}

static void init_scanset(spec_t *sp, const char **f) {
  s21_memzero(sp->set, 256);
  sp->set_negate = 0;

  if (**f == '^') {
    sp->set_negate = 1;
    (*f)++;
  }
}

static void handle_first_bracket(const char **f, spec_t *sp) {
  if (**f == ']') {
    sp->set[(unsigned char)']'] = 1;
    (*f)++;
  }
}

static void process_char_range(const char **f, spec_t *sp) {
  unsigned char a = (unsigned char)*(*f);
  unsigned char b = (unsigned char)*(*f + 2);

  if (a > b) {
    unsigned char temp = a;
    a = b;
    b = temp;
  }

  for (unsigned char c = a; c <= b; ++c) {
    sp->set[c] = 1;
  }

  *f += 3;
}

static void process_single_char(const char **f, spec_t *sp) {
  sp->set[(unsigned char)*(*f)] = 1;
  (*f)++;
}

static void process_scanset_content(const char **f, spec_t *sp) {
  while (**f && **f != ']') {
    if (*(*f + 1) == '-' && *(*f + 2) && *(*f + 2) != ']') {
      process_char_range(f, sp);
    } else {
      process_single_char(f, sp);
    }
  }
}

static void scanset_build(spec_t *sp, const char **pfmt) {
  const char *f = *pfmt;

  init_scanset(sp, &f);
  handle_first_bracket(&f, sp);
  process_scanset_content(&f, sp);

  if (*f == ']') {
    f++;
  }

  *pfmt = f;
}

static int parse_length(const char **pf, length_t *out) {
  const char *f = *pf;
  int result = 0;

  if (*f == 'h' && *(f + 1) == 'h') {
    *out = LEN_HH;
    *pf = f + 2;
    result = 1;
  } else if (*f == 'l' && *(f + 1) == 'l') {
    *out = LEN_LL;
    *pf = f + 2;
    result = 1;
  } else if (*f == 'h') {
    *out = LEN_H;
    *pf = f + 1;
    result = 1;
  } else if (*f == 'l') {
    *out = LEN_L;
    *pf = f + 1;
    result = 1;
  } else if (*f == 'j') {
    *out = LEN_J;
    *pf = f + 1;
    result = 1;
  } else if (*f == 'z') {
    *out = LEN_Z;
    *pf = f + 1;
    result = 1;
  } else if (*f == 't') {
    *out = LEN_T;
    *pf = f + 1;
    result = 1;
  } else if (*f == 'L') {
    *out = LEN_BIGL;
    *pf = f + 1;
    result = 1;
  } else {
    *out = LEN_NONE;
    result = 0;
  }

  return result;
}

static void init_specifier(spec_t *sp) {
  s21_memzero(sp, sizeof(sp));
  sp->width = -1;
  sp->len = LEN_NONE;
  sp->needs_skip_ws = 1;
}

static const char *parse_suppress_flag(const char *f, spec_t *sp) {
  if (*f == '*') {
    sp->suppress = 1;
    f++;
  }
  return f;
}

static const char *parse_width_value(const char *f, spec_t *sp) {
  if (is_dec_digit((unsigned char)*f)) {
    int width = 0;
    while (is_dec_digit((unsigned char)*f)) {
      width = width * 10 + (*f - '0');
      f++;
    }
    sp->width = width;
  }
  return f;
}

static const char *parse_specifier_and_flags(const char *f, spec_t *sp) {
  sp->conv = *f ? *f++ : '\0';

  if (sp->conv == 'c' || sp->conv == '[' || sp->conv == 'n' ||
      sp->conv == '%') {
    sp->needs_skip_ws = 0;
  }

  return f;
}

static const char *handle_special_specifiers(const char *f, spec_t *sp) {
  if (sp->conv == '[') {
    scanset_build(sp, &f);
  }
  return f;
}

static spec_t parse_spec(const char **pfmt) {
  spec_t sp;
  const char *f = *pfmt;

  init_specifier(&sp);
  f++;

  f = parse_suppress_flag(f, &sp);
  f = parse_width_value(f, &sp);
  parse_length(&f, &sp.len);
  f = parse_specifier_and_flags(f, &sp);
  f = handle_special_specifiers(f, &sp);

  *pfmt = f;
  return sp;
}

static int read_sign(const char **p) {
  int sign = 1;
  if (**p == '+') {
    (*p)++;
  } else if (**p == '-') {
    (*p)++;
    sign = -1;
  }
  return sign;
}

static int read_base_prefix(const char **p, int *base) {
  const char *s = *p;

  if (*base == 0) {
    if (*s == '0') {
      if ((*(s + 1) == 'x' || *(s + 1) == 'X')) {
        if (is_hex_digit((unsigned char)*(s + 2))) {
          *base = 16;
          s += 2;
        } else {
          *base = 10;
        }
      } else if (is_oct_digit((unsigned char)*(s + 1))) {
        *base = 8;
        s += 1;
      } else {
        *base = 10;
      }
    } else {
      *base = 10;
    }
  } else if (*base == 16) {
    if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X') &&
        is_hex_digit((unsigned char)*(s + 2))) {
      s += 2;
    }
  }
  *p = s;
  return 1;
}

static int read_unsigned_integer(const char **p, int base, int width,
                                 unsigned long long *out, int *digits_read) {
  const char *s = *p;
  unsigned long long acc = 0;
  int count = 0;
  int result = 0;

  while (*s && (width < 0 || count < width)) {
    unsigned char ch = (unsigned char)*s;
    int dv = -1;

    if (base == 8) {
      if (is_oct_digit(ch)) dv = ch - '0';
    } else if (base == 10) {
      if (is_dec_digit(ch)) dv = ch - '0';
    } else {
      if (is_hex_digit(ch)) dv = hex_val(ch);
    }

    if (dv < 0 || dv >= base) break;

    acc = acc * (unsigned long long)base + (unsigned long long)dv;
    s++;
    count++;
  }

  if (count > 0) {
    *out = acc;
    *digits_read = count;
    *p = s;
    result = 1;
  }

  return result;
}

static int read_integer_any(const char **p, int base, int width,
                            long long *out) {
  int result = 0;
  const char *start = *p;
  int sign = read_sign(p);

  const char *before_base = *p;

  if (base == 0) {
    read_base_prefix(p, &base);
  }

  int had_prefix = (*p > before_base);

  unsigned long long uval = 0;
  int digits = 0;

  if (read_unsigned_integer(p, base, width, &uval, &digits)) {
    if (had_prefix && digits == 0) {
      *p = start;
      result = 0;
    } else {
      if (sign < 0) {
        if (uval > (unsigned long long)LLONG_MAX + 1ULL) {
          *out = LLONG_MIN;
        } else {
          long long tmp = (long long)uval;
          if (tmp == (long long)LLONG_MIN)
            *out = tmp;
          else
            *out = -(long long)uval;
        }
      } else {
        if (uval > (unsigned long long)LLONG_MAX)
          *out = LLONG_MAX;
        else
          *out = (long long)uval;
      }
      result = 1;
    }
  } else {
    *p = start;
  }

  return result;
}

static int parse_float_special_values(const char **s, int *remaining, int sign,
                                      long double *out) {
  const char *t = *s;
  int result = 0;

  if (*remaining >= 3 && ((*t | 32) == 'i') && ((*(t + 1) | 32) == 'n') &&
      ((*(t + 2) | 32) == 'f')) {
    *s += 3;
    *remaining -= 3;

    if (*remaining >= 5 && ((*(*s) | 32) == 'i') && ((*(*s + 1) | 32) == 'n') &&
        ((*(*s + 2) | 32) == 'i') && ((*(*s + 3) | 32) == 't') &&
        ((*(*s + 4) | 32) == 'y')) {
      *s += 5;
      *remaining -= 5;
    }

    *out = (sign < 0) ? (-1.0 / 0.0) : (1.0 / 0.0);
    result = 1;
  } else if (*remaining >= 3 && ((*t | 32) == 'n') &&
             ((*(t + 1) | 32) == 'a') && ((*(t + 2) | 32) == 'n')) {
    *s += 3;
    *remaining -= 3;
    *out = NAN;
    result = 1;
  }

  return result;
}

static int parse_float_parts(const char **s, int *remaining, int *digits_before,
                             int *digits_after) {
  *digits_before = 0;
  *digits_after = 0;

  while (*remaining > 0 && is_dec_digit((unsigned char)**s)) {
    (*digits_before)++;
    (*s)++;
    (*remaining)--;
  }

  if (*remaining > 0 && **s == '.') {
    (*s)++;
    (*remaining)--;

    while (*remaining > 0 && is_dec_digit((unsigned char)**s)) {
      (*digits_after)++;
      (*s)++;
      (*remaining)--;
    }
  }

  return (*digits_before + *digits_after > 0);
}

static int parse_float_exponent(const char **s, int *remaining, int *exp_sign,
                                int *exp_val) {
  int has_exp = 0;
  const char *exp_ptr = *s;
  int rem2 = *remaining;

  if (rem2 > 0 && (*exp_ptr == 'e' || *exp_ptr == 'E')) {
    has_exp = 1;
    exp_ptr++;
    rem2--;

    if (rem2 > 0 && (*exp_ptr == '+' || *exp_ptr == '-')) {
      if (*exp_ptr == '-') *exp_sign = -1;
      exp_ptr++;
      rem2--;
    }

    int exp_digits = 0;
    while (rem2 > 0 && is_dec_digit((unsigned char)*exp_ptr)) {
      *exp_val = *exp_val * 10 + (*exp_ptr - '0');
      exp_ptr++;
      rem2--;
      exp_digits++;
    }

    if (exp_digits > 0) {
      *s = exp_ptr;
      *remaining = rem2;
    } else {
      has_exp = 0;
    }
  }

  return has_exp;
}

static long double calculate_float_value(const char *start, const char *end,
                                         int has_exp, int exp_sign,
                                         int exp_val) {
  const char *q = start;
  long double val = 0.0L;

  if (*q == '+' || *q == '-') q++;

  while (q < end && is_dec_digit((unsigned char)*q)) {
    val = val * 10.0L + (long double)(*q - '0');
    q++;
  }

  if (*q == '.') {
    q++;
    long double place = 0.1L;
    while (q < end && is_dec_digit((unsigned char)*q)) {
      val += place * (long double)(*q - '0');
      place *= 0.1L;
      q++;
    }
  }

  if (has_exp && exp_val != 0) {
    long double pow10 = 1.0L, base = 10.0L;
    int e = exp_val;
    while (e) {
      if (e & 1) pow10 *= base;
      base *= base;
      e >>= 1;
    }
    if (exp_sign < 0)
      val /= pow10;
    else
      val *= pow10;
  }

  return val;
}

static int read_float_dec(const char **p, int width, long double *out) {
  const char *s = *p;
  int remaining = (width < 0 ? INT_MAX : width);
  int result = 0;

  int sign = 1;
  if (remaining > 0 && (*s == '+' || *s == '-')) {
    if (*s == '-') sign = -1;
    s++;
    remaining--;
  }

  if (parse_float_special_values(&s, &remaining, sign, out)) {
    *p = s;
    result = 1;
  } else {
    int digits_before, digits_after;
    if (parse_float_parts(&s, &remaining, &digits_before, &digits_after)) {
      int exp_sign = 1, exp_val = 0;
      int has_exp = parse_float_exponent(&s, &remaining, &exp_sign, &exp_val);

      long double val =
          calculate_float_value(*p, s, has_exp, exp_sign, exp_val);
      *out = sign < 0 ? -val : val;
      *p = s;
      result = 1;
    }
  }

  return result;
}

static void store_signed(void *dst, length_t len, long long v) {
  switch (len) {
    case LEN_HH:
      *(signed char *)dst = (signed char)v;
      break;
    case LEN_H:
      *(short *)dst = (short)v;
      break;
    case LEN_L:
      *(long *)dst = (long)v;
      break;
    case LEN_LL:
      *(long long *)dst = (long long)v;
      break;
    case LEN_J:
      *(intmax_t *)dst = (intmax_t)v;
      break;
    case LEN_Z:
      *(size_t *)dst = (size_t)v;
      break;
    case LEN_T:
      *(ptrdiff_t *)dst = (ptrdiff_t)v;
      break;
    default:
      *(int *)dst = (int)v;
      break;
  }
}

static void store_unsigned(void *dst, length_t len, unsigned long long v) {
  switch (len) {
    case LEN_HH:
      *(unsigned char *)dst = (unsigned char)v;
      break;
    case LEN_H:
      *(unsigned short *)dst = (unsigned short)v;
      break;
    case LEN_L:
      *(unsigned long *)dst = (unsigned long)v;
      break;
    case LEN_LL:
      *(unsigned long long *)dst = (unsigned long long)v;
      break;
    case LEN_J:
      *(uintmax_t *)dst = (uintmax_t)v;
      break;
    case LEN_Z:
      *(size_t *)dst = (size_t)v;
      break;
    case LEN_T:
      *(ptrdiff_t *)dst = (ptrdiff_t)v;
      break;
    default:
      *(unsigned int *)dst = (unsigned int)v;
      break;
  }
}

static void store_float(void *dst, length_t len, long double v) {
  if (len == LEN_BIGL)
    *(long double *)dst = v;
  else if (len == LEN_L)
    *(double *)dst = (double)v;
  else
    *(float *)dst = (float)v;
}

static int conv_int_signed(const char **p, const spec_t *sp, void *dst) {
  int base;

  if (sp->conv == 'o') {
    base = 8;
  } else if (sp->conv == 'x' || sp->conv == 'X' || sp->conv == 'p') {
    base = 16;
  } else if (sp->conv == 'i') {
    base = 0;
  } else {
    base = 10;
  }

  int width = sp->width;
  const char *start = *p;
  int result = 0;

  long long val;
  if (read_integer_any(p, base, width, &val)) {
    if (!sp->suppress) {
      store_signed(dst, sp->len, val);
    }
    result = 1;
  } else {
    *p = start;
  }

  return result;
}

static int conv_int_unsigned(const char **p, const spec_t *sp, void *dst) {
  int base;

  if (sp->conv == 'o') {
    base = 8;
  } else if (sp->conv == 'x' || sp->conv == 'X') {
    base = 16;
  } else {
    base = 10;
  }

  int width = sp->width;
  const char *start = *p;

  int sign = 1;
  if (**p == '+' || **p == '-') {
    if (**p == '-') sign = -1;
    (*p)++;
  }

  if (base == 16 && **p == '0' && (*(*p + 1) == 'x' || *(*p + 1) == 'X')) {
    const char *temp = *p + 2;
    if (is_hex_digit((unsigned char)*temp)) {
      *p = temp;
    }
  }

  int consumed = (int)(*p - start);
  int remaining = (width < 0 ? INT_MAX : (width - consumed));
  if (remaining < 0) remaining = 0;

  unsigned long long u = 0;
  int digs = 0;
  int result = 0;

  if (read_unsigned_integer(p, base, remaining, &u, &digs) && digs > 0) {
    if (sign < 0) {
      unsigned long long uu = (unsigned long long)(-(long long)u);
      u = uu;
    }
    if (!sp->suppress) {
      store_unsigned(dst, sp->len, u);
    }
    result = 1;
  } else {
    *p = start;
  }

  return result;
}

static int conv_float_any(const char **p, const spec_t *sp, void *dst) {
  int width = sp->width;
  const char *start = *p;
  int result = 0;

  long double v;
  if (read_float_dec(p, width, &v)) {
    if (!sp->suppress) {
      store_float(dst, sp->len, v);
    }
    result = 1;
  } else {
    *p = start;
  }

  return result;
}

static int conv_char(const char **p, const spec_t *sp, void *dst) {
  int w = sp->width < 0 ? 1 : sp->width;
  const char *s = *p;
  int result = 0;

  if (*s) {
    if (sp->suppress) {
      int i = 0;
      while (*s && i < w) {
        s++;
        i++;
      }
      *p = s;
      result = (i > 0);
    } else {
      char *out = (char *)dst;
      int i = 0;
      while (*s && i < w) {
        out[i++] = *s++;
      }
      *p = s;
      result = 1;
    }
  }

  return result;
}

static int conv_string(const char **p, const spec_t *sp, void *dst) {
  const char *s = *p;
  int result = 0;

  if (*s) {
    int w = sp->width < 0 ? INT_MAX : sp->width;
    int n = 0;

    if (sp->suppress) {
      while (*s && !s21_isspace((unsigned char)*s) && n < w) {
        s++;
        n++;
      }
      *p = s;
      result = (n > 0);
    } else {
      char *out = (char *)dst;
      while (*s && !s21_isspace((unsigned char)*s) && n < w) {
        out[n++] = *s++;
      }
      if (n > 0) {
        out[n] = '\0';
        *p = s;
        result = 1;
      }
    }
  }

  return result;
}

static int conv_scanset(const char **p, const spec_t *sp, void *dst) {
  const char *s = *p;
  int result = 0;

  if (*s) {
    int w = sp->width < 0 ? INT_MAX : sp->width;
    int n = 0;

    while (*s && n < w) {
      unsigned char c = (unsigned char)*s;
      int in = sp->set[c] ? 1 : 0;
      if (sp->set_negate) in = !in;
      if (!in) break;
      s++;
      n++;
    }

    if (n > 0) {
      if (!sp->suppress) {
        char *out = (char *)dst;
        for (int i = 0; i < n; i++) {
          out[i] = (*p)[i];
        }
        out[n] = '\0';
      }
      *p = s;
      result = 1;
    }
  }

  return result;
}

static int conv_pointer(const char **p, const spec_t *sp, void *dst) {
  int ok = 0;
  const char *s = *p;
  unsigned long long val = 0;
  int digits = 0;
  int width = (sp->width < 0) ? INT_MAX : sp->width;

  skip_ws(&s);

  const char *before_prefix = s;

  if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X')) {
    s += 2;
    width -= 2;
  }

  if (read_unsigned_integer(&s, 16, width, &val, &digits) && digits > 0) {
    if (!sp->suppress && dst) {
      *(void **)dst = (void *)(uintptr_t)val;
    }
    *p = s;
    ok = 1;
  } else {
    s = before_prefix;
    if (read_unsigned_integer(&s, 16, width, &val, &digits) && digits > 0) {
      if (!sp->suppress && dst) {
        *(void **)dst = (void *)(uintptr_t)val;
      }
      *p = s;
      ok = 1;
    }
  }

  return ok;
}

int handle_n_specifier(const spec_t *sp, va_list *ap, const char *src,
                       const char *p) {
  if (!sp->suppress) {
    void *np = va_arg(*ap, void *);
    ptrdiff_t n = p - src;

    switch (sp->len) {
      case LEN_HH:
        *(signed char *)np = (signed char)n;
        break;
      case LEN_H:
        *(short *)np = (short)n;
        break;
      case LEN_L:
        *(long *)np = (long)n;
        break;
      case LEN_LL:
        *(long long *)np = (long long)n;
        break;
      default:
        *(int *)np = (int)n;
        break;
    }
  }
  return 1;
}

static void *prepare_specifier_argument(const spec_t *sp, va_list *ap) {
  void *arg_ptr = NULL;

  if (!sp->suppress && sp->conv != 'n') {
    arg_ptr = va_arg(*ap, void *);
  }

  return arg_ptr;
}

static int handle_numeric_specifiers(const char **p, const spec_t *sp,
                                     void *arg_ptr) {
  int result = 0;

  switch (sp->conv) {
    case 'd':
    case 'i':
      result = conv_int_signed(p, sp, arg_ptr);
      break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
      result = conv_int_unsigned(p, sp, arg_ptr);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      result = conv_float_any(p, sp, arg_ptr);
      break;
    default:
      break;
  }

  return result;
}

static int handle_string_specifiers(const char **p, const spec_t *sp,
                                    void *arg_ptr) {
  int result = 0;

  switch (sp->conv) {
    case 'c':
      result = conv_char(p, sp, arg_ptr);
      break;
    case 's':
      result = conv_string(p, sp, arg_ptr);
      break;
    case '[':
      result = conv_scanset(p, sp, arg_ptr);
      break;
    case 'p':
      result = conv_pointer(p, sp, arg_ptr);
      break;
    default:
      break;
  }

  return result;
}

static int finalize_specifier_processing(int processed, const spec_t *sp,
                                         int *assigned) {
  int result = 0;

  if (processed) {
    if (!sp->suppress && sp->conv != 'n') {
      (*assigned)++;
    }
    result = 1;
  }

  return result;
}

int handle_specifier(const char **f, const char **p, va_list *ap, int *assigned,
                     const char *src) {
  int result = 0;

  spec_t sp = parse_spec(f);
  if (sp.conv == '\0') {
    result = 0;
  } else if (sp.conv == '%') {
    result = match_literal(p, '%');
  } else {
    if (sp.needs_skip_ws && sp.conv != 'n') skip_ws(p);

    if (sp.conv != 'n' && **p == '\0') {
      result = (*assigned == 0) ? -1 : 0;
    } else {
      void *arg_ptr = prepare_specifier_argument(&sp, ap);

      if (arg_ptr != NULL || sp.suppress || sp.conv == 'n') {
        int processed = 0;

        if (sp.conv == 'n') {
          processed = handle_n_specifier(&sp, ap, src, *p);
          result = processed;
        } else {
          processed = handle_numeric_specifiers(p, &sp, arg_ptr);

          if (!processed) {
            processed = handle_string_specifiers(p, &sp, arg_ptr);
          }

          result = finalize_specifier_processing(processed, &sp, assigned);
        }
      }
    }
  }

  return result;
}

static const char *skip_format_whitespace(const char *f, const char **p) {
  while (s21_isspace((unsigned char)*f)) {
    f++;
  }
  skip_ws(p);
  return f;
}

static int process_literal_char(const char **f, const char **p) {
  int result = 1;

  if (!**p || **p != **f) {
    result = 0;
  } else {
    (*p)++;
    (*f)++;
  }

  return result;
}

static int process_format_char(const char **f, const char **p, va_list *ap,
                               int *assigned, const char *src) {
  int result = 1;

  if (**f != '%') {
    result = process_literal_char(f, p);
  } else {
    result = handle_specifier(f, p, ap, assigned, src);
  }

  return result;
}

static int parse_loop(const char **f, const char **p, va_list *ap,
                      int *assigned, const char *src) {
  int result = 1;

  while (**f && result) {
    if (s21_isspace((unsigned char)**f)) {
      *f = skip_format_whitespace(*f, p);
    } else {
      result = process_format_char(f, p, ap, assigned, src);
    }
  }

  return result;
}

int s21_sscanf(const char *src, const char *fmt, ...) {
  int result = -1;

  if (src != S21_NULL && fmt != S21_NULL) {
    va_list ap;
    va_start(ap, fmt);

    const char *p = src;
    const char *f = fmt;
    int assigned = 0;

    int has_n_specifier = 0;
    const char *temp_fmt = fmt;
    while (*temp_fmt) {
      if (*temp_fmt == '%' && *(temp_fmt + 1) == 'n') {
        has_n_specifier = 1;
        break;
      }
      temp_fmt++;
    }

    if (*src == '\0' && *fmt != '\0' && !has_n_specifier) {
      result = -1;
    } else if (*fmt != '\0') {
      const char *temp = src;
      skip_ws(&temp);
      if (*temp == '\0' && *fmt != '\0' && !has_n_specifier) {
        result = -1;
      } else {
        parse_loop(&f, &p, &ap, &assigned, src);
        result = assigned;
      }
    } else {
      result = 0;
    }

    va_end(ap);
  }

  return result;
}