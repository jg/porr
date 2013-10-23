#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

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

// returns difference in seconds
double timediff(struct timeval start, struct timeval end) {
  return ((end.tv_sec * 1000 + end.tv_usec/1000) -
          (start.tv_sec * 1000 + start.tv_usec/1000));
}

void main (int argc, char **argv) {
  LinearEquation leq;
  Options opt = parse_command_line_arguments(argc, argv);

  // record time
  struct timeval begin, end;
  gettimeofday(&begin, NULL);
  int time_spent; // millis

  leq = read_linear_equation_from_file(opt.file_name);

  if (opt.use_conjugate_gradient) {
    run_linbcg(&leq, opt.tolerance, opt.max_iterations);

    // record time
    gettimeofday(&end, NULL);

    // print out results
    printf("%.0f %.2f\n", timediff(begin, end), compute_error(leq));
  } else {
    run_gaussj(&leq);

    // record time
    gettimeofday(&end, NULL);

    printf("%.0f %.2f\n", timediff(begin, end), compute_error(leq));
  }

  // free leq memory
  free_linear_equation(leq);
}

