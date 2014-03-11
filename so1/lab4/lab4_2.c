/* Solution for Assignment 2 of Lab 4 in Software Construction
 * File: lab4_2.c
 * Daniel Kessener, HAW 2159858
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define N 5

void set_4_elems(int[N][N], int);
void printM(int[N][N]);

int main(int argc, char *argv[])
{
	int i;
	int m_2D[N][N] = {{0}};

	printf("Initial matrix:\n");
	printM(m_2D);

	// for all possible indices
	for(i = 0 ; i <= (N - 1) / 2 ; i++)
	{
		printf("\nIndex %d:\n", i);

		set_4_elems(m_2D, i);
		printM(m_2D);
		// resets matrix to 0
		memset(*m_2D, 0, N * N * sizeof(int));
	}

#ifndef UNIX
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

void set_4_elems(int matrix_2D[N][N], int index)
{
	int lo, hi;

	assert(index<=(N-1)/2);

	// using rounding-properties of integer division,
	// for uneven N 'hi - lo == 2 * index' and
	// for   even N 'hi - lo == 2 * index + 1'
	// this way the algorithm works for both even
	// and uneven N
	lo = (N - 1) / 2 - index;
	hi =  N      / 2 + index;

	matrix_2D[lo][lo] = 1;
	
	// for even matrices and index == 0, only one field
	// has to be set. (since hi == lo)
	if(lo != hi)
	{
		matrix_2D[lo][hi] = 1;
		matrix_2D[hi][lo] = 1;
		matrix_2D[hi][hi] = 1;
	}

	return;
}

void printM(int a[N][N])
{
	char buf[(N + 1) * N + 1];
	int i, j;

	for(i = 0 ; i < N ; i++)
	{
		for(j = 0 ; j < N ; j++)
		{
			buf[i * (N + 1) + j] = a[i][j] ? '1' : '0'; // same as "a[i][j] + '0';", really.
		}

		buf[i * (N + 1) + N] = '\n';
	}

	buf[(N + 1) * N] = '\0';

	printf("%s\n", buf);
}

