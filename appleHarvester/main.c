#include <stdio.h>
#include <stdlib.h>

typedef struct ap
{
    int weight;
    int height;
}AppleT;

int maxim(int a, int b)
{
    if(a>b)
        return a;
    else
        return b;
}

int **allocMatrix(int n, int m)
{
    int **M=(int **)calloc(n,sizeof(int *));
    int i;
    for(i=0;i<n;i++)
        M[i]=(int)calloc(m,sizeof(int));
    return M;
}

void printMatrix(int n, int m, int **M)
{
    int i;
    int j;
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=m;j++)
            printf("%d ",M[i][j]);
        printf("\n");
    }
}

int apples(int x, int d, int n, AppleT *apple, int **taken)
{
    int **A=allocMatrix(n+1,d+1);
    int i,j;
    for(i=0;i<=d;i++)
    {
        A[0][i]=0;
        taken[0][i]=0;
    }
    for(i=0;i<=n;i++)
    {
        A[i][0]=0;
        taken[i][0]=0;
    }
    for(i=1;i<=n;i++)
    {
        for(j=0;j<=d;j++)
        {
            if(apple[i].height<=j)
            {
                A[i][j]=maxim(A[i-1][j],apple[i].weight+A[i-1][j-x]);
                if(A[i-1][j]>=A[i][j])
                    taken[i][j]=0;
                else
                    taken[i][j]=1;
            }
            else
            {
                A[i][j]=A[i-1][j];
                taken[i][j]=0;
            }
        }
    }
    printMatrix(n,d,A);
    printf("\n");
    printMatrix(n,d,taken);
    return A[n][d];
}

void printApples(int n, int d, int **taken, AppleT *apple)
{
    while(n>=0)
    {
        if(taken[n][d]==1)
        {
            printf("%d [%d %d]\n",n, apple[n].weight,apple[n].height);
            d==apple[n].height;
        }
        n--;
    }
    printf("\n");
}

int main()
{
    FILE *f=fopen("data.txt","r");
    int n, x, d;
    fscanf(f,"%d %d %d\n",&n,&x,&d);
    AppleT *apple=(AppleT *)calloc(n+1,sizeof(AppleT));
    int i;
    for(i=1;i<=n;i++)
        fscanf(f,"%d %d\n",&apple[i].weight,&apple[i].height);
    int *taken=allocMatrix(n+1,d+1);
    printf("%d\n",apples(x,d,n,apple,taken));
    printApples(n,d,taken,apple);
    return 0;
}
