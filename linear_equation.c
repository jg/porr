#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linear_equation.h"
#include "lib/nr.h"

/* WARNING: one-based array indexing is happening here. Don't ask. */

/* 
   File format description:
   
   0. File contains a description of a linear equation system, Ax = b 
   1. First line contains two numbers. The dimension of the A matrix
   2. The following i-1'th line of the file contains the coefficients of the i'th row of A followed by the i'th member of b.
 */


LinearEquation read_linear_equation_from_file(const char *file_name) {
  FILE *fp;
  int n; // matrix dimensions
  double x;
  
  if ((fp = fopen(file_name, "r")) == NULL ) {
    exit(EXIT_FAILURE);
  }

  fp = fopen(file_name,"r");

  fscanf(fp,"%d", &n);

  // init A
  double **A = (double**) malloc((n + 1) * sizeof(double*));
  for (int i = 1; i <= n; ++i) {
    A[i] = (double*) malloc((n + 1) * sizeof(double));
  }
  
  // init b
  double *b = (double*) malloc((n + 1) * sizeof(double));


  for (int i = 1; i <= n; i++) {
    // read A matrix
    for(int j = 1; j <= n; j++) {
      fscanf(fp,"%lf", &x);
      A[i][j] = x;
    }
    
    // read b column vector
    fscanf(fp,"%lf", &x);
    b[i] = x;
  }

  fclose(fp);
  
  // return result
  LinearEquation leq;
  leq.A = A;
  leq.n = n;
  leq.b = b;

  // init sparse representation
  int sa_size = (leq.n + 1) * (leq.n + 1);
  leq.sa = (double*) malloc(sa_size * sizeof(double));
  leq.ija = (unsigned long*) malloc((sa_size) * sizeof(unsigned long));
  sprsin(leq.A, leq.n, 0.1, sa_size, leq.sa, leq.ija);
  leq.sparse_n = leq.ija[leq.ija[1]-1]-1;

  // init x and fill with zeros
  leq.x = (double*) malloc((leq.n + 1) * sizeof(double));
  for (int i = 0; i <= leq.n; i++) { leq.x[i] = 1; }

  return leq;
}

void free_linear_equation(LinearEquation leq) {
  free(leq.A);
  free(leq.b);
  free(leq.sa);
  free(leq.ija);
}

void print_linear_equation(LinearEquation leq) {
  double **A;
  double *b;
  int n;

  n = leq.n;
  A = leq.A;
  b = leq.b;

  printf("n = %d\n\n", n);

  printf("A = \n");
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      printf("%f  ", A[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  printf("b = ");
  for (int i = 1; i <= n; ++i) {
      printf("%f ", b[i]);
  }

  printf("\n");

  fflush(stdout);
}

double compute_error(LinearEquation leq) {
  double **A = leq.A; int n = leq.n;
  double *x = leq.x;
  double *b = leq.b;

  double *computed_x = malloc((n + 1) * sizeof(double));

  for (int i = 1; i <= n; i++) {
    double tmp = 0;
    for (int j = 1; j <= n; j++) {
      tmp += A[i][j] * x[j];
    }
    computed_x[i] = tmp;
  }

  double *errors = malloc((n + 1) * sizeof(double));

  for (int i = 1; i <= n; i++)
    errors[i] = fabs(computed_x[i] - x[i]);

  double error_sum = 0;
  for (int i = 1; i <= n; i++) 
    error_sum += errors[i];

  return error_sum;
}

