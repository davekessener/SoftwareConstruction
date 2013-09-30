#ifndef __PARAMS_H
#define __PArAMS_H

#include <stdlib.h>
#include "parameter.h"

#define FLAG_NONE 0
#define FLAG_HELP 1
#define FLAG_VERBOSE 2
#define FLAG_USER 4
#define FLAG_FORCE 8
#define FLAG_LOG 16
#define FLAG_COMMAND 32
#define FLAG_CROSSSUM 64

#ifdef PARAMS_C
typedef const char const * CSTR;
CSTR paramHelp[]     = {"h", "help"};
CSTR paramVerbose[]  = {"v", "verbose"};
CSTR paramUser[]     = {"u", "user"};
CSTR paramForce[]    = {"f", "force"};
CSTR paramLog[]      = {"l", "log-file"};
CSTR paramCommand[]  = {"c", "command"};
CSTR paramCrossSum[] = {"x", "cross-sum"};
#endif

typedef struct
{
	int flags;
	FILE *logFile;
	char *command;
} PARAMS;

void readParameter(PARAMS*, int, char **);
void disposeParameter(PARAMS*);

#endif

