// #include "s21_decimal.h"

// void print_bin(s21_decimal value) {
//   int32_t bit = 0;
//   for (int32_t j = 3; j >= 0; j--) {
//     for (int32_t i = 0; i < 32; i++) {
//       bit = 1 & (value.bits[j] >> 31);
//       printf("%d", bit);
//       value.bits[j] = value.bits[j] << 1;
//     }
//     printf(" ");
//   }
//   printf("\n");
// }

// void print_hex(s21_decimal value) {
//   int32_t hex;

//   for (int32_t j = 3; j >= 0; j--) {
//     for (int32_t i = 0; i < 8; i++) {
//       hex = 15 & (value.bits[j] >> 28);
//       printf("%X", hex);
//       value.bits[j] = value.bits[j] << 4;
//     }
//     printf(" ");
//   }
//   printf("\n");
// }

// /*
//   Ничего лучше и правильнее не придумал, ем децимал в строку двоичную ее в
//   строку десятичную
// */
// void print_dec(s21_decimal value) {
//   sign_and_pow scale = parsing_sign_and_pow(value);
//   char str_decimal[31] = "";
//   if (s21_is_equal(value, DECIMAL_0))
//     str_decimal[0] = '0';
//   else
//     // сама функция в support_func
//     s21_from_decimal_to_str(value, str_decimal);

//   printf("%c%s\n", scale.sign ? '-' : ' ', str_decimal);
// }

// void print_bin_big(s21_big_decimal value) {
//   int32_t bit = 0;
//   for (int32_t j = 7; j >= 0; j--) {
//     for (int i = 0; i < 32; i++) {
//       bit = 1 & (value.bits[j] >> 31);
//       printf("%d", bit);
//       value.bits[j] = value.bits[j] << 1;
//     }
//     printf(" ");
//   }
//   printf("\n");
// }

// void print_dec_big(s21_big_decimal value) {
//   sign_and_pow scale = parsing_sign_and_pow_big(value);
//   char str_decimal[1000] = "";
//   if (s21_is_equal_big(value, DECIMAL_0_BIG))
//     str_decimal[0] = '0';
//   else
//     s21_from_big_decimal_to_str(value, str_decimal);

//   printf("%c%s\n", scale.sign ? '-' : ' ', str_decimal);
// }
