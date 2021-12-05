#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include<iostream>
#include<math.h>
#include<cstring>

using namespace std;

double t=100.0;
inline long strike(bool composite[],int start,int stride,int limit)
{
    for(;start<=limit;start+=stride)
    {
        composite[start]=true;
    }
    return start;
}

long CacheUnfriendlySieve(long n)
{
    long count=0;
    double start,end;
    bool *composite = new bool[n+1];
    memset(composite,0,n);
    long m = (long) sqrt((double)n);
    start = omp_get_wtime();
    for(int i=2;i<=m;i++)
    {
        if(!composite[i])
        {
            count++;
            strike(composite,2*i,i,n);
        }
    }
    for(long i=m+1;i<=n;i++)
    {
        if(!composite[i])
        {
            count++;
        }
    }
    end = omp_get_wtime();
    t = end-start;
    delete [] composite;
    return count;
}

long CacheFriendlySieve(long n)
{
    long count=0;
    bool * composite = new bool[n+1];
    memset(composite,0,n);
    long m = (long) sqrt((double)n);
    long * factor = new long[m];
    long * striker = new long[m];
    int n_factor = 0;
    double start = omp_get_wtime();
    for(int i=2;i<=m;i++)
    {
        if(!composite[i])
        {
            count++;
            striker[n_factor] = strike(composite,2*i,i,m);
            factor[n_factor++] = i;
        }
    }
    for(long window = m+1; window<=n;window+=m)
    {
        long limit = min(window+m-1,n);
        for(long k=0;k<n_factor;k++)
        {
            striker[k] = strike(composite,striker[k],factor[k],limit);
        }
        for(long i=window;i<=limit;i++)
        {
            if(!composite[i])
            {
                count++;
            }
        }
    }
    double end = omp_get_wtime();
    t = end-start;
    delete [] composite;
    delete [] factor;
    delete [] striker;
    return count;
}

long CacheParallelSieve(long n)
{
    long count=0;
    long m = (long) sqrt((double)n);
    long * factor = new long[m];
    long n_factor = 0;
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        bool * composite = new bool[m+1];
        long * striker = new long[m];
        #pragma omp single
        {
            memset(composite,0,m);
            for(int i=2;i<=m;++i)
            {
                if(!composite[i])
                {
                    ++count;
                    strike(composite,2*i,i,m);
                    factor[n_factor++] = i;
                }
            }
        }
        long base = -1;
        omp_set_num_threads(4);
        #pragma omp for reduction(+:count)
        for(long window = m+1;window<=n;window+=m)
        {
            memset(composite,0,m);
            if(base!=window)
            {
                base = window;
                for(long k=0;k<n_factor;++k)
                {
                    striker[k] = (base+factor[k]-1)/factor[k] * factor[k] - base;
                }
            }
            long limit = min(window+m-1,n)-base;
            for(int k=0;k<n_factor;k++)
            {
                striker[k] = strike(composite,striker[k],factor[k],limit)-m;
            }
            for(int i=0;i<=limit;i++)
            {
                if(!composite[i])
                {
                    count++;
                }
            }
            base+=m;
        }
        delete [] composite;
        delete [] striker;
    }
    double end = omp_get_wtime();
    t = end-start;
    return count;
}

int main()
{
    cout<<t<<endl;
    for(long z = 10000;z<=100000000;z=z*10)
    {
        cout<<"CacheUnfriendlySieve "<<CacheUnfriendlySieve(z)<<" time "<<t<<endl;
        cout<<"CacheFriendlySieve "<<CacheFriendlySieve(z)<<" time "<<t<<endl;
        cout<<"CacheParallelSieve "<<CacheParallelSieve(z)<<" time "<<t<<endl;
    }
    return 0;
}
