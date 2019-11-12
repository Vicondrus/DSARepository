#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

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

void bfs(int nodes, int **arcs, int startNode,FILE *g)
{
    int *vis=(int *)calloc(nodes,sizeof(int));     ///unvisited by default
    int *queue=(int *)calloc(nodes,sizeof(int));
    int i;
    int s=0,e=0;
    queue[s]=startNode;
    vis[startNode]=VISITED;
    while(s<=e)
    {
        for(i=0;i<nodes;i++)
            if(arcs[i][queue[s]]==1 && vis[i]==UNVISITED)
            {
                vis[i]=VISITED;
                queue[++e]=i;
            }
        fprintf(g,"%d ",queue[s]);
        s++;
    }
    fprintf(g,"\n");
}

int dfs(int nodes, int **arcs, int crtNode, int *vis,FILE *g)
{
    int i;
    vis[crtNode]=VISITED;
    fprintf(g,"%d ",crtNode);
    for(i=0;i<nodes;i++)
        if(arcs[crtNode][i] && vis[i]==UNVISITED)
                dfs(nodes,arcs,i,vis,g);
}
