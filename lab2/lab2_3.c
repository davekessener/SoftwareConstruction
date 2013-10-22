//#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

int checkInput(const char *);
char *reorder(const char *);

int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	char **tmp;
	int i;

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
		// Print prompt
		printf("# Enter logical expression in prefix notation\n"
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
		r = executeNumberEvaluator(3, tmp);
	}

	// Free arguments
	for(i = 0 ; i < 3 ; i++)
	{
		free(tmp[i]);
	}

	free(tmp);

	return EXIT_SUCCESS;
}

int checkInput(const char *line)
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
		if(c != '&' && c != '|' && c != '!' && c != '~' && (c < '0' || c > '9') &&
			c != 'b' && c != 'h' && c != 'x' && c != 'd') return 1;
	}

	// Read expression is valid.
	return 0;
}

char *reorder(const char *line)
{
	// Buffer for operator and operants 1 and 2.
	char op[BUF_SIZE / 4], op1[BUF_SIZE / 4], op2[BUF_SIZE / 4];
	// Buffer for final expression.
	char expr[BUF_SIZE];

	// Unless exactly three whitespace-separated strings of valid character
	// are encountered return an error (NULL)
	if(sscanf(line, " %s %s %s ", op, op1, op2) != 3)
	{
		return NULL;
	}

	// Concatenate the oprator and operants in infix notation
	sprintf(expr, "%s%s%s", op1, op, op2);

	// Return copy of expression
	return strdup(expr);
}

