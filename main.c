#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "linear_equation.h"
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
    run_linbcg(&leq, opt.tolerance, opt.max_iterations);

    // record time
    end = time(NULL);
    time_spent = difftime(end, begin);

    // print out results
    printf("%f %f\n", time_spent, compute_error(leq));
    // print_double(leq.x, leq.n);
  } else {
    run_gaussj(&leq);

    // record time
    end = time(NULL);
    time_spent = difftime(end, begin);

    printf("%f %f\n", time_spent, compute_error(leq));
    // print_double(leq.x, leq.n);
  }

  // free leq memory
  free_linear_equation(leq);
}
