#include "include.h"

int readShort(short *);
int fromSTDINtoInt(int *);

int main(int argc, char *argv[])
{
	short n1, n2, r;
	int t;

	if(readShort(&n1) || readShort(&n2))
	{
		return EXIT_FAILURE;
	}

	t = n1 * n2;

	if(t < -0x8000 || t >= 0x8000)
	{
		fprintf(stderr, "ERR: Overflow. Result '%d' of '%hd * %hd' is not representable with a signed 16 bit short.\n", t, n1, n2);
		return EXIT_FAILURE;
	}

	r = (short) t;

	printf("%hd * %hd == %hd\n", n1, n2, r);

	return EXIT_SUCCESS;
}

int fromSTDINtoInt(int *r)
{
	char buf[BUF_SIZE];
	int n;

	scanf("%"STRX(BUF_SIZE)"s", buf);
	fflush(stdin);

	return sscanf(buf, " %i %n", r, &n) == 1 && !buf[n];
}

int readShort(short *r)
{
	int t;
	printf("Please enter an integer of the range [-0x8000, 0x8000): ");

	if(!fromSTDINtoInt(&t))
	{
		fprintf(stderr, "ERR: Couldn't read the integer/invalid input.\n");
		return 1;
	}

	if(t < -0x8000 || t >= 0x8000)
	{
		fprintf(stderr, "ERR: Read integer '%d' is too large!\n", t);
		return 1;
	}

	*r = (short) t;

	return 0;
}

