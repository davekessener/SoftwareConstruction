#ifndef __LOGGER_H
#define __LOGGER_H

#include "include.h"
#include "evaluate.h"

void setLogger(FILE *);

#ifdef LOGGER_C
FILE *logger = NULL;
#else
#define DLOG(...) if(logger!=NULL){fprintf(logger,__VA_ARGS__);}
extern FILE *logger;
#endif

#endif

