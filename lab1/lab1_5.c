#include "main.h"

int main(int argc, char *argv[])
{
	int i, r;
	char **tmp;

	tmp = malloc((argc + 2) * sizeof(char *));
	tmp[0] = strdup(argv[0]);
	tmp[1] = strdup("-x");
	tmp[2] = strdup("-c");

	for(i = 3 ; i < argc + 2 ; i++)
	{
		tmp[i] = strdup(argv[i - 2]);
	}

	r = executeNumberEvaluator(argc + 2, tmp);

	for(i = 0 ; i < argc + 2 ; i++)
	{
		free(tmp[i]);
	}
	free(tmp);

#ifdef WINDOWS
	system("pause>NUL");
#endif

	return r;
}

