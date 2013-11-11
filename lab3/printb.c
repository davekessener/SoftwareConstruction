#include "printb.h"

const char *printb(void *src, size_t l, char *buf, size_t n)
{
	int i, j;
	char *ptr = src;

	assert(n>(BYTE_SIZE + 1)*l);

	j = 0;
	while(l-- > 0)
	{
		for(i = 0 ; i < BYTE_SIZE ; i++)
		{
			buf[j + BYTE_SIZE - i - 1] = (ptr[l] & (1 << i)) ? '1' : '0';
		}

		j += BYTE_SIZE;

		if(l) buf[j++] = ' ';

		buf[j] = '\0';
	}

	return buf;
}

#define readX(x) x read_##x (const char *in) \
{ \
	char buf[BUF_SIZE]; const char *tmp; \
	if(in) strncpy(buf, in, BUF_SIZE - 1); \
	else if(!gets(buf)) \
	{ \
		fprintf(stderr, "ERR: Couldn't read from stdin.\nAbort.\n"); \
		exit(EXIT_FAILURE); \
	} \
	tmp = buf; \
	return ( x ) evalNumber(&tmp); \
}
readX(short)

char *getCharBuf()
{
	static char buf[BUF_SIZE];

	return buf;
}

