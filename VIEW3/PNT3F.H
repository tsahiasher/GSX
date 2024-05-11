
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				pnt3f.h
 Purpose : Prototype header file for 3D float point.

 Libraries: the math library must be linked, by using the linker flag "-lm".
------------------------------------------------------------------------------*/

#ifndef _pnt3f_h
#define _pnt3f_h

#include <stdio.h>
#include "geo.h"                                                    /* angles */
#include "pnt_basic.h"
#include "cext.h"
#include "vec3f.h"
#include "pnt2f.t"                                                    /* Proj */
#include "pnt3f.t"

/*----------------------------------------------------------------------------*/
/* Queries */

#define Pnt3fX(p)    Pox(p) 
#define Pnt3fY(p)    Poy(p) 
#define Pnt3fZ(p)    Poz(p) 
#define Pnt3fI(p,i)  Poi(p,i) 
#define Pnt3fEl(p)   PntEl(p) 

double Pnt3fDistFromOrigSq(Pnt3f p);
double Pnt3fDistFromOrig(Pnt3f p);

/*------------------------------------*/
/* angle queries; 
   origin illegal as input. */

Radian Pnt3fRadianWithXY (Pnt3f p);  /* angle between (p-origin) and xy plane */
Radian Pnt3fRadianInXY  (Pnt3f p);           /* angle with x axis in xy plane */
/*------------------------------------*/

JBool  Pnt3fPntAreEq(Pnt3f p1, Pnt3f p2);
JBool  Pnt3fIsZero (Pnt3f p); 

AxisT  Pnt3fMaxAxis (Pnt3f p);	 	           /*  axis of max coordinate */
double Pnt3fDet (Pnt3f a, Pnt3f b, Pnt3f c);

/*----------------------------------------------------------------------------*/
/* Standard Operations */

Pnt3f  Pnt3fAlloc (void);    
JBool  Pnt3fFree (Pnt3f p);

Pnt3f  Pnt3fInit (Pnt3f p);                             /* inits to (0, 0, 0) */
Pnt3f  Pnt3fFromXYZ (Pnt3f p, float x, float y, float z);
void   Pnt3fToXYZ (Pnt3f p, float *x, float *y, float *z);   
Pnt3f  Pnt3fFromVec3f (Pnt3f p, Vec3f v); 	 /* v from origin points to p */
Pnt3f  Pnt3fFromPolar (Pnt3f p, double len, Radian in_xy, Radian with_xy);
void   Pnt3fToPolar (Pnt3f p, double *len, Radian *in_xy, Radian *with_xy);
Pnt3f  Pnt3fFromAxisT (Pnt3f p, AxisT axis); 
           		/* returns a point on the input axis, 1.0 from origin */
JBool  Pnt3fDtor (Pnt3f p);         /* does nothing, supplied for consistency */

Pnt3f  Pnt3fCreate (void);
Pnt3f  Pnt3fCreateFromXYZ (float x, float y, float z);
Pnt3f  Pnt3fCreateFromPolar (double len, Radian in_xy, Radian with_xy);
Pnt3f  Pnt3fCreateFromVec3f (Vec3f v);

JBool  Pnt3fDelete (Pnt3f p);

Pnt3f  Pnt3fCopy (Pnt3f orig, Pnt3f dest);
Pnt3f  Pnt3fDup (Pnt3f orig);

JBool   Pnt3fRead (Pnt3f p, FILE *fp);                   /* comment char is # */
JBool   Pnt3fBasicRead (Pnt3f p, FILE *fp);
JBool   Pnt3fWrite (Pnt3f p, FILE *fp);		 
#define Pnt3fPrint(p)   Pnt3fWrite(p, stdout)

int    Pnt3fStrLen (Pnt3f p);
JStr   Pnt3fStrAllocWrite (Pnt3f p, int len);
JStr   Pnt3fStrWrite (Pnt3f p, JStr s);   

/*----------------------------------------------------------------------------*/
/* Synthesis Operations */

double Pnt3fDist      (Pnt3f p1, Pnt3f p2);
double Pnt3fDistSq    (Pnt3f p1, Pnt3f p2);

/*----------------------------------------
  Operations involving both Pnt3f's and Vec3f's
  !!! (included here for now, since pnt has to include
  !!!  vec anyway, and vice versa is not true)
------------------------------------------*/

Pnt3f Pnt3fVec3fAdd (Pnt3f p, Vec3f v, Pnt3f res);         /* Pnt + Vec = Pnt */
Pnt3f Pnt3fVec3fAddS (Pnt3f p, Vec3f v);
Pnt3f Pnt3fVec3fSub (Pnt3f p, Vec3f v, Pnt3f res);         /* Pnt - Vec = Pnt */
Pnt3f Pnt3fVec3fSubS (Pnt3f p, Vec3f v);

Vec3f  Pnt3fSub (Pnt3f p1, Pnt3f p2, Vec3f res);           /* Pnt - Pnt = Vec */

/*----------------------------------------
  ThreePnt3fDot:    Vec3fDot ((p1 - center), (p2 - center))
  ThreePnt3fCross:  Vec3fCross ((p1 - center), (p2 - center))

  ThreePnt3fAngle:  Vec3fAngle ((p1 - center), (p2 - center))
  ThreePnt3fSin:    Vec3fSin ((p1 - center), (p2 - center))
  ThreePnt3fCos:    Vec3fCos ((p1 - center), (p2 - center))

  it is illegal for center to coincide with either of the 
  other points in the angle operations.

  !!! example usage: ThreePnt3fCross gives the normal to the plane
  !!! containing the 3 Pnt3f's, if they are not colinear.
------------------------------------------*/

double ThreePnt3fDot (Pnt3f p1, Pnt3f center, Pnt3f p2);
Vec3f  ThreePnt3fCross (Pnt3f p1, Pnt3f center, Pnt3f p2);

Radian ThreePnt3fAngle (Pnt3f p1, Pnt3f center, Pnt3f p2);
double ThreePnt3fSin (Pnt3f p1, Pnt3f center, Pnt3f p2);
double ThreePnt3fCos (Pnt3f p1, Pnt3f center, Pnt3f p2);

Pnt3f  Pnt3fNeg  (Pnt3f p, Pnt3f res);
Pnt3f  Pnt3fNegS (Pnt3f p);
Pnt3f  Pnt3fReflect (Pnt3f p, AxisT a, Pnt3f res);
Pnt3f  Pnt3fReflectS (Pnt3f p, AxisT a);

Pnt3f  Pnt3fAbs  (Pnt3f p, Pnt3f res);
Pnt3f  Pnt3fAbsS (Pnt3f p);

/* Pnt2f  Pnt3fProj (Pnt3f p, AxisT a, Pnt2f res); !!! until pnt2f exists  */



#endif
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

