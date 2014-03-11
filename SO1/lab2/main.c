#include "main.h"

void evalStack(const char *);
DS *getStack();
void printChar(char);

#ifdef STANDALONE
int main(int argc, char *argv[])
{
	return executeNumberEvaluator(argc, argv);
}
#endif

// Main function used in most solutions
int executeNumberEvaluator(int argc, char *argv[])
{
	char buf[2048];
	int err;
	DS *stack = getStack(); // Pointer to global data stack the program operates on

	PARAMS params;

	DS_init(stack);

	// Read and evaluate command line arguments
	readParameter(&params, argc, argv);
	
	// If the 'HELP'-flag was given, print usage and quit
	if(params.flags & FLAG_HELP)
	{
		printf("Usage: %s [-h] [-v] [-u] [-x] [-b base] [-d digits] [-f] [-l logfile] [-c command]\n", argv[0]);
		printf("\t'-h' prints help.\n");
		printf("\t'-v' enters verbose mode.\n");
		printf("\t'-u' enters user-mode.\n");
		printf("\t'-x' calculates the cross-sum of the result.\n");
		printf("\t'-b' specifies base of result. Either b|q|o|d|h,x or an positive integer.\n");
		printf("\t'-d' specifies the amount of digits printed after the decimal separator.\n");
		printf("\t'-f' forces continuation after an error.\n");
		printf("\t'-l' specifies logfile for verbose mode.\n");
		printf("\t'-c' allows passing of an expression as argument.\n");

		return EXIT_SUCCESS;
	}

	*MAX_DIGITS() = params.digits;

	// If 'VERBOSE'-flag is given, set Logger function
	// (Defaults to stdout)
	if(params.flags & FLAG_VERBOSE)
	{
		setLogger(params.logFile);
	}

	// Supply parser with a pointer to a function it will call
	// for each successfully parsed line of the output.
	// The function will feed that line to the stackmachine for evaluation.
	setEvalOutput(evalStack);

	// If a command is provided as command line argument
	if(params.command)
	{
		// If the command is evaluated correctly (returns 0 on success)
		if(!evaluate(params.command))
		{
			// If the user wants to calculate the cross-sum of the result
			if(params.flags & FLAG_CROSSSUM)
			{
				evalStack("xsum");
			}

			// The stack the stackmachine operated on has to contain exactly one number
			assert(stack!=NULL&&stack->data!=NULL&&stack->i>0);

			// Print the result in the base provided (defaults to 10/decimal)
			// If the 'VERBOSE'-flag is set append base to result
			printNumber(stack->data[stack->i - 1], params.base, printChar);
			if(params.flags & FLAG_VERBOSE) printf("(%d)", params.base);
			printf("\n");
		}
	}
	else
	{
		// Do while the 'USER'-flag is set. (Or rather: until the loop breakes)
		do
		{
			// If we are in 'User'-mode print input-prompt
			if(params.flags & FLAG_USER) { printf("Enter an expression: "); }
			// Read input
			gets(buf);
		
			// If the user supplied 'q' as input, quit input loop. (Quit)
			if(strcmp(buf, "q") == 0) break;
		
			// If an error has been encountered during evaluation, print error
			if((err = evaluate(buf)))
			{
				fprintf(stderr, "ERR(%d): Abort.\n", err);

				// If we are in 'USER'-mode and the 'FORCE'-flag was supplied,
				// force continuation of the input loop, otherwise break.
				if((params.flags & FLAG_FORCE) && (params.flags & FLAG_USER))
				{
					continue;
				}
				else
				{
					break;
				}
			}

			// If the user wants to calculate the cross-sum
			if(params.flags & FLAG_CROSSSUM)
			{
				evalStack("xsum");
			}

			// If we are in 'USER'-mode, print the input-expression
			if(params.flags & FLAG_USER)
			{
				printf("%s == ", buf);
			}

			// Print result in the supplied base (default: 10)
			// In 'VERBOSE'-mode append the base to the result.
			printNumber(stack->data[stack->i - 1], params.base, printChar);
			if(params.flags & FLAG_VERBOSE) printf("(%d)", params.base);
			printf("\n");
		} while(params.flags & FLAG_USER); // Repeat loop if in 'USER'-mode
	}

	// Free parameter and dispose of the stack
	disposeParameter(&params);
	DS_dispose(stack);

	return EXIT_SUCCESS;
}

// Evaluation-function that pipes the output of the parser to the stackmachine
// Log the intermediate representation (Defaults to NUL, is overriden with the
// 'LOG'-flag and the 'VERBOSE'-value.)
void evalStack(const char *line)
{
	DLOG("%s\n", line);
	interpret(getStack(), line);	
}

// Returns pointer to static data stack, workaround since global variables are not permitted
DS *getStack(void)
{
	static DS stack;

	return &stack;
}

// Auxilliary function for 'printNumber' in 'include.c'
void printChar(char c)
{
	printf("%c", c);
}

