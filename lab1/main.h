#ifndef __MAIN_H
#define __MAIN_H

#include "include.h"
#include "evaluate.h"
#include "logger.h"
#include "parameter.h"
#include "params.h"
#include "dstack.h"

#define SM_LIB
#include "stackmachine.h"
#undef SM_LIB

// Runs the tokenizer, parser and the stackmachine.
// Called by the main functions of the assignment with
// appropriate arguments.
int executeNumberEvaluator(int, char **);

#endif

