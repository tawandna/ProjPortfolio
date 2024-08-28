#ifndef SRC_S21_SPRINTF_H
#define SRC_S21_SPRINTF_H

#define BUFF_SIZE 512

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "s21_strcpy.c"
#include "s21_string.h"

typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool zero;
  int precision;
  int is_precision_set;
  int width;
  char length;
  char specifier;
} flags;

// main func
int s21_sprintf(char *str, const char *format, ...);

// check format functions
const char *check_length(const char *format, flags *f);
const char *check_width(const char *format, flags *f, va_list va);
const char *check_precision(const char *format, flags *f, va_list va);
const char *check_flags(const char *format, flags *f);

// parse functions
void parse_string(flags f, char *buff, va_list va);
void parse_int(flags f, char *buff, va_list va);
void parse_float(flags f, char *buff, va_list va);
void parse_char(flags f, char *buff, va_list va);
void parse_unsigned(flags f, char *buff, va_list va);
void specs_switch(flags f, char *buff, va_list va);

// helper functions
// char *str_cat(char *dest, const char *src);
void unsigned_num_to_string(uint64_t val, char *ret, int base);
int check_num(char c);
int str_to_num(const char *str);
bool check_integer_specifier(char c);
void double_to_str(long double val, char *ret, flags f);
void whole_num_to_string(int64_t val, char *ret, int base);
char *str_cat(char *dest, const char *src);

// format functions
void format_flags(char *buff, flags f);
void format_precision(char *buff, flags f);
void format_char(flags f, char *buff, char c);
void format_string(flags f, char *buff, char *str);

#endif  // SRC_S21_SPRINTF_H_
