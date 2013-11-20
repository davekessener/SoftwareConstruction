/* Solution for Assignment 3 of Lab 4 in Software Construction
 * File: lab4_3.c
 * Daniel Kessener, HAW 2159858
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// comparison function for quicksort ('qsort' in stdlib)
int cmp(const void *p1, const void *p2) { return *((const int *) p1) > *((const int *) p2); }

void multiple_entry_remover(int[], int *);
void print_final_list(int[], int *);

int main(int argc, char *argv[])
{
	int field[] = {1, 2, 2, 1, 1, 1, 3, 1, 2, 3, 2, 1};
	int elements = sizeof(field)/sizeof(int);

	printf("=========================================\n");
	printf("elements = %d\n", elements);

	multiple_entry_remover(field, &elements);

	printf("=========================================\n");
	print_final_list(field, &elements);

	return EXIT_SUCCESS;
}

void multiple_entry_remover(int array[], int *p2_num_elems)
{
	int i, j;
	int n = *p2_num_elems;
	int *tmp = malloc(n * sizeof(int));

	// sort the array, that way the function only has
	// to compare each (potential) new element against
	// the previous one, instead of all previously
	// accepted elements.
	qsort(array, n, sizeof(int), cmp);

	for(i = 0, j = 0 ; i < n ; i++)
	{
		// if the solution array is empty or the new
		// value has not been added to the solution, add it
		if(j == 0 || tmp[j - 1] != array[i])
		{
			tmp[j++] = array[i];
		}
	}

	// transfer set of individual integers
	memcpy(array, tmp, j * sizeof(int));
	// set empty space to '-1'
	memset(array + j, -1, (n - j) * sizeof(int));
	free(tmp);

	// update element-counter
	*p2_num_elems = j;
}

// but why am i supposed to pass the array-size
// as an int pointer instead of just an int?
void print_final_list(int a[], int *ps)
{
	int i, s = *ps;
	for(i = 0 ; i < s ; i++)
	{
		printf("%d", a[i]);
		if(i < s - 1) printf(", ");
		else printf(" [%d]\n", s);
	}
}

