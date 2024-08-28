#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) {
    return 0;
  }
  s21_decimal_to_null(result);
  int flag = 0;

  if ((value_1.bits[0] == 0 &&
       (value_1.bits[1] == 0 && value_1.bits[2] == 0)) ||
      (value_2.bits[0] == 0 &&
       (value_2.bits[1] == 0 && value_2.bits[2] == 0))) {
    s21_decimal_to_null(result);
  } else {
    s21_big_decimal big_res = {{0}};
    s21_mul_big(value_1, value_2, &big_res);
    s21_set_pow_and_mul(value_1, value_2, &big_res);

    s21_round_to_dec_precision(&big_res);

    for (int i = 3; i < 7; i++) {
      if (big_res.bits[i] != 0) flag = 1;
    }
    if (flag && s21_get_sign_big(big_res)) {
      flag = 2;
    }

    if (!flag) {
      *result = s21_big_decimal_to_decimal(big_res);
      if (((*result).bits[0] == 0 &&
           ((*result).bits[1] == 0 && (*result).bits[2] == 0))) {
        flag = 2;
      }
    }
  }
  if (flag) {
    s21_decimal_to_null(result);
  }
  return flag;
}

int s21_mul_big(s21_decimal value_1, s21_decimal value_2,
                s21_big_decimal *result) {
  int flag = 0;
  s21_big_decimal value_1_big = s21_decimal_to_big_decimal(value_1);
  s21_big_decimal res = {0};
  s21_big_decimal tmp = s21_decimal_to_big_decimal(value_1);
  int add_res;
  int bits = s21_count_bits(value_2);
  for (int i = 0; i < bits; i++) {
    int current_bit = 1 & s21_right_shift(value_2, i).bits[0];
    if (current_bit) {
      tmp = s21_left_shift_big(value_1_big, i);
      add_res = s21_add_two_positiv_big(&res, tmp, res);
      if (add_res) {
        flag = add_res;
      }
    }
  }
  *result = res;
  return flag;
}

void s21_round_to_dec_precision(s21_big_decimal *value) {
  int scale = s21_get_power_big(*value);
  int sign = s21_get_sign_big(*value);

  char big_dec_str[1000] = "";
  s21_from_big_decimal_to_str(*value, big_dec_str);
  int len = strlen(big_dec_str);
  if (strchr(big_dec_str, '.')) len--;

  s21_big_decimal tmp = {{0}};

  while (len > 30 && scale > 0) {
    s21_div_integer_part_big(*value, DECIMAL_10_BIG, &tmp);
    *value = tmp;
    s21_big_decimal_to_null(&tmp);
    scale--;
    len--;
  }

  if (scale > 0 && len > 29) {
    s21_bank_rounding(value, &scale, &len);
    if ((*value).bits[3] != 0) {
      s21_bank_rounding(value, &scale, &len);
    }
  }
  s21_set_power_big(value, scale);
  s21_set_sign_big(value, sign);
}

void s21_bank_rounding(s21_big_decimal *value, int *scale, int *len) {
  int bank_round = 0;
  int to_up = 0;
  s21_big_decimal tmp = {{0}};
  int last_digit = s21_get_last_dec_digit(*value);
  if (last_digit == 5) {
    bank_round = 1;
  } else if (last_digit > 5) {
    to_up = 1;
  }

  s21_div_integer_part_big(*value, DECIMAL_10_BIG, &tmp);
  *value = tmp;
  s21_big_decimal_to_null(&tmp);
  (*scale)--;
  (*len)--;

  last_digit = s21_get_last_dec_digit(*value);
  if (to_up || (bank_round && last_digit % 2 != 0)) {
    s21_add_two_positiv_big(value, *value, DECIMAL_1_BIG);
  }
}

void s21_set_pow_and_mul(s21_decimal value_1, s21_decimal value_2,
                         s21_big_decimal *result) {
  int8_t power_1 = s21_get_power(value_1);
  int8_t power_2 = s21_get_power(value_2);

  s21_set_power_big(result, power_1 + power_2);

  if (s21_get_sign(value_1) != s21_get_sign(value_2)) {
    s21_set_sign_big(result, 1);
  }
}

void s21_remove_nonsignificant_zeros(s21_big_decimal *value) {
  int scale = s21_get_power_big(*value);
  int sign = s21_get_sign_big(*value);
  s21_big_decimal tmp = {{0}};
  while (scale > 0 && s21_get_last_dec_digit(*value) == 0) {
    s21_div_integer_part_big(*value, DECIMAL_10_BIG, &tmp);
    *value = tmp;
    s21_big_decimal_to_null(&tmp);
    scale--;
  }
  s21_set_power_big(value, scale);
  s21_set_sign_big(value, sign);
}

int s21_mul_equal_pow(s21_decimal value_1, s21_decimal value_2,
                      s21_decimal *result) {
  int flag = 0;
  sign_and_pow value_1_info = s21_parsing_sign_and_pow(value_1);
  sign_and_pow value_2_info = s21_parsing_sign_and_pow(value_2);

  s21_decimal res = {0};
  s21_decimal tmp = value_1;
  s21_decimal buffer = {0};
  int add_res = 0;
  int bits = s21_count_bits(value_2);
  for (int i = 0; i < bits && !flag; i++) {
    int current_bit = 1 & s21_right_shift(value_2, i).bits[0];
    if (current_bit) {
      if (s21_get_bit(tmp, 95) == 1) {
        flag = 1;
      } else {
        tmp = s21_left_shift(value_1, i);
        add_res = s21_add_two_positiv(&buffer, tmp, res);
        if (add_res) {
          flag = add_res;
        } else {
          res = buffer;
          s21_decimal_to_null(&buffer);
        }
      }
    }
  }
  if (value_1_info.pow + value_2_info.pow > 28) flag = 1;
  *result = res;
  return flag;
}
