#include "include.h"

int readInt(int *);
int flushEmptySTDIN();

int main(int argc, char *argv[])
{
	int n1, n2, r;
	long long t;

	if(readInt(&n1) || readInt(&n2))
	{
		return EXIT_FAILURE;
	}

	t = n1 * n2;

	if(t < -0x80000000l || t >= 0x80000000l)
	{
		fprintf(stderr, "ERR: Result '%lld' of '%d * %d' is too large to fit in a 32 bit integer.\n", t, n1, n2);
		return EXIT_FAILURE;
	}

	r = (int) t;

	printf("%d * %d == %d\n", n1, n2, r);

	return EXIT_SUCCESS;
}

int readInt(int *r)
{
	char buf[BUF_SIZE], *ptr;
	int t;

	printf("Please enter an integer from the range [-0x80000000, 0x80000000): ");

	fgets(buf, BUF_SIZE - 1, stdin);
	buf[strlen(buf) - 1] = '\0';

//	if(flushEmptySTDIN())
//	{
//		return 1;
//	}

	fflush(stdin);

	errno = 0;
	t = strtol(buf, &ptr, 0);

	if(ERANGE == 0)
	{
		fprintf(stderr, "ERR: Invalid number!\n");
		return 1;
	}
	else if(*ptr)
	{
		fprintf(stderr, "ERR: Found invalid character '%c'.\n", *ptr);
		return 1;
	}
	else
	{
		*r = t;
		return 0;
	}
}

int flushEmptySTDIN(void)
{
	while(!feof(stdin))
	{
		switch(getchar())
		{
			case ' ':
			case '\t':
			case '\n':
			case '\r':
				break;
			default:
				fflush(stdin);
				return 1;
		}
	}

	fflush(stdin);

	return 0;
}

