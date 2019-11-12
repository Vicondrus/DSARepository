#include <stdio.h>
#include <stdlib.h>

typedef struct w
{
    int start;
    int money;
    int speed;
    int ratio;
    int hired;
} WorkerT;

int main()
{
    FILE *f=fopen("data.txt","r");
    int area, n;
    fscanf(f,"%d %d\n",&n,&area);
    WorkerT *workers=(WorkerT *)calloc(n,sizeof(WorkerT));
    int i;
    for(i=0; i<n; i++)
    {
        fscanf(f,"%d %d %d\n",&workers[i].start,&workers[i].money,&workers[i].speed);
        workers[i].ratio=workers[i].speed/workers[i].money;
        workers[i].hired=0;
    }
    int ok=0;
    while(ok==0)
    {
        ok=1;
        for(i=0; i<n-1; i++)
            if(workers[i].start>workers[i+1].start)
            {
                ok=0;
                WorkerT aux=workers[i];
                workers[i]=workers[i+1];
                workers[i+1]=aux;
            }
    }
    i=1;
    int currTime=workers[0].start;
    int currSpeed=workers[0].speed;
    workers[0].hired=1;
    while(area>0)
    {
        area=area-(workers[i].start-currTime)*currSpeed;
        if(area>0 && workers[i].speed>currSpeed)
        {
            currSpeed=workers[i].speed;
            workers[i].hired=1;
        }
        currTime=workers[i].start;
        i++;
    }
    int money=0;
    for(i=0; i<n; i++)
    {
        if(workers[i].hired==1)
            money+=workers[i].money;
    }
    printf("%d\n",money);
    return 0;
}
