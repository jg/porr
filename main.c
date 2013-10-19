#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include "lib/nr.h"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

double *sa;
unsigned long *ija;

void main (int argc, char **argv) {
  LinearEquation leq;

  char *filename = argv[1];
  leq = read_linear_equation_from_file(filename);


  int sa_size = (leq.n + 1) * (leq.n + 1);
  sa = (double*) malloc(sa_size * sizeof(double));
  ija = (unsigned long*) malloc((sa_size) * sizeof(unsigned long));
  sprsin(leq.A, leq.n, 0.1, sa_size, sa, ija);
  int element_count = ija[ija[1]-1]-1;
  
  
  /*
  for (int i = 1; i <= sa_size; ++i) {
    printf("%f  ", sa[i]);
  }
  
  printf("\n");
  
  printf("element count is %d\n", element_count);
  for (int i = 1; i <= element_count; ++i) {
    printf("%lu  ", ija[i]);
  }
  */

  // init x and fill with zeros
  leq.x = (double*) malloc((leq.n + 1) * sizeof(double));
  for (int i = 0; i <= leq.n; i++) { leq.x[i] = 0; }
  pri(leq.x, leq.n);

  int iterations;
  double error;
  linbcg(leq.n, leq.b, leq.x, 1, 0.1, 10, &iterations, &error);
  
  free_linear_equation(leq);
  free(sa);
  free(ija);
}


void prui(unsigned long *tab, int n) {
  for (int i = 1; i <= n; ++i) {
    printf("%lu  ", tab[i]);
  }
  printf("\n");
}

void pri(int *tab, int n) {
  for (int i = 1; i <= n; ++i) {
    printf("%d  ", tab[i]);
  }
  printf("\n");
}

