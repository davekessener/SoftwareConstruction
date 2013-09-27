#include "logger.h"

int main(int argc, char *argv[])
{
	setLogger(stdout);
	DLOG("Test%d\n", 5);
	return 0;
}

