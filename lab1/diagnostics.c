#include "diagnostics.h"

void printBin(int v, int s)
{
	int i;
	for(i = s - 1 ; i >= 0 ; i--)
	{
		printf("%d", (v >> i) & 1);
	}
}

