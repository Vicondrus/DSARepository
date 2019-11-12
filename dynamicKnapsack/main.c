#include <stdio.h>
#include <stdlib.h>

typedef struct It
{
    int weight;
    int value;
} ItemT;

int max(int i, int j)
{
    if(i>j)
        return i;
    else
        return j;
}

int knapsack(int n, int w, ItemT *items)
{
    int i, j;
    int **K=(int **)calloc(n+2,sizeof(int *));
    int **taken=(int **)calloc(n+2,sizeof(int *));
    for(i=0; i<=n; i++)
    {
        K[i]=(int *)calloc(w+2,sizeof(int *));
        taken[i]=(int *)calloc(w+2,sizeof(int *));
    }
    for(i=1; i<=n; i++)
        for(j=1; j<=w; j++)
            if(items[i].weight<j)
            {
                K[i][j]=max(K[i-1][j],items[i].value+K[i][j-items[i].weight]);
                            if(K[i-1][j]>=K[i][j])
                            taken[i][j]=0;
                            else
                            taken[i][j]=1;
            }
                    else
            {
                K[i][j]=K[i-1][j];
                taken[i][j]=0;
            }
    return K[n][w];
}

int main()
{

    return 0;
}
