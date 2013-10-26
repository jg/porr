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

void print_result(LinearEquation leq, struct timeval begin, const char *method) {
  struct timeval end;
  // record time
  gettimeofday(&end, NULL);
#ifdef OPENMP
  printf("%.0f %.2f %s omp\n", timediff(begin, end),
                               compute_error(leq), method);
#else
  printf("%.0f %.2f %s no_omp\n", timediff(begin, end),
                                  compute_error(leq), method);
#endif
}


void main (int argc, char **argv) {
  LinearEquation leq;
  Options opt = parse_command_line_arguments(argc, argv);

  // record time
  struct timeval begin;
  gettimeofday(&begin, NULL);
  int time_spent; // millis

  leq = read_linear_equation_from_file(opt.file_name);

  if (opt.use_conjugate_gradient) {
    run_linbcg(&leq, opt.tolerance, opt.max_iterations);
    print_result(leq, begin,"conjugate_gradient");
  } else {
    run_gaussj(&leq);
    print_result(leq, begin,"gauss_jordan");
  }

  // free leq memory
  free_linear_equation(leq);
}

