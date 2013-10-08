#include "main.h"

int main(int argc, char *argv[])
{
	int i, r;
	char **tmp;

	tmp = malloc((argc + 1) * sizeof(char *));
	tmp[0] = strdup(argv[0]);
	tmp[1] = strdup("-c");

	for(i = 2 ; i < argc + 1 ; i++)
	{
		tmp[i] = strdup(argv[i - 1]);
	}

	r = executeNumberEvaluator(argc + 1, tmp);

	for(i = 0 ; i < argc + 1 ; i++)
	{
		free(tmp[i]);
	}
	free(tmp);

	return r;
}

