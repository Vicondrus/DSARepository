#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


int main(int argc, int *argv[])
{
    if(argc>2)
    {
    FILE *f=fopen(argv[1],"r");
    FILE *g=fopen(argv[2],"w");
    char *str1=(char *)calloc(2000,sizeof(char));
    char *str2=(char *)calloc(2000,sizeof(char));
    int nr;
    fscanf(f,"%d\n",&nr);
    int i;
    for(i=0; i<nr; i++)
    {
        fscanf(f,"%s\n%s",str1,str2);
        int n=strlen(str1);
        int m=strlen(str2);
        int rez=minEdit(str1,str2,n,m);
        fprintf(g,"\n%d\n",rez);
    }
    free(str1);
    free(str2);
    }
    else printf("\nNOT ENOUGH ARGUMETNS\n");
    return 0;
}
