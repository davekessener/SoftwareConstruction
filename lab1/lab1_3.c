#include "include.h"
#include "evaluate.h"
#include "logger.h"
#include "parameter.h"
#include "params.h"

int main(int argc, char *argv[])
{
	char buf[2048];
	long double r;

	PARAMS params;
	readParameter(&params, argc, argv);
	
	if(params.flags & FLAG_HELP)
	{
		printf("Usage: %s [-h] [-v] [-u] [-f] [-l logfile] [-c command]\n", argv[0]);
		printf("\t'-h' prints help.\n");
		printf("\t'-v' enters verbose mode.\n");
		printf("\t'-u' enters user-mode.\n");
		printf("\t'-f' forces continuation after an error.\n");
		printf("\t'-l' specifies logfile for verbose mode.\n");
		printf("\t'-c' allows passing of an expression as argument.\n");

		return EXIT_SUCCESS;
	}

	if(params.flags & FLAG_VERBOSE)
	{
		setLogger(params.logFile);
	}

	if(params.command)
	{
		if(!evaluate(params.command, &r))
		{
			printf("%Lg\n", r);
		}
	}
	else
	{
		do
		{
			if(params.flags & FLAG_USER) { printf("Enter an expression: "); }
			gets(buf);
		
			if(strcmp(buf, "q") == 0) break;
		
			if(evaluate(buf, &r))
			{
				if((params.flags & FLAG_FORCE) && (params.flags & FLAG_USER))
				{
					continue;
				}
				else
				{
					break;
				}
			}
		
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
	
	return EXIT_SUCCESS;
}

