#ifndef __LOGGER_H
#define __LOGGER_H

#include "include.h"
#include "evaluate.h"

// Change standard log-file (NULL)
void setLogger(FILE *);
// Function that return a pointer to a static pointer to a FILE
FILE **getLogger();

// Print to the standard logfile if it is not NULL
#ifndef LOGGER_C
#define DLOG(...) if(*getLogger()!=NULL){fprintf(*getLogger(),__VA_ARGS__);}
#endif

#endif

