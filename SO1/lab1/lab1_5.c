/* Solution for Assignment 5 of Lab 1 in Software Construction
 * File:     lab1_5.c
 * Includes: main.h include.h evaluate.h stackmachine.h
 *           params.h parameter.h logger.h dstack.h tokenizer.h
 * Daniel Kessener, HAW
 */
#include "main.h"

int main(int argc, char *argv[])
{
	int i, r, s;
	char **tmp;

	s = argc > 1 ? 2 : 1;

	tmp = malloc((argc + s) * sizeof(char *));
	tmp[0] = strdup(argv[0]);
	tmp[1] = strdup("-x");

	if(argc > 1)
	{
		tmp[2] = strdup("-c");
	
		for(i = 3 ; i < argc + 2 ; i++)
		{
			tmp[i] = strdup(argv[i - 2]);
		}
	}

	r = executeNumberEvaluator(argc + s, tmp);

	for(i = 0 ; i < argc + s ; i++)
	{
		free(tmp[i]);
	}
	free(tmp);

#ifndef UNIX
	system("pause>NUL");
#endif

	return r;
}
