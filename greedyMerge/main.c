#include <stdio.h>
#include <stdlib.h>

typedef struct n
{
    struct n *next,*prev;
    int id;
    int size;
} NodeT;

typedef struct l
{
    NodeT *first, *last;
    int size;
} ListT;

ListT *createList()
{
    ListT *pNew=(ListT *)malloc(sizeof(ListT));
    pNew->first=NULL;
    pNew->last=NULL;
    pNew->size=0;
}

void insert(ListT *list, int id, int size)
{
    NodeT *pNew=(NodeT *)malloc(sizeof(NodeT));
    pNew->id=id;
    pNew->size=size;
    if(list->first==NULL)
    {
        pNew->prev=NULL;
        pNew->next=NULL;
        list->first=pNew;
        list->last=pNew;
    }
    else
    {
        if(size<list->first->size)
        {
            list->first->prev=pNew;
            pNew->next=list->first;
            pNew->prev=NULL;
            list->first=pNew;
        }
        else
        {
            NodeT *walker=list->first;
            while(walker!=NULL)
            {
                if(walker->size>size)
                    break;
                walker=walker->next;
            }
            if(walker==NULL)
            {
                list->last->next=pNew;
                pNew->prev=list->last;
                pNew->next=NULL;
                list->last=pNew;
            }
            else
            {
                walker->prev->next=pNew;
                pNew->prev=walker->prev;
                walker->prev=pNew;
                pNew->next=walker;
            }
        }
    }
    list->size++;
}

void deleteNode(ListT *list, int id)
{
    if(list->first==list->last)
    {
        if(list->first->id==id)
        {
            list->first=NULL;
            list->last=NULL;
            list->size=0;
        }
    }
    else

        if(list->first->id==id)
        {
            NodeT *aux=list->first;
            list->first=list->first->next;
            list->first->prev=NULL;
            free(aux);
            list->size--;
        }
        else if(list->last->id==id)
        {
            NodeT *aux=list->last;
            list->last=list->last->prev;
            list->last->next=NULL;
            free(aux);
            list->size--;
        }
        else
        {
            NodeT *walker=list->first;
            while(walker!=NULL)
            {
                if(walker->id==id)
                    break;
                walker=walker->next;
            }
            if(walker!=NULL)
            {
                walker->prev->next=walker->next;
                walker->next->prev=walker->prev;
                free(walker);
                list->size--;
            }
        }
}

void printList(ListT *list)
{
    NodeT *walker=list->first;
    while(walker!=NULL)
    {
        printf("%d %d\n",walker->id,walker->size);
        walker=walker->next;
    }
    printf("\n");
}

int main()
{
    ListT *list=createList();
    int m;
    FILE *f=fopen("data.txt","r");
    fscanf(f,"%d\n",&m);
    int i,aux;
    for(i=0; i<m; i++)
    {
        fscanf(f,"%d ",&aux);
        insert(list,i,aux);
        int j;
        for(j=0; j<aux; j++)
            fscanf(f,"%*d");
    }
    printList(list);
    while(list->first!=list->last)
    {
        int auxSize=list->first->size+list->first->next->size;
        int auxId;
        if(list->first->id>list->first->next->id)
            auxId=list->first->next->id;
        else
            auxId=list->first->id;
        printf("Vectors %d and %d merged obtained a vector of size %d\n",list->first->id,list->first->next->id,auxSize);
        deleteNode(list,list->first->id);
        deleteNode(list,list->first->id);
        insert(list,auxId,auxSize);
        printList(list);
    }
    printList(list);
    return 0;
}
