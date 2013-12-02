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

#ifndef UNIX
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

void multiple_entry_remover(int array[], int *p2_num_elems)
{
	int *p1, *p2, *e = (int *) array + *p2_num_elems;

	// sort the array, that way the function only has
	// to compare each (potential) new element against
	// the previous one, instead of all previously
	// accepted elements.
	qsort(array, *p2_num_elems, sizeof(int), cmp);

	// start with both pointers at index 0
	p1 = p2 = (int *) array;

	do
	{
		// advance p2 at least once until it points to the first
		// element that differs from p1 or it supercedes the end
		// of the array
		while(*++p2 == *p1 && p2 < e);

		// if p2 is out of bounds (only duplicate elements left
		// between p1 and e), break
		if(p2 == e) break;

		// if the are elements between p1 and p2 (the have been
		// multiple elements in the array at some point), copy
		// the element at p2 to p1
		if(++p1 < p2) *p1 = *p2;
	} while(p2 < e); // repeat until eoa is reached

	// if p1 does not point to the end of the array there have
	// been multiple elements and the remainder of the array
	// has to be set to -1
	if(++p1 < e) memset(p1, -1, (e - p1) * sizeof(int));

	// update element-counter
	*p2_num_elems = p1 - (int *) array;
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

