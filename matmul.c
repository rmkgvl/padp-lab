#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

	int row = 500, col = 500, i, j, count = 0, k, d, n;

	for (d = 500; d <= 1250; d = d + 250)
	{
		printf("%d x %d matrices\n", d, d);
		int **arr1 = (int **)malloc(row * sizeof(int *));

		for (i = 0; i < row; i++)
			arr1[i] = (int *)malloc(col * sizeof(int));
		int **arr2 = (int **)malloc(row * sizeof(int *));
		for (i = 0; i < row; i++)
			arr2[i] = (int *)malloc(col * sizeof(int));
		int **arr3 = (int **)malloc(row * sizeof(int *));
		for (i = 0; i < row; i++)
			arr3[i] = (int *)malloc(col * sizeof(int));

		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
				arr1[i][j] = count++;

		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++)
				arr2[i][j] = count++;

		//Extra piece of code for parallelization
		for (n = 1; n <= 16; n = n * 2)
		{
			double x = omp_get_wtime();
			omp_set_num_threads(n);
			#pragma omp parallel for private(j, k)
			for (i = 0; i < row; i++)
				for (j = 0; j < col; j++)
					for (k = 0; k < row; k++)
						arr3[i][j] += arr1[i][k] * arr2[k][j]; //Main multiplication operation

			double y = omp_get_wtime();

			printf("For %d threads, time :%lf\n", n, y - x);
		}
	}
	return 0;
}

/*Matrix multiplication using dynamic memory allocation
#include <stdio.h>  
#include<stdlib.h> 
/* Main Function   
int main()  
{ 
/* Declaring pointer for matrix multiplication.
int **ptr1, **ptr2, **ptr3; 
/* Declaring integer variables for row and columns of two matrices.
int row1, col1, row2, col2; 
/* Declaring indexes. 
int i, j, k; 
/* Request the user to input number of columns of the matrices.
printf("\nEnter number of rows for first matrix : "); 
scanf("%d", &row1);  
printf("\nEnter number of columns for first matrix : "); 
scanf("%d", &col1); 
printf("\nEnter number of rows for second matrix : "); 
scanf("%d", &row2); 
printf("\nEnter number of columns for second matrix : "); 
scanf("%d", &col2); 
if(col1 != row2) 
{ 
	printf("\nCannot multiply two matrices.");  
	return(0);  
} 
/* Allocating memory for three matrix rows.
ptr1 = (int **) malloc(sizeof(int *) * row1);  
ptr2 = (int **) malloc(sizeof(int *) * row2); 
ptr3 = (int **) malloc(sizeof(int *) * row1); 
/* Allocating memory for the col of three matrices.
for(i=0; i<row1; i++) 
 	ptr1[i] = (int *)malloc(sizeof(int) * col1); 
for(i=0; i<row2; i++)  
 	ptr2[i] = (int *)malloc(sizeof(int) * col2); 
for(i=0; i<row1; i++)  
 	ptr3[i] = (int *)malloc(sizeof(int) * col2); 
/* Request the user to input members of first matrix. 
printf("\nEnter elements of first matrix :\n");  
for(i=0; i< row1; i++) 
{ 
	for(j=0; j< col1; j++) 
	{ 
		printf("\tA[%d][%d] = ",i, j); 
		scanf("%d", &ptr1[i][j]); 
	} 
} 
/* request to user to input members of second matrix.
printf("\nEnter elements of second matrix :\n"); 
for(i=0; i< row2; i++) 
{ 
	for(j=0; j< col2; j++) 
	{ 
		printf("\tB[%d][%d] = ",i, j); 
		scanf("%d", &ptr2[i][j]); 
	} 
} 
/* Calculation begins for the resultant matrix.
for(i=0; i < row1; i++) 
{ 
	for(j=0; j < col1; j++) 
	{ 
		ptr3[i][j] = 0; 
 		for(k=0; k<col2; k++)  
		ptr3[i][j] = ptr3[i][j] + ptr1[i][k] * ptr2[k][j]; 
	} 
} 
/* Printing the contents of third matrix. 
printf("\n\nResultant matrix :");  
for(i=0; i< row1; i++)  
{ 
	printf("\n\t\t\t"); 
	for(j=0; j < col2; j++) 	 
	printf("%d\t", ptr3[i][j]); 
} 
return 0; 
} 
*/ 

