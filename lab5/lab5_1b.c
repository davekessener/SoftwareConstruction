#include <stdio.h>
#include <stdlib.h>

#define ROWS 2
#define COLUMNS 3
#define PLANES 4

void print_3D_matrix(double [][ROWS][COLUMNS]);

int main(int argc, char *argv[])
{
	double matrix_3D[PLANES][ROWS][COLUMNS] = {
	{
		{1, 2, 3},
		{4, 5, 6}
	},
	{
		{11, 22, 33},
		{44, 55, 66}
	},
	{
		{111, 222, 333},
		{444, 555, 666}
	},
	{
		{1111, 2222, 3333},
		{4444, 5555, 6666}
	}};

	print_3D_matrix(matrix_3D);

#ifndef UNIX
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

void print_3D_matrix(double m[][ROWS][COLUMNS])
{
	int i, j, k;
	for(i = 0 ; i < PLANES ; i++)
	{
		for(j = 0 ; j < ROWS ; j++)
		{
			for(k = 0 ; k < COLUMNS ; k++)
			{
				printf("%lg%s", m[i][j][k], k == COLUMNS - 1 ? (j == ROWS - 1 ? "\n\n" : "\n") : " ");
			}
		}
	}
}

