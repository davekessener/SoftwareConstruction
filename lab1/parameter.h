#ifndef __PARAMETER_H
#define __PARAMETER_H

#include <string.h>
#include <malloc.h>

#define PARAM_NONE	0
#define PARAM_ONE	1
#define PARAM_MANY	2

#define STATUS_OK 0
#define STATUS_DUPLICATE 1
#define STATUS_UNKNOWN 2

struct __parameter_type
{
	char *shortName, *fullName;
	int argType;
};

#ifdef PARAMETER_C
typedef struct __parameter_type PTYPE;

void PTYPE_init(PTYPE*, const char *, const char *, int);
void PTYPE_dispose(PTYPE*);
#endif

struct __parameter
{
	char *id;
	char **vals;
	int status;
};

#ifdef PARAMETER_C
typedef struct __parameter PARA;

void PARA_init(PARA*, const char *);
int  PARA_getSize(PARA*);
void PARA_addValue(PARA*, const char *);
void PARA_dispose(PARA*);
#endif

typedef struct
{
	struct __parameter_type *types;
	struct __parameter *params;
	char *name, *fullName;
	int tc, pc;
	int status;
} PTABLE;

void   PTABLE_init(PTABLE*);
void   PTABLE_addParameter(PTABLE*, const char *, const char *, int);
void   PTABLE_read(PTABLE*, int, char **);
int    PTABLE_hasArgument(PTABLE*, const char *);
char  *PTABLE_getValue(PTABLE*, const char *);
char **PTABLE_getValues(PTABLE*, const char *);
void   PTABLE_dispose(PTABLE*);

#ifdef PARAMETER_C
int    PTABLE_getIndex(PTABLE*, const char *);
#endif

#endif

