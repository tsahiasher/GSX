
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                comparison.c
------------------------------------------------------------------------------*/

#include <math.h>
#include "comparison.h"
#include "cext.h"

#define M_PI 3.141
/*----------------------------------------------------------------------------*/
JBool FIsEq(float a, float b, double eps)
{
	return ((JBool)(JAbs(a-b) < eps));
}

/*----------------------------------------------------------------------------*/
JBool FIsZero(float a, double eps)
{
	return (FIsEq(a, 0.0, eps));
}

/*----------------------------------------------------------------------------*/
JBool FIsNeg(float a, double eps)
{
	return ((JBool)(a < -eps));
}

/*----------------------------------------------------------------------------*/
JBool FIsPos(float a, double eps)
{
	return ((JBool)(a > eps));
}

/*----------------------------------------------------------------------------*/
JBool FIsSmaller(float a, float b, double eps)
{
	return (FIsNeg(a-b, eps));
}
/*----------------------------------------------------------------------------*/
JBool FIsLarger(float a, float b, double eps)
{
	return (FIsNeg(b-a, eps));
}

/*----------------------------------------------------------------------------*/
JBool FIsEqOrSmaller(float a, float b, double eps)
{
	return ( (JBool)(FIsEq(a, b, eps) || FIsNeg(a-b, eps)) );
}

/*----------------------------------------------------------------------------*/
JBool FIsEqOrLarger(float a, float b, double eps)
{
	return ( (JBool)(FIsEq(a, b, eps) || FIsNeg(b-a, eps)) );
}

/*----------------------------------------------------------------------------*/
JBool DIsEq(double a, double b, double eps)
{
	return ((JBool)(JAbs(a-b) < eps));
}

/*----------------------------------------------------------------------------*/
JBool DIsZero(double a, double eps)
{
	return ((JBool)(DIsEq(a, 0.0, eps)));
}

/*----------------------------------------------------------------------------*/
JBool DIsNeg(double a, double eps)
{
	return ((JBool)(a < -eps));
}

/*----------------------------------------------------------------------------*/
JBool DIsPos(double a, double eps)
{
	return ((JBool)(a > eps));
}

/*----------------------------------------------------------------------------*/
JBool DIsSmaller(double a, double b, double eps)
{
	return (DIsNeg(a-b, eps));
}
/*----------------------------------------------------------------------------*/
JBool DIsLarger(double a, double b, double eps)
{
	return (DIsNeg(b-a, eps));
}

/*----------------------------------------------------------------------------*/
JBool DIsEqOrSmaller(double a, double b, double eps)
{
	return ( (JBool)(DIsEq(a, b, eps) || DIsNeg(a-b, eps)) );
}

/*----------------------------------------------------------------------------*/
JBool DIsEqOrLarger(double a, double b, double eps)
{
	return ( (JBool)(DIsEq(a, b, eps) || DIsNeg(b-a, eps)) );
}

/*----------------------------------------------------------------------------*/
JBool DegreeIsEq(Degree a, Degree b, double eps)
{
	double diff = JMax(a, b) - JMin(a, b);

	while (!DIsSmaller( diff, 360.0, eps))
		diff -= 360.0;

	return (DIsEq (diff, 0.0, eps));
}

/*----------------------------------------------------------------------------*/
JBool DegreeIsZero(Degree a, double eps)
{
	double abs = JAbs(a);

	while (!DIsSmaller (a, 360.0, eps))
		abs -= 360.0;

	return (DIsEq(abs, 0.0, eps));
}

/*----------------------------------------------------------------------------*/
JBool RadianIsEq(Radian a, Radian b, double eps)
{
	double diff = JMax(a, b) - JMin(a, b);

	while (!DIsSmaller( diff, 2*M_PI, eps))
		diff -= 2*M_PI;

	return (DIsEq (diff, 0.0, eps));
}

/*----------------------------------------------------------------------------*/
JBool RadianIsZero(Radian a, double eps)
{
        double abs = JAbs(a);

        while (!DIsSmaller (a, 2*M_PI, eps))
                abs -= 2*M_PI;

        return (DIsEq(abs, 0.0, eps));
}

/*----------------------------------------------------------------------------
                                EOF
------------------------------------------------------------------------------*/

