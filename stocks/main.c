#include <stdio.h>
#include <stdlib.h>
#include "stocks.h"

int main(int argc, int *argv[])
{
    if(argc>2)
    {
    FILE *f=fopen(argv[1],"r");
    FILE *g=fopen(argv[2],"w");
    int n;
    fscanf(f,"%d",&n);
    double *A=(int *)malloc(n*sizeof(double));
    int i;
    for(i=0;i<n;i++)
        fscanf(f,"%lf",&A[i]);
    double x=profit(A,0,n-1);
    fprintf(g,"%lf\n",x);
    }
    else
        printf("\nNEED MORE ARGUMENTS\n");
    return 0;
}
