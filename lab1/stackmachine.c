#define STACKMACHINE_C
#include "stackmachine.h"
#undef STACKMACHINE_C

#ifndef SM_LIB
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
			case SM_ERR_INPUT:
				fprintf(stderr, "ERR: Invalid input '%.16s'\nAbort.\n", buf);
				DS_dispose(&stack);
				return EXIT_FAILURE;
			case SM_ERR_EMPTY:
				fprintf(stderr, "ERR: Empty stack!\nAbort.\n");
				DS_dispose(&stack);
				return EXIT_FAILURE;
			case SM_ERR_UNKNOWN:
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
#endif

int  interpret(DS *stack, const char *input)
{
	char buf[1024];
	long double v1, v2;

	if(!*input) return SM_ERR_INPUT;

	sscanf(input, " %s", buf);

#define BEQ(i) (strcmp(buf, SM_OP_INS[i])==0)

	if(BEQ(SM_OP_PUSH))
	{
		if(!sscanf(input + 4, " %Lf", &v1)) return SM_ERR_INPUT;
		DS_push(stack, v1);
	}
	else 
	{
		if(stack->c < 1) return SM_ERR_EMPTY;
		v1 = DS_pop(stack);

		if(BEQ(SM_OP_NEG))
		{
			DS_push(stack, -v1);
		}
		else if(BEQ(SM_OP_SIN))
		{
			while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
			while(v1 < 0.0) v1 += 2.0 * M_PI;
			DS_push(stack, (long double) sin((double) v1));
		}
		else if(BEQ(SM_OP_COS))
		{
			while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
			while(v1 < 0.0) v1 += 2.0 * M_PI;
			DS_push(stack, (long double) cos((double) v1));
		}
		else if(BEQ(SM_OP_TAN))
		{
			while(v1 > 2.0 * M_PI) v1 -= 2.0 * M_PI;
			while(v1 < 0.0) v1 += 2.0 * M_PI;
			DS_push(stack, (long double) tan((double) v1));
		}
		else if(BEQ(SM_OP_LOG) || BEQ(SM_OP_LG))
		{
			DS_push(stack, (long double) log10((double) v1));
		}
		else if(BEQ(SM_OP_LN))
		{
			DS_push(stack, (long double) log((double) v1));
		}
		else if(BEQ(SM_OP_RUP))
		{
			v2 = v1 < 0.0L ? -1.0L : 1.0L; v1 = v1 < 0.0L ? -v1 : v1;
			DS_push(stack, v2 * ((long double) ((long long) (v1 + 0.999999L))));
		}
		else if(BEQ(SM_OP_RDWN))
		{
			v2 = v1 < 0.0L ? -1.0L : 1.0L; v1 = v1 < 0.0L ? -v1 : v1;
			DS_push(stack, v2 * ((long double) ((long long) v1)));
		}
		else if(BEQ(SM_OP_RND))
		{
			v2 = v1 < 0.0L ? -1.0L : 1.0L; v1 = v1 < 0.0L ? -v1 : v1;
			DS_push(stack, v2 * ((long double) ((long long) (v1 + 0.5L))));
		}
		else if(BEQ(SM_OP_XSUM))
		{
			long long t = (long long) (v1 < 0.0L ? -v1 : v1);
			v1 = 0.0L;
			while(t > 0)
			{
				v1 += t % 10;
				t /= 10;
			}
			DS_push(stack, v1);
		}
		else
		{
			if(stack->c < 1) return SM_ERR_EMPTY;
			v2 = DS_pop(stack);

			if(BEQ(SM_OP_ADD))
			{
				DS_push(stack, v2 + v1);
			}
			else if(BEQ(SM_OP_SUB))
			{
				DS_push(stack, v2 - v1);
			}
			else if(BEQ(SM_OP_MUL))
			{
				DS_push(stack, v2 * v1);
			}
			else if(BEQ(SM_OP_DIV))
			{
				DS_push(stack, v2 / v1);
			}
			else if(BEQ(SM_OP_EXP))
			{
				DS_push(stack, (long double) pow((double) v2, (double) v1));
			}
			else
			{
				return SM_ERR_UNKNOWN;
			}
		}
	}

	return SM_ERR_NONE;
#undef BEQ
}

