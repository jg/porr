#include <math.h>
#include <stdio.h>

void gauss_jordan(double **a, int n, double *b, double *x) {
  double alfa;
  int i, j, k;

  for (k = 1; k <= n; k++) {
    #ifdef OPENMP
#pragma omp parallel for private(alfa, j)
    #endif
    for (i = 1; i <= n; i++) {
      if (i == k)
        continue;
      alfa = a[i][k] / a[k][k];
      for (j = k; j <= n; j++)
        a[i][j] = a[i][j] - alfa * a[k][j];
      b[i] = b[i] - alfa * b[k];
    }
  }

  for (k = 1; k <= n; k++)
    x[k] = b[k] / a[k][k];
}
