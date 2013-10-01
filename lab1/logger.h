#ifndef __LOGGER_H
#define __LOGGER_H

#include "include.h"
#include "evaluate.h"

void setLogger(FILE *);
FILE **getLogger();

#ifndef LOGGER_C
#define DLOG(...) if(*getLogger()!=NULL){fprintf(*getLogger(),__VA_ARGS__);}
#endif

#endif

