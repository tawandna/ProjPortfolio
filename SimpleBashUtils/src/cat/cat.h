#ifndef C3_SIMPLEBASHUTILS_SRC_CAT_CAT_H
#define C3_SIMPLEBASHUTILS_SRC_CAT_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

typedef struct arguments {
  int b, n, s, E, T, v;
} arguments;

// --- SUPPORT FUNCTIONS --- //
char v_output(int ch);
void outline(arguments *arg, char *line, int n);
void output(arguments *arg, char **argv);
#endif  // C3_SIMPLEBASHUTILS_SRC_CAT_CAT_H