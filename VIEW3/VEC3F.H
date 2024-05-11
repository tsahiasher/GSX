
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				vec3f.h
 Purpose : Prototype header file for 3D float vector.

 Libraries: the math library must be linked, by using the linker flag "-lm".
------------------------------------------------------------------------------*/

#ifndef _vec3f_h
#define _vec3f_h

#include <stdio.h>
#include "geo.h"                                                    /* angles */
#include "vec_basic.h"
#include "vec2f.t"                                             	      /* Proj */
#include "vec3f.t"
#include "pnt3f.t"
#include "dir3f.t"

/*----------------------------------------------------------------------------*/
/* Queries */

#define Vec3fX(v)    Vex(v) 
#define Vec3fY(v)    Vey(v) 
#define Vec3fZ(v)    Vez(v) 
#define Vec3fI(v,i)  Vei(v,i) 
#define Vec3fEl(v)   VecEl(v) 

double Vec3fLenSq (Vec3f v);
double Vec3fLen (Vec3f v);

double Vec3fDot (Vec3f v1, Vec3f v2);
double Vec3fDet (Vec3f a, Vec3f b, Vec3f c);

/*------------------------------------
 angle queries; 
 zero vectors are illegal as input. 
--------------------------------------*/
Radian Vec3fRadianWithXY (Vec3f v);       /* angle between v and the xy plane */
Radian Vec3fRadianInXY  (Vec3f v);           /* angle with x axis in xy plane */
Radian Vec3fAngle (Vec3f v1, Vec3f v2);               /* 0 <= angle < 2*M_PI) */
double Vec3fSin (Vec3f v1, Vec3f v2);
double Vec3fCos (Vec3f v1, Vec3f v2);
/*------------------------------------*/

JBool  Vec3fVecAreEq (Vec3f v1, Vec3f v2);
JBool  Vec3fVecAreParallel (Vec3f v1, Vec3f v2);
JBool  Vec3fIsZero (Vec3f v); 

AxisT  Vec3fMaxAxis (Vec3f v);	 	           /*  axis of max coordinate */

/*----------------------------------------------------------------------------*/
/* Standard Operations */

Vec3f  Vec3fAlloc (void);    
JBool  Vec3fFree (Vec3f v);

Vec3f  Vec3fInit (Vec3f v);                             /* inits to (1, 0, 0) */
Vec3f  Vec3fFromXYZ (Vec3f v, float x, float y, float z);
void   Vec3fToXYZ (Vec3f v, float *x, float *y, float *z);   
Vec3f  Vec3fFromPnt3f (Vec3f v, Pnt3f p); 	   /* vector from origin to p */
Vec3f  Vec3fFromPolar (Vec3f v, double len, Radian in_xy, Radian with_xy);
void   Vec3fToPolar (Vec3f v, double *len, Radian *in_xy, Radian *with_xy);
Vec3f  Vec3fFromDir3f (Vec3f v, Dir3f d);
Vec3f  Vec3fFromAxisT (Vec3f v, AxisT axis); 
           /* returns a unit length vector in the direction of the input axis */
JBool  Vec3fDtor (Vec3f v);         /* does nothing, supplied for consistency */

Vec3f  Vec3fCreate (void);
Vec3f  Vec3fCreateFromXYZ (float x, float y, float z);
Vec3f  Vec3fCreateFromPolar (double len, Radian in_xy, Radian with_xy);
Vec3f  Vec3fCreateFromPnt3f (Pnt3f p);
Vec3f  Vec3fCreateFromDir3f (Dir3f d);
Vec3f  Vec3fCreateFromAxisT (AxisT axis); 

JBool  Vec3fDelete (Vec3f v);

Vec3f  Vec3fCopy (Vec3f orig, Vec3f dest);
Vec3f  Vec3fDup (Vec3f orig);

JBool   Vec3fRead (Vec3f v, FILE *fp);                   /* comment char is # */
JBool   Vec3fBasicRead (Vec3f v, FILE *fp);
JBool   Vec3fWrite (Vec3f v, FILE *fp);		 
#define Vec3fPrint(v)   Vec3fWrite(v, stdout)

int    Vec3fStrLen (Vec3f v);
JStr   Vec3fStrAllocWrite (Vec3f v, int len);
JStr   Vec3fStrWrite (Vec3f v, JStr s);   

/*----------------------------------------------------------------------------*/
/* Conversions */

double Vec3fNormalize (Vec3f v, Dir3f res); 
			     /* calls Dir3fFromVec3f, returns original length */
			    		/* illegal to invoke with zero vector */
/*----------------------------------------------------------------------------*/
/* Synthesis Operations */

Vec3f  Vec3fAdd  (Vec3f v1, Vec3f v2, Vec3f res);
Vec3f  Vec3fAddS (Vec3f v, Vec3f v1);
Vec3f  Vec3fSub  (Vec3f v1, Vec3f v2, Vec3f res);
Vec3f  Vec3fSubS (Vec3f v, Vec3f v1);
Vec3f  Vec3fSca  (Vec3f v, double s, Vec3f res);
Vec3f  Vec3fScaS (Vec3f v, double s);
Vec3f  Vec3fNeg  (Vec3f v, Vec3f res);
Vec3f  Vec3fNegS (Vec3f v);
Vec3f  Vec3fReflect (Vec3f v, AxisT a, Vec3f res);
Vec3f  Vec3fReflectS (Vec3f v, AxisT a);

Vec3f  Vec3fAbs  (Vec3f v, Vec3f res);
Vec3f  Vec3fAbsS (Vec3f v);
Vec3f  Vec3fCross (Vec3f v1, Vec3f v2, Vec3f res);/* res should not be v1, v2 */
Vec3f  Vec3fCrossS (Vec3f v, Vec3f v1);
Vec3f  Vec3fOrthog (Vec3f v, Vec3f res);	  /* returns NULL on zero vec */
Vec3f  Vec3fOrthogS (Vec3f v);

Vec3f  Vec3fAddSca (Vec3f v1, Vec3f v2, double s, Vec3f r);  /* r = v1 + s*v2 */
Vec3f  Vec3fAddScaS (Vec3f v1, Vec3f v2, double s);    

Vec3f  Vec3fAvg (Vec3f v1, Vec3f v2, double w, Vec3f res); 
	    /* res = (v1 + v2)/w, if w=2 it gives the average, hence the name */
Vec3f  Vec3fCnvxComb (Vec3f v1, Vec3f v2, double t, Vec3f res); 
	                        /* res = t*v1 + (1-t)*v2,  convex combination */
              /* >>> return to Convex issue after polygon etc */
Vec3f  Vec3fLinearComb (Vec3f v1, double s1, Vec3f v2, double s2, Vec3f res);
						       /* res = s1*v1 + s2*v2 */
Vec3f  Vec3fLinearComb3 (Vec3f v1, double s1, Vec3f v2, double s2, 
			 Vec3f v3, double s3, Vec3f res); 
                                               /* res = s1*v1 + s2*v2 + s3*v3 */
Vec3f  Vec3fConvolve (Vec3f v1, Vec3f v2, Vec3f res);	     /* x = x1*x2 etc */

Vec2f  Vec3fProj (Vec3f v, AxisT a, Vec2f res); 

#endif
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

