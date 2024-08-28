#ifndef C3_SIMPLEBASHUTILS_SRC_GREP_GREP_H
#define C3_SIMPLEBASHUTILS_SRC_GREP_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

typedef struct arguments {
  int e, i, v, c, l, n, h, s;
  char *pattern;
} arguments;

// --- SUPPORT FUNCTIONS --- //
void output(arguments arg, int argc, char **argv);
arguments argument_parser(int argc, char **argv);
void processFile(arguments arg, char *path, regex_t *reg);

#endif  // C3_SIMPLEBASHUTILS_SRC_GREP_GREP_H
