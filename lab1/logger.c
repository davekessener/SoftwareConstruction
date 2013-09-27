#define LOGGER_C
#include "logger.h"
#undef LOGGER_C

void setLogger(FILE *f)
{
	logger = f;
}

