#ifndef __TOKENIZER_H
#define __TOKENIZER_H

#define TAG_NONE	0
#define TAG_TAG		1
#define TAG_VALUE	2
#define T_BUF_SIZE 1024

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "include.h"

typedef struct
{
	char *src;
	char *cp, *pp;
} TKN;

typedef struct
{
	union
	{
		int tag;
		FQP val;
	} data;
	int type;
} T;

typedef struct
{
	char **ids;
	int *vals;
	int c;
} TABLE;

void TKN_init(TKN*);
void TKN_load(TKN*, const char *);
T	 TKN_get(TKN*, TABLE *);
void TKN_unget(TKN*);
void TKN_dispose(TKN*);

void TABLE_init(TABLE*);
void TABLE_add(TABLE*, const char *, int);
int  TABLE_find(TABLE*, const char *);
void TABLE_dispose(TABLE*);

void deleteWhitespace(char *);

#endif

