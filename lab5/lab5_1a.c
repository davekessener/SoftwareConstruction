/* Solution for Assignment 1.1 of Lab 5 in Software Construction
 * File: lab5_1a.c
 * Daniel Kessener, HAW 2159858
 */
#include <stdio.h>
#include <stdlib.h>

#define ROWS 2
#define COLUMNS 3

void print_2D_matrix(double [][COLUMNS]);

int main(int argc, char *argv[])
{
	double matrix_2D[ROWS][COLUMNS] = {
		{1, 2, 3},
		{4, 5, 6}
	};

	print_2D_matrix(matrix_2D);

#ifndef UNIX
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

void print_2D_matrix(double m[][COLUMNS])
{
	int i, j;
	for(i = 0 ; i < ROWS ; i++)
	{
		for(j = 0 ; j < COLUMNS ; j++)
		{
			printf("%lg%c", m[i][j], j == COLUMNS - 1 ? '\n' : ' ');
		}
	}
}

