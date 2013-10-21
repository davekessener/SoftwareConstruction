#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

// Minimal increment size of data buffer
#define DATA_MIN_SIZE 0x10
// Buffer size of standard character buffer
#define BUF_SIZE 0x400

// Structure that holds the passed data concerning one day.
// fptrRference points to the first data entry (Temperature)
// and is used as an array to simply data access.
typedef struct __weather_data
{
	float  fTemp;
	float  fWindDir;
	float  fWindSpeed;
	float  fWindChill;
	float *fptrReference;
} WD;

// Structure that holds the data buffer
typedef struct __wd_array
{
	struct __weather_data *data;
	size_t c, i;
} WDA;

// Type of functions that compare two floats
// Used in the function that determines minimum
// and maximum of the data entries.
typedef int (*CMPFN)(float, float);

// # --------------------------------------------------------------------------

// Allocate and initialize an empty data-set
WD  *WD_makeEmpty();
// Parse a string
WD   WD_readLine(const char *);

void WDA_init(WDA*);
// Add an entry
void WDA_push(WDA*, WD);
// Return a new data-set containing the
// smallest entries of all data-sets
WD  *WDA_getMin(WDA*);
WD  *WDA_getMax(WDA*);
WD  *WDA_getMean(WDA*);
// Return new data-set based of passed
// comparison function.
WD  *WDA_getMinMax(WDA*, int (*)(float, float));
// Internal function used to appropriately
// resize the data-buffer
void WDA_resize(WDA*);
void WDA_dispose(WDA*);

// Check read string if it is valid
int checkInput(const char *);
// Print an evaluation of the data-buffer
// according to the assignment
void printStuff(WDA *);

// GreaterThan function
int cmpFnGt(float, float);
// LessThan function
int cmpFnLt(float, float);

int main(int argc, char *argv[])
{
	// Input buffer for read string
	char in[BUF_SIZE];
	// Data buffer
	WDA wda;

	WDA_init(&wda);

	while(1)
	{
		// Flush stdin
		fflush(stdin);

		// If no string could be read correctly print error and quit
		if(!gets(in))
		{
			fprintf(stderr, "ERR: Couldn't read from stdin.\nAbort.\n");
			return EXIT_FAILURE;
		}

		// If the input isn't valid break
		if(checkInput(in))
		{
			break;
		}

		// Add read data-set to the data-buffer
		WDA_push(&wda, WD_readLine(in));

		// Print current status
		printStuff(&wda);
	}

	WDA_dispose(&wda);

#ifndef UNIX
	system("pause>NUL");
#endif
	
	return EXIT_SUCCESS;
}

// # ===========================================================================

WD *WD_makeEmpty(void)
{
	// Allocate new data-set on the heap
	WD *ret = malloc(sizeof(WD));
	// and initialize it.
	ret->fTemp = 0.0f;
	ret->fWindDir = 0.0f;
	ret->fWindSpeed = 0.0f;
	ret->fWindChill = 0.0f;
	// Point to the first data-entry
	ret->fptrReference = (float *) ret;

	return ret;
}

WD WD_readLine(const char *line)
{
	WD wd;
	int csum;
	float *t;

	// Data-set on the stack;
	// Will be return by value -> pointer would be invalid
	wd.fptrReference = NULL;

	// Pointer to the beginning of the entries in the new set
	t = (float *) &wd;

	// Scan floats from the given string
	csum = sscanf(line, " %f %f %f %f ", t, t + 1, t + 2, t + 3);

	// Assert that it read four floats successfully
	assert(csum==4);

	// Return read data-set by value
	return wd;
}

int checkInput(const char *line)
{
	// If the input string is NULL or an empty string
	// the string is not valid
	if(!line || !*line)
	{
		return 1;
	}

	// Iterate over the string one character at a time,
	// return an error if an invalid character is encountered
	do
	{
		// Skip whitespace
		if(*line == ' ' || *line == '\t' || *line == '\n') continue;

		// If the current character is neither a digit nor a period nor dash,
		// break loop and return since the string is invalid
		if((*line < '0' || *line > '9') && *line != '-' && *line != '.') return 1;
	} while(*++line);

	// String is valid
	return 0;
}

