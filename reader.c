#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

/* WARNING: one-based array indexing is happening here. Don't ask. */

/* 
   File format description:
   
   0. File contains a description of a linear equation system, Ax = b 
   1. First line contains two numbers. The dimension of the A matrix
   2. The following i-1'th line of the file contains the coefficients of the i'th row of A followed by the i'th member of b.
 */


LinearEquation read_linear_equation_from_file(char *file_name) {
  FILE *fp;
  int n; // matrix dimensions
  float x;
  
  if ((fp = fopen(file_name, "r")) == NULL ) {
    exit(EXIT_FAILURE);
  }

  fp = fopen(file_name,"r");

  fscanf(fp,"%d", &n);

  // init A
  float **A = (float**) malloc((n + 1) * sizeof(float*));
  for (int i = 1; i <= n; ++i) {
    A[i] = (float*) malloc((n + 1) * sizeof(float));
  }
  
  // init b
  float *b = (float*) malloc(n * sizeof(float*));


  for (int i = 1; i <= n; i++) {
    // read A matrix
    for(int j = 1; j <= n; j++) {
      fscanf(fp,"%f", &x);
      A[i][j] = x;
    }
    
    // read b column vector
    fscanf(fp,"%f", &x);
    b[i] = x;
  }

  fclose(fp);
  
  // return result
  LinearEquation leq;
  leq.A = A;
  leq.n = n;
  leq.b = b;

  return leq;
}

void free_linear_equation(LinearEquation leq) {
  free(leq.A);
  free(leq.b);
}

void print_linear_equation(LinearEquation leq) {
  float **A;
  float *b;
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

}
