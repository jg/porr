typedef struct _LinearEquation {
  float **A;
  int n; // dimensions of A matrix
  float *b;
} LinearEquation;


LinearEquation read_linear_equation_from_file(char*);

void free_linear_equation(LinearEquation);

void print_linear_equation(LinearEquation);
