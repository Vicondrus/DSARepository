#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n=5;


typedef struct n
{
    char cfg[50];
    int spacePos;
    int cost;
    struct n *next, *prev, *parent;
} NodeT;

typedef struct l
{
    NodeT *first;
    NodeT *last;
} ListT;

ListT *createList()
{
    ListT *list=(ListT *)malloc(sizeof(ListT));
    list->first=list->last=NULL;
}

int getCost(char *cfg, int n)
{
    int cost=n;
    int ok=-n+1;
    int i;
    for(i=0; i<2*n+1; i++)
    {
        if(cfg[i]=='b')
            ok++;
        if(cfg[i]=='a' && ok==1)
            cost--;
    }
    return cost;
}

void insert(NodeT *node, ListT *list)
{
    if(list->first==NULL)
    {
        list->first=list->last=node;
        return;
    }
    if(node->cost<list->first->cost)
    {
        node->next=list->first;
        node->prev=NULL;
        list->first->prev=node;
        list->first=node;
        return;
    }
    if(node->cost>list->last->cost)
    {
        node->next=NULL;
        node->prev=list->last;
        list->last->next=node;
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
    if(walker->next)
        walker->next->prev=node;
    node->next=walker->next;
    walker->next=node;
    node->prev=walker;
    return;
}

NodeT *getNode(ListT *list)
{
    NodeT *node=list->first;
    list->first=list->first->next;
    if(list->first)
        list->first->prev=NULL;
    node->next=node->prev=NULL;
    return node;
}

void printSol(NodeT *p)
{
    if(p==NULL)
        return;
    printSol(p->parent);
    printf("%s\n",p->cfg);

}

NodeT *getNextCfg(NodeT *i, int k)
{
    NodeT *j=(NodeT *)malloc(sizeof(NodeT));
    j->next=j->prev=NULL;
    j->parent=i;
    strcpy(j->cfg,i->cfg);
    if(k==0)
    {
        if(i->spacePos>0 && i->cfg[i->spacePos-1]=='a')
        {
            j->cfg[i->spacePos]='a';
            j->cfg[i->spacePos-1]=' ';
            j->spacePos=i->spacePos-1;
            j->cost=getCost(j->cfg,n);
            return j;
        }
    }
    else if(k==1)
    {
        if(i->spacePos<2*n && i->cfg[i->spacePos+1]=='b')
        {
            j->cfg[i->spacePos]='b';
            j->cfg[i->spacePos+1]=' ';
            j->spacePos=i->spacePos+1;
            j->cost=getCost(j->cfg,n);
            return j;
        }
    }
    else if(k==2)
    {
        if(i->spacePos>1 && i->cfg[i->spacePos-2]=='a' && i->cfg[i->spacePos-1]=='b')
        {
            j->cfg[i->spacePos]='a';
            j->cfg[i->spacePos-2]=' ';
            j->spacePos=i->spacePos-2;
            j->cost=getCost(j->cfg,n);
            return j;
        }
    }
    else if(k==3)
    {
        if(i->spacePos<2*n-1 && i->cfg[i->spacePos+2]=='b' && i->cfg[i->spacePos+1]=='a')
        {
            j->cfg[i->spacePos]='b';
            j->cfg[i->spacePos+2]=' ';
            j->spacePos=i->spacePos+2;
            j->cost=getCost(j->cfg,n);
            return j;
        }
    }
    return NULL;
}

int main()
{
    NodeT *root=(NodeT *)malloc(sizeof(NodeT));
    int i;
    for(i=0; i<n; i++)
        root->cfg[i]='a';
    root->cfg[n]=' ';
    for(i=n+1; i<2*n+1; i++)
        root->cfg[i]='b';
    root->spacePos=n;
    root->cost=getCost(root->cfg,n);
    root->prev=root->next=root->parent=NULL;
    ListT *liveNodes=createList();
    insert(root,liveNodes);
    ListT *deadNodes=createList();
    while(1)
    {
        NodeT *i=getNode(liveNodes);
        if(i==NULL)
        {
            printf("\nNO SOLUTION\n");
            break;
        }
        insert(i,deadNodes);
        int k;
        for(k=0; k<4; k++)
        {
            NodeT *j=getNextCfg(i,k);
            if(j==NULL)
                continue;
            if(j->cost==0)
            {
                printSol(j);
                exit(0);
            }
            insert(j,liveNodes);
            j->parent=i;
        }
    }
    return 0;
}
