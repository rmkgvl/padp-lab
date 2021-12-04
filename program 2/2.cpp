#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

	int row , col , i, j, count = 0, k, d, n;

	for (d = 500; d <= 1250; d = d + 250)
	{
		row = d;
		col = d;
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