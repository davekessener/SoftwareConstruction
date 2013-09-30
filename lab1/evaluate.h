#ifndef __EVALUATE_H
#define __EVALUATE_H

//#i"\t$(CC) $(CFLAGS) -DSM_LIB -c stackmachine.c -o stackmachine_lib.o\n"
//#d-stackmachine.c
//#D-stackmachine.c
//#D+stackmachine_lib

#include "include.h"
#include "tokenizer.h"
#include "dstack.h"
#include "logger.h"
#include <math.h>

#define SM_LIB
#include "stackmachine.h"
#undef SM_LIB

#ifdef EVAL_C
#define TOK_NONE	 0
#define TOK_PLUS	 1
#define TOK_MINUS	 2
#define TOK_AST		 3
#define TOK_SLASH	 4
#define TOK_EXP		 5
#define TOK_LOG		 6
#define TOK_LN		 7
#define TOK_SIN		 8
#define TOK_COS		 9
#define TOK_TAN		10
#define TOK_OP		11
#define TOK_CP		12
#define TOK_PI		13
#define TOK_E		14
#define TOK_RUP		15
#define TOK_RDOWN	16
#define TOK_ROUND	17

typedef struct __token
{
	int type;
	long double val;
} TOK;

typedef struct __parser
{
	TKN tokenizer;
	TABLE symtable;
} P;

void P_init(P*);
void P_print(P*, TOK);
void P_dispose(P*);

void evalAS(P *);
void evalMD(P *);
void evalE(P *);
void evalU(P *);
void evalTL(P *);
void evalC(P *);

void stdEvalPrint(const char *);
void (*pFn)(const char *) = stdEvalPrint;
#endif

void setEvalOutput(void (*)(const char *));
int evaluate(const char *);

#endif

