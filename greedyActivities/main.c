#include <stdio.h>
#include <stdlib.h>

typedef struct a
{
    int start;
    int end;
} ActivityT;

int main()
{
    FILE *f=fopen("data.txt","r");
    int n;
    fscanf(f,"%d",&n);
    ActivityT *activities=(ActivityT *)calloc(n,sizeof(ActivityT));
    int i;
    int maxEnd=-1;
    for(i=0; i<n; i++)
    {
        fscanf(f,"%d %d\n",&activities[i].start,&activities[i].end);
        if(maxEnd<activities[i].end)
            maxEnd=activities[i].end;
    }
    int ok=0;
    while(ok!=0)
    {
        ok=1;
        for(i=0; i<n-1; i++)
            if(activities[i+1].start<activities[i].start)
            {
                ok=0;
                ActivityT aux=activities[i];
                activities[i]=activities[i+1];
                activities[i+1]=aux;
            }
    }
    i=0;
    int end=activities[i].end;
    int sum=0;
    while(i<n)
    {
        printf("%d-%d ",activities[i].start,activities[i].end);
        sum=sum+activities[i].end-activities[i].start;
        while(end>activities[i].start)
            i++;
        end=activities[i].end;
    }
    int efficency=sum*100/maxEnd;
    printf("%d%%\n",efficency);
    return 0;
}
