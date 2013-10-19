#include <math.h>

void sprsin(double **a, int n, float thresh, unsigned long nmax, double sa[],
	unsigned long ija[])
{
	void nrerror(char error_text[]);
	int i,j;
	unsigned long k;

	for (j=1;j<=n;j++) sa[j]=a[j][j];
	ija[1]=n+2;
	k=n+1;
	for (i=1;i<=n;i++) {
		for (j=1;j<=n;j++) {
			if (fabs(a[i][j]) >= thresh && i != j) {
				if (++k > nmax) nrerror("sprsin: nmax too small");
				sa[k]=a[i][j];
				ija[k]=j;
			}
		}
		ija[i+1]=k+1;
	}
}

void sprsin2(double **a, int n, double thresh, unsigned long nmax, double sa[],
	unsigned long ija[])
{
	void nrerror(char error_text[]);
	int i,j;
	unsigned long k;

	for (j=1;j<=n;j++) sa[j]=a[j][j];
	ija[1]=n+2;
	k=n+1;
	for (i=1;i<=n;i++) {
		for (j=1;j<=n;j++) {
			if (fabs(a[i][j]) >= thresh && i != j) {
				if (++k > nmax) nrerror("sprsin: nmax too small");
				sa[k]=a[i][j];
				ija[k]=j;
			}
		}
		ija[i+1]=k+1;
	}
}
/* (C) Copr. 1986-92 Numerical Recipes Software . */
