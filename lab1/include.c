#include "include.h"

// Is the character c somewhere within the string l?
int isIn(const char *l, char c) { while(*l) { if(*l == c) return 1; l++; } return 0; }

FQP evalNumber(const char **src)
{
	const char *digits = (const char *) "fedcba9876543210";
	const char *line = *src;

	long double val = 0.0;
	int base = 10, off = 1;
	int dec = 0, f = 0, v;

	// Read next character
	char c = *line++;

	// If the first character is a zero ...
	// (Indicates either a hexadecimal number '0x...',
	//  an binary number '0b...' or an octal number '0...'
	if(c == '0')
	{
		c = *line++;

		// A '0' followed by an 'x' -> Hexadecimal
		if(c == 'x')
		{
			c = *line++;
			base = 16;
		}
		// A '0' followed by a 'b' -> Binary
		else if(c == 'b')
		{
			c = *line++;
			base = 2;
		}
		// A '0' followed by a '.' -> Not an octal number 
		else if(c != '.')
		{
			base = 8;
		}
		// Decimal number, set flag for reading the
		// fractional part.
		else
		{
			f = 1;
		}
	}

	// While c is a valid character for the specified base
	while(c && ((dec == 0 && c == '.') || isIn(digits + 16 - base, c)))
	{
		// In case of a dot, set flag for the fractional part of the number
		if(c == '.')
		{
			dec = 1;
			c = *line++;

			// Reset 'successfull read'-flag, since a number
			// may not end with a dot
			f = 0;

			continue;
		}

		// Number representation -> Number
		v = c;
		if(c >= '0' && c <= '9') v -= '0';
		if(c >= 'a' && c <= 'f') v -= 'a' - 10;

		// With hexadecimal as largest numeral system,
		// no single digit can be larger than 15(10)
		assert(v<16);

		// If we are reading the fractional part of the number
		if(dec)
		{
			// Shift offset left one digit
			off *= base;
			// Add the number (shifted right by offset) to the result
			val += (long double)v / off;
		}
		else
		{
			// Shift result left one digit
			val *= base;
			// Add the number to the result
			val += v;
		}

		// Set flag indication a successfull read
		f = 1;
		// Read next character
		c = *line++;
	}

	// Assure at least one digit has been read
	assert(f);

	// Update string pointer
	*src = line - 1;

	// Cast to desired number format and return result
	return (FQP) val;
}

void printNumber(FQP n, int b, void (*pf)(char))
{
	const char *digits = (const char *) "0123456789abcdefghijklmnopqrstuvwxyz";
	char buf[1024];
	int i, j, k, t;

	if(n < 0)
	{
		pf('-');
		n = -n;
	}

	if(b <= 0 || b >= strlen(digits)) b = 10;

	i = 0;
	while(n >= 1)
	{
		t = ((long long) n) % b;
		n = (n - ((long long) n)) + (FQP) (((long long) n) / b);
		buf[i++] = (char) t;
	}

	while(i > 0)
	{
		pf(digits[buf[--i]]);
	}

	if(n > 0)
	{
		pf('.');

		for(i = 0, j = 0 ; i < MAX_DIGITS ; i++)
		{
			n *= b;
			t = (int) n;
			n -= t;

			buf[j++] = (char) t;
			
			if(t > 0)
			{
				for(k = 0 ; k < j ; k++) pf(digits[buf[k]]);
				j = 0;
			}
		}
	}
}

