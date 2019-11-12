#include <stdio.h>
#include <stdlib.h>

#define INF 1000000

typedef struct n
{
    struct n *next;
    int key;
}NodeT;

typedef struct l
{
    NodeT *first,*last;
    int size;
}ListT;

ListT *initList()
{
    ListT *pNew=(ListT *)malloc(sizeof(ListT));
    pNew->first=NULL;
    pNew->last=NULL;
    pNew->size=0;
    return pNew;
}

void append(ListT *list, int key)
{
    NodeT *pNew=(NodeT *)malloc(sizeof(NodeT));
    pNew->key=key;
    pNew->next=NULL;
    if(list->first==NULL)
        list->first=pNew;
    else
        list->last->next=pNew;
    list->last=pNew;
    list->size++;
}

void printList(ListT *list)
{
    NodeT *walker=list->first;
    while(walker!=NULL)
    {
        printf("%d ",walker->key);
        walker=walker->next;
    }
    printf("\n");
}

int findKey(ListT *list, int key)
{
    NodeT *finder=list->first;
    while(finder!=NULL)
    {
        if(finder->key==key)
            return 1;
        finder=finder->next;
    }
    return INF;
}

void path(int source, int dest, ListT **list, int nodes)
{
    int *dist=(int *)calloc(nodes,sizeof(int));
    int *s=(int *)calloc(nodes,sizeof(int));
    int *parent=(int *)calloc(nodes,sizeof(int));
    int i,k,j;
    for(i=0;i<nodes;i++)
    {
        if(findKey(list[source],i)==1)
        {
            dist[i]=1;
            parent[i]=source;
        }
        else
        {
            dist[i]=INF;
            parent[i]=-1;
        }
    }
    s[source]=1;
    dist[source]=0;
    parent[source]=-1;
    for(i=0;i<nodes-1;i++)
    {
        int minDist=INF;
        for(j=0;j<nodes;j++)
            if(minDist>dist[j] && s[j]==0)
            {
                k=j;
                minDist=dist[j];
            }
        if(minDist==INF)
        {
            break;
        }
        s[k]=1;
        for(j=0;j<nodes;j++)
        {
            int arc=findKey(list[k],j);
            if(s[j]==0 && dist[k]+arc<dist[j])
            {
                dist[j]=dist[k]+1;
                parent[j]=k;
            }
        }
    }
    i=0;
    int *auxPath=(int *)calloc(nodes,sizeof(int));
    if(parent[dest]==-1)
    {
        printf("No path found\n");
        return;
    }
    while(parent[dest]!=-1)
    {
        auxPath[i++]=dest;
        dest=parent[dest];
    }
    auxPath[i]=source;
    for(j=i;j>=0;j--)
        printf("%d ",auxPath[j]);
}

int main()
{
    int x, y;
    FILE *f=fopen("data.txt","r");
    fscanf(f,"V nodes");
    int nodes=-1;
    while(fscanf(f," %d",&x)==1)
        if(nodes<x)
            nodes=x;
    nodes++;
    ListT **list=(ListT **)calloc(nodes,sizeof(ListT *));
    int i;
    for(i=0;i<nodes;i++)
        list[i]=initList();
    fscanf(f,"\nV arcs");
    while(fscanf(f," (%d %d)",&x,&y)==2)
    {
        append(list[x],y);
    }
//    for(i=0;i<nodes;i++)
//    {
//        printf("%d ",i);
//        printList(list[i]);
//    }
    path(1,2,list,nodes);
    return 0;
}
