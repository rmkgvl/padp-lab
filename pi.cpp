#include<iostream>
#include <stdlib.h>
#include<stdio.h>
#include<omp.h>
#include<math.h>

const double PI=2*acos(0.0);
using namespace std;


int main()
{
double x,y,t,start,pi;
long i, nc;
unsigned int seed;
start = omp_get_wtime();
printf("\ninpsize threads time error\n");
for(long long z=10000;z<=10000000;z=z*10)
{
for(int l=1;l<=8;l<<=1)
{
nc=0;
srand(time(NULL));
#pragma omp parallel private(x,y,t,seed) num_threads(l)
{
seed = time(NULL) + omp_get_thread_num();
cout<<omp_get_num_threads()<<endl;
#pragma omp for reduction(+:nc)
for(int i=0;i<z;i++)
{
x=(double)rand_r(&seed)/RAND_MAX;
y=(double)rand_r(&seed)/RAND_MAX;
t= x*x + y*y;
if(t<=1)
{
nc++;
}
}
pi = 4.0 * ((double)nc/(double)z);
}
printf("\n %ld  %d  %lf  %f",z,l,omp_get_wtime()-start,fabs(PI-pi));
}
}
}