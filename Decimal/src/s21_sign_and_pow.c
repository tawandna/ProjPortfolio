#include "s21_decimal.h"

sign_and_pow s21_parsing_sign_and_pow(s21_decimal value) {
  sign_and_pow result_scale = {0};
  result_scale.sign = (value.bits[3] >> 31) & 1;
  result_scale.pow =
      (value.bits[3] >> 16) & 0xFF;  // вытаскиваем 8 битов с 16 до 23
  return result_scale;
}

uint8_t s21_get_power(s21_decimal value) {
  uint8_t res = 0;
  res = (uint8_t)(255 & (value.bits[3] >> 16));
  return res;
}

int s21_set_power(s21_decimal *value, uint8_t power) {
  int sign = s21_get_sign(*value);
  (*value).bits[3] = (uint32_t)(power << 16);
  s21_set_sign(value, sign);
  return 0;
}

int s21_get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

void s21_set_sign(s21_decimal *value, int sign) {
  if (sign != s21_get_sign(*value)) {
    if (sign == 1) {
      (*value).bits[3] += HIGH_BIT;
    } else {
      (*value).bits[3] -= HIGH_BIT;
    }
  }
}
