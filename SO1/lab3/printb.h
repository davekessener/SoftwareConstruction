#ifndef _PRINTB_H
#define _PRINTB_H

#include <stdio.h>
#include <assert.h>
#include "include.h"

#define BYTE_SIZE 8

#define PRINTB(v) printb(&(v),sizeof(v),getCharBuf(),BUF_SIZE)

char *getCharBuf();

const char *printb(void *, size_t, char *, size_t);

short read_short(const char *);

#endif

