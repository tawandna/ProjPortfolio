#include "s21_sprintf.h"

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {  //основная функция
  flags f = {0};
  va_list va;
  va_start(va, format);
  char *str_beginning = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
      continue;
    } else {
      format++;
      s21_memset(&f, 0, sizeof(flags));
    }

    format = check_flags(format, &f);
    format = check_width(format, &f, va);
    format = check_precision(format, &f, va);
    format = check_length(format, &f);

    f.specifier = *format;
    format++;

    char buff[BUFF_SIZE] = {'\0'};
    specs_switch(f, buff, va);
    for (int i = 0; buff[i]; i++, str++) *str = buff[i];

    if (f.specifier == 'n') {
      int *ret = va_arg(va, int *);
      *ret = str - str_beginning;
    }
  }
  *str = '\0';
  va_end(va);
  return str - str_beginning;
}
int str_to_num(const char *str) {
  int res = 0;
  int sign = 1;
  int overflow = 0;

  while (*str == ' ') str++;

  if (*str == '-') {
    str++;
    sign = -1;
  }

  if (*str == '+') {
    str++;
  }

  while (*str && *str >= '0' && *str <= '9') {
    res = res * 10 + (*str - '0');
    if (res < 0) {
      overflow = 1;
      break;
    }
    str++;
  }
  if (overflow)
    res = sign > 0 ? INT32_MAX : INT32_MIN;
  else
    res *= sign;

  return res;
}

const char *check_flags(const char *format, flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    switch (*format) {
      case '0':
        f->zero = true;
        break;
      case '-':
        f->minus = true;
        break;
      case '+':
        f->plus = true;
        break;
      case ' ':
        f->space = true;
        break;
    }
    format++;
  }
  return format;
}

const char *check_width(const char *format, flags *f, va_list va) {
  if (*format == '*') {
    format++;
    f->width = va_arg(va, int);
  }
  if (check_num(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; check_num(*format); i++, format++) tmp[i] = *format;
    f->width = str_to_num(tmp);
  }
  return format;
}

const char *check_precision(const char *format, flags *f, va_list va) {
  if (*format == '.') {
    f->is_precision_set = true;
    format++;
  }

  if (*format == '*') {
    format++;
    f->precision = va_arg(va, int);
  }
  if (check_num(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    for (int i = 0; check_num(*format); i++, format++) tmp[i] = *format;
    f->precision = str_to_num(tmp);
  }
  return format;
}

const char *check_length(const char *format, flags *f) {
  switch (*format) {
    case 'h':
      f->length = 'h';
      format++;
      break;
    case 'l':
      f->length = 'l';
      format++;
      break;
  }
  return format;
}

void specs_switch(flags f, char *buff, va_list va) {
  if (f.specifier == 'd' || f.specifier == 'i')
    parse_int(f, buff, va);
  else if (f.specifier == 'u')
    parse_unsigned(f, buff, va);
  else if (f.specifier == '%')
    buff[0] = '%';
  else if (f.specifier == 'c')
    parse_char(f, buff, va);
  else if (f.specifier == 's')
    parse_string(f, buff, va);
  else if (f.specifier == 'f')
    parse_float(f, buff, va);
}

void parse_int(flags f, char *buff, va_list va) {
  int64_t val = va_arg(va, int64_t);

  switch (f.length) {
    case 0:
      val = (int32_t)val;
      break;
    case 'h':
      val = (int16_t)val;
  }
  whole_num_to_string(val, buff, 10);
  format_precision(buff, f);
  format_flags(buff, f);
}

void whole_num_to_string(int64_t val, char *ret, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;

  bool neg = val < 0 ? 1 : 0;
  val = neg ? -val : val;

  if (val == 0) tmp[idx] = '0';

  while (val > 0) {
    idx--;
    tmp[idx] = "0123456789abcdef"[val % base];
    val /= base;
  }
  for (int j = 0; tmp[idx]; idx++, j++) {
    if (neg && j == 0) {
      ret[j++] = '-';
    }

    ret[j] = tmp[idx];
  }
}

void format_precision(char *buff, flags f) {
  char tmp[BUFF_SIZE] = {'\0'};

  int sign = 0;
  int len = s21_strlen(buff);

  if (buff[0] == '-') {
    tmp[0] = '-';
    len--;
    sign = 1;
  }

  if (f.precision > len) {
    int idx;
    for (idx = sign; idx < f.precision - len + sign; idx++) tmp[idx] = '0';

    for (int i = sign; buff[i]; i++, idx++) tmp[idx] = buff[i];

    s21_strcpy(buff, tmp);
  }

  if (f.is_precision_set && f.precision == 0 &&
      check_integer_specifier(f.specifier) && buff[0] == '0')
    buff[0] = '\0';
}

bool check_integer_specifier(char c) {
  char specs[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  bool res = false;
  for (s21_size_t i = 0; i < sizeof(specs); i++) {
    if (specs[i] == c) {
      res = true;
      break;
    }
  }
  return res;
}

void format_flags(char *buff, flags f) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (f.plus && f.specifier != 'u') {
    tmp[0] = buff[0] == '-' ? buff[0] : '+';
    s21_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff);
    s21_strcpy(buff, tmp);
  } else if (f.space && buff[0] != '-' && f.specifier != 'u') {
    tmp[0] = ' ';
    s21_strcpy(tmp + 1, buff);
    s21_strcpy(buff, tmp);
  }
  if (f.width > (int)s21_strlen(buff)) {
    int idx = f.width - s21_strlen(buff);
    if (!f.minus) {
      s21_memset(tmp, f.zero ? '0' : ' ', idx);
      s21_strcpy(tmp + idx, buff);
    } else {
      s21_strcpy(tmp, buff);
      s21_memset(tmp + s21_strlen(tmp), ' ', idx);
    }
    s21_strcpy(buff, tmp);
  }
}

