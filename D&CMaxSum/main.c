#include <stdio.h>
#include <stdlib.h>
#include "D&C.h"

int main(int argc, int *argv[])
{
    if(argc>2)
    {
        FILE *f=fopen(argv[1],"r");
        FILE *g=fopen(argv[2],"w");
        int n=0;
        int size=5;
        int *v=(int *)malloc(size*sizeof(int));
        while(fscanf(f,"%d ",&v[n])==1)
        {
            n++;
            if(n+2>size)
            {
                size+=5;
                v=realloc(v,size*sizeof(int));
            }
        }
        int maxleft,maxright;
        int sum=divideAndConquer(v,0,n-1,&maxleft,&maxright);
        int i;
        for(i=maxleft; i<=maxright; i++)
            fprintf(g,"%d ",v[i]);
        fprintf(g,"\n%d\n",sum);
    }
    else
        printf("\nNEED MORE ARGUMETS\n");
    return 0;
}
