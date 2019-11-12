#include <stdio.h>
#include <stdlib.h>

#define INF 100000

int getBest(int S[10][10], int n, int d[10], int i, int j)
{
    if(i==j)
        return 0;
    if(S[i][j]!=0)
        return S[i][j];
    int bestCost=INF;
    int bestK;
    int k;
    for(k=i;k<j;k++)
    {
        int cost=getBest(S,n,d,i,k)+getBest(S,n,d,k+1,j)+d[i]*d[k+1]*d[j+1];
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

int printSol(int S[10][10], int i, int j)
{
    if(i<j)
    {
        printSol(S,i,S[j][i]);
        printSol(S,S[j][i]+1,j);
        printf("%d %d\n",i,j);
    }
    return;
}

int main()
{
    int n, d[10];
    FILE *f=fopen("data.txt","r");
    fscanf(f,"%d ",&n);
    int i;
    for(i=1;i<=n+1;i++)
        fscanf(f,"%d ",&d[i]);
    int j;
    int S[10][10];
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            S[i][j]=0;
    int rez=getBest(S,n,d,1,n);
    printf("%d \n",rez);
    printSol(S,1,n);
    return 0;
}