void printStuff(WDA *wda)
{
	// Names of the data-entries
	static const char *szNames[4] = {"Temperature", "Wind Direction", "Wind Speed", "Wind Chill"};
	static const char *szMinMax[2] = {"Min", "Max"};
	// Comparative functions, used to print min and max
	// in a loop (for convenience sake)
	static CMPFN fnptrs[2] = {cmpFnGt, cmpFnLt};
	WD *wdptr;
	int i, j;
	double deviation, tmp;

	printf("# ==============================================================\n");
	printf("# Read %zu real numbers so far.\n", wda->i * 4);
	printf("# --------------------------------------------------------------\n");
	
	for(i = 0 ; i < 2 ; i++)
	{
		// Get the smallest/largest entries of all sets
		wdptr = WDA_getMinMax(wda, fnptrs[i]);
	
		for(j = 0 ; j < 4 ; j++)
		{
			if(j == 1) continue; // Skip wind-direction
	
			printf("# %s %s: %g\n", szMinMax[i], szNames[j], wdptr->fptrReference[j]);
		}
	
		printf("# --------------------------------------------------------------\n");

		free(wdptr);
	}

	// If we have more than one data-set, calculating the mean and
	// standard deviation is feasable, with only one set it is not.
	if(wda->i > 1)
	{
		wdptr = WDA_getMean(wda);
	
		for(i = 0 ; i < 4 ; i++)
		{
			printf("# Mean of %s: %g\n", szNames[i], wdptr->fptrReference[i]);
		}
	
		printf("# --------------------------------------------------------------\n");
	
		for(i = 0 ; i < 4 ; i++)
		{
			deviation = 0.0;
	
			// Add the squares of the difference of each data-set
			for(j = 0 ; j < wda->i ; j++)
			{
				tmp = wda->data[j].fptrReference[i] - wdptr->fptrReference[i];
				deviation += tmp * tmp;
			}
	
			deviation = sqrt(deviation / (wda->i - 1));
	
			printf("# Std. deviation of %s: %lg\n", szNames[i], deviation);
		}
	
		free(wdptr);

		printf("# --------------------------------------------------------------\n");
	}
}

// # --------------------------------------------------------------------------

void WDA_init(WDA *this)
{
	this->data = NULL;
	this->c    = 0;
	this->i    = 0;
}

void WDA_push(WDA *this, WD wd)
{
	this->i++;
	// Resize the buffer is necessary to accommodate
	// for the new set
	WDA_resize(this);
	memcpy(&this->data[this->i - 1], &wd, sizeof(WD));
	this->data[this->i - 1].fptrReference = (float *) &this->data[this->i - 1];
}

int cmpFnGt(float f1, float f2) { return f1 > f2; }
int cmpFnLt(float f1, float f2) { return f1 < f2; }

WD  *WDA_getMinMax(WDA *this, int (*cmpFn)(float, float))
{
	WD *ret;
	
	assert(this->data);
	assert(cmpFn);
	
	ret = WD_makeEmpty();

	int i, j;
	for(i = 0 ; i < this->i ; i++)
	{
		for(j = 0 ; j < 4 ; j++)
		{
			if(i == 0 || cmpFn(ret->fptrReference[j], this->data[i].fptrReference[j]))
			{
				ret->fptrReference[j] = this->data[i].fptrReference[j];
			}
		}
	}

	return ret;
}

WD  *WDA_getMin(WDA *this)
{
	return WDA_getMinMax(this, cmpFnGt);
}

WD  *WDA_getMax(WDA *this)
{
	return WDA_getMinMax(this, cmpFnLt);
}

WD  *WDA_getMean(WDA *this)
{
	WD *ret;

	assert(this->data);

	ret = WD_makeEmpty();

	int i, j;
	for(i = 0 ; i < this->i ; i++)
	{
		for(j = 0 ; j < 4 ; j++)
		{
			ret->fptrReference[j] += this->data[i].fptrReference[j];
		}
	}

	for(i = 0 ; i < 4 ; i++)
	{
		ret->fptrReference[i] /= this->i;
	}

	return ret;
}

void WDA_resize(WDA *this)
{
	struct __weather_data *tmp;

	// If we have nothing allocated,
	// allocate DATA_MIN_SIZE objects
	if(this->c == 0)
	{
		this->c = DATA_MIN_SIZE;
	}
	// If the buffer is full, double
	// its capacity
	else if(this->i == this->c)
	{
		this->c <<= 1;
	}
	else
	{
		return;
	}
	
	// Cache the returned pointer, if it is NULL
	// memory allocation has failed
	tmp = realloc(this->data, this->c * sizeof(struct __weather_data));
	assert(tmp!=NULL);
	this->data = tmp;
}

void WDA_dispose(WDA *this)
{
	free(this->data);

	WDA_init(this);
}

