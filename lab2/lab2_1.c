#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define DATA_MIN_SIZE 0x10
#define BUF_SIZE 0x400

typedef struct __weather_data
{
	float  fTemp;
	float  fWindDir;
	float  fWindSpeed;
	float  fWindChill;
	float *fptrReference;
} WD;

typedef struct __wd_array
{
	struct __weather_data *data;
	size_t c, i;
} WDA;

typedef int (*CMPFN)(float, float);

// # --------------------------------------------------------------------------

WD  *WD_makeEmpty();
WD   WD_readLine(const char *);

void WDA_init(WDA*);
void WDA_push(WDA*, WD); 
WD  *WDA_getMin(WDA*);
WD  *WDA_getMax(WDA*);
WD  *WDA_getMean(WDA*);
WD  *WDA_getMinMax(WDA*, int (*)(float, float));
void WDA_resize(WDA*);
void WDA_dispose(WDA*);

int checkInput(const char *);
void printStuff(WDA *);

int cmpFnGt(float, float);
int cmpFnLt(float, float);

int main(int argc, char *argv[])
{
	char in[BUF_SIZE];
	WDA wda;

	WDA_init(&wda);

	while(1)
	{
		fflush(stdin);

		if(!gets(in))
		{
			fprintf(stderr, "ERR: Couldn't read from stdin.\nAbort.\n");
			return EXIT_FAILURE;
		}

		if(checkInput(in))
		{
			break;
		}

		WDA_push(&wda, WD_readLine(in));

		printStuff(&wda);
	}

	WDA_dispose(&wda);
	
	return EXIT_SUCCESS;
}

// # ===========================================================================

WD *WD_makeEmpty(void)
{
	WD *ret = malloc(sizeof(WD));
	ret->fTemp = 0.0f;
	ret->fWindDir = 0.0f;
	ret->fWindSpeed = 0.0f;
	ret->fWindChill = 0.0f;
	ret->fptrReference = &ret->fTemp;
	return ret;
}

WD WD_readLine(const char *line)
{
	WD wd;
	int csum;
	float *t;

	wd.fptrReference = NULL;

	t = (float *) &wd;

	csum = sscanf(line, " %f %f %f %f ", t, t + 1, t + 2, t + 3);

	assert(csum==4);

	return wd;
}

int checkInput(const char *line)
{
	if(!line || !*line)
	{
		return 1;
	}

	do
	{
		if(*line == ' ' || *line == '\t' || *line == '\n') continue;

		if((*line < '0' || *line > '9') && *line != '-' && *line != '.') return 1;
	} while(*++line);

	return 0;
}

void printStuff(WDA *wda)
{
	static const char *szNames[4] = {"Temperature", "Wind Direction", "Wind Speed", "Wind Chill"};
	static const char *szMinMax[2] = {"Min", "Max"};
	static CMPFN fnptrs[2] = {cmpFnGt, cmpFnLt};
	WD *wdptr;
	int i, j;
	double deviation, tmp;

	printf("# ==============================================================\n");
	printf("# Read %zu real numbers so far.\n", wda->i * 4);
	printf("# --------------------------------------------------------------\n");
	
	for(i = 0 ; i < 2 ; i++)
	{
		wdptr = WDA_getMinMax(wda, fnptrs[i]);
	
		for(j = 0 ; j < 4 ; j++)
		{
			if(j == 1) continue; // Skip wind-direction
	
			printf("# %s %s: %g\n", szMinMax[i], szNames[j], wdptr->fptrReference[j]);
		}
	
		printf("# --------------------------------------------------------------\n");

		free(wdptr);
	}

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

	if(this->c == 0)
	{
		this->c = DATA_MIN_SIZE;
	}
	else if(this->i == this->c)
	{
		this->c <<= 1;
	}
	else
	{
		return;
	}

	tmp = realloc(this->data, this->c * sizeof(struct __weather_data));
	assert(tmp!=NULL);
	this->data = tmp;
}

void WDA_dispose(WDA *this)
{
	free(this->data);

	WDA_init(this);
}

