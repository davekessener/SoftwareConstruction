#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// Number of days per month
	int mths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	// Names of months
	char *names[] = {"January", "February", "March", "April", "May", "June", "July", 
					 "August", "September", "October", "November", "December"};
	
	int i;
	// For each month
	for(i = 0 ; i < 12 ; i++)
	{
		printf("%10s: %d even && %d odd days.", names[i], mths[i] / 2, (mths[i] + 1) / 2);
		if(i == 1) // If February
		{
			printf(" (In leap years: %d even && %d odd days.)", (mths[i] + 1) / 2, mths[i] / 2 + 1);
		}
		printf("\n");
	}

#ifndef UNIX
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

