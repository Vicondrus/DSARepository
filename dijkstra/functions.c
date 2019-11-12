#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


void printMatrix(int **matrix, int size)
{
    int i,j;
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
}

int findInAr(int node, int *parent, int maxNode)
{
    int i;
    for(i=0; i<maxNode; i++)
        if(parent[i]==node)
            return i;
    return -1;
}

void printPath(int source, int *parent, int maxNode, int dest, int **arcs,FILE *g)
{
    if (parent[dest]==-1)
    {
        fprintf(g,"No path found between %d and %d",source, dest);
        return;
    }
    int *path=(int *)calloc(maxNode,sizeof(int));
    int *cost=(int *)calloc(maxNode,sizeof(int));
    int sum=0;
    int i=0;
    while(dest!=source)
    {
        cost[i]=arcs[parent[dest]][dest];
        path[i++]=dest;
        dest=parent[dest];
    }
    path[i]=source;
    int j;
    for(j=i-1; j>=0; j--)
        sum+=cost[j];
    fprintf(g,"%d ",sum);
    for(j=i; j>=1; j--)
        fprintf(g,"%d-",path[j]);
    fprintf(g,"%d",path[0]);
    fprintf(g," (");
    for(j=i-1; j>=1; j--)
        fprintf(g,"%d,",cost[j]);
    fprintf(g,"%d",cost[0]);
    fprintf(g,")");
}

void dijkstra(int maxNodes, int source, int *S, int **arcs, int *dist,int *parent)
{
    int k, i;
    for(i=0; i<maxNodes; i++)
    {
        S[i]=0;
        dist[i]=arcs[source][i];
        if(dist[i]<INF)
            parent[i]=source;
        else
            parent[i]=-1;
    }
    S[source]=1;
    parent[source]=-1;
    dist[source]=0;
    for(i=0; i<maxNodes-1; i++)
    {
        int j, minDist=INF;
        for(j=0; j<maxNodes; j++)
            if(dist[j]<minDist && S[j]==0)
            {
                k=j;
                minDist=dist[j];
            }
        if(minDist == INF)
            return;
        S[k]=1;
        for(j=0; j<=maxNodes; j++)
            if(S[j]==0 && dist[k]+arcs[k][j]<dist[j])
            {
                dist[j]=dist[k]+arcs[k][j];
                parent[j]=k;
            }
    }
}

void dijkstraAgain(int maxNodes, int **arcs, int source, int *S, int *dist, int *parent)
{
    int i,k;
    for(i=0;i<maxNodes;i++)   ///initialize all nodes
    {
        S[i]=0;
        dist[i]=arcs[source][i];
        if(dist[i]!=INF)
            parent[i]=source;
        else
            parent[i]=-1;
    }
    S[i]=1;
    dist[source]=0;        ///initialize source
    parent[source]=-1;
    for(i=0;i<maxNodes-1;i++)
    {
        int j,minDist=INF;
        for(j=0;j<maxNodes;j++)     ///find minimum distance because of dijkstra's greed
            if(minDist>dist[j] && S[j]==0)
            {
                k=j;
                minDist=dist[j];
            }
        if(minDist==INF)   ///if no min distance, the rest is useless
            return;
        S[k]=1;
        for(j=0;j<maxNodes;j++)   ///from the node with min distance at this iteration
        {
            if(S[k]==0 && dist[k]+arcs[k][j]<dist[j])
            {
                parent[j]=k;               ///if find a path to another node which is shorter trough k, replace it
                dist[j]=dist[k]+arcs[k][j];
            }
        }
    }
}
