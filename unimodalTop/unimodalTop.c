#include "unimodalTop.h"

int divideAndConquer (int *v, int left, int right)
{
    if (left==right)
        return v[left];
    else
    {
        int m=(left+right)/2;
        if(v[m]<v[m+1])
            return divideAndConquer(v,m+1,right);
        else
            return divideAndConquer(v,left,m);
    }
}
