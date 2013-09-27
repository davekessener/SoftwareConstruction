#ifndef __PARAMETER_H
#define __PARAMETER_H

#include <string.h>
#include <assert.h>

#define P_MAX 32

typedef struct
{
	char *args[P_MAX];
	char *vals[P_MAX];
	char *fullName, *name;
	int argc;
} PT;

void PT_init(PT*);
void PT_read(PT*, int, char **);
int  PT_hasKey(PT*, const char *);
const char *PT_getValue(PT*, const char *);
void PT_dispose(PT*);

#endif

