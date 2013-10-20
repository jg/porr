#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "reader.h"
#include "command_line_options.h"
#include "lib/nr.h"
#include <omp.h>

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

/*
   Program reads and solves a linear equation from file given as first argument.
   Input file format is described in reader.c
   First line of output contains three numbers: time spent in execution, number of iterations and the computed error of the solution.
   Second line of the output contains the solution vector
 */



void print_double(double *tab, int n) {
  for (int i = 1; i <= n; ++i) {
    printf("%f ", tab[i]);
  }
  printf("\n");
}


void main (int argc, char **argv) {
  LinearEquation leq;
  Options opt = parse_command_line_arguments(argc, argv);

  // record time
  time_t begin, end;
  double time_spent;
  begin = time(NULL);

  leq = read_linear_equation_from_file(opt.file_name);

  if (opt.use_conjugate_gradient) {
    int iterations;
    double error;
    /* Solves A · x = b for x[1..n], given b[1..n], by the iterative biconjugate gradient method. On input x[1..n] should be set to an initial guess of the solution (or all zeros); itol is 1,2,3, or 4, specifying which convergence test is applied (see text); itmax is the maximum number of allowed iterations; and tol is the desired convergence tolerance. On output, x[1..n] is reset to the improved solution, iter is the number of iterations actually taken, and err is the estimated error. The matrix A is referenced only through the user-supplied routines atimes, which computes the product of either A or its transpose on a vector; and asolve, which solves A · x = b or A' · x = b for some preconditioner matrix A (possibly the trivial diagonal part of A). */
    linbcg(leq.sa, leq.ija, leq.n, leq.b, leq.x, 1,
           opt.tolerance, opt.max_iterations, &iterations, &error);

    // record time
    end = time(NULL);
    time_spent = difftime(end, begin);

    // print out results
    printf("%f %f %d\n", time_spent, compute_error(leq), iterations);
    print_double(leq.x, leq.n);
  } else {
    /* Linear equation solution by Gauss-Jordan elimination, equation (2.1.1) above. a[1..n][1..n] is the input matrix. b[1..n][1..m] is input containing the m right-hand side vectors. On output, a is replaced by its matrix inverse, and b is replaced by the corresponding set of solution vectors. */

    // give it a copy of the b vector so that it doesn't mutate!
    double **b = (double**) malloc(2 * sizeof(double*));
    double *b_copy = (double*) malloc((leq.n + 1) * sizeof(double));
    memcpy(b_copy, leq.b, leq.n * sizeof(double));
    b[0] = NULL;
    b[1] = b_copy;

    gaussj(leq.A, leq.n, b, 1);

    // copy result back
    for (int i = 1; i <= leq.n; i++)
      leq.x[i] = b_copy[i];

    free(b_copy);

    // record time
    end = time(NULL);
    time_spent = difftime(end, begin);

    printf("%f %f\n", time_spent, compute_error(leq));
    print_double(leq.x, leq.n);
  }


  // free memory
  free_linear_equation(leq);
}
