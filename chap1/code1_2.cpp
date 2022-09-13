#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5
/*
행렬이 여러 개일 때 하나의 function으로 처리하는 방법을 고안
*/

int get_data(int(*p)[ACOLS], int n)
{
	for (int i = 0; i < AROWS; i++)
		for (int j = 0; j < ACOLS; j++)
			p[i][j] = rand() % (n * n);
	return 1;
}

void show_data(int(*p)[ACOLS], int n)
{
	for (int i = 0; i < AROWS; i++)
	{
		for (int j = 0; j < ACOLS; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

int get_data_B(int(*p)[BCOLS], int n)
{


	for (int i = 0; i < BROWS; i++)
		for (int j = 0; j < BCOLS; j++)
			p[i][j] = rand() % (n * n);
	return 1;
}

void show_data_B(int(*p)[BCOLS], int n)
{
	for (int i = 0; i < BROWS; i++)
	{
		for (int j = 0; j < BCOLS; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

int get_data_C(int(*p)[CCOLS], int n)
{
	for (int i = 0; i < CROWS; i++)
		for (int j = 0; j < CCOLS; j++)
        {
			p[i][j] = rand() % (n * n);
        }
    return 1;
}

void show_data_C(int(*p)[CCOLS], int n)
{
	for (int i = 0; i < CROWS; i++)
	{
		for (int j = 0; j < CCOLS; j++)
			printf("%d ", p[i][j]);
		printf("\n");
	}
}

/*
void multiply(int matrixA[][ACOLS], int ar, int matrixB[][BCOLS], int br, int matrixC[][CCOLS], int cr) {

}
*/

int main(void)
{
	int matrixA[AROWS][ACOLS];
	int matrixB[BROWS][BCOLS];
	int matrixC[CROWS][CCOLS];
	srand(time(NULL));
	get_data(matrixA, AROWS);
	show_data(matrixA, AROWS);
	get_data_B(matrixB, BROWS);
	show_data_B(matrixB, BROWS);

	// multiply(matrixA, AROWS, matrixB, BROWS, matrixC, CROWS);
    get_data_C(matrixC, CROWS);
	show_data_C(matrixC, CROWS);
    return 0;
}