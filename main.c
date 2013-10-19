#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

float *sa;

unsigned long *ija;

void main (int argc, char **argv) {
  LinearEquation leq;

  char *filename = argv[1];
  leq = read_linear_equation_from_file(filename);

  int sa_size = leq.n * leq.n;


  sa = (float*) malloc(sa_size * sizeof(float));
  ija = (unsigned long*) malloc(sa_size * sizeof(unsigned long));

  // print_linear_equation(leq);
  sprsin(leq.A, leq.n, 0.1, sa_size, sa, ija);

  free_linear_equation(leq);
}

