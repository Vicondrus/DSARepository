#include <stdio.h>
#include <stdlib.h>

typedef struct n
{
    int cfg[4][4];
    int cost;
    int mov;
    int blankRow;
    int blankCol;
    struct n *next, *prev, *parent;
}NodeT;

typedef struct l
{
    NodeT *first, *last;
}ListT;

ListT *createList()
{
    ListT *list=(ListT *)malloc(sizeof(ListT));
    list->first=list->last=NULL;
    return list;
}

void *insert(ListT *list, NodeT *node)
{
    if(list->first==NULL)
    {
        list->first=list->last=node;
        return;
    }
    if(list->first->cost>node->cost)
    {
        list->first->prev=node;
        node->next=list->first;
        node->prev=NULL;
        list->first=node;
        return;
    }
    if(list->last->cost<node->cost)
    {
        list->last->next=node;
        node->next=NULL;
        node->prev=list->last;
        list->last=node;
        return;
    }
    NodeT *walker=list->first;
    while(walker->next!=NULL)
    {
        if(walker->next->cost>node->cost)
            break;
        walker=walker->next;
    }
    if(walker->next!=NULL)
        walker->next->prev=node;
    node->next=walker->next;
    node->prev=walker;
    walker->next=node;
    return;
}

int getCost(int us[4][4], int s[4][4])
{
    int cost,i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(us[i][j]!=s[i][j])
                cost++;
    return cost;
}

NodeT *getFirst(ListT *list)
{
    NodeT *node=list->first;
    if(list->first)
    {
        if(list->first->next)
            list->first->next->prev=NULL;
        list->first=list->first->next;
    }
    return node;
}

NodeT *getNextCfg(NodeT *i, int k, int sol[4][4])
{
    NodeT *j=(NodeT *)malloc(sizeof(NodeT));
    j->parent=i;
    j->next=j->prev=NULL;
    int l,m;
    for(l=0;l<4;l++)
        for(m=0;m<4;m++)
            j->cfg[l][m]=i->cfg[l][m];
    if(k==0)
    {
        if(i->blankCol>0 && i->mov!=3-k)
        {
            j->blankCol=i->blankCol-1;
            j->blankRow=i->blankRow;
            j->cfg[i->blankRow][i->blankCol]=j->cfg[i->blankRow][i->blankCol-1];
            j->cfg[i->blankRow][i->blankCol-1]=0;
            j->mov=k;
            j->cost=getCost(j->cfg,sol);
            return j;
        }
    }
    else if(k==1)
    {
        if(i->blankRow>0 && i->mov!=3-k)
        {
            j->blankRow=i->blankRow-1;
            j->blankCol=i->blankCol;
            j->cfg[i->blankRow][i->blankCol]=j->cfg[i->blankRow-1][i->blankCol];
            j->cfg[i->blankRow-1][i->blankCol]=0;
            j->mov=k;
            j->cost=getCost(j->cfg,sol);
            return j;
        }
    }
    else if(k==2)
    {
        if(i->blankRow<4 && i->mov!=3-k)
        {
            j->blankRow=i->blankRow+1;
            j->blankCol=i->blankCol;
            j->cfg[i->blankRow][i->blankCol]=j->cfg[i->blankRow+1][i->blankCol];
            j->cfg[i->blankRow+1][i->blankCol]=0;
            j->mov=k;
            j->cost=getCost(j->cfg,sol);
            return j;
        }
    }
    else if(k==3)
    {
        if(i->blankCol<4 && i->mov!=3-k)
        {
            j->blankCol=i->blankCol+1;
            j->blankRow=i->blankRow;
            j->cfg[i->blankRow][i->blankCol]=j->cfg[i->blankRow][i->blankCol+1];
            j->cfg[i->blankRow][i->blankCol+1]=0;
            j->mov=k;
            j->cost=getCost(j->cfg,sol);
            return j;
        }
    }
    return NULL;
}

void printSol(NodeT *node)
{
    if(node==NULL)
        return;
    printSol(node->parent);
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
            printf("%2d ",node->cfg[i][j]);
        printf("\n");
    }
    printf("\n------------\n");
}

int main()
{
    FILE *f=fopen("data.txt","r");
    int i,j;
    NodeT *root=(NodeT *)malloc(sizeof(NodeT));
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
        {
            fscanf(f,"%d",&root->cfg[i][j]);
            if(root->cfg[i][j]==0)
            {
                root->blankRow=i;
                root->blankCol=j;
            }
        }
    int solved[4][4];
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            fscanf(f,"%d",&solved[i][j]);
    root->cost=getCost(root->cfg,solved);
    root->mov=-1;
    root->next=root->prev=root->parent=NULL;
    ListT *liveNodes=createList();
    insert(liveNodes,root);
    ListT *deadNodes=createList();
    while(1)
    {
        NodeT *i=getFirst(liveNodes);
        if(i==NULL)
        {
            printf("\nNO SOLUTION\n");
            break;
        }
        insert(deadNodes,i);
        int k;
        for(k=0;k<4;k++)
        {
            NodeT *j=getNextCfg(i,k,solved);
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
