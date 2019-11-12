#include <stdio.h>
#include <stdlib.h>

#define INF 1000000

void floyd(int nodes, int **A, int **p)
{
    int i,j,k;
    for(k=0; k<nodes; k++)
        for(i=0; i<nodes; i++)
            for(j=0; j<nodes; j++)
                if(A[i][k]+A[k][j]<A[i][j])
                {
                    A[i][j]=A[i][k]+A[k][j];
                    p[i][j]=k;
                }
}

void path(int i, int j, int **p)
{
    int k;
    k=p[i][j];
    if (k!=0)
    {
        path(i,k,p);
        printf("%d ",k);
        path(k,j,p);
    }
}

int main()
{
    FILE *f=fopen("data.txt","r");
    int maxNode=-1;
    int x,y,c;
    while(fscanf(f,"%d,%d=%d",&x,&y,&c)==3)
    {
        if(x>maxNode)
            maxNode=x;
        if(y>maxNode)
            maxNode=y;
    }
    rewind(f);
    int **arcs, **A, **p;
    maxNode++;
    arcs=(int **)calloc(maxNode,sizeof(int *));
    A=(int **)calloc(maxNode,sizeof(int *));
    p=(int **)calloc(maxNode,sizeof(int *));
    int i;
    for(i=0; i<maxNode; i++)
    {
        arcs[i]=(int *)calloc(maxNode,sizeof(int));
        A[i]=(int *)calloc(maxNode,sizeof(int));
        p[i]=(int *)calloc(maxNode,sizeof(int));
    }
    int j;
    for(i=0; i<maxNode; i++)
        for(j=0; j<maxNode; j++)
            if(i==j)
                arcs[i][j]=A[i][j]=0;
            else
                arcs[i][j]=A[i][j]=INF;
    while(fscanf(f,"%d,%d=%d",&x,&y,&c)==3)
    {
        arcs[x][y]=A[x][y]=c;
        // arcs[y][x]=c;
    }
    floyd(maxNode,A,p);
    for(i=0; i<maxNode; i++)
        for(j=0; j<maxNode; j++)
            if(i!=j && A[i][j]<INF)
            {
                printf("%d ",i);
                path(i,j,p);
                printf("%d  ---->  %d\n",j,A[i][j]);
            }
    return 0;
}
