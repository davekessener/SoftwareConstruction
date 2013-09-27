#ifndef __LOGGER_H
#define __LOGGER_H

#include "include.h"
#include "evaluate.h"

typedef const char * C_STR;

void setLogger(FILE *);

#ifdef LOGGER_C
FILE *logger = NULL;
const C_STR OP_LOGS[] = {"push", "add", "sub", "mul", "div", "exp", "log", "ln", "sin", "cos", "tan", "neg"};
#else
#define DLOG(...) if(logger!=NULL){fprintf(logger,__VA_ARGS__);}
extern FILE *logger;
extern const C_STR OP_LOGS[];
#endif

#endif

