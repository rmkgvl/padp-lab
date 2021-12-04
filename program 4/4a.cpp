#include<stdio.h>
#include<gd.h>
#include<omp.h>

char *in,*out;

double gray(int threads){
    FILE *fp;
    if(!(fp=fopen(in,"r"))){
        printf("Unable to open input file.\n");
        exit(0);
    }

    gdImagePtr img=gdImageCreateFromPng(fp);
    int W=gdImageSX(img);
    int H=gdImageSY(img);
    double t=omp_get_wtime();
    #pragma omp parallel for collapse(2) num_threads(threads) schedule(guided)
    for(int x=0;x<W;x++)
        for(int y=0;y<H;y++){
            int color=gdImageGetPixel(img,x,y);
            int avg=(gdImageRed(img,color),
                    gdImageRed(img,color),
                    gdImageRed(img,color)
                    )/3;
            color=gdImageColorAllocate(img,avg,avg,avg);
            gdImageSetPixel(img,x,y,color);
        }
    return omp_get_wtime()-t;
}

int main(int argc,char *argv[]){
    if(argc<3){
        printf("Require input and output files.\n");
        exit(0);
    }else{
        in=argv[1];
        out=argv[2];
    }

    printf("%10s%10d%10d%10d%10d\n","threads",1,2,4,8);
    printf("%10s%10.6f%10.6f%10.6f%10.6f\n","time",gray(1),gray(2),gray(4),gray(8));
}