#include <stdio.h>
#include <stdlib.h>

typedef struct n
{
    struct n* next;
    int id;
}NodeT;

typedef struct s
{
    NodeT *top;
    int size;
}StackT;

StackT *createStack()
{
    StackT *s=(StackT *)malloc(sizeof(StackT));
    s->size=0;
    s->top=NULL;
}

void push(StackT *s, int id)
{
    NodeT *pNew=(NodeT *)malloc(sizeof(NodeT));
    pNew->id=id;
    if(s->top==NULL)
    {
        s->top=pNew;
        pNew->next=NULL;
    }
    else
    {
        pNew->next=s->top;
        s->top=pNew;
    }
    s->size++;
}

int pop(StackT *s)
{
    if(s->top==NULL)
        return -1;
    else
    {
        int top=s->top->id;
        NodeT *aux=s->top;
        s->top=s->top->next;
        free(aux);
        return top;
    }
}

void listStack(StackT *s)
{
    NodeT *walker=s->top;
    while(walker!=NULL)
    {
        printf("%d ",walker->id);
        walker=walker->next;
    }
    printf("\n");
}

void divideAndConquer (int n, StackT *from, StackT *to, StackT *other, StackT **pegs)
{
    if (n==0)
        return;
    divideAndConquer(n-1,from,other,to,pegs);
    push(to,pop(from));
    int i;
    for(i=0;i<3;i++)
    {
        printf("%c: ",i+'A');
        listStack(pegs[i]);
    }
    printf("\n");
    divideAndConquer(n-1,other,to,from,pegs);
}

int main()
{
    int n;
    FILE *f=fopen("data.txt","r");
    StackT **pegs=(StackT **)calloc(3,sizeof(StackT*));
    int i;
    for(i=0;i<3;i++)
        pegs[i]=createStack();
    scanf("%d",&n);
    for(i=n;i>=1;i--)
        push(pegs[0],i);
    for(i=0;i<3;i++)
    {
        printf("%c: ",i+'A');
        listStack(pegs[i]);
    }
    divideAndConquer(n,pegs[0],pegs[1],pegs[2],pegs);
    return 0;
}
