#include "include.h"

int inline isIn(const char *l, char c) { while(*l) { if(*l == c) return 1; l++; } return 0; }

FQP evalNumber(const char **src)
{
	const char *digits = (const char *) "fedcba9876543210";
	const char *line = *src;

	long double val = 0.0;
	int base = 10, off = 1;
	int dec = 0, f = 0;

	char c = *line++;

	if(c == '0')
	{
		c = *line++;
		if(c == 'x')
		{
			c = *line++;
			base = 16;
		}
		else if(c == 'b')
		{
			c = *line++;
			base = 2;
		}
		else if(c != '.')
		{
			base = 8;
		}
		else
		{
			f = 1;
		}
	}

	while(c && (c == '.' || isIn(digits + 16 - base, c)))
	{
		if(c == '.')
		{
			dec = 1;
			c = *line++;
			continue;
		}

		int v = c;
		if(c >= '0' && c <= '9') v -= '0';
		if(c >= 'a' && c <= 'f') v -= 'a' - 10;

		assert(v<16);

		if(dec)
		{
			off *= base;
			val += (long double)v / off;
		}
		else
		{
			val *= base;
			val += v;
		}

		f = 1;
		c = *line++;
	}

	assert(f);

	*src = line - 1;

	return (FQP) val;
}

