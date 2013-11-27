#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isin(int[], int[], int, int);

int Is_large_1D_array_inside_small_1D_array(
	int large_array_1D[], 
	int small_array_1D[], 
	int size_large, 
	int size_small)
{
	return isin(large_array_1D, small_array_1D, size_large, size_small);
}

int main(int argc, char *argv[])
{
	int large_array_1D[] = {1, 8, 11, 4, 6, 9, 15, 4, 6, 9, 8};
	int small_array_1D[] = {4, 6, 9};
	int size_large = sizeof(large_array_1D) / sizeof(int), 
		size_small = sizeof(small_array_1D) / sizeof(int), 
		result;

	result = Is_large_1D_array_inside_small_1D_array(large_array_1D, small_array_1D, size_large, size_small);
	printf("result == %d\n", result);

	return EXIT_SUCCESS;
}

int isin(int a1[], int a2[], int s1, int s2)
{
	int i;
	for(i = 0 ; i <= s1 - s2 ; i++)
	{
		if(memcmp(a1 + i, a2, s2 * sizeof(int)) == 0) return 1;
	}

	return 0;
}

