
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                comparison.h
Purpose : Header file for comparison module. comparisons are implemented for
	the basic types "size" (float, double) and "angle" (degree, radian).
	this file is open to general use, in order to provide e.g. comparisons
	between distances. we do not provide a special "size" typedef since
	float and double are already distinguished by the compiler.
------------------------------------------------------------------------------*/

#ifndef comparison_h
#define comparison_h

#include "epsilon.h"
#include "cext.h" 						 /* JBool etc */
#include "geo.h"  					      /* Deg, Rad etc */

/*----------------------------------------------------------------------------*/
typedef enum { LessThanT, EqT, GreaterThanT } ComparatorT;

/*----------------------------------------------------------------------------*/
/* float */

JBool FIsEq(float a, float b, double eps);

JBool FIsZero(float a, double eps);
JBool FIsNeg(float a, double eps);
JBool FIsPos(float a, double eps);

JBool FIsSmaller(float a, float b, double eps);
JBool FIsLarger(float a, float b, double eps);
JBool FIsEqOrSmaller(float a, float b, double eps);
JBool FIsEqOrLarger(float a, float b, double eps);

/*----------------------------------------------------------------------------*/
/* double */

JBool DIsEq(double a, double b, double eps);

JBool DIsZero(double a, double eps);
JBool DIsNeg(double a, double eps);
JBool DIsPos(double a, double eps);

JBool DIsSmaller(double a, double b, double eps);
JBool DIsLarger(double a, double b, double eps);
JBool DIsEqOrSmaller(double a, double b, double eps);
JBool DIsEqOrLarger(double a, double b, double eps);


/*----------------------------------------------------------------------------*/
/* Degree */

JBool DegreeIsEq(Degree a, Degree b, double eps);
JBool DegreeIsZero(Degree a, double eps);

#define DegreeIsNeg(a, eps)            DIsNeg((double)(a), eps)
#define DegreeIsPos(a, eps)            DIsPos((double)(a), eps)

#define DegreeIsSmaller(a, b, eps)     DIsSmaller((double)(a), (double)(b), eps)
#define DegreeIsLarger(a, b, eps)      DIsLarger((double)(a), (double)(b), eps)
#define DegreeIsEqOrSmaller(a, b, eps) \
			DIsEqOrSmaller((double)(a), (double)(b), eps)
#define DegreeIsEqOrLarger(a, b, eps)  \
			DIsEqOrLarger((double)(a), (double)(b), eps)

/*----------------------------------------------------------------------------*/
/* Radian */
JBool RadianIsEq (Radian a, Radian b, double eps);
JBool RadianIsZero (Radian a, double eps);

#define RadianIsNeg(a, eps)            DIsNeg((double)(a), eps)
#define RadianIsPos(a, eps)            DIsPos((double)(a), eps)

#define RadianIsSmaller(a, b, eps)     DIsSmaller((double)(a), (double)(b), eps)
#define RadianIsLarger(a, b, eps)      DIsLarger((double)(a), (double)(b), eps)
#define RadianIsEqOrSmaller(a, b, eps) \
			DIsEqOrSmaller((double)(a), (double)(b), eps)
#define RadianIsEqOrLarger(a, b, eps)  \
			DIsEqOrLarger((double)(a), (double)(b), eps)

#endif
/*----------------------------------------------------------------------------
                                E O F
------------------------------------------------------------------------------*/
