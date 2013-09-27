#include "include.h"
#include "evaluate.h"
#include "logger.h"

int main(int argc, char *argv[])
{
	char buf[2048];
	long double r;
	int force = 0, user = 0;
	FILE *l = NULL;

	buf[0] = '\0';

	if(argc > 1)
	{
		if(strcmp(argv[1], "-h") == 0)
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
		else
		{
			int i = 1;
			if(strcmp(argv[i], "-v") == 0)
			{
				l = stdout;
				i++;
			}
			if(argc > i && strcmp(argv[i], "-u") == 0)
			{
				user = 1;
				i++;
			}
			if(argc > i && strcmp(argv[i], "-f") == 0)
			{
				force = 1;
				i++;
			}
			if(argc > i + 1 && strcmp(argv[i], "-l") == 0)
			{
				l = fopen(argv[i + 1], "wb");
				i += 2;
			}
			if(argc > i + 1 && strcmp(argv[i], "-c") == 0)
			{
				for(++i ; i < argc ; i++)
				{
					strcat(buf, argv[i]);
				}
			}
		}
	}

	setLogger(l);

	if(buf[0])
	{
		if(!evaluate(buf, &r))
		{
			printf("%Lg\n", r);
		}
	}
	else
	{
		do
		{
			if(user) { printf("Enter an expression: "); }
			gets(buf);
		
			if(strcmp(buf, "q") == 0) break;
		
			if(evaluate(buf, &r))
			{
				if(force)
				{
					continue;
				}
				else
				{
					break;
				}
			}
		
			if(user)
			{
				printf("%s == %Lg\n", buf, r);
			}
			else
			{
				printf("%Lg\n", r);
			}
		} while(user);
	}

	if(l != NULL) fclose(l);
	
	return EXIT_SUCCESS;
}

