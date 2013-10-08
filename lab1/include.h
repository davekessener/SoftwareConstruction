#ifndef __INCLUDE_H
#define __INCLUDE_H

#define BUF_SIZE 1024

// Macro for string insertion.
// Currently unused.
#define STR(x) # x
#define STRX(x) STR(x)

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

// Default to using long doubles if there
// was no number-type predefined with the
// compiler-call
#ifndef FQP
#define FQP long double 
#endif

// Defines PI and E globally
inline static double PI(void)
{
	static double pi = 4.0 * atan(1.0);
	return pi;
}

inline static double E(void)
{
	static double e = exp(1.0);
	return e;
}

// Reads a number from a string, updates pointer
// position.
FQP evalNumber(const char**);

#endif

