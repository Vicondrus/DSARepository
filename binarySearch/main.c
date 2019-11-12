#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *A, int left, int right, int x)
{
    if (left > right)
        return -1;
    int m=(left + right)/2;
    if(A[m]==x)
        return m;
    else
        if(A[m] < x)
            return binarySearch(A,m+1,right,x);
        else
            return binarySearch(A,left,m-1,x);
}

int main()
{
    int n;
    scanf("%d",&n);
    int *A=(int *)malloc(sizeof(int));
    int i;
    for(i=0;i<n;i++)
        scanf("%d ",&A[i]);
    int x;
    scanf("%d",&x);
    int m=binarySearch(A,0,n-1,x);
    printf("%d\n",m);
    return 0;
}
