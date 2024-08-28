CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
DATE = $(shell date -R)
TEST_DIR = ./tests
SRCS := s21_strlen.c s21_strpbrk.c s21_memchr.c s21_memcmp.c s21_memset.c s21_memcpy.c s21_strncpy.c s21_strchr.c s21_strncmp.c s21_to_lower.c s21_to_upper.c s21_strncat.c s21_strrchr.c s21_trim.c s21_insert.c s21_strerror.c s21_strcspn.c s21_strstr.c s21_strtok.c s21_sprintf.c
OBJS := $(SRCS:c=o)
TEST_SRCS := $(TEST_DIR)/main.c $(TEST_DIR)/s21_strlen_test.c $(TEST_DIR)/s21_memchr_test.c $(TEST_DIR)/s21_strpbrk_test.c $(TEST_DIR)/s21_memcmp_test.c $(TEST_DIR)/s21_memset_test.c $(TEST_DIR)/s21_memcpy_test.c $(TEST_DIR)/s21_strncpy_test.c  $(TEST_DIR)/s21_strchr_test.c $(TEST_DIR)/s21_strncmp_test.c $(TEST_DIR)/s21_to_lower_test.c $(TEST_DIR)/s21_to_upper_test.c $(TEST_DIR)/s21_strncat_test.c $(TEST_DIR)/s21_strrchr_test.c $(TEST_DIR)/s21_trim_test.c $(TEST_DIR)/s21_insert_test.c $(TEST_DIR)/s21_strerror_test.c $(TEST_DIR)/s21_strcspn_test.c $(TEST_DIR)/s21_strstr_test.c $(TEST_DIR)/s21_strtok_test.c $(TEST_DIR)/s21_sprintf_test.c
TEST_OBJS := $(TEST_SRCS:c=o)
GCOVR := $(TEST_SRCS:c=gcno)

OS := $(shell uname)
UBUNTU := $(shell hostnamectl | grep -o 'Ubuntu')
MAC_X86 := $(shell uname -a | grep -o _X86_64)
MAC_M1 := $(shell uname -a | grep -o _ARM64)

ifeq ($(OS), Linux)
    TEST_LIBS = -lcheck -pthread -lrt -lm -lsubunit
else ifeq ($(MAC_M1), _ARM64)
    TEST_LIBS = -I/opt/homebrew/opt/check/include -L/opt/homebrew/opt/check/lib -lcheck
else ifeq ($(MAC_X86), _X86_64)
    TEST_LIBS = $(shell pkg-config --libs --cflags check) -lm
endif

.PHONY: all clean test

all: s21_string.a

s21_string.a: $(OBJS)
	ar rcs s21_string.a  $(OBJS)
	ranlib $@
	rm *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJS) s21_string.a
	$(CC) $(CFLAGS) $(TEST_OBJS) $(TEST_LIBS) -L. s21_string.a -o $(TEST_DIR)/s21_tests
	./tests/s21_tests
	
memcheck: test
	valgrind -q --tool=memcheck --leak-check=yes ./tests/s21_tests

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	reset
	brew install lcov
	brew install check
	sleep 1
	reset

gcov_report: CFLAGS += --coverage -o0
gcov_report: clean test
	mkdir -p report
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory report
	rm -rf *.gcno *.gcda *.gcov *.info

clean:
	rm -f *.o *gcno *gcda ./tests/*.o ./tests/s21_tests ./tests/*gcda ./tests/*gcno gcovr_report.html
