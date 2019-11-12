#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, int *argv[])
{
    if(argc>2)
    {
    FILE *f=fopen(argv[1],"r");
    FILE *g=fopen(argv[2],"w");
    char *buf=(char *)malloc(20*sizeof(char));
    fscanf(f,"%s",buf);
    fscanf(f,"%s",buf);
    int maxNode=-1;
    int node;
    while(fscanf(f," %d",&node)==1)
    {
        if(node>maxNode)
            maxNode=node;
    }
    int **arcs;
    maxNode++;
    arcs=(int **)calloc(maxNode,sizeof(int *));
    int i;
    for(i=0;i<maxNode;i++)
        arcs[i]=(int *)calloc(maxNode,sizeof(int));
    int x,y;
    fscanf(f,"%s",buf);
    fscanf(f,"%s",buf);
    while(fscanf(f," (%d %d)",&x,&y)==2)
        arcs[x][y]=1;
    int *sub=(int *)malloc(30*sizeof(int));
    int nr=0;
    fscanf(f,"%s",buf);
    fscanf(f,"%s",buf);
    while(fscanf(f," %d",&node)==1)
    {
        sub[nr]=node;
        nr++;
    }
    int j,k;
    //printMatrix(arcs,maxNode);
    fprintf(g,"V' arcs ");
    for(i=0;i<maxNode;i++)
    {
        for(j=0;j<maxNode;j++)
        {
            if(findTwoNodes(sub,nr,i,j)==1 && arcs[i][j]==1)
                fprintf(g,"(%d %d) ",i,j);
        }
    }
    }
    else
        printf("\nNOT ENOUGH ARGUMETS\n");
    return 0;
}
