#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int findTwoNodes(int *sub, int nr ,int i ,int j)
{
    int k;
    int ok=-1;
    for(k=0;k<nr;k++)
        if(sub[k]==i || sub[k]==j)
            ok++;
    return ok;
}

void printMatrix(int **matrix, int size)
{
    int i,j;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
}
