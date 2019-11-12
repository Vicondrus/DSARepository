#include <stdio.h>
#include <stdlib.h>

void printInverted(int source, int dest, int *parents)
{
    if(dest==source)
        printf("% ",source);
    else
        printInverted(source,parents[dest],parents);
    printf("%d ",dest);
}

void pathFinder(int source, int dest, int **arcs, int maxNode)
{
    int *queue=(int *)calloc(maxNode+1,sizeof(int));
    int *parents=(int *)calloc(maxNode+1,sizeof(int));
    int *vis=(int *)calloc(maxNode+1,sizeof(int));
    int s=0,e=0;
    vis[source]=1;
    queue[e++]=source;
    while(s<e)
    {
        int i;
        for(i=0; i<=maxNode; i++)
            if(vis[i]==0 && arcs[queue[s]][i]==1)
            {
                queue[e++]=i;
                vis[i]=1;
                parents[i]=queue[s];
            }
        s++;
    }
    if(parents[dest]==0)
        printf("\nNo path found\n");
    else
        printInverted(source,dest,parents);

}

int main()
{
    FILE *f=fopen("data.txt","r");
    char *s=(char *)malloc(200*sizeof(char));
    fscanf(f,"%s",s);
    fscanf(f,"%s",s);
    int y,x, maxNode=-1;
    while(fscanf(f,"%d ",&x)==1)
    {
        if(x>maxNode)
            maxNode=x;
    }
    int **arcs=(int **)calloc(maxNode+2,sizeof(int *));
    int i;
    for(i=0; i<=maxNode; i++)
        arcs[i]=(int *)calloc(maxNode+2,sizeof(int));
    fscanf(f,"%s",s);
    fscanf(f,"%s",s);
    while (fscanf(f," (%d %d)",&x,&y)==2)
    {
        arcs[x][y]=1;
    }
    pathFinder(1,6,arcs,maxNode);
    return 0;
}
