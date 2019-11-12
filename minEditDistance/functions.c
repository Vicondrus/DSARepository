#include "functions.h"

int min(int i, int j, int k)
{
    if (i>j)
        if(j>k)
            return k;
        else
            return j;
    else if (i>k)
        return k;
    else
        return i;
}

int minEdit(char *str1, char *str2, int n, int m)
{
    int **C=(int **)calloc(n+1,sizeof(int *));
    int i,j;
    for (i=0; i<n+1; i++)
        C[i]=(int *)calloc(m+1,sizeof(int));
    for(i=0; i<n+1; i++)
        for(j=0; j<m+1; j++)
        {
            if(i==0)
                C[i][j]=j;
            else if(j==0)
                C[i][j]=i;
            else if(str1[i-1]==str2[j-1])
                C[i][j]=C[i-1][j-1];
            else
                C[i][j]=1+min(C[i][j-1],C[i-1][j-1],C[i-1][j]);
        }
    /*for(i=0; i<n+1; i++)
    {
        for(j=0; j<m+1; j++)
            printf("%d ",C[i][j]);
        printf("\n");
    }
    printf("\n");*/
    int aux=C[n][m];
    for (i=0; i<n+1; i++)
        free(C[i]);
    free(C);
    return aux;
}
