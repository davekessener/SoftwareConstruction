/* Solution for assignment 3 of Lab 2 in Software Construction
 * File: lab2_3.c
 * Includes: main.h include.h evaluate.h stackmachine.h tokenizer.h
 *           dstack.h logger.h params.h parameter.h 
 * A/N: All included files are directly copied from Lab 1 Assignement 5
 * Test cases:
 && 0 0
 = 0

 || 0 1
 = 1

 ~ 4
 = -5

 & 10 2
 = 2

 | 10 7
 = 15
 */
#include "main.h"

#define BUF_SIZE 1024

int checkInput(char *);
char *reorder(const char *);

int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	char **tmp;
	int i, r;

	// Initialize argument buffer
	// It will contain arguments for the
	// evaluation call as follows:
	// name_of_program -c expr
	// where expr is the infix form
	// of the user-provided expression
	tmp = malloc(3 * sizeof(char *));
	tmp[0] = strdup(argv[0]);
	tmp[1] = strdup("-c");
	tmp[2] = NULL;

	while(1)
	{
		fflush(stdout);

		// Print prompt
		printf("# Enter logical expression ('&&', '||', '&', '|', '!', '~') in prefix notation\n"
			   "# Or enter 'q' or 'quit' to exit.\n");

		// If stdin cannot correctly be read from,
		// print error message and quit.
		if(!gets(buf))
		{
			fprintf(stderr, "ERR: Couldn't read input correctly.\nAbort.\n");
			break;
		}

		// If we have invalid characters in our input, check for
		// 'quit' to see if the user wants to quit, otherwise print
		// a format error and prompt the user again.
		if(checkInput(buf))
		{
			if(strcmp(buf, "quit") == 0 || (buf[0] == 'q' && !buf[1]))
			{
				break;
			}
			else
			{
				fprintf(stderr, "ERR: Invalid input.\nTry again.\n");

				continue;
			}
		}

		// Free last read expression.
		// (If free is called with NULL it terminates unaffected.)
		free(tmp[2]);

		// If the read expression cannot be converted to infix notation
		// it is incorrectly formatted. Print errormessage and prompt user again.
		if((tmp[2] = reorder(buf)) == NULL)
		{
			fprintf(stderr, "ERR: Couldn't reorder input.\nInput '%s' is an invalid format.\n", buf);

			continue;
		}

		// Call evaluation, continue loop.
		printf("= ");
		r = executeNumberEvaluator(3, tmp);
		printf("\n");
	}

	// Free arguments
	for(i = 0 ; i < 3 ; i++)
	{
		free(tmp[i]);
	}

	free(tmp);

	return EXIT_SUCCESS;
}

int checkInput(char *line)
{
	char c;

	// Invalidly read line or empty string
	if(!line || !*line) return 1;

	while(*line)
	{
		c = *line++;

		// Remove non-blank whitespace
		if(c == '\t' || c == '\n') line[-1] = ' ';

		// Skip remaining whitespace
		if(c == ' ') continue;

		// Everything to lowercase
		if(c >= 'A' && c <= 'Z') c -= 'A' - 'a';

		// Return error if an invalid character is encountered
		switch(c)
		{
			case '&':
			case '|':
			case '!':
			case '~':
			case 'b':
			case 'h':
			case 'o':
			case 'd':
			case 'x':
				break;
			default:
				if(c < '0' || c > '9') return 1;
		}
	}

	// Read expression is valid.
	return 0;
}

char *reorder(const char *line)
{
	int c;
	// Buffer for operator and operants 1 and 2.
	char op[BUF_SIZE / 4], op1[BUF_SIZE / 4], op2[BUF_SIZE / 4];
	// Buffer for final expression.
	char expr[BUF_SIZE];

	// Unless exactly three whitespace-separated strings of valid character
	// are encountered return an error (NULL)
	if((c = sscanf(line, " %s %s %s ", op, op1, op2)) != 3)
	{
		if(c == 2 && (strcmp(op, "!") == 0 || strcmp(op, "~") == 0))
		{
			sprintf(expr, "%s%s", op, op1);
			return strdup(expr);
		}
		else
		{
			return NULL;
		}
	}

	// Concatenate the oprator and operants in infix notation
	sprintf(expr, "%s%s%s", op1, op, op2);

	// Return copy of expression
	return strdup(expr);
}

