typedef struct _Options {
  int max_iterations;
  double tolerance;
  const char *file_name;
  int use_conjugate_gradient;
} Options;


Options default_options();
Options parse_command_line_arguments(int, char**);
