CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
C_FILES = $(wildcard *.c)

SOURCES = $(C_FILES)
OBJECTS = $(SOURCES:.c=.o)
LIBRARY = s21_string.a
HEADER = s21_string.h

TEST_DIR = ../test
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_EXECUTABLE = $(TEST_DIR)/unit_tests

ARCHIVE = ar
RC = ranlib

CLANG_FORMAT = clang-format
CLANG_FORMAT_STYLE = ../materials/linters/.clang-format
CPPCHECK_CAT_FLAGS = --enable=all \
	--suppress=missingIncludeSystem \
	--suppress=normalCheckLevelMaxBranches \
	--suppress=unusedStructMember \
	--suppress=unusedFunction \
	--suppress=checkersReport \
	--suppress=missingInclude \
	--suppress=unmatchedSuppression \
	--suppress=staticStringCompare \
	--suppress=memsetZeroBytes \
	--suppress=unreadVariable \
	--suppress=duplicateExpression

CHECK_CFLAGS = $(shell pkg-config --cflags check 2>/dev/null || echo "")
CHECK_LIBS = $(shell pkg-config --libs check 2>/dev/null || echo "")
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: s21_string.a

s21_string.a: $(OBJECTS)
	$(ARCHIVE) rcs $(LIBRARY) $^
	$(RC) $(LIBRARY)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

cppcheck:
	cppcheck $(SOURCES) $(HEADER) $(CPPCHECK_CAT_FLAGS)
	cd $(TEST_DIR) && cppcheck $(TEST_SOURCES) $(CPPCHECK_CAT_FLAGS)

style:
	$(CLANG_FORMAT) -n -style=file:$(CLANG_FORMAT_STYLE) $(SOURCES) $(HEADER)
	cd $(TEST_DIR) && $(CLANG_FORMAT) -n -style=file:$(CLANG_FORMAT_STYLE) $(TEST_SOURCES)

format:
	$(CLANG_FORMAT) -i -style=file:$(CLANG_FORMAT_STYLE) $(SOURCES) $(HEADER)
	cd $(TEST_DIR) && $(CLANG_FORMAT) -i -style=file:$(CLANG_FORMAT_STYLE) $(TEST_SOURCES)

check: style cppcheck

clean:
	rm -f $(OBJECTS) $(LIBRARY)
	cd $(TEST_DIR) && make clean

build: check s21_string.a

test: s21_string.a
	cd $(TEST_DIR) && make unit-test

gcov_report: s21_string.a
	cd $(TEST_DIR) && make gcov_report

asan: s21_string.a
	cd $(TEST_DIR) && make asan

.PHONY: all s21_string.a cppcheck style format check clean build test gcov_report asan