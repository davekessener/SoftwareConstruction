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
inline static CSTR paramHelp(int i)     { static CSTR v[] = {"h", "help"};      return v[i]; }
inline static CSTR paramVerbose(int i)  { static CSTR v[] = {"v", "verbose"};   return v[i]; }
inline static CSTR paramUser(int i)     { static CSTR v[] = {"u", "user"};      return v[i]; }
inline static CSTR paramForce(int i)    { static CSTR v[] = {"f", "force"};     return v[i]; }
inline static CSTR paramLog(int i)      { static CSTR v[] = {"l", "log-file"};  return v[i]; }
inline static CSTR paramCommand(int i)  { static CSTR v[] = {"c", "command"};   return v[i]; }
inline static CSTR paramCrossSum(int i) { static CSTR v[] = {"x", "cross-sum"}; return v[i]; }
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

