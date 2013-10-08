#ifndef __INCLUDE_H
#define __INCLUDE_H

#define BUF_SIZE #{i} //#rbl line.gsub!(/#\{i\}/, 512.to_s)

//#rbi procs
//#ops = {:add => '+', :sub => '-', :mul => '*', :div => '/' }
//#lns = []
//#ops.each do |n, op|
//#	lines.each do |e|
//#		lns << e.gsub(/#\{name\}/, n.to_s).gsub(/#\{op\}/, op)
//#	end
//#end
//#lines = lns
//#rbe

//#rbb
int proc_#{name}(LCELL *cell, CELLS params) 
{
	if(params.c != 2)
	{
		fprintf(stderr, "ERR in primitive '#{name}'.");
		return 1;
	}

	BIGNUM v = 0;

	int i;
	for(i = 0 ; i < params.c ; i++)
	{
		v #{op}= params.cells[i].car.number;
	}

	return 0;
}
//#rbe :procs

#define STR(x) # x
#define STRX(x) STR(x)

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#ifndef FQP
#define FQP long double 
#endif

FQP evalNumber(const char**);

#endif

