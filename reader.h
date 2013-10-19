typedef struct _LinearEquation {
  double **A;
  int n; // dimensions of A matrix
  double *b;
  double *x; // solution, why not
  double *sa; // sparse representation of A, used by linbcg
  unsigned long* ija; // indexes of sparse A representation, used by linbcg
  long sparse_n; // size of sa
} LinearEquation;


LinearEquation read_linear_equation_from_file(char*);

void free_linear_equation(LinearEquation);

void print_linear_equation(LinearEquation);
