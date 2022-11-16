#include "s21_cat.h"

int main(int argc, char **argv) {
  char flag = get_flag(argv);  // для хранения флага

  int startfile = start_file(argv);

  loop_file(argc, argv, flag, startfile);

  return 0;
}

void print_c(FILE *file) {
  int ch;  //буфер для хранения очередноuj символа из файла
  while ((ch = fgetc(file)) != EOF) {
    printf("%c", ch);
  }
}

void print_T(FILE *file) {
  int ch;  //буфер для хранения очередноuj символа из файла
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\t') {
      printf("^I");
      continue;
    } else {
      printf("%c", ch);
    }
  }
}

void print_E(FILE *file) {
  int ch;  //буфер для хранения очередноuj символа из файла
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      printf("&\n");
      continue;
    } else {
      printf("%c", ch);
    }
  }
}

void print_t(FILE *file) {
  int ch;  //буфер для хранения очередноuj символа из файла
  while ((ch = fgetc(file)) != EOF) {
    if (ch > 127 && ch < 160) {
      printf("M-^%c", ch - 64);
      continue;
    } else if (ch == 127) {
      printf("^?");
      continue;
    } else if (ch == '\t') {
      printf("^I");
      continue;
    } else if (ch < 32 && ch != '\n' && ch != '\t') {
      printf("^X");
      continue;
    } else {
      printf("%c", ch);
    }
  }
}

void print_e(FILE *file) {
  int ch;  //буфер для хранения очередноuj символа из файла
  while ((ch = fgetc(file)) != EOF) {
    if (ch > 127 && ch < 160) {
      printf("M-^%c", ch - 64);
      continue;
    } else if (ch == 127) {
      printf("^?");
      continue;
    } else if (ch == '\n') {
      printf("$\n");
      continue;
    } else if (ch < 32 && ch != '\n' && ch != '\t') {
      printf("^X");
      continue;
    } else {
      printf("%c", ch);
    }
  }
}

void print_s(FILE *file) {
  char buf[2001];  //буфер для хранения очередной строки из файла
  char ch = '1';
  //    int line_num = 1;
  while (fgets(buf, 2000, file) != NULL) {
    if (buf[0] != '\n') {
      printf("%s", buf);
      ch = '1';
    } else if (buf[0] == '\n' && ch == '1') {
      printf("%s", buf);
      ch = '0';
    } else {
      ch = '0';
      continue;
    }
  }
}

void print_n(FILE *file) {
  char buf[2001];  //буфер для хранения очередной строки из файла
  int line_num = 1;
  while (fgets(buf, 2000, file) != NULL) {
    print_space(line_num);
    printf("%s", buf);
    line_num++;
  }
}

void print_b(FILE *file) {
  char buf[2001];  //буфер для хранения очередной строки из файла
  int line_nonblank_num = 1;
  while (fgets(buf, 2000, file) != NULL) {
    if (buf[0] != '\n') {
      print_space(line_nonblank_num);
      printf("%s", buf);
      line_nonblank_num++;
    } else {
      printf("%s", buf);
    }
  }
}

void print_space(int line) {
  if (line < 10) {
    printf("     %d\t", line);
  } else if (line >= 10 && line < 100) {
    printf("    %d\t", line);
  } else if (line >= 100 && line < 1000) {
    printf("   %d\t", line);
  } else if (line >= 1000 && line < 10000) {
    printf("   %d\t", line);
  } else if (line >= 10000 && line < 100000) {
    printf("  %d\t", line);
  } else if (line >= 100000 && line < 1000000) {
    printf(" %d\t", line);
  } else if (line >= 1000000 && line < 10000000) {
    printf("%d\t", line);
  }
}

void loop_file(int argc, char **argv, char flag, int startfile) {
  for (int i = startfile; i < argc; i++) {
    FILE *file;
    if ((file = fopen(argv[i], "r")) == NULL) {
      printf("cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    switch (flag) {
      case 'b':
        print_b(file);
        break;
      case 'e':
        print_e(file);
        break;
      case 'n':
        print_n(file);
        break;
      case 's':
        print_s(file);
        break;
      case 't':
        print_t(file);
        break;
      case 'E':
        print_E(file);
        break;
      case 'T':
        print_T(file);
        break;
      case 'c':
        print_c(file);
        break;
      default:
        printf("что то пошло не так\n");
    }
    fclose(file);
  }
}

int start_file(char **argv) {
  if (argv[1][0] != '-') {
    return 1;
  }
  return 2;
}

char get_flag(char **argv) {
  if ((argv[1][0] == '-')) {
    if ((argv[1][1] == 'b') || strcmp(argv[1], "--number-nonblank") == 0) {
      return 'b';
    } else if (argv[1][1] == 'e') {
      return 'e';
    } else if ((argv[1][1] == 'n') || strcmp(argv[1], "--number") == 0) {
      return 'n';
    } else if ((argv[1][1] == 's') || strcmp(argv[1], "--squeeze-blank") == 0) {
      return 's';
    } else if (argv[1][1] == 't') {
      return 't';
    } else if (argv[1][1] == 'E') {
      return 'E';
    } else if (argv[1][1] == 'T') {
      return 'T';
    } else {
      printf("cat: illegal option -- %c", argv[1][1]);
      exit(1);
    }
  } else {
    return 'c';
  }
}
