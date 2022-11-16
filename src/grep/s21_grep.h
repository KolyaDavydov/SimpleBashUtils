#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_flag(char **argv);
void get_template(char flag, char **argv, char *template);
void loop_file(int argc, char **argv, char flag, char *template);
void print_eifsh(FILE *file, char *template, char **argv, int i, char flag,
                 int argc);
void print_v(FILE *file, char *template, char **argv, int i, int argc);
void print_c(FILE *file, char *template, char **argv, int i, int argc);
void print_l(FILE *file, char *template, char **argv, int i);
void print_n(FILE *file, char *template, char **argv, int i, int argc);
void print_o(FILE *file, char *template, char **argv, int i, int argc);

#endif // S21_GREP_H_