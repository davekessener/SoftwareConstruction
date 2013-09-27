#ifndef __EVALUATE_H
#define __EVALUATE_H

#include "include.h"
#include "tokenizer.h"
#include "dstack.h"
#include "logger.h"
#include <math.h>

#define OP_CONST 0
#define OP_ADD	 1
#define OP_SUB	 2
#define OP_MUL	 3
#define OP_DIV	 4
#define OP_EXP	 5
#define OP_LOG	 6
#define OP_LN 	 7
#define OP_SIN	 8
#define OP_COS	 9
#define OP_TAN	10
#define OP_NEG	11

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

typedef struct
{
	int type;
	long double val;
} TOK;

typedef struct __parser
{
	TKN tokenizer;
	TABLE symtable;
	TOK *tkns;
	int c;
} P;

void P_init(P*);
int  P_eval(P*, DS *);
void P_push(P*, TOK);
TOK	 P_poll(P*);
void P_dispose(P*);

void evalAS(P *);
void evalMD(P *);
void evalE(P *);
void evalU(P *);
void evalTL(P *);
void evalC(P *);

int evaluate(const char *, long double *);

#endif

