#ifndef __STACKMACHINE_H
#define __STACKMACHINE_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include "dstack.h"

enum SM_ERR
{
	SM_ERR_NONE,
	SM_ERR_INPUT,
	SM_ERR_EMPTY,
	SM_ERR_UNKNOWN
};

//#define SM_ERR_NONE 0
//#define SM_ERR_INPUT 1
//#define SM_ERR_EMPTY 2
//#define SM_ERR_UNKNOWN 3

enum SM_OP
{
	SM_OP_PUSH,
	SM_OP_ADD,	
	SM_OP_SUB,	
	SM_OP_MUL,	
	SM_OP_DIV,	
	SM_OP_EXP,	
	SM_OP_LOG,	
	SM_OP_LG,	
	SM_OP_LN,	
	SM_OP_SIN,	
	SM_OP_COS,	
	SM_OP_TAN,	
	SM_OP_NEG,	
	SM_OP_RUP,	
	SM_OP_RDWN,
	SM_OP_RND,	
	SM_OP_XSUM
};

//#define SM_OP_PUSH	 0
//#define SM_OP_ADD	 1
//#define SM_OP_SUB	 2
//#define SM_OP_MUL	 3
//#define SM_OP_DIV	 4
//#define SM_OP_EXP	 5
//#define SM_OP_LOG	 6
//#define SM_OP_LG	 7
//#define SM_OP_LN 	 8
//#define SM_OP_SIN	 9
//#define SM_OP_COS	10
//#define SM_OP_TAN	11
//#define SM_OP_NEG	12
//#define SM_OP_RUP	13
//#define SM_OP_RDWN	14
//#define SM_OP_RND	15
//#define SM_OP_XSUM	16

inline static const char *SM_OP_Instructions(int i)
{
	static const char *SM_OP_INS[] = {
		"push", 
		"add", 
		"sub", 
		"mul", 
		"div", 
		"exp", 
		"log", 
		"lg",
		"ln", 
		"sin", 
		"cos", 
		"tan", 
		"neg", 
		"rup", 
		"rdown", 
		"round",
		"xsum"};
	
	return SM_OP_INS[i];
}

#define STR_EQ(s,v) strcmp(s,v)==0

#ifndef SM_LIB
#include "include.h"
#include "parameter.h"

#define FLAG_NONE 0
#define FLAG_VERBOSE 1

const char const *flagVerbose[] = {"v", "verbose"};

typedef struct
{
	int flags;
} PARAMS;

void readParameter(PARAMS*, int, char **);
#endif

int  interpret(DS*, const char *);

#endif

