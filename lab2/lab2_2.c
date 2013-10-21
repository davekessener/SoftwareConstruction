#include <stdio.h>
#include <stdlib.h>

//#define WINDOWS

#ifdef WINDOWS
#include <conio.h> // NOT ANSI STANDARD!
#else
#include "conio_e.h"
#endif

int main(int argc, char *argv[])
{
	char ch;

#ifndef WINDOWS
	// If compiled on a UNIX based system,
	// manually set up tty to emulate windows behavior
	// (This function registers a function hook to restore
	//  the terminal to its default behavior on exit.)
	prepare_terminal();
#endif

	while(1)
	{
		// If a key on the keyboard is pressed ...
		if(kbhit())
		{
			// ... read character.
			ch = getch();

			// If the character is alphanumerical print it
			if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
			{
				printf("%c", ch);
			}
			// Else if the escape key has been pressed, break and quit.
			else if(ch == 27)
			{
				break;
			}

#ifndef WINDOWS
			// Flush stdout manually
			fflush(stdout);
#endif
		}
	}

	// New line. Only really necessary on UNIX systems.
	// (carriage return is necessary since the terminal
	//  still emulates windows.)
	printf("\r\n");

#ifdef WINDOWS
	system("pause>NUL");
#endif

	return EXIT_SUCCESS;
}

