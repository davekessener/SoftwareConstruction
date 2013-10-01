#include "include.h"
#include "evaluate.h"
#include "logger.h"
#include "parameter.h"
#include "params.h"
#include "dstack.h"

#define SM_LIB
#include "stackmachine.h"
#undef SM_LIB

void evalStack(const char *);
DS *getStack();

int main(int argc, char *argv[])
{
	char buf[2048];
	long double r = 0.0L;
	int err;
	DS *stack = getStack();

	PARAMS params;
	DS_init(stack);

	readParameter(&params, argc, argv);
	
	if(params.flags & FLAG_HELP)
	{
		printf("Usage: %s [-h] [-v] [-u] [-x] [-f] [-l logfile] [-c command]\n", argv[0]);
		printf("\t'-h' prints help.\n");
		printf("\t'-v' enters verbose mode.\n");
		printf("\t'-u' enters user-mode.\n");
		printf("\t'-x' calculates the cross-sum of the result.\n");
		printf("\t'-f' forces continuation after an error.\n");
		printf("\t'-l' specifies logfile for verbose mode.\n");
		printf("\t'-c' allows passing of an expression as argument.\n");

		return EXIT_SUCCESS;
	}

	if(params.flags & FLAG_VERBOSE)
	{
		setLogger(params.logFile);
	}

	setEvalOutput(evalStack);

	if(params.command)
	{
		if(!evaluate(params.command))
		{
			if(params.flags & FLAG_CROSSSUM)
			{
				evalStack("xsum");
			}

			printf("%Lg\n", (long double) stack->data[stack->i - 1]);
		}
	}
	else
	{
		do
		{
			if(params.flags & FLAG_USER) { printf("Enter an expression: "); }
			gets(buf);
		
			if(strcmp(buf, "q") == 0) break;
		
			if((err = evaluate(buf)))
			{
				fprintf(stderr, "ERR(%d): Abort.\n", err);

				if((params.flags & FLAG_FORCE) && (params.flags & FLAG_USER))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			if(params.flags & FLAG_CROSSSUM)
			{
				evalStack("xsum");
			}

			r = (long double) stack->data[stack->i - 1];
		
			if(params.flags & FLAG_USER)
			{
				printf("%s == %Lg\n", buf, r);
			}
			else
			{
				printf("%Lg\n", r);
			}
		} while(params.flags & FLAG_USER);
	}

	disposeParameter(&params);
	DS_dispose(stack);
	
	return EXIT_SUCCESS;
}

void evalStack(const char *line)
{
	DLOG("%s\n", line);
	interpret(getStack(), line);	
}

DS *getStack(void)
{
	static DS stack;

	return &stack;
}

