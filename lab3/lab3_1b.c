#include <stdio.h>
#include <stdlib.h>
#include "include.h"
#include "printb.h"

int main(int argc, char *argv[])
{
	short v = read_short(argc >= 2 ? argv[1] : NULL);

	printf("Read short:\n\t%s\n", PRINTB(v));

	// Set bits 0 and 1 to 1.
	// Doesn't even warrant its own macro.
	// Seriously.
	// Seven characters.
	// Including the semicolon.
	v |= 3;

	printf("After setting bits 0 and 1 to 1:\n\t%s\n", PRINTB(v));

#ifndef UNIX
	system("pause>NUL");
#endif
	
	return EXIT_SUCCESS;
}

