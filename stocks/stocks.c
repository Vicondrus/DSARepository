#include "stocks.h"

double minn(double *A, int left, int right)
{
    int i;
    double min=10000.0;
    for(i=left;i<=right;i++)
        if(min>A[i])
            min=A[i];
    return min;
}

double maxx(double *A, int left, int right)
{
    int i;
    double max=0.0;
    for(i=left;i<=right;i++)
        if(max<A[i])
            max=A[i];
    return max;
}

double profit(double *A, int left, int right)
{
    if(right < left)
        return -100000000000.0;
    int m=(left+right)/2;
    double p1=profit(A,left,m-1);
    double p2=profit(A,m+1,right);
    double p3=maxx(A,m,right)-minn(A,left,m-1);
    if(p1>p2)
        if(p3>p1)
            return p3;
        else
            return p1;
    else
        if(p3>p2)
            return p3;
        else
            return p2;
}
