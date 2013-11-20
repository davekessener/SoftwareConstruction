#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8
#define M 5
#define BYTE_SIZE 8

#define RSTMSB(v) ((v)=(v)&~(1<<(sizeof(v)*BYTE_SIZE-1)))

void clear_MSBs(unsigned char[], unsigned char[]);
const char *printbin(uint8_t, char *);

int isin(unsigned char v, unsigned char a[], size_t s) {int i; for(i = 0 ; i < s ; i++) if(a[i] == v) return 1; return 0; }

int main(int argc, char *argv[])
{
	unsigned char dest_array[N] = {246, 249, 250, 251, 252, 253, 254, 255};
	unsigned char array_indices[M] = {0, 2, 3, 6, 7};
	char printbuf[BYTE_SIZE + 1];
	int i;

	clear_MSBs(dest_array, array_indices);

	printf(	"Modified array:\n\t('*' == modified)\n"
			"Index | Value | Value(binary)\n------+-------+----------\n");

	for(i = 0 ; i < N ; i++)
	{
		printf(" %c%02d  |  %.3d  | %.*s\n", isin(i, array_indices, M) ? '*' : ' ', 
			i, dest_array[i], BYTE_SIZE, printbin(dest_array[i], printbuf));
	}

	return EXIT_SUCCESS;
}

void clear_MSBs(unsigned char dst[], unsigned char ind[])
{
	int i;
	for(i = 0 ; i < M ; i++)
	{
		if(ind[i] >= 0 && ind[i] < N)
		{
			RSTMSB(dst[ind[i]]);
		}
		else
		{
			break;
		}
	}
}

const char *printbin(uint8_t v, char *buf)
{
	int i;

	for(i = 0 ; i < BYTE_SIZE ; i++)
	{
		buf[BYTE_SIZE - i - 1] = ((v >> i) & 1) ? '1' : '0';
	}

	buf[BYTE_SIZE] = '\0';

	return buf;
}

