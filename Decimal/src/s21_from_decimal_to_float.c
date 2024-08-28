#include "s21_decimal.h"
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  // Проверка условия. Если это условие выполняется, функция возвращает 1 и не
  // выполняет дальнейшие действия.
  if (s21_validation_check_for_float(src) || dst == NULL)
    res = 1;
  else {
    // массив будет содержать полный набор элементов s21_decimal
    int arr[96] = {0};

    // заполняем массив 0 и 1 из структуры src
    s21_filling_in_the_array(src, arr);

    // находим степень из структуры src
    int scale = (src.bits[3] >> 16) & 0xFF;

    // получаем знак из структуры src
    int sign = (src.bits[3] >> 31) & 1;

    /* с помощью цикла собираем мантису в long double который хранит 128 бит
    Каждое значение массива умножается на соответствующую степень двойки и
    добавляется к mantissa*/
    long double mantissa = 0.0L;
    for (int i = 0; i < 96; i++) mantissa += arr[i] * pow(2, i);
    // Если mantissa больше максимального значения для типа long double, функция
    // возвращает 1 и устанавливает значение *dst в 0.

    if (mantissa > 3.402823466e+38) {
      res = 1;
      *dst = 0;
      // Если mantissa не превышает максимальное значение, происходит установка
      // точки в мантисе с помощью цикла, где каждый раз мантиса делится на 10.
    } else {
      // находим место установки точки
      for (int i = 0; i < scale; i++) mantissa /= 10;

      // ставим минус, если sign = 1
      if (sign) mantissa = -1 * mantissa;

      *dst = (float)mantissa;
    }
  }
  return res;
}

// функция заполняет массив 0 и 1 из s21_decimal - добавить в общие функции
void s21_filling_in_the_array(s21_decimal src, int *arr) {
  // заполняет элементы массива arr с индексами от 95 до 64 значениями из
  // соответствующих битов структуры src.bits[2].
  for (int i = 95; i >= 64; i--) arr[i] = (src.bits[2] >> (95 - i)) & 1;
  // заполняет элементы массива arr с индексами от 63 до 32 значениями из
  // соответствующих битов структуры src.bits[1].
  for (int i = 63; i >= 32; i--) arr[i] = (src.bits[1] >> (63 - i)) & 1;
  // заполняет элементы массива arr с индексами от 31 до 0 значениями из
  // соответствующих битов структуры src.bits[0].
  for (int i = 31; i >= 0; i--) arr[i] = (src.bits[0] >> i) & 1;
}

int s21_validation_check_for_float(s21_decimal src) {
  int res = 0;

  // проверка для первых 16 бит на заполненность нулями
  for (int i = 0; i <= 15; i++)
    if ((src.bits[3] >> i) & 1) res = 1;

  // проверка битов 17-23, если содержимое больше 28 или меньше 0, то ошибка
  int degree = (src.bits[3] >> 16) & 0xFF;
  if (degree > 40 || degree < 0) res = 1;

  // проверка битов 24-30 на заполненость нулями, 31 - знаковый, не трогаем
  for (int i = 24; i <= 30; i++)
    if ((src.bits[3] >> i) & 1) res = 1;

  return res;
}
