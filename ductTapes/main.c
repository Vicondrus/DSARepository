#include <stdio.h>
#include <stdlib.h>

int main()
{
    int cells, grid, stickiness;
    FILE *f=fopen("data.txt","r");
    fscanf(f,"%d %d %d\n",&cells,&grid,&stickiness);
    int *A=(int *)calloc(cells,sizeof(int));
    int i;
    for(i=0; i<cells; i++)
        fscanf(f,"%d",&A[i]);
    int sum=0;
    int stick=0;
    int j;
    int ok=1;
    for(i=0; i<cells-grid+1; i++)
    {
        sum=0;
        for(j=i; j<i+grid && j<cells; j++)
        {
            sum+=A[j];
        }
        if(sum<stickiness)
        {
            int R=0;
            if(A[i+grid-1]>0)
            {
                R=(A[j-1]+stickiness-sum)/A[i+grid-1];
                if(R<2)
                    R=2;
            }
            else
            {
                ok=0;
                break;
            }
            for(j=i+grid-1; j<i+grid+grid-1 && j<cells; j++)
                A[j]=A[j]*R;
            stick++;
        }
    }

    for(i=0; i<cells; i++)
        printf("%d ",A[i]);
    printf("\n");
    for(i=0; i<cells-grid; i++)
    {
        sum=0;
        for(j=i; j<i+grid && j<cells; j++)
        {
            sum+=A[j];
        }
        if(sum<stickiness)
        {
            ok=0;
        }
    }
    if(ok)
        printf("\n%d\n",stick);
    else
        printf("\n-1\n");
    return 0;
}
