#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "include.h"

#define BUF_SIZE 1024
#define PI 3.1415926535897932384626433832795028841971693993751058
#define E  2.7182818284590452353602874713526624977572470936999595
#define MIN_STEP 1E-15L

#ifndef NAN
#define NAN ((double)(-1l))
#endif

#define ABS(x) ((x)<0?-(x):(x))

double sin_IE1(double);
double cos_IE1(double);
double tan_IE1(double);
double exp_IE1(double);

typedef double (*m_func)(double);
enum
{
	IE_SIN,
	IE_COS,
	IE_TAN,
	IE_EXP,
	M_SIN,
	M_COS,
	M_TAN,
	M_EXP,
	MATH_LAST
};

double relative_error(double, double);

int main(int argc, char *argv[])
{
	int i;
	double x, v[MATH_LAST];
	char buf[BUF_SIZE];
	m_func funcs[MATH_LAST] = { sin_IE1, cos_IE1, tan_IE1, exp_IE1, sin, cos, tan, exp};

	while(1)
	{	
		printf("Enter double: ");

		fflush(stdin);

		if(!gets(buf))
		{
			fprintf(stderr, "ERR: Couldn't read from stdin.\nAbort.\n");
			return EXIT_FAILURE;
		}

		putchar('\n');

		if(strcmp(buf, "quit") == 0 || (buf[0] == 'q' && buf[1] == '\0'))
		{
			break;
		}

		if(!sscanf(buf, "%lf", &x))
		{
			fprintf(stderr, "ERR: Invalid input.\n'%s' is not a valid decimal number.\n\n", buf);
			continue;
		}

		if(argc >= 2 && strcmp(argv[1], "-d") == 0)
		{
			x = (double) (x * P_PI() / 180.0L);
		}

		printf("! x == %.10lf\n", x);

		for(i = 0 ; i < MATH_LAST ; i++)
		{
			v[i] = funcs[i](x);
		}

#define RE(i) relative_error(v[i],v[(i)+MATH_LAST/2])
		printf("# =============================================================================================================\n");
		printf("         | %14s %14s %20s %20s\n", "sin", "cos", "tan", "exp");
		printf("---------+-----------------------------------------------------------------------------------------------------\n");
		printf("%8s | %14.10lf %14.10lf %20.10lf %20.10lf\n", "IE1", v[IE_SIN], v[IE_COS], v[IE_TAN], v[IE_EXP]);
		printf("%8s | %14.10lf %14.10lf %20.10lf %20.10lf\n", "math", v[M_SIN], v[M_COS], v[M_TAN], v[M_EXP]);
		printf("%8s | %14.10lf %14.10lf %20.10lf %20.10lf\n\n", "rel. err", RE(IE_SIN), RE(IE_COS), RE(IE_TAN), RE(IE_EXP));
#undef RE
	}

	return EXIT_SUCCESS;
}

double relative_error(double v1, double v2)
{
	if(ABS(ABS(v1)-ABS(v2)) < MIN_STEP) return 0.0;
	if(ABS(v2) < MIN_STEP) return NAN;

	return ABS(v1 - v2) / v2;
}

// # ==========================================================================

double exp_IE1(double x)
{
	int i, j, inv;
	long double e = 1.0L, tmp;

	if(x == 0.0) return 1.0;

	// If x < 0, then 1 / e**|x| will be calculated
	inv = x < 0 ? 1 : 0;
	x = ABS(x);

	i = 1;
	do
	{
		tmp = 1.0L;

		for(j = 1 ; j <= i ; j++)
		{
			tmp *= x / (long double) j;
		}

		e += tmp;

		i++;
	} while(tmp > MIN_STEP);

	if(inv) { e = 1.0L / e; }

//	printf("#[%d turns!]\n", i);

	return (double) e;
}

double tan_IE1(double x) { return sin_IE1(x) / sin_IE1(x + 0.5 * PI); }
double cos_IE1(double x) { return sin_IE1(x + 0.5 * PI); }
double sin_IE1(double x) 
{
	int i, j;
	long double sin = 0, tmp;

	// Shifting until x is an element of the
	// interval [-PI,PI)
	while(x > PI)  x -= 2 * PI;
	while(x < -PI) x += 2 * PI;

	if(ABS(x) < MIN_STEP || ABS(ABS(x) - PI) < 1E-8L) return 0.0;

	// With x=max(|[-PI,PI)|) the summands are larger than 1E-9
	// for the first 21 (= 2 * 10 + 1) iterations.
	i = 0;
	do
	{
		// Tyler series.

		tmp = (i & 1) ? -1.0L : 1.0L;

		for(j = 1 ; j <= 2 * i + 1 ; j++)
		{
			tmp *= x / (long double) j;
		}

		sin += tmp;

		i++;
	} while(ABS(tmp) > MIN_STEP);

//	printf("![%d turns!]\n", i);

	return (double) sin;
}

