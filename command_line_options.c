#include <stdlib.h>
#include <stdio.h>
#include <argtable2.h>

#include "command_line_options.h"

// those are overriden by command line options
Options default_options() {
  Options opts;
  opts.max_iterations = 10000;
  opts.tolerance = 0.01;
  opts.use_conjugate_gradient = 0;

  return opts;
}

Options parse_command_line_arguments(int argc, char **argv) {

  struct arg_lit *conjugate_gradient =
    arg_lit0("g", NULL, "use conjugate gradient method, gauss-jordan is default");
  struct arg_int *max_iterations =
    arg_int0("i", "max-iterations", "max_iterations", "maximum number of iterations");
  struct arg_dbl *tolerance =
    arg_dbl0("t", "tolerance", "tolerance", "tolerance to be archieved");
  struct arg_lit *help =
    arg_lit0("h", "help", "print help");
  struct arg_file *file =
    arg_file1("f", "file", "file path", "file containing lienar equation");
  struct arg_end *end = arg_end(20);
  const char* progname = argv[0];

  void *argtable[] = {
    max_iterations, tolerance, file, conjugate_gradient, help, end
  };

  int nerrors = arg_parse(argc, argv, argtable);

  if (help->count > 0 || argc == 1) {
    printf("Usage: %s", progname);
    arg_print_syntax(stdout, argtable, "\n");
    arg_print_glossary(stdout,argtable,"  %-25s %s\n");
    exit(0);
  }

  if (nerrors > 0) {
    arg_print_errors(stdout, end, progname);
    printf("Try '%s --help' for more information.\n",progname);
    exit(0);
  }

  Options opts = default_options();

  opts.file_name = file->filename[0];

  if (conjugate_gradient->count > 0)
    opts.use_conjugate_gradient = 1;

  if (max_iterations->count > 0)
    opts.max_iterations = max_iterations->ival[0];

  if (tolerance->count > 0)
    opts.tolerance = tolerance->dval[0];

  arg_freetable(argtable, sizeof(argtable)/sizeof(argtable[0]));

  return opts;
}
