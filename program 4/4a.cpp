#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<gd.h>

int main(int argc,char * argv[])
{
	int w,h,red,blue,green,color,x,y;
	w=h=x=y=red=blue=green=color=0;
	char * iname = NULL,* oname = NULL;
	if(argc!=3)
	{
		printf("please enter the input and output file names\n");
		exit(0);
	}
	else
	{
		iname = argv[1];
		oname = argv[2];
	}
	FILE * fp = {0};
	if((fp=fopen(iname,"r"))==NULL)
	{
		printf("input file size error\n");
		exit(0);
	}
	gdImagePtr img = gdImageCreateFromPng(fp);
	w = gdImageSX(img);
	h = gdImageSY(img);
	printf("threads time\n");
	for(int l=1;l<=8;l*=2)
	{
	omp_set_num_threads(l);
	double t = omp_get_wtime();
	#pragma omp parallel for private(red,blue,green,color) collapse(2)
	for(x=0;x<w;x++)
	{
		for(y=0;y<h;y++)
		{
			color = gdImageGetPixel(img,x,y);
			red = gdImageRed(img,color);
			blue = gdImageBlue(img,color);
			green = gdImageGreen(img,color);
			int avg = (red+blue+green)/3;
			color = gdImageColorAllocate(img,avg,avg,avg);
			gdImageSetPixel(img,x,y,color);
		}
	}
	if((fp=fopen(oname,"w"))==NULL)
	{
		printf("output file size error\n");
		exit(0);
	}
	gdImagePng(img,fp);
	t = omp_get_wtime()-t;
	printf("%d %lf\n",l,t);
	}
	gdImageDestroy(img);
	return 0;
}
