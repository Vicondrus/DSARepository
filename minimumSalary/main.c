#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    if(argc>2)
    {
    FILE *f=fopen(argv[1],"r");
    FILE *g=fopen(argv[2],"w");
    int n;
    fscanf(f,"%d\n",&n);
    int *e=(int *)calloc(n+1,sizeof(int));
    int *c=(int *)calloc(n+1,sizeof(int));
    int **M=(int **)calloc(n+1,sizeof(int *));
    int i;
    for (i=0;i<n;i++)
        M[i]=(int *)calloc(n+1,sizeof(int));
    for(i=1; i<=n; i++)
        fscanf(f,"%d %d\n",&e[i],&c[i]);
    int rez=e[n]+minSal(e,c,n-1,(n/2)-1,M);
    int j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            fprintf(g,"%d ",M[i][j]);
        fprintf(g,"\n");
    }
    fprintf(g,"\n%d\n",rez);
    }
    else
        printf("\nNOT ENOUGH ARUMENTS\n");
    return 0;
}
