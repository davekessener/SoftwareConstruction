#include <stdio.h>
#include <stdlib.h>
#include "include.h"
#include "printb.h"

#define TOGGLE_MSB(v) ((v)^(1<<(sizeof(v)*BYTE_SIZE-1)))

int main(int argc, char *argv[])
{
	short v = read_short(argc >= 2 ? argv[1] : NULL);

	printf("Read short:\n\t%s\n", PRINTB(v));

	v = TOGGLE_MSB(v);

	printf("After toggling the MSG:\n\t%s\n", PRINTB(v));

	return EXIT_SUCCESS;
}

