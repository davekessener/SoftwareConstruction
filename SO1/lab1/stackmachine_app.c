#include "stackmachine.h"

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
	PTABLE t;
	PTABLE_init(&t);

	p->flags = FLAG_NONE;

	PTABLE_addParameter(&t, flagVerbose()[0], flagVerbose()[1], PARAM_NONE);

	PTABLE_read(&t, argc, argv);

	if(PTABLE_hasArgument(&t, flagVerbose()[0])) p->flags |= FLAG_VERBOSE;

	PTABLE_dispose(&t);
}

