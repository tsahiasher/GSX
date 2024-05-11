
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                geo.c
        Purpose : general geometric operations.
------------------------------------------------------------------------------*/

#include <math.h>   						  /* for M_PI */

#include "comparison.h" 
#include "geo.h"
#define	M_PI 3.141

/*----------------------------------------------------------------------------*/
Degree RadianToDegree (Radian rad)
{
	return ((Degree)((rad)*180.0/M_PI));
}

/*----------------------------------------------------------------------------*/
Radian DegreeToRadian (Degree deg)
{
	return ((Radian)((deg)*M_PI/180.0));
}

/*---------------------------------------------------------------------------*/
Degree XYToDegree (double dx, double dy)
{
    Degree ang;

        if (!DIsZero (dx, epsilon)){
                ang = RadianToDegree (atan(dy/dx));
                if (dx < 0.0)
                    ang += 180.0;
                if (dx > 0.0 && dy < 0.0)
                    ang += 360.0;
        }
        else
                if (dy > 0.0)
                    ang = 90.0;
                else
                    ang = 270.0;
        return (ang);
}

/*---------------------------------------------------------------------------*/
Radian XYToRadian (double dx, double dy)
{
    Radian ang;

	if (!DIsZero (dx, epsilon)){
		ang = atan(dy/dx);
		if (DIsNeg (dx, epsilon))
		    ang += M_PI;
		if (DIsPos (dx, epsilon) && DIsNeg (dy, epsilon) )
		    ang += M_PI*2.0;
	}
	else
		if (DIsPos (dx, epsilon))
		    ang = M_PI/2.0;
		else
		    ang = 3*M_PI/2.0;
	return (ang);
}

/*----------------------------------------------------------------------------*/
Degree CosSinToDegree (double c, double s)
{
        Degree ang;

        if (DIsZero(c, epsilon))
                ang = (s > 0.5) ? 90.0 : 270.0;
        else {
                ang = RadianToDegree (atan (s/c));
                if (DIsPos (ang, epsilon))
                        if (DIsNeg (s, epsilon))
                                ang += 180.0;
                        else
                                ;
                else
                        if (DIsPos (s, epsilon))
                                ang += 180.0;
                        else
				ang += 360.0;
        }
        return (ang);
}

/*----------------------------------------------------------------------------*/
Radian CosSinToRadian (double c, double s)
{
        Radian ang;

        if (DIsZero(c, epsilon))
                ang = DIsLarger (s, 0.5, epsilon) ? M_PI*0.5 : M_PI*1.5;
        else {
                ang = atan (s/c);
                if (DIsPos (ang, epsilon))
                        if (DIsNeg (s, epsilon))
                                ang += M_PI;
                        else
                                ;
                else
                        if (DIsPos (s, epsilon))
                                ang += M_PI;
                        else
				ang += 2*M_PI;
        }
        return (ang);
}




/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

