#include "D&C.h"

int divideAndConquer(int *v, int left, int right, int *maxleft, int *maxright)
{
    if (right < left)
        return -1000;
    else
    {
        int m=(left+right)/2;
        int s1=divideAndConquer(v,left,m-1,maxleft,maxright);
        int s2=divideAndConquer(v,m+1,right,maxleft,maxright);
        int s3=0;
        int p1=-1000;
        int p2=-1000;
        int i;
        int sum=0;
        int auxleft;
        int auxright;
        for (i=m+1;i<right+1;i++)
        {
            sum+=v[i];
            if(p1<sum)
            {
                auxright=i;
                p1=sum;
            }
        }
        sum=0;
        for (i=m;i>left;i--)
        {
            sum+=v[i];
            if(p2<sum)
            {
                auxleft=i;
                p2=sum;
            }
        }
        s3=p1+p2;
        if(s1>s2)
            if(s3>s1)
            {
                *maxleft=auxleft;
                *maxright=auxright;
                return s3;
            }
            else
                return s1;
        else if(s3>s2)
        {
            *maxleft=auxleft;
            *maxright=auxright;
            return s3;
        }
        else
            return s2;
    }
}
