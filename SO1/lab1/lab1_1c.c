#include "include.h"

int readInt(int, long long *);

int main(int argc, char *argv[])
{
	long long n1, n2;
	int w = 16;

	if(readInt(w, &n1) || readInt(w, &n2))
	{
		return EXIT_FAILURE;
	}

	printf("%lld * %lld == %lld\n", n1, n2, n1 * n2);

	return EXIT_SUCCESS;
}

void skipWhitespace()
{
	int c;

	while((c = getchar()) == ' ' || c == '\t');
	ungetc(c, stdin);
}

int contained(int c, const char *p) { while(*p) { if(*p++ == c) return 1; } return 0; }
void toLower(int *c) { if(*c >= 'A' && *c <= 'Z') { *c -= 'A' - 'a'; } }

int readInt(int w, long long *r)
{
	const char *digits = (const char *) "fedcba9876543210";
	long long v = 0l, width = (1l << (w - 1l));
	int s = 1, b = 10, f = 0, c;

	printf("Please enter a number of the range [-0x%llX, 0x%llX): ", width, width);

	skipWhitespace();

	c = getchar();

	if(c == '-' || c == '+')
	{
		s = c == '-' ? -1 : 1;
		c = getchar();
	}

	if(c == '0')
	{
		c = getchar();
		if(c == 'x' || c == 'X')
		{
			c = getchar();
			b = 16;
		}
		else
		{
			b = 8;
		}
	}

	toLower(&c);

	while(contained(c, digits + 16 - b))
	{
		if(c >= '0' && c <= '9') c -= '0';
		if(c >= 'a' && c <= 'f') c -= 'a' - 10;

		v *= b;
		v += c;

		if(v * s < -width || v * s >= width)
		{
			fprintf(stderr, "ERR: Number is too large!\n");
			fflush(stdin);
			return 1;
		}

		f = 1;

		c = getchar();
		toLower(&c);
	}

	if(!f)
	{
		fprintf(stderr, "ERR: Invalid input!\n");
		return 1;
	}

	if(c != '\n')
	{
		fprintf(stderr, "ERR: Invalid character '%c'!\n", (char) c);
		return 1;
	}

	v *= s;

	*r = v;

	fflush(stdin);

	return 0;
}

