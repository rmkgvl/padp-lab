#include<stdio.h>
#include<gd.h>
#include<omp.h>
#include<string.h>

int main(int argc,char ** argv)
{
FILE * fp = {0};
gdImagePtr img;
char * iname = NULL;
char * oname = NULL;
int color,x,y,w,h,i=0;
color=x=y=w=h=0;
if(argc!=3)
{
return 0;
}
iname = argv[1];
oname = argv[2];
if((fp=fopen(iname,"r"))==NULL)
printf("file not exists");
else
img = gdImageCreateFromPng(fp);
w = gdImageSX(img);
h = gdImageSY(img);
float t = omp_get_wtime();
for(x=0;x<w;x++)
{
for(y=0;y<h;y++)
{
color = x+0;
color = gdImageGetPixel(img,x,y);
red = 255 - gdImageRed(img,color);
green = 255 - gdImageGreen(img,color);
blue = 255 - gdImageBlue(img,color);
color = gdImageColorAllocate(img,red,green,blue);
gdImageSetPixel(img,x,y,color);
}
}
if((fp=fopen(oname,"w"))==NULL)
cout<<"output error"<<endl;
else
{
gdImagePng(img,fp);
fclose(fp);
}
t = omp_get_wtime()-t;
gdImageDestroy(img);
printf("time taken = %f",t);
}
