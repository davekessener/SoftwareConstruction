#include <math.h>
#include "include.h"
#include "parameter.h"
#include "dstack.h"

#define FLAG_NONE 0
#define FLAG_VERBOSE 1

#define ERR_NONE 0
#define ERR_INPUT 1
#define ERR_EMPTY 2
#define ERR_UNKNOWN 3

#define STR_EQ(s,v) strcmp(s,v)==0

const char const *flagVerbose[] = {"v", "verbose"};

typedef struct
{
	int flags;
} PARAMS;

void readParameter(PARAMS*, int, char **);
int  interpret(DS*, char *);

int main(int argc, char *argv[])
{
	char buf[2048];

	PARAMS p;
	DS stack;

	readParameter(&p, argc, argv);
	DS_init(&stack);

	while(1)
	{
		gets(buf);

		if(feof(stdin) || !buf[0]) break;

		if(p.flags & FLAG_VERBOSE) { printf("%s\n", buf); }

		switch(interpret(&stack, buf))
		{
			case ERR_INPUT:
				fprintf(stderr, "ERR: Invalid input '%.16s'\nAbort.\n", buf);
				DS_dispose(&stack);
				return EXIT_FAILURE;
			case ERR_EMPTY:
				fprintf(stderr, "ERR: Empty stack!\nAbort.\n");
				DS_dispose(&stack);
				return EXIT_FAILURE;
			case ERR_UNKNOWN:
				fprintf(stderr, "ERR: Unknown command '%.16s'!\nAbort.\n", buf);
				DS_dispose(&stack);
				return EXIT_FAILURE;
		}

		if(p.flags & FLAG_VERBOSE) { printf("%Lg\n", stack.data[stack.i - 1]); }
	}

	printf("%Lg\n", stack.data[stack.i - 1]);

	DS_dispose(&stack);

	return EXIT_SUCCESS;
}

void readParameter(PARAMS *p, int argc, char **argv)
{
	p->flags = FLAG_NONE;

	PTABLE t;
	PTABLE_init(&t);

	PTABLE_addParameter(&t, flagVerbose[0], flagVerbose[1], PARAM_NONE);

	PTABLE_read(&t, argc, argv);

	if(PTABLE_hasArgument(&t, flagVerbose[0])) p->flags |= FLAG_VERBOSE;

	PTABLE_dispose(&t);
}

int  interpret(DS *stack, char *input)
{
	char buf[1024];
	long double v1, v2;

	if(!*input) return ERR_INPUT;

	sscanf(input, " %s", buf);

	if(STR_EQ(buf, "push"))
	{
		if(!sscanf(input + 4, " %Lf", &v1)) return ERR_INPUT;
		DS_push(stack, v1);
	}
	else 
	{
		if(stack->c < 1) return ERR_EMPTY;
		v1 = DS_pop(stack);

		if(STR_EQ(buf, "neg"))
		{
			DS_push(stack, -v1);
		}
		else if(STR_EQ(buf, "sin"))
		{
			while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
			while(v1 < 0.0) v1 += 2.0 * M_PI;
			DS_push(stack, (long double) sin((double) v1));
		}
		else if(STR_EQ(buf, "cos"))
		{
			while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
			while(v1 < 0.0) v1 += 2.0 * M_PI;
			DS_push(stack, (long double) cos((double) v1));
		}
		else if(STR_EQ(buf, "tan"))
		{
			while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
			while(v1 < 0.0) v1 += 2.0 * M_PI;
			DS_push(stack, (long double) tan((double) v1));
		}
		else if(STR_EQ(buf, "log") || STR_EQ(buf, "lg"))
		{
			DS_push(stack, (long double) log10((double) v1));
		}
		else if(STR_EQ(buf, "ln"))
		{
			DS_push(stack, (long double) log((double) v1));
		}
		else
		{
			if(stack->c < 1) return ERR_EMPTY;
			v2 = DS_pop(stack);

			if(STR_EQ(buf, "add"))
			{
				DS_push(stack, v2 + v1);
			}
			else if(STR_EQ(buf, "sub"))
			{
				DS_push(stack, v2 - v1);
			}
			else if(STR_EQ(buf, "mul"))
			{
				DS_push(stack, v2 * v1);
			}
			else if(STR_EQ(buf, "div"))
			{
				DS_push(stack, v2 / v1);
			}
			else if(STR_EQ(buf, "exp"))
			{
				DS_push(stack, (long double) pow((double) v2, (double) v1));
			}
			else
			{
				return ERR_UNKNOWN;
			}
		}
	}

	return ERR_NONE;
}