void unsigned_num_to_string(uint64_t val, char *ret, int base) {
  char buf[BUFF_SIZE + 1] = {'\0'};
  int idx = BUFF_SIZE - 1;
  if (val == 0) {
    buf[idx] = '0';
    idx--;
  }

  for (; val && idx; --idx, val /= base)
    buf[idx] = "0123456789abcdef"[val % base];
  for (int j = 0; buf[idx + 1]; idx++, j++) ret[j] = buf[idx + 1];
}

void parse_unsigned(flags f, char *buff, va_list va) {
  uint64_t val = va_arg(va, uint64_t);
  switch (f.length) {
    case 'h':
      val = (uint16_t)val;
      break;
    case 'l':
      val = (uint64_t)val;
      break;
    case 0:
      val = (uint32_t)val;
  }
  unsigned_num_to_string(val, buff, 10);
  format_precision(buff, f);
  format_flags(buff, f);
}

void parse_char(flags f, char *buff, va_list va) {
  char c;
  c = va_arg(va, int);
  format_char(f, buff, c);
}

void format_char(flags f, char *buff, char c) {
  if (!f.minus && f.width) {
    for (int i = 0; i < f.width; i++) {
      buff[i] = ' ';
      if (i == f.width - 1) buff[i] = c;
    }
  } else if (f.width) {
    buff[0] = c;
    for (int i = 1; i < f.width; i++) buff[i] = ' ';
  } else {
    buff[0] = c;
  }
}

void parse_string(flags f, char *buff, va_list va) {
  char *str = va_arg(va, char *);
  format_string(f, buff, str);
}

void format_string(flags f, char *buff, char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  s21_strcpy(tmp, str);
  if (f.is_precision_set) tmp[f.precision] = '\0';

  int shift = f.width - s21_strlen(tmp);
  int len = s21_strlen(tmp);

  if (f.minus && shift > 0) {
    s21_strcpy(buff, tmp);
    s21_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    s21_memset(buff, ' ', shift);
    s21_strcpy(buff + shift, tmp);
  } else {
    s21_strcpy(buff, tmp);
  }
}

void parse_float(flags f, char *buff, va_list va) {
  long double val = 0;
  if (f.length == 'L') {
    val = va_arg(va, long double);
  } else {
    val = va_arg(va, double);
  }

  if (!f.is_precision_set) {
    f.precision = 6;
  }

  double_to_str(val, buff, f);
  format_flags(buff, f);
}
void double_to_str(long double val, char *ret, flags f) {
  char buff[BUFF_SIZE] = {'\0'};
  int idx = BUFF_SIZE - 2;
  bool neg = val < 0 ? 1 : 0;
  val = neg ? val * -1 : val;
  long double l = 0, r = modfl(val, &l);
  if (f.precision == 0) {
    l = roundl(val);
    r = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < f.precision; i++) {
    r = r * 10;
    fractions[i] = (int)r + '0';
  }
  long long right = roundl(r), left = l;
  if (!right) {
    for (int i = 0; i < f.precision; idx--, i++) buff[idx] = '0';
  } else {
    for (int i = s21_strlen(fractions); right || i > 0; right /= 10, idx--, i--)
      buff[idx] = (int)(right % 10 + 0.05) + '0';
  }
  if ((f.is_precision_set && f.precision != 0) || (int)r ||
      (!f.is_precision_set && val == 0) || s21_strlen(fractions))
    buff[idx--] = '.';
  if (!left) {
    buff[idx] = '0';
    idx--;
  } else {
    for (; left; left /= 10, idx--) buff[idx] = (int)(left % 10) + '0';
  }
  for (int i = 0; buff[idx + 1]; idx++, i++) {
    if (neg && i == 0) {
      ret[i] = '-';
      i++;
    }
    ret[i] = buff[idx + 1];
  }
}

int check_num(char c) { return (c >= '0' && c <= '9'); }
