#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 10000

int n=3;
int d[]= {0,1,2,3,4};
int S[10][10]; ///zeros

int getBestCost(int i, int j)
{
    if(i==j)
        return 0;
    if(S[i][j]!=0)
        return S[i][j];
    int bestCost=INT_MAX, bestK;
    int k;
    for(k=i; k<j; k++)
    {
        int cost=getBestCost(i,k)+getBestCost(k+1,j)+d[i]*d[k+1]*d[j+1];
        if(bestCost>cost)
        {
            bestCost=cost;
            bestK=k;
        }
    }
    S[i][j]=bestCost;
    S[j][i]=bestK;
    return bestCost;
}

void printOrder(int i, int j)
{
    if (i<j)
    {
        printOrder(i,S[j][i]);
        printOrder(S[j][i]+1,j);
        printf("%d %d\n",i,j);
    }
    else
    {
        //printf("%d %d\n",i,j);
        return;
    }
}

int main()
{
    printf("cost=%d\n",getBestCost(1,n));
    printOrder(1,n);
    return 0;
}
