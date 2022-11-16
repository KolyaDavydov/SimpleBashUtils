CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

s21_grep: s21_grep.o
	$(CC) s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) -c s21_grep.c

clean:
	rm *.o s21_grep

rebiuld:
	clean
	make

testgrep: s21_grep
	../../test/test_grep.sh

test_clang:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n s21_grep.c
	rm .clang-format