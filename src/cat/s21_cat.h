#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_flag(char **argv);
int start_file(char **argv);
void loop_file(int argc, char **argv, char flag, int startfile);
void print_space(int line);
void print_b(FILE *file);
void print_n(FILE *file);
void print_s(FILE *file);
void print_e(FILE *file);
void print_t(FILE *file);
void print_E(FILE *file);
void print_T(FILE *file);
void print_c(FILE *file);

#endif  // S21_CAT_H_