#include <stdio.h>
#include <stdlib.h>

#define INF 10000

typedef struct n
{
    int cfg[4][4];
    int spaceRow;
    int spaceCol;
    int mov;
    struct n *parent, *prev, *next;
    int cost;
} NodeT;

typedef struct l
{
    NodeT *first, *last;
} ListT;

ListT *createList()
{
    ListT *list=(ListT *)malloc(sizeof(ListT));
    list->first=list->last=NULL;
    return list;
}

void insert(ListT *list, NodeT *node)
{
    if(list->first==NULL)
    {
        list->first=list->last=node;
        return;
    }
    else
    {
        list->first->prev=node;
        node->next=list->first;
        list->first=node;
        return;
    }
}

int getCost(int sol[4][4], NodeT *node)
{
    int i,j,cost=0;
    for (i=0; i<4; i++)
        for(j=0; j<4; j++)
            if(node->cfg[i][j]!=sol[i][j])
                cost++;
    return cost;
}

NodeT *getBest(ListT *list)
{
    NodeT *j=(NodeT *)malloc(sizeof(NodeT));
    int minc=INF;
    NodeT *walker=list->first;
    j=NULL;
    while(walker!=NULL)
    {
        if(walker->cost<minc)
        {
            j=walker;
            if(walker->prev)
                walker->prev->next=walker->next;
            if(walker->next)
                walker->next->prev=walker->prev;
            minc=j->cost;
        }
        walker=walker->next;
    }
    return j;
}

NodeT *getNextCfg(NodeT *i, int k,int sol[4][4])
{
    NodeT *j=(NodeT *)malloc(sizeof(NodeT));
    j->next=j->prev=NULL;
    j->parent=i;
    j->spaceCol=i->spaceCol;
    j->spaceRow=i->spaceRow;
    int m,l;
    for(m=0; m<4; m++)
        for(l=0; l<4; l++)
            j->cfg[m][l]=i->cfg[m][l];
    if(k==0)
    {
        if(i->spaceCol>0 && i->mov!=1)
        {
            j->cfg[j->spaceRow][j->spaceCol]=j->cfg[j->spaceRow][j->spaceCol-1];
            j->cfg[j->spaceRow][j->spaceCol-1]=0;
            j->spaceCol--;
            j->cost=getCost(sol,j);
            j->mov=k;
        }
        else
        {
            free(j);
            j=NULL;
        }
    }
    if(k==1)
    {
        if(i->spaceCol<3 && i->mov!=0)
        {
            j->cfg[j->spaceRow][j->spaceCol]=j->cfg[j->spaceRow][j->spaceCol+1];
            j->cfg[j->spaceRow][j->spaceCol+1]=0;
            j->spaceCol++;
            j->cost=getCost(sol,j);
            j->mov=k;
        }
        else
        {
            free(j);
            j=NULL;
        }
    }
    if(k==2)
    {
        if(i->spaceRow>0 && i->mov!=3)
        {
            j->cfg[j->spaceRow][j->spaceCol]=j->cfg[j->spaceRow-1][j->spaceCol];
            j->cfg[j->spaceRow-1][j->spaceCol]=0;
            j->spaceRow--;
            j->cost=getCost(sol,j);
            j->mov=k;
        }
        else
        {
            free(j);
            j=NULL;
        }
    }
    if(k==3)
    {
        if(i->spaceRow<3 && i->mov!=2)
        {
            j->cfg[j->spaceRow][j->spaceCol]=j->cfg[j->spaceRow+1][j->spaceCol];
            j->cfg[j->spaceRow+1][j->spaceCol]=0;
            j->spaceRow++;
            j->cost=getCost(sol,j);
            j->mov=k;
        }
        else
        {
            free(j);
            j=NULL;
        }
    }
    return j;
}

void printSol(NodeT *node)
{
    int i,j;
    if(node==NULL)
        return;
    printSol(node->parent);
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            printf("%d ",node->cfg[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    FILE *f=fopen("data.txt","r");
    NodeT *root=(NodeT *)malloc(sizeof(NodeT));
    root->next=root->parent=root->prev=NULL;
    int i,j;
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            fscanf(f,"%d ",&root->cfg[i][j]);
            if(root->cfg[i][j]==0)
            {
                root->spaceRow=i;
                root->spaceCol=j;
            }

        }
    int sol[4][4];
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
            fscanf(f,"%d ",&sol[i][j]);
    root->cost=getCost(sol,root);
    ListT *liveNodes=createList();
    insert(liveNodes,root);
    ListT *deadNodes=createList();
    while(1)
    {
        NodeT *i=getBest(liveNodes);
        if(i==NULL)
        {
            printf("\nNo Solution\n");
            break;
        }
        int k;
        insert(deadNodes,i);
        for(k=0; k<4; k++)
        {
            NodeT *j=getNextCfg(i,k,sol);
            if(j==NULL)
                continue;
            if(j->cost==0)
            {
                printSol(j);
                exit(0);
            }
            insert(liveNodes,j);
        }
    }
    return 0;
}
