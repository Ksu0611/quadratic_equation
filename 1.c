#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>    //Assert(!Is_NAN(a)) ассерт остановит когда внутри 0
#define zero 1.0E-6
int ifnumzero(double x);
int comparenum(double x, double y);
int isnan(double x);
void clean();
double discriminant(double a, double b, double c);
int lineq(double b, double c, double * x1);
int quadeq(double a, double b, double c, double * x1, double * x2);


//----------------------------------------------------------------------------------------------------


int main()
{
	double a = NAN, b = NAN, c = NAN;
	double x1 = NAN, x2 = NAN;
	int numroots = 11;

	printf("\n-----------------------------------------------------------\n");
	printf("\nEnter coeff for equation ax^2 + bx + c = 0\n");
	int result = scanf("%lf%lf%lf", &a, &b, &c);
	while (result != 3)
	{
		printf("Enter only numbers!\n");
		clean();
		result = scanf("%lf%lf%lf", &a, &b, &c);
	}
	printf("%.2lfx^2 + %.2lfx + %.2lf = 0\n", a, b, c);
	if (comparenum(a, 0) == 0)
		numroots = lineq(b, c, &x1);
	else
		numroots = quadeq(a, b, c, &x1, &x2);
	printf("numroots = %d\n", numroots);
	if (x1 == -0)
		x1 = 0;
	if (x2 == -0)         // не ебу как тут еще сделать чтобы убрать -0
		x2 = 0;
	//assert(!isnan(x1));
	//assert(!isnan(x2));
	switch (numroots)
	{
		case 8: printf("inf roots\n");
			    break;

		case 2: printf("x1 = %.2lf   x2 = %.2lf\n", x1, x2);
				break;
		case 1: printf("x = %.2lf\n", x1);
				break;
		case 0: printf("No roots\n");
				break;
		default: printf("error\n");

	}

	return 0;
}


//----------------------------------------------------------------------------------------------------


int ifnumzero(double x)
{
	if ((x > zero) || (x < -zero))
		return 0;
	else 
		return 1;
}

//----------------------------------------------------------------------------------------------------


int comparenum(double x, double y)
{
	if (ifnumzero(fabs(x - y)) == 1)
		return 0;
	else
		return 1;
}


//------------------------------------------------------------------------------------------------------


int isnan(double x)
{
	if (x != x)
		return 1;
	else 
		return 0;
}


//------------------------------------------------------------------------------------------------------


void clean()
{
	int x;
    while ((x = getchar()) != EOF && x != '\n');
}


//------------------------------------------------------------------------------------------------------


double discriminant(double a, double b, double c)
{
	double D = NAN;
	D = (b * b - 4 * a * c);
	assert(!isnan(D));
	//printf("d = %.2lf\n", D);
	return D;
}

//------------------------------------------------------------------------------------------------------


int lineq(double b, double c, double * x1)
{
	int numroots = 11;
	assert(!isnan(b));
	assert(!isnan(c));
	if ((comparenum(b, 0) == 1) && (comparenum(c, 0) == 1))
	{
		*x1 = -c / b;
		numroots = 1;
	} 
	if ((comparenum(b, 0) == 0) && (comparenum(c, 0) == 1))
	{
		numroots = 0;
	}
	if ((comparenum(b, 0) == 0) && (comparenum(c, 0) == 0))
	{
		numroots = 8;
	}
	if ((comparenum(b, 0) == 1) && (comparenum(c, 0) == 0))
	{
		*x1 = 0;
		numroots = 1;
	} 
	if (x1 == -0)
		x1 = 0;        // не ебу как тут еще сделать чтобы убрать -0
	return(numroots);
}

//------------------------------------------------------------------------------------------------------


int quadeq(double a, double b, double c, double * x1, double * x2)
{
	assert(!isnan(a));
	assert(!isnan(c));
	assert(!isnan(b));
	double D = discriminant(a, b, c);
	int numroots = 11;
	if(comparenum(a, 0) == 1)
	{
		if ((D > 0) || (comparenum(D, 0) == 0))
		{
			*x1 = (-b + sqrt(D)) / (2 * a);
			*x2 = (-b - sqrt(D)) / (2 * a);	
			numroots = 2;
		}
		if (D < 0)
		{
			numroots = 0;
		}
	}
	if (x1 == -0)
		x1 = 0;
	if (x2 == -0)         // не ебу как тут еще сделать чтобы убрать -0
		x2 = 0;
	return(numroots);
}