#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc < 2) return EXIT_FAILURE;

	FILE *f = fopen(argv[1], "r");

	if(f == NULL) return EXIT_FAILURE;

	fseek(f, 0, SEEK_END);
	long s = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *buf = malloc(s);

	fread(buf, s, 1, f);

	fclose(f);

	int i;
	for(i = 0 ; i < s ; i++)
	{
		if(buf[i] == '\n')
		{
			putc('\r');
		}

		putc(buf[i]);
	}

	free(buf);

	return EXIT_SUCCESS;
}

