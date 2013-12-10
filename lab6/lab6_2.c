#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>

//------------------- prototypes ----------------------------- 
double* allocate_mem_on_heap_for_vector_1D(int N);
double ** allocate_mem_on_heap_for_matrix_2D( int N);
void free_mem_on_heap_for_vector_1D( double *);
void free_mem_on_heap_for_matrix_2D( double **, int N);
void copy_vector_1D_from_stack_to_heap( double p2vector_1D_on_stack[], double p2vector_1D_on_heap[], int N);
void copy_vector_1D_from_heap_to_stack( double vector_1D_on_heap[], double vector_1D_on_stack[], int N);
double * vector_1D_add( double *p2A, double *p2B, int N);
double dot_product( double *p2A, double *p2B, int N);
double ** column_vector_1D_times_row_vector_1D( double *p2A, double *p2B, int N);
void print_vector_1D( double *p2_vec, int N);
void print_matrix_2D( double **p2p2_matrix, int N);
//------------------------------------------------------------ 
//------------------- main program, variables --------------------- 
int main(int argc, char *argv[])
{ 
	double A_on_stack[] = {1, 2, 3, 4};
	double B_on_stack[] = {11, 22, 33, 44};
	double *p2A_on_heap = NULL;
	double *p2B_on_heap = NULL;
	double *p2C_on_heap = NULL;
	double *p2D_on_heap = NULL;
	double dot_prod_val;
	int elements;
	double **p2_matrix2D_on_heap = NULL;

	//-------------------------------------------------------------- 
	// code starts: 
	// calculate the number of elements 

	elements = sizeof (A_on_stack)/ sizeof ( double );
	printf( "number of elements in vectors : %d\n\n" , elements);

	// allocate space for vectors A and B on heap 
	p2A_on_heap = allocate_mem_on_heap_for_vector_1D(elements);
	p2B_on_heap = allocate_mem_on_heap_for_vector_1D(elements);

	// copy vectors A and B from stack to heap 
	copy_vector_1D_from_stack_to_heap(A_on_stack, p2A_on_heap, elements);
	copy_vector_1D_from_stack_to_heap(B_on_stack, p2B_on_heap, elements);

	// computes C = A + B. Note : A, B and C are on heap 
	p2C_on_heap = vector_1D_add(p2A_on_heap, p2B_on_heap, elements);
	printf( "vector addition:\n" );
	print_vector_1D(p2C_on_heap, elements);

	// computes dot_prod(A, B), A and B on heap, result is a SCALAR value on stack 
	dot_prod_val= dot_product(p2A_on_heap, p2B_on_heap, elements);
	printf( "\ndot_prod_val = %lf\n\n" , dot_prod_val);

	// calculate 1D column vector times 1D row vector --> matrix 
	p2_matrix2D_on_heap = column_vector_1D_times_row_vector_1D(p2A_on_heap, p2B_on_heap, elements);
	printf( "1D column vector times 1D row vector :\n" );
	print_matrix_2D(p2_matrix2D_on_heap, elements);

	// free memory 
	free_mem_on_heap_for_vector_1D(p2A_on_heap);
	free_mem_on_heap_for_vector_1D(p2B_on_heap);
	free_mem_on_heap_for_matrix_2D(p2_matrix2D_on_heap, elements);

	return EXIT_SUCCESS;
} // end of main  

double* allocate_mem_on_heap_for_vector_1D(int n)
{
	return malloc(n * sizeof(double));
}

double ** allocate_mem_on_heap_for_matrix_2D(int n)
{
	return malloc(n * sizeof(double *));
}

void free_mem_on_heap_for_vector_1D(double *v)
{
	free(v);
}

void free_mem_on_heap_for_matrix_2D(double **m, int n)
{
	while(n-- > 0)
	{
		free(m[n]);
	}

	free(m);
}

void copy_vector_1D_from_stack_to_heap(double p2vector_1D_on_stack[], double p2vector_1D_on_heap[], int n)
{
	memcpy(p2vector_1D_on_heap, p2vector_1D_on_stack, n * sizeof(double));
}

void copy_vector_1D_from_heap_to_stack(double vector_1D_on_heap[], double vector_1D_on_stack[], int n)
{
	memcpy(vector_1D_on_stack, vector_1D_on_heap, n * sizeof(double));
}

double * vector_1D_add(double *p2A, double *p2B, int n)
{
	double *r = malloc(n * sizeof(double)), *v = r;

	while(n--)
	{
		*v++ = *p2A++ + *p2B++;
	}

	return r;
}

double dot_product(double *p2A, double *p2B, int n)
{
	double a = 0.0;

	while(n--)
	{
		a += *p2A++ * *p2B++;
	}

	return a;
}

double ** column_vector_1D_times_row_vector_1D(double *p2A, double *p2B, int n)
{
	double **m = malloc(n * sizeof(double *));
	int i, j;

	for(i = 0 ; i < n ; i++)
	{
		m[i] = malloc(n * sizeof(double));

		for(j = 0 ; j < n ; j++)
		{
			m[i][j] = p2A[i] * p2B[j];
		}
	}

	return m;
}

void print_vector_1D(double *p2_vec, int n)
{
	printf("{");

	while(n--)
	{
		printf("%lg%s", *p2_vec++, n ? ", " : "}");
	}
}

void print_matrix_2D(double **p2p2_matrix, int n)
{
	int i;
	for(i = 0 ; i < n ; i++)
	{
		printf("%c", i ? ' ' : '{');
		print_vector_1D(p2p2_matrix[i], n);
		printf("%c\n", i == n - 1 ? '}' : ',');
	}
}

