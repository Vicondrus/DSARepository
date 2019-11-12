#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int i, int j, int k)
{
    if(i>j)
        if(j>k)
            return k;
        else
            return j;
    else if(i>k)
        return k;
    else
        return i;
}

int minEditDist(char *str1, char *str2, int n, int m)
{
    int **C=(int **)calloc(n+2,sizeof(int *));
    int i,j;
    for(i=0; i<=n; i++)
        C[i]=(int *)calloc(m+2,sizeof(int));
    for(i=0; i<=n; i++)
        for(j=0; j<=m; j++)
        {
            if(i==0)
                C[i][j]=j;
            else if(j==0)
                C[i][j]=i;
            else if(str1[i-1]==str2[j-1])
                C[i][j]=C[i-1][j-1];
            else
                C[i][j]=1+min(C[i-1][j-1],C[i-1][j],C[i][j-1]);

        }
    return C[n][m];
}

int main()
{
    FILE *f=fopen("data.txt","r");
    char *str1=(char *)calloc(sizeof(char),200);
    char *str2=(char *)calloc(sizeof(char),200);
    fscanf(f,"%s %s",str1,str2);
    int rez=minEditDist(str1,str2,strlen(str1),strlen(str2));
    printf("\n%d\n",rez);
    return 0;
}
