cmake_minimum_required(VERSION 3.28)
project(src C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(tests)

add_executable(src
        tests/main.c
        tests/s21_insert_test.c
        tests/s21_memchr_test.c
        tests/s21_memcmp_test.c
        tests/s21_memcpy_test.c
        tests/s21_memset_test.c
        tests/s21_sprintf_test.c
        tests/s21_strchr_test.c
        tests/s21_strcspn_test.c
        tests/s21_strerror_test.c
        tests/s21_string_test.h
        tests/s21_strlen_test.c
        tests/s21_strncat_test.c
        tests/s21_strncmp_test.c
        tests/s21_strncpy_test.c
        tests/s21_strpbrk_test.c
        tests/s21_strrchr_test.c
        tests/s21_strstr_test.c
        tests/s21_strtok_test.c
        tests/s21_to_lower_test.c
        tests/s21_to_upper_test.c
        tests/s21_trim_test.c
        s21_insert.c
        s21_memchr.c
        s21_memcmp.c
        s21_memcpy.c
        s21_memset.c
        s21_sprintf.c
        s21_sprintf.h
        s21_strchr.c
        s21_strcpy.c
        s21_strcspn.c
        s21_strerror.c
        s21_string.h
        s21_strlen.c
        s21_strncat.c
        s21_strncmp.c
        s21_strncpy.c
        s21_strpbrk.c
        s21_strrchr.c
        s21_strstr.c
        s21_strtok.c
        s21_to_lower.c
        s21_to_upper.c
        s21_trim.c)
