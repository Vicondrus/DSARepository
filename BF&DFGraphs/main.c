#include <stdio.h>
#include <stdlib.h>

int main(int argc, int *argv[])
{
    if (argc>2)
    {

    FILE *f=fopen(argv[1],"r");
    FILE *g=fopen(argv[2],"w");
    int nodes;
    char *buf=(char *)malloc(20*sizeof(char));
    char aux;
    fscanf(f,"%s %d",buf,&nodes);
    fscanf(f,"%c",&aux);
    fscanf(f,"%s",buf);
    int **arcs;
    arcs=(int **)calloc(nodes,sizeof(int *));
    int i;
    for(i=0;i<nodes;i++)
        arcs[i]=(int *)calloc(nodes,sizeof(int));
    int x,y;
    while(fscanf(f," (%d %d)",&x,&y)==2)
    {
        arcs[x][y]=1;
        arcs[y][x]=1;
    }
    int *vis=(int *)calloc(nodes,sizeof(int));
    bfs(nodes,arcs,1,g);
    dfs(nodes,arcs,1,vis,g);

    }
    else
        printf("\nNOT ENOUGH ARGUMENTS\n");
    return 0;
}
