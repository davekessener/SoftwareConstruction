/* Solution for Assignment 2 of Lab 5 in Software Construction
 * File: lab5_2.c
 * Daniel Kessener, HAW 2159858
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef UNIX
#include <conio.h>
#else
#include <unistd.h>
#include "conio_e.h"
#endif

#define NUMBER_OF_DICE 3
#define WIDTH_OF_DICE 12
#define HEIGHT_OF_ONE_DIE 6
#define POSSIBLE_DICE_VALUES 6
#define HEIGHT_OF_DISPLAY 6
#define WIDTH_OF_DISPLAY (3*WIDTH_OF_DICE)

void display(char [] [HEIGHT_OF_ONE_DIE] [WIDTH_OF_DICE], int []);
int check_for_triplets(int *);
int check_for_doubles(int *);
// comparison function for qsort
int cmp(const void *i1, const void *i2) { return *((const int *) i1) > *((const int *) i2); }
// returns pointer to dice charmaps (to keep main clean)
char (*dice())[HEIGHT_OF_ONE_DIE][WIDTH_OF_DICE];

int main(int argc, char *argv[])
{
	int throws[NUMBER_OF_DICE], doubles = 0, triplets = 0;
	int i;
	uint32_t t;
	char c = '\0';

#ifdef UNIX
	prepare_terminal();
#endif

	srand(time(NULL));
	
	while(1)
	{
		t = (uint32_t) rand();
		for(i = 0 ; i < NUMBER_OF_DICE ; i++)
		{
			// extract three dice-values from the random number
			throws[i] = t % POSSIBLE_DICE_VALUES;
			t /= POSSIBLE_DICE_VALUES;
		}

		// display dice before sorting
		display(dice(), throws);

		// sort the dice by value in ascending order
		qsort(throws, NUMBER_OF_DICE, sizeof(int), cmp);

		triplets += check_for_triplets(throws);
		doubles += check_for_doubles(throws);

		printf("==> %d doubles && %d triples.\n\r[Press any key to quit.]\n\n\r", doubles, triplets);

		for(i = 0 ; i < 100 ; i++)
		{
#ifndef UNIX
			// windows 'Sleep' takes time in milliseconds
			// run 100 times 10 ms -> run 1 second
			Sleep(10);
#else
			// posix 'usleep' takes time in microseconds
			// run 100 times 10000 us -> run 1 second
			usleep(10000);
#endif

			// check if user wants to quit ~100 times a second
			if(kbhit())
			{
				c = getchar();
			}

			if(c != '\0') break;
		}

		if(c != '\0') break;
	}

	return EXIT_SUCCESS;
}

void display(char d[][HEIGHT_OF_ONE_DIE][WIDTH_OF_DICE], int *t)
{
	int i, j;
	for(i = 0 ; i < HEIGHT_OF_ONE_DIE ; i++)
	{
		for(j = 0 ; j < NUMBER_OF_DICE ; j++)
		{
			// iterate over the top slices of the correct
			// dice first
			printf("%s%s", d[t[j]][i], j == NUMBER_OF_DICE - 1 ? "\n\r" : " ");
		}
	}
}

int check_for_doubles(int *t)
{
	int dc = 0;
	int i;
	for(i = 0 ; i < NUMBER_OF_DICE - 1 ; i++)
	{
		// if @i equals @(i+1) and not @(i-1) and @(i+2) [-> no triples]
		// there is a double;
		if(t[i] == t[i + 1] 
			&& (i == NUMBER_OF_DICE - 2 || t[i + 1] != t[i + 2])
			&& (i == 0 || t[i - 1] != t[i]))
			dc++;
	}

	return dc;
}

int check_for_triplets(int *t)
{
	int tc = 0;
	int i;
	for(i = 0 ; i < NUMBER_OF_DICE - 2 ; i++)
	{
		// if @i equals @(i+1) and !(i+2) [quadruples are not accounted for]
		// there is a triplet.
		if(t[i] == t[i + 1] && t[i + 1] == t[i + 2]) { tc++; i += 2; }
	}

	return tc;
}

char (*dice())[HEIGHT_OF_ONE_DIE][WIDTH_OF_DICE]
{
	static char d[][HEIGHT_OF_ONE_DIE][WIDTH_OF_DICE] = {
	{
		{" _________ "},
		{"|         |"},
		{"|         |"},
		{"|    O    |"},
		{"|         |"},
		{"|_________|"}
	},
	{
		{" _________ "},
		{"|         |"},
		{"| O       |"},
		{"|         |"},
		{"|       O |"},
		{"|_________|"}
	},
	{
		{" _________ "},
		{"|         |"},
		{"| O       |"},
		{"|    O    |"},
		{"|       O |"},
		{"|_________|"}
	},
	{
		{" _________ "},
		{"|         |"},
		{"| O     O |"},
		{"|         |"},
		{"| O     O |"},
		{"|_________|"}
	},
	{
		{" _________ "},
		{"|         |"},
		{"| O     O |"},
		{"|    O    |"},
		{"| O     O |"},
		{"|_________|"}
	},
	{
		{" _________ "},
		{"|         |"},
		{"| O  O  O |"},
		{"|         |"},
		{"| O  O  O |"},
		{"|_________|"}
	}};

	return d;
}
