#include <stdio.h>
#include <stdlib.h>

int *colour(int **A, int n)
{
    int *colours=(int *)calloc(n+2,sizeof(int));
    int i,c=1;
    for(i=1; i<=n; i++)
    {
        int j, k=1;
        for(j=1; j<=n; j++)
        {
            if(A[i][j]==1)
            {
                if(colours[j]==k)
                    k++;
                if(k>c)
                    c++;
            }
        }
        colours[i]=k;
    }
    colours[0]=c;
    return colours;
}

void printMatrix(int **A, int n)
{
    int i,j;
    for (i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            printf("%d ",A[i][j]);
        printf("\n");
    }
}

int main()
{
    FILE *f=fopen("data.txt","r");
    int n,x,y;
    fscanf(f,"%d\n",&n);
    int **A=(int **)calloc(n+2,sizeof(int *));
    int i;
    for(i=0; i<=n; i++)
        A[i]=(int *)calloc(n+2,sizeof(int));
    while(fscanf(f,"%d %d\n",&x,&y)==2)
    {
        A[x][y]=1;
        A[y][x]=1;
    }
    int *colours=colour(A,n);
    //printMatrix(A,n);
    printf("%d\n",colours[0]);
    for(i=1; i<=n; i++)
        printf("%d ",colours[i]);
    return 0;
}
