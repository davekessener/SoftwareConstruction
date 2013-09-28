#ifndef __LOGGER_H
#define __LOGGER_H

#include "include.h"
#include "evaluate.h"

void setLogger(FILE *);

#ifdef LOGGER_C
FILE *logger = NULL;
const char *OP_LOGS[] = {"push", "add", "sub", "mul", "div", "exp", "log", "ln", "sin", "cos", "tan", "neg"};
#else
#define DLOG(...) if(logger!=NULL){fprintf(logger,__VA_ARGS__);}
extern FILE *logger;
extern const char *OP_LOGS[];
#endif

#endif

