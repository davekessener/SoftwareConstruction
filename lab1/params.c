#define PARAMS_C
#include "params.h"
#undef PARAMS_C

void readParameter(PARAMS *this, int argc, char **argv)
{
	const char *fn;
	char **cmds;
	PTABLE tbl;
	PTABLE_init(&tbl);

	this->logFile = stdout;
	this->command = NULL;
	this->flags   = FLAG_NONE;
	this->base    = 10;
	this->digits  = 8;

	PTABLE_addParameter(&tbl, paramHelp(0),    paramHelp(1),    PARAM_NONE);
	PTABLE_addParameter(&tbl, paramVerbose(0), paramVerbose(1), PARAM_NONE);
	PTABLE_addParameter(&tbl, paramUser(0),    paramUser(1),    PARAM_NONE);
	PTABLE_addParameter(&tbl, paramForce(0),   paramForce(1),   PARAM_NONE);
	PTABLE_addParameter(&tbl, paramLog(0),     paramLog(1),     PARAM_ONE);
	PTABLE_addParameter(&tbl, paramCommand(0), paramCommand(1), PARAM_MANY);
	PTABLE_addParameter(&tbl, paramCrossSum(0), paramCrossSum(1), PARAM_NONE);
	PTABLE_addParameter(&tbl, paramBase(0),    paramBase(1),    PARAM_ONE);
	PTABLE_addParameter(&tbl, paramDigits(0),  paramDigits(1),  PARAM_ONE);

	PTABLE_read(&tbl, argc, argv);

	if(PTABLE_hasArgument(&tbl, paramHelp(0))) this->flags |= FLAG_HELP;
	else
	{
		if(PTABLE_hasArgument(&tbl, paramVerbose(0)))  this->flags |= FLAG_VERBOSE;
		if(PTABLE_hasArgument(&tbl, paramUser(0)))     this->flags |= FLAG_USER;
		if(PTABLE_hasArgument(&tbl, paramForce(0)))    this->flags |= FLAG_FORCE;
		if(PTABLE_hasArgument(&tbl, paramCrossSum(0))) this->flags |= FLAG_CROSSSUM;

		if(PTABLE_hasArgument(&tbl, paramDigits(0)))
		{
			fn = PTABLE_getValue(&tbl, paramDigits(0));

			if(fn != NULL)
			{
				this->digits = (int) evalNumber(&fn);
			}
		}
		if(PTABLE_hasArgument(&tbl, paramBase(0)))
		{
			fn = PTABLE_getValue(&tbl, paramBase(0));
			if(fn != NULL)
			{
				switch(*fn)
				{
					case 'b':
					case 'B':
						this->base = 2;
						break;
					case 'q':
					case 'Q':
						this->base = 4;
						break;
					case 'o':
					case 'O':
						this->base = 8;
						break;
					case 'd':
					case 'D':
						break;
					case 'h':
					case 'H':
					case 'x':
					case 'X':
						this->base = 16;
						break;
					default:
						this->base = (int) evalNumber(&fn);	
						break;
				}
			}
		}
		if(PTABLE_hasArgument(&tbl, paramLog(0)))
		{
			this->flags |= FLAG_LOG;
			fn = PTABLE_getValue(&tbl, paramLog(0));
			if(fn != NULL) { this->logFile = fopen(fn, "w"); }
		}
		if(PTABLE_hasArgument(&tbl, paramCommand(0)))
		{
			this->flags |= FLAG_COMMAND;
			cmds = PTABLE_getValues(&tbl, paramCommand(0));

			if(cmds == NULL || cmds[0] == NULL)
			{
				fprintf(stderr, "ERR: No command supplied with command flag '-c'.\nAbort.\n");
				exit(1);
			}

			this->command = strdup(cmds[0]);
			cmds++;
			while(*cmds)
			{
				this->command = realloc(this->command, strlen(this->command) + strlen(*cmds) + 1);
				strcat(this->command, *cmds);
				cmds++;
			}
		}
	}
}

void disposeParameter(PARAMS *this)
{
	if(this->logFile != NULL && this->logFile != stdin) fclose(this->logFile);
	free(this->command);
}

