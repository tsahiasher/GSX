
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				geo.h
	Purpose : Header file for general geometric types and operations.
------------------------------------------------------------------------------*/

#ifndef geo_h
#define geo_h

/*----------------------------------------------------------------------------*/
typedef enum { AxisXT, AxisYT, AxisZT, AxisWT } AxisT;	   /* !!! sb in lcs.h */

#define Axis2Next(a) (((a)+1)%2)			   /* !!! sb in lcs.h */
#define Axis2Prev(a) (((a)+1)%2) 			   /* !!! sb in lcs.h */

#define Axis3Next(a) (((a)+1)%3)			   /* !!! sb in lcs.h */
#define Axis3Prev(a) (((a)+2)%3) 			   /* !!! sb in lcs.h */

#define Axis4Next(a) (((a)+1)%4)			   /* !!! sb in lcs.h */
#define Axis4Prev(a) (((a)+3)%4) 			   /* !!! sb in lcs.h */

/*----------------------------------------------------------------------------*/
/* angles */

typedef double Radian;
typedef double Degree;

/*----------------------------------------------------------------------------
  convert degrees into radians and vice versa
------------------------------------------------------------------------------*/
Degree RadianToDegree (Radian rad);
Radian DegreeToRadian (Degree deg);

/*--------------------------------------------------------------------------
  translates a pair dx, dy into an angle in degrees, radians.
--------------------------------------------------------------------------*/
Degree XYToDegree (double dx, double dy);
Radian XYToRadian (double dx, double dy);

/*--------------------------------------------------------------------------
  translates a cos, sin pair into an angle in degrees, radians.
--------------------------------------------------------------------------*/
Degree  CosSinToDegree (double c, double s);
Radian  CosSinToRadian (double c, double s);

/*----------------------------------------------------------------------------*/
/* determinants */

/*----------------------------------------------------------------------------
  returns the determinant of the 2x2 following matrix:
    |  a  b  |
    |  c  d  |
------------------------------------------------------------------------------*/
#define Det2x2(a,b,c,d) ((a)*(d) - (b)*(c))

/*----------------------------------------------------------------------------
  returns the determinant of the 3x3 following matrix:
    |  a1  a2  a3  |
    |  b1  b2  b3  |
    |  c1  c2  c3  |
------------------------------------------------------------------------------*/
#define Det3x3(a1,a2,a3,b1,b2,b3,c1,c2,c3)              \
                ((a1) * Det2x2 (b2, b3, c2, c3) -       \
                 (b1) * Det2x2 (a2, a3, c2, c3) +       \
                 (c1) * Det2x2 (a2, a3, b2, b3))

/*----------------------------------------------------------------------------
  returns the determinant of the 4x4 following matrix:
    |  a1  a2  a3  a4 |
    |  b1  b2  b3  b4 |
    |  c1  c2  c3  c4 |
    |  d1  d2  d3  d4 |
------------------------------------------------------------------------------*/
#define Det4x4(a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4)  \
                ((a1) * Det3x3 (b2, b3, b4, c2, c3, c4, d2, d3, d4) -   \
                 (b1) * Det3x3 (a2, a3, a4, c2, c3, c4, d2, d3, d4) +   \
                 (c1) * Det3x3 (a2, a3, a4, b2, b3, b4, d2, d3, d4) -	\
                 (d1) * Det3x3 (a2, a3, a4, b2, b3, b4, c2, c3, c4))


#endif
/*----------------------------------------------------------------------------
                                E O F
------------------------------------------------------------------------------*/


