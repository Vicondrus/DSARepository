#include "functions.h"

int min(int i, int j)
{
    if(i>j)
        return j;
    else
        return i;
}

int minSal(int *e, int *c, int i, int j, int **f)
{
        if(i==1 && j==0)
            return c[1];
        if((i-j)<j)
            return INF;
        if(f[i][j]!=0)
            return f[i][j];
        int minn=min(minSal(e,c,i-1,j-1,f)+e[i],minSal(e,c,i-1,j,f)+c[i]);
        f[i][j]=minn;
        return minn;
}
