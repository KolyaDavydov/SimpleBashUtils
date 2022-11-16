#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc > 3) {
    char flag = get_flag(argv);
    char template[512] = {0};
    get_template(flag, argv, template);
    loop_file(argc, argv, flag, template);
  } else {
    fprintf(stderr, "мало аргументов\n");
  }
  return 0;
}

void print_o(FILE *file, char *template, char **argv, int i, int argc) {
  char buf[2000];
  regex_t compiled;
  regmatch_t pmatch[1];
  const size_t nmatch = 1;
  if (regcomp(&compiled, template, REG_EXTENDED) == 0) {
    while (fgets(buf, 2000, file) != NULL) {
      if (regexec(&compiled, buf, nmatch, pmatch, 0) == 0) {
        if (argc > 4) {
          printf("%s:", argv[i]);
        }
        printf("%s\n", template);
      }
    }
    regfree(&compiled);
  }
}

void print_n(FILE *file, char *template, char **argv, int i, int argc) {
  int line_num = 0;
  char buf[2000];
  regex_t compiled;
  regmatch_t pmatch[1];
  const size_t nmatch = 1;
  if (regcomp(&compiled, template, REG_EXTENDED) == 0) {
    while (fgets(buf, 2000, file) != NULL) {
      line_num++;
      if (regexec(&compiled, buf, nmatch, pmatch, 0) == 0) {
        if (argc > 4) {
          printf("%s:", argv[i]);
        }
        printf("%d:%s", line_num, buf);
      }
    }
    regfree(&compiled);
  }
}

void print_l(FILE *file, char *template, char **argv, int i) {
  int line_num = 0;
  char buf[2000];
  regex_t compiled;
  regmatch_t pmatch[1];
  const size_t nmatch = 1;
  if (regcomp(&compiled, template, REG_EXTENDED) == 0) {
    while (fgets(buf, 2000, file) != NULL) {
      if (regexec(&compiled, buf, nmatch, pmatch, 0) == 0) {
        line_num++;
      }
    }
    if (line_num > 0) {
      printf("%s\n", argv[i]);
    }
    regfree(&compiled);
  }
}

void print_c(FILE *file, char *template, char **argv, int i, int argc) {
  int line_num = 0;
  char buf[2000];
  regex_t compiled;
  regmatch_t pmatch[1];
  const size_t nmatch = 1;
  if (regcomp(&compiled, template, REG_EXTENDED) == 0) {
    while (fgets(buf, 2000, file) != NULL) {
      if (regexec(&compiled, buf, nmatch, pmatch, 0) == 0) {
        line_num++;
      }
    }
    if (argc > 4) {
      printf("%s:", argv[i]);
    }
    printf("%d\n", line_num);
    regfree(&compiled);
  }
}

void print_v(FILE *file, char *template, char **argv, int i, int argc) {
  char buf[2000];
  regex_t compiled;
  regmatch_t pmatch[1];
  const size_t nmatch = 1;
  if (regcomp(&compiled, template, 0) == 0) {
    while (fgets(buf, 2000, file) != NULL) {
      if (regexec(&compiled, buf, nmatch, pmatch, 0) == REG_NOMATCH) {
        if (argc > 4) {
          printf("%s:", argv[i]);
        }
        printf("%s", buf);
        if (feof(file)) {
          printf("\n");
        }
      }
    }

    regfree(&compiled);
  }
}

void print_eifsh(FILE *file, char *template, char **argv, int i, char flag,
                 int argc) {
  char buf[2000];
  regex_t compiled;
  regmatch_t pmatch[1] = {0};
  const size_t nmatch = 1;
  if (flag == 'i') {
    if (regcomp(&compiled, template, REG_ICASE) == 0) {
      while (fgets(buf, 2000, file) != NULL) {
        if (regexec(&compiled, buf, nmatch, pmatch, 0) == 0) {
          if (argc > 4 && flag != 'h') {
            printf("%s:", argv[i]);
          }
          printf("%s", buf);
        }
      }
      regfree(&compiled);
    }
  } else {
    if (regcomp(&compiled, template, REG_EXTENDED) == 0) {
      while (fgets(buf, 2000, file) != NULL) {
        if (regexec(&compiled, buf, nmatch, pmatch, 0) == 0) {
          if (argc > 4 && flag != 'h') {
            printf("%s:", argv[i]);
          }
          printf("%s", buf);
        }
      }
      regfree(&compiled);
    }
  }
}

void get_template(char flag, char **argv, char *template) {
  if (flag == 'f') {
    FILE *file;
    char buf[256];
    if ((file = fopen(argv[2], "r")) != NULL) {
      fgets(buf, 256, file);
      strcpy(template, buf);
    } else {
      if (flag != 's') {
        fprintf(stderr, "темплат не считался с файла\n");
      }
      exit(1);
    }

    fclose(file);
  } else {
    strcpy(template, argv[2]);
  }
}

void loop_file(int argc, char **argv, char flag, char *template) {
  for (int i = 3; i < argc; i++) {
    FILE *file;
    if ((file = fopen(argv[i], "r")) == NULL) {
      if (flag != 's') {
        fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      }
      continue;
    }
    switch (flag) {
      case 'e':
        print_eifsh(file, template, argv, i, flag, argc);
        break;
      case 'i':
        print_eifsh(file, template, argv, i, flag, argc);
        break;
      case 'v':
        print_v(file, template, argv, i, argc);
        break;
      case 'c':
        print_c(file, template, argv, i, argc);
        break;
      case 'l':
        print_l(file, template, argv, i);
        break;
      case 'n':
        print_n(file, template, argv, i, argc);
        break;
      case 'h':
        print_eifsh(file, template, argv, i, flag, argc);
        break;
      case 's':
        print_eifsh(file, template, argv, i, flag, argc);
        break;
      case 'f':
        print_eifsh(file, template, argv, i, flag, argc);
        break;
      case 'o':
        print_o(file, template, argv, i, argc);
        break;
      default:
        fprintf(stderr, "что то пошло не так\n");
    }
    fclose(file);
  }
}

char get_flag(char **argv) {
  char ch = 'w';
  int razmer = strlen(argv[1]);
  if ((argv[1][0] == '-') && razmer == 2) {
    if ((argv[1][1] == 'e')) {
      ch = 'e';
    } else if (argv[1][1] == 'i') {
      ch = 'i';
    } else if (argv[1][1] == 'v') {
      ch = 'v';
    } else if (argv[1][1] == 'c') {
      ch = 'c';
    } else if (argv[1][1] == 'l') {
      ch = 'l';
    } else if (argv[1][1] == 'n') {
      ch = 'n';
    } else if (argv[1][1] == 'h') {
      ch = 'h';
    } else if (argv[1][1] == 's') {
      ch = 's';
    } else if (argv[1][1] == 'f') {
      ch = 'f';
    } else if (argv[1][1] == 'o') {
      ch = 'o';
    } else {
      fprintf(stderr, "cat: illegal option -- %c", argv[1][1]);
      exit(1);
    }
  } else {
    //    ch = w; // ощибка
    fprintf(stderr, "unknown --direcrories option");
    exit(1);
  }
  return ch;
}
