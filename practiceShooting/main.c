#include <stdio.h>
#include <stdlib.h>

int minShot(int n, int points)
{
    int *values=(int *)calloc(points+2,sizeof(int));
    int i, j;
    for(i=1;i<=points;i++)
    {
        values[i]=10000;
        for(j=1;j<=n;j++)
            if(i>=j)
                if(values[i-j]+1<values[i])
                    values[i]=values[i-j]+1;
    }
    return values[points];
}

int main()
{
    int n, points;
    scanf("%d %d",&points,&n);
    printf("\n%d\n",minShot(n,points));
    return 0;
}
