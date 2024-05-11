
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                               epsilon.c
 Purpose : comparison tolerances (epsilons)
------------------------------------------------------------------------------*/

#include "epsilon.h"

/*------------------------------------*/

double eps3 = 1.0E-3;
double eps5 = 1.0E-5;
double eps7 = 1.0E-7;
double eps9 = 1.0E-9;

double epsilon  = 1.0E-5;			   /* standard initialization */

/*----------------------------------------------------------------------------*/
double set_eps (AccuracyT acc)
{
	double prev;

	switch (acc){
		case Acc3T:
			prev = epsilon;
			epsilon = eps3;
			return (prev);
		case Acc5T:
			prev = epsilon;
			epsilon = eps5;
			return (prev);
		case Acc7T:
			prev = epsilon;
			epsilon = eps7;
			return (prev);
		case Acc9T:
			prev = epsilon;
			epsilon = eps9;
			return (prev);
	}
	return (0);
}

/*----------------------------------------------------------------------------
                               E O F
------------------------------------------------------------------------------*/

