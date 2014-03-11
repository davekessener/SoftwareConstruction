#include <stdio.h>
#include <stdlib.h>

#define PLANES 4
#define ROWS 2
#define COLUMNS 3

int main(int argc, char *argv[])
{
	double ***m = malloc(PLANES * sizeof(double **));
	int i, j, k;

	for(i = 0 ; i < PLANES ; i++)
	{
		m[i] = malloc(ROWS * sizeof(double *));

		printf("plane %d:\n", i);

		for(j = 0 ; j < ROWS ; j++)
		{
			m[i][j] = malloc(COLUMNS * sizeof(double));

			for(k = 0 ; k < COLUMNS ; k++)
			{
				printf("% 5lg%s", m[i][j][k] = i * 1000 + j * 10 + k * 100,
						k == COLUMNS - 1 ? (j == ROWS - 1 ? "\n\n" : "\n") : "");
			}

			free(m[i][j]);
		}

		free(m[i]);
	}

	free(m);

#ifndef UNIX
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

