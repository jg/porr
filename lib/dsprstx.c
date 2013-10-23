void dsprstx(double sa[], unsigned long ija[], double x[], double b[], unsigned long n)
{
	void nrerror(char error_text[]);
	unsigned long i,j,k;
	if (ija[1] != n+2) nrerror("mismatched vector and matrix in dsprstx");

	for (i=1;i<=n;i++) b[i]=sa[i]*x[i];
    #ifdef OPENMP
    #pragma omp parallel for shared(sa, ija, x, b, n)  private(i, k) num_threads(2)
    #endif
	for (i=1;i<=n;i++) {
		for (k=ija[i];k<=ija[i+1]-1;k++) {
			j=ija[k];
			b[j] += sa[k]*x[i];
		}
	}
}
/* (C) Copr. 1986-92 Numerical Recipes Software . */
