#include "grep.h"
#define _GNU_SOURCE

arguments argument_parser(int argc, char **argv) {
  arguments arg = {0};
  int opt = 0;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        arg.pattern = optarg;
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      default:
        break;
    }
  }
  if (arg.pattern == NULL) {
    arg.pattern = argv[optind];
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void processFile(arguments arg, char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    exit(1);
  }
  char *line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_count = 1;
  int argc_count = 0;
  read = getline(&line, &memlen, f);

  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);

    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        for (int i = 0; i < read; i++) {
          putchar(line[i]);
        }
      }
      argc_count++;
    }
    read = getline(&line, &memlen, f);
    line_count++;
  }
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", argc_count);
  }
  if (arg.l && argc_count > 0) printf("%s\n", path);
  free(line);
  fclose(f);
}

void output(arguments arg, int argc, char **argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, arg.i);
  if (error) perror("Error");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}

int main(int argc, char **argv) {
  arguments arg = argument_parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}