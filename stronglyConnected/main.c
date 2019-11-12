#include <stdio.h>
#include <stdlib.h>

void bfs(int nodes, int **arcs, int source,int *visited)
{
    int *vis=(int *)calloc(nodes,sizeof(int));
    vis[source]=1;
    int *queue=(int *)calloc(nodes,sizeof(int));
    int beg=0,end=0;
    queue[end++]=source;
    visited[source]++;
    while(end>beg)
    {
        int i;
        printf("%d ",queue[beg]);
        for(i=0; i<nodes; i++)
            if(vis[i]==0 && arcs[queue[beg]][i]==1)
            {
                queue[end++]=i;
                vis[i]=1;
                visited[i]++;
            }
        beg++;
    }
    printf("\n");
}

int main()
{
    FILE *f=fopen("data.txt","r");
    int x, y;
    fscanf(f,"V nodes");
    int nodes=-1;
    int *visited;
    int nodesaux=0;
    while(fscanf(f," %d",&x)==1)
    {
        if(nodes<x)
            nodes=x;
        nodesaux++;
    }
    nodes++;
    visited=(int *)calloc(nodes,sizeof(int));
    int i;
    for(i=0; i<nodes; i++)
        visited[i]=-1;
    rewind(f);
    fscanf(f,"V nodes");
    while(fscanf(f," %d",&x)==1)
    {
        visited[x]=0;
    }
    fscanf(f,"\nV arcs");
    int **arcs;
    arcs=(int **)calloc(nodes,sizeof(int *));
    for(i=0; i<nodes; i++)
        arcs[i]=(int *)calloc(nodes,sizeof(int));
    while(fscanf(f," (%d %d)",&x,&y)==2)
    {
        arcs[x][y]=1;
    }
    for(i=0; i<nodes; i++)
    {
        if(visited[i]>-1)
            bfs(nodes,arcs,i,visited);
    }
    int ok=1;
    for(i=0; i<nodes; i++)
        if(visited[i]<nodesaux && visited[i]!=-1)
            ok=0;
    if(ok==0)
        printf("no");
    else
        printf("yes");
    return 0;
}
