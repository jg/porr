#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include "lib/nr.h"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

/*
   Program reads and solves a linear equation from file given as first argument.
   Input file format is described in reader.c
   First line of output contains two numbers: the number of iterations and the computed error of the solution.
   Second line of the output contains the solution vector
 */

void main (int argc, char **argv) {
  LinearEquation leq;

  char *filename = argv[1];
  leq = read_linear_equation_from_file(filename);

  int iterations;
  double error;
  linbcg(leq.sa, leq.ija, leq.n, leq.b, leq.x, 1, 0.1, 10, &iterations, &error);

  printf("%d %f\n", iterations, error);
  print_double(leq.x, leq.n);
  
  free_linear_equation(leq);
}

void print_double(double *tab, int n) {
  for (int i = 1; i <= n; ++i) {
    printf("%f ", tab[i]);
  }
  printf("\n");
}
