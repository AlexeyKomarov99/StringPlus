CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
EXECUTABLE = unit-tests

SRC_DIR = ../src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADER = $(SRC_DIR)/s21_string.h

TEST_MAIN = unit_tests_main.c
TEST_FILES = test_s21_memchr.c test_s21_memcmp.c test_s21_memcpy.c \
             test_s21_memset.c test_s21_strncat.c test_s21_strchr.c \
             test_s21_strncmp.c test_s21_strncpy.c test_s21_strcspn.c \
             test_s21_strlen.c test_s21_strpbrk.c test_s21_strrchr.c \
             test_s21_strstr.c test_s21_strtok.c test_s21_strerror.c \
             test_s21_to_upper.c test_s21_to_lower.c test_s21_insert.c \
             test_s21_trim.c test_s21_sprintf.c test_s21_sscanf.c

CHECK_CFLAGS = $(shell pkg-config --cflags check)
CHECK_LIBS = $(shell pkg-config --libs check)
INCLUDES = -I$(SRC_DIR)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    TEST_CFLAGS = $(CFLAGS) -Wno-stringop-overflow -Wno-stringop-truncation
else
    TEST_CFLAGS = $(CFLAGS)
endif

all: unit-test

unit-test: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(TEST_MAIN) $(TEST_FILES) $(SOURCES) $(HEADER)
	$(CC) $(TEST_CFLAGS) $(INCLUDES) $(CHECK_CFLAGS) -o $(EXECUTABLE) \
	$(TEST_MAIN) $(TEST_FILES) $(SOURCES) $(CHECK_LIBS)

gcov_report: $(TEST_MAIN) $(TEST_FILES) $(SOURCES) $(HEADER)
	$(CC) $(TEST_CFLAGS) -g $(INCLUDES) $(CHECK_CFLAGS) $(GCOV_FLAGS) -o $(EXECUTABLE) \
	$(TEST_MAIN) $(TEST_FILES) $(SOURCES) $(CHECK_LIBS)
	./$(EXECUTABLE) || true
	cp *.gcda *.gcno ../src/ 2>/dev/null || true
	gcovr --html --html-details -o coverage.html --root=../src --gcov-ignore-errors=all --print-summary 2>/dev/null
	open coverage.html 2>/dev/null || true

asan: $(TEST_MAIN) $(TEST_FILES) $(SOURCES) $(HEADER)
	$(CC) $(TEST_CFLAGS) -g -fsanitize=address $(INCLUDES) $(CHECK_CFLAGS) -o $(EXECUTABLE) \
	$(TEST_MAIN) $(TEST_FILES) $(SOURCES) $(CHECK_LIBS)
	./$(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE) *.gcno *.gcda *.gcov *.info *.html *.css report *.dSYM
	rm -f $(SRC_DIR)/*.o $(SRC_DIR)/s21_string.a
	rm -f $(SRC_DIR)/*.gcno $(SRC_DIR)/*.gcda $(SRC_DIR)/*.gcov $(SRC_DIR)/*.info

.PHONY: all unit-test gcov_report clean asan