#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, int *argv[])
{
    FILE *f=fopen(argv[1],"r");
    FILE *g=fopen(argv[2],"w");
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
    int **arcs;
    maxNode++;
    arcs=(int **)calloc(maxNode,sizeof(int *));
    int i;
    for(i=0; i<maxNode; i++)
        arcs[i]=(int *)calloc(maxNode,sizeof(int));
    int j;
    for(i=0; i<maxNode; i++)
        for(j=0; j<maxNode; j++)
            if(i==j)
                arcs[i][j]=0;
            else
                arcs[i][j]=INF;
    while(fscanf(f,"%d,%d=%d",&x,&y,&c)==3)
    {
        arcs[x][y]=c;
       // arcs[y][x]=c;
    }
    //printMatrix(arcs,maxNode);
    for(i=0; i<maxNode; i++)
    {
        for(j=i+1; j<maxNode; j++)
        {
            int *dist=(int *)calloc(maxNode,sizeof(int));
            int *parent=(int *)calloc(maxNode,sizeof(int));
            int *S=(int *)calloc(maxNode,sizeof(int));
            dijkstra(maxNode,i,S,arcs,dist,parent);
//    for(i=0;i<maxNode;i++)
//        printf("%d ",parent[i]);
//    printf("\n");
            printPath(i,parent,maxNode,j,arcs,g);
            fprintf(g,"\n");
        }
    }
    return 0;
}
