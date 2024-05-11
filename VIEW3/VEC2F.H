
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				vec2f.h
 Purpose : Prototype header file for 2D float vector.

 Libraries: the math library must be linked, by using the linker flag "-lm".
------------------------------------------------------------------------------*/

#ifndef _vec2f_h
#define _vec2f_h

#include <stdio.h>
#include "geo.h"                                                    /* angles */
#include "vec_basic.h"
#include "vec2f.t"

/*----------------------------------------------------------------------------*/
/* Queries */

#define Vec2fX(v)    Vex(v) 
#define Vec2fY(v)    Vey(v) 
#define Vec2fI(v,i)  Vei(v,i) 
#define Vec2fEl(v)   VecEl(v) 

double Vec2fLenSq (Vec2f v);
double Vec2fLen (Vec2f v);

double Vec2fDot (Vec2f v1, Vec2f v2);
double Vec2fDet (Vec2f a, Vec2f b);

JBool  Vec2fVecAreEq (Vec2f v1, Vec2f v2);
JBool  Vec2fVecAreParallel (Vec2f v1, Vec2f v2);
JBool  Vec2fIsZero (Vec2f v); 

AxisT  Vec2fMaxAxis (Vec2f v);	 	           /*  axis of max coordinate */

/*----------------------------------------------------------------------------*/
/* Standard Operations */

Vec2f  Vec2fAlloc (void);    
JBool  Vec2fFree (Vec2f v);

Vec2f  Vec2fInit (Vec2f v);                                /* inits to (1, 0) */
Vec2f  Vec2fFromXY (Vec2f v, float x, float y);
void   Vec2fToXY (Vec2f v, float *x, float *y);   
Vec2f  Vec2fFromAxisT (Vec2f v, AxisT axis); 
           /* returns a unit length vector in the direction of the input axis */

JBool  Vec2fDtor (Vec2f v);         /* does nothing, supplied for consistency */

Vec2f  Vec2fCreate (void);
Vec2f  Vec2fCreateFromXY (float x, float y);
Vec2f  Vec2fCreateFromAxisT (AxisT axis); 

JBool  Vec2fDelete (Vec2f v);

Vec2f  Vec2fCopy (Vec2f orig, Vec2f dest);
Vec2f  Vec2fDup (Vec2f orig);

JBool   Vec2fRead (Vec2f v, FILE *fp);                   /* comment char is # */
JBool   Vec2fBasicRead (Vec2f v, FILE *fp);
JBool   Vec2fWrite (Vec2f v, FILE *fp);		 
#define Vec2fPrint(v)   Vec2fWrite(v, stderr)

int    Vec2fStrLen (Vec2f v);
JStr   Vec2fStrAllocWrite (Vec2f v, int len);
JStr   Vec2fStrWrite (Vec2f v, JStr s);   

/*----------------------------------------------------------------------------*/
/* Synthesis Operations */

Vec2f  Vec2fAdd  (Vec2f v1, Vec2f v2, Vec2f res);
Vec2f  Vec2fAddS (Vec2f v, Vec2f v1);
Vec2f  Vec2fSub  (Vec2f v1, Vec2f v2, Vec2f res);
Vec2f  Vec2fSubS (Vec2f v, Vec2f v1);
Vec2f  Vec2fSca  (Vec2f v, double s, Vec2f res);
Vec2f  Vec2fScaS (Vec2f v, double s);
Vec2f  Vec2fNeg  (Vec2f v, Vec2f res);
Vec2f  Vec2fNegS (Vec2f v);
Vec2f  Vec2fReflect (Vec2f v, AxisT a, Vec2f res);
Vec2f  Vec2fReflectS (Vec2f v, AxisT a);

Vec2f  Vec2fAbs  (Vec2f v, Vec2f res);
Vec2f  Vec2fAbsS (Vec2f v);
Vec2f  Vec2fCross (Vec2f v1, Vec2f v2, Vec2f res);
Vec2f  Vec2fCrossS (Vec2f v, Vec2f v1);
Vec2f  Vec2fOrthog (Vec2f v, Vec2f res);
Vec2f  Vec2fOrthogS (Vec2f v);

Vec2f  Vec2fAddSca (Vec2f v1, Vec2f v2, double s, Vec2f r);  /* r = v1 + s*v2 */
Vec2f  Vec2fAddScaS (Vec2f v1, Vec2f v2, double s);    

Vec2f  Vec2fAvg (Vec2f v1, Vec2f v2, double w, Vec2f res); 
	    /* res = (v1 + v2)/w, if w=2 it gives the average, hence the name */
Vec2f  Vec2fCnvxComb (Vec2f v1, Vec2f v2, double t, Vec2f res); 
	                        /* res = t*v1 + (1-t)*v2,  convex combination */
              /* >>> return to Convex issue after polygon etc */
Vec2f  Vec2fLinearComb (Vec2f v1, double s1, Vec2f v2, double s2, Vec2f res);
						       /* res = s1*v1 + s2*v2 */
Vec2f  Vec2fLinearComb3 (Vec2f v1, double s1, Vec2f v2, double s2, 
			 Vec2f v3, double s3, Vec2f res); 
                                               /* res = s1*v1 + s2*v2 + s3*v3 */
Vec2f  Vec2fConvolve (Vec2f v1, Vec2f v2, Vec2f res);	     /* x = x1*x2 etc */

#endif
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

