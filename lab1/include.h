/* Header for include.c that contains auxiliary function
 * used to read/print numbers
 * File: include.h for include.c
 * Daniel Kessener, HAW
 */
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

// Default maximum amount of printed digits
#ifndef MAX_DIGITS
#define MAX_DIGITS 8
#endif

// Defines PI and E globally
#define PI 3.14159265359
#define E  2.71828182846

// Reads a number from a string, updates pointer
// position.
FQP evalNumber(const char**);
// Print a number in the specified base
void printNumber(FQP, int, void (*)(char));

#endif

