#include <stdio.h>
#include <stdlib.h>

typedef struct item
{
    float weight;
    float value;
    float ratio;
} ItemT;

int main()
{
    int n,cap;
    FILE *f=fopen("data.txt","r");
    fscanf(f,"%d %d\n",&n,&cap);
    ItemT *items=(ItemT *)calloc(n,sizeof(ItemT));
    int i;
    for(i=0; i<n; i++)
    {
        fscanf(f,"%f %f\n",&items[i].weight,&items[i].value);
        items[i].ratio=items[i].value/items[i].weight;
    }
    int ok=0;
    while(ok==0)
    {
        ok=1;
        for(i=0; i<n-1; i++)
            if(items[i].ratio<items[i+1].ratio)
            {
                ok=0;
                ItemT aux=items[i];
                items[i]=items[i+1];
                items[i+1]=aux;
            }
    }
    int capAux=cap;
    int sum=0;
    int total=0;
    i=0;
    printf("Case a)\n");
    while(capAux>0 && i<n)
    {
        if(items[i].weight<capAux)
        {
            sum+=items[i].value;
            total+=items[i].weight;
            capAux-=items[i].weight;
        }
        i++;
    }
    printf("Weight:%d Value:%d\n",total,sum);
    printf("Case b)\n");
    capAux=cap;
    sum=0;
    total=0;
    i=0;
    while(capAux>0)
    {
        if(items[i].weight<capAux)
        {
            sum+=items[i].value;
            total+=items[i].weight;
            capAux-=items[i].weight;
        }
        else
        {
            sum+=(items[i].ratio*capAux);
            total+=capAux;
            capAux-=capAux;
        }
        i++;
    }
    printf("Weight:%d Value:%d\n",total,sum);
    return 0;
}
