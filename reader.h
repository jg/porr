typedef struct _LinearEquation {
  double **A;
  int n; // dimensions of A matrix
  double *b;
  double *x; // solution, why not
} LinearEquation;


LinearEquation read_linear_equation_from_file(char*);

void free_linear_equation(LinearEquation);

void print_linear_equation(LinearEquation);
