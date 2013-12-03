/* Solution for Assignment 3 of Lab 4 in Software Construction
 * File: lab4_3.c
 * Daniel Kessener, HAW 2159858
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// I deem it beneficial to use the optimized qsort routine
// of the standard library for sorting purposes
#define STD_SORT

#ifdef STD_SORT
// comparison function for quicksort ('qsort' in stdlib)
int cmp(const void *p1, const void *p2) { return *((const int *) p1) > *((const int *) p2); }
#else
// sorting function for the array
void sort_arr(int *, int);
#endif

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
#ifdef STD_SORT
	qsort(array, *p2_num_elems, sizeof(int), cmp);
#else
	sort_arr(array, *p2_num_elems);
#endif

	// start with both pointers at index 0
	p1 = p2 = (int *) array;

	while(p2 < e)
	{
		// advance p2 at least once until it points to the first
		// element that differs from p1 or it supercedes the end
		// of the array
		while(*++p2 == *p1 && p2 < e);

		// if p2 is not out of bounds and there are elements between
		// p1 and p2 (there have been multiple elements in the array
		// at some point), copy the element at p2 to p1
		if(p2 < e && ++p1 < p2) *p1 = *p2;

		// repeat until p2 is out of bounds (only duplicate elements
		// are left between p1 and e)
	}

	// if p1 does not point to the end of the array there have
	// been multiple elements and the remainder of the array
	// has to be set to -1
	// since (int)-1 == 0xffffffff, we can use memset to set
	// all four bytes of every int to (char)-1 == 0xff to archieve
	// the same result.
	if(++p1 < e) memset(p1, -1, (e - p1) * sizeof(int)); 
	//// non-little endian alternative
	// while(++p1 < e) *p1 = -1;

	// update element-counter
	*p2_num_elems = p1 - (int *) array;
}

#ifndef STD_SORT
void sort_arr(int *a, int n)
{
	int i, j, t, f;
	for(i = 0 ; i < n ; i++)
	{
		f = 1;
		for(j = i + 1 ; j < n ; j++)
		{
			if(a[j] < a[i])
			{
				t = a[j];
				a[j] = a[i];
				a[i] = t;
				f = 0;
			}
		}

		if(f) break;
	}
}
#undef _SWP
#endif

// but why am i supposed to pass the array-size
// as an int pointer instead of just an int?
void print_final_list(int a[], int *ps)
{
	int i, s = *ps;
	for(i = 0 ; i < s ; i++)
	{
		printf("%c%d%s", i ? '\0' : '{', a[i], i < s - 1 ? ", " : "} ");
	}

	printf("[%d]\n", s);
}

