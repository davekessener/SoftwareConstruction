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

char *getCharBuf()
{
	static char buf[BUF_SIZE];

	return buf;
}

