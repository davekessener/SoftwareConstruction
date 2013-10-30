#include <stdio.h>
#include <stdlib.h>
#include "include.h"
#include "printb.h"

#define SWAPMLSB(v) ((((short)(v))&0x7FFE)|((((short)(v))&0x8000)>>15)|((((short)(v))&0x0001)<<15))

int main(int argc, char *argv[])
{
	short v = read_short(argc >= 2 ? argv[1] : NULL);

	printf("Read short:\n\t%s\n", PRINTB(v));

	v = SWAPMLSB(v);

	printf("After switching MSB and LSB:\n\t%s\n", PRINTB(v));

#ifndef UNIX
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

