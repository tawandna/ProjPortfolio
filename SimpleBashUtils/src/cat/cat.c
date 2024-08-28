#include "cat.h"

arguments argument_parser(int argc, char **argv) {
  arguments arg = {0};
  struct option long_options[] = {
      {"number", no_argument, NULL, 'n'},
      {"number-nonblank", no_argument, NULL, 'b'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {0, 0, 0, 0},
  };
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "bnsEeTtv", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'e':
        arg.E = 1;
        arg.v = 1;
        break;
      case 'E':
        arg.E = 1;
        break;
      case 'T':
        arg.T = 1;
        break;
      case 't':
        arg.T = 1;
        arg.v = 1;
        break;
      case '?':
        perror("ERROR");
        exit(1);
        break;
      default:
        break;
    }
  }
  return arg;
}

char v_output(int ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch < 0) {
    printf("M-");
    ch = ch & 0x7F;
  }
  if (ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}

void outline(arguments *arg, char *line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == '\t')
      printf("^I");
    else {
      if (arg->E && line[i] == '\n') putchar('$');
      if (arg->v) line[i] = v_output(line[i]);
      putchar(line[i]);
    }
  }
}

void output(arguments *arg, char **argv) {
  FILE *file = fopen(argv[optind], "r");
  char *line = NULL;
  size_t memline = 0;
  int read = 0;
  int line_count = 1;
  int empty_count = 0;
  read = getline(&line, &memline, file);
  while (read != -1) {
    if (line[0] == '\n')
      empty_count++;
    else
      empty_count = 0;
    if (arg->s && empty_count > 1) {
    } else {
      if (arg->b) {
        if (line[0] != '\n') {
          printf("%6d\t", line_count);
          line_count++;
        }
      } else if (arg->n) {
        printf("%6d\t", line_count);
        line_count++;
      } else if (arg->b && arg->n) {
        if (line[0] != '\n') {
          printf("%6d\t", line_count);
          line_count++;
        }
      }
      outline(arg, line, read);
    }
    read = getline(&line, &memline, file);
  }
  free(line);
  fclose(file);
}

int main(int argc, char **argv) {
  arguments arg = argument_parser(argc, argv);
  output(&arg, argv);
  return 0;
}