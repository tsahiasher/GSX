
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				vec4f.h
 Purpose : Prototype header file for 4D float vector.
 Libraries: the math library must be linked, by using the linker flag "-lm".

------------------------------------------------------------------------------*/

#ifndef _vec4f_h
#define _vec4f_h

#include <stdio.h>
#include "geo.h"                                                    /* angles */
#include "vec_basic.h"
#include "vec3f.t"	                                              /* Proj */
#include "vec4f.t"

/*----------------------------------------------------------------------------*/
/* Queries */

#define Vec4fX(v)    Vex(v) 
#define Vec4fY(v)    Vey(v) 
#define Vec4fZ(v)    Vez(v) 
#define Vec4fW(v)    Vez(v) 
#define Vec4fI(v,i)  Vei(v,i) 
#define Vec4fEl(v)   VecEl(v) 

double Vec4fLenSq (Vec4f v);
double Vec4fLen (Vec4f v);

double Vec4fDot (Vec4f v1, Vec4f v2);
double Vec4fDet (Vec4f a, Vec4f b, Vec4f c, Vec4f d);

JBool  Vec4fVecAreEq (Vec4f v1, Vec4f v2);
JBool  Vec4fIsZero (Vec4f v); 

AxisT Vec4fMaxAxis (Vec4f v);			   /*  axis of max coordinate */
/*----------------------------------------------------------------------------*/
/* Standard Operations */

Vec4f  Vec4fAlloc (void);    
JBool  Vec4fFree (Vec4f v);

Vec4f  Vec4fInit (Vec4f v);                          /* inits to (1, 0, 0, 0) */
Vec4f  Vec4fFromXYZW (Vec4f v, float x, float y, float z, float w);
void   Vec4fToXYZW (Vec4f v, float *x, float *y, float *z, float *w);   

Vec4f  Vec4fFromAxisT (Vec4f v, AxisT axis); 
           /* returns a unit length vector in the direction of the input axis */

JBool  Vec4fDtor (Vec4f v);         /* does nothing, supplied for consistency */

Vec4f  Vec4fCreate (void);
Vec4f  Vec4fCreateFromXYZW (float x, float y, float z, float w);
Vec4f  Vec4fCreateFromAxisT (AxisT axis); 
JBool  Vec4fDelete (Vec4f v);


Vec4f  Vec4fCopy (Vec4f orig, Vec4f dest);
Vec4f  Vec4fDup (Vec4f orig);

JBool   Vec4fRead (Vec4f v, FILE *fp);                   /* comment char is # */
JBool   Vec4fBasicRead (Vec4f v, FILE *fp);
JBool   Vec4fWrite (Vec4f v, FILE *fp);		 
#define Vec4fPrint(v)   Vec4fWrite(v, stderr)

int    Vec4fStrLen (Vec4f v);
JStr   Vec4fStrAllocWrite (Vec4f v, int len);
JStr   Vec4fStrWrite (Vec4f v, JStr s);   

/*----------------------------------------------------------------------------*/
/* Synthesis Operations */

Vec4f  Vec4fAdd  (Vec4f v1, Vec4f v2, Vec4f res);
Vec4f  Vec4fAddS (Vec4f v, Vec4f v1);
Vec4f  Vec4fSub  (Vec4f v1, Vec4f v2, Vec4f res);
Vec4f  Vec4fSubS (Vec4f v, Vec4f v1);
Vec4f  Vec4fSca  (Vec4f v, double s, Vec4f res);
Vec4f  Vec4fScaS (Vec4f v, double s);
Vec4f  Vec4fNeg  (Vec4f v, Vec4f res);
Vec4f  Vec4fNegS (Vec4f v);
Vec4f  Vec4fReflect (Vec4f v, AxisT a, Vec4f res);
Vec4f  Vec4fReflectS (Vec4f v, AxisT a);

Vec4f  Vec4fAbs  (Vec4f v, Vec4f res);
Vec4f  Vec4fAbsS (Vec4f v);
Vec4f  Vec4fOrthog (Vec4f v, Vec4f res);
Vec4f  Vec4fOrthogS (Vec4f v);

Vec4f  Vec4fAddSca (Vec4f v1, Vec4f v2, double s, Vec4f r);  /* r = v1 + s*v2 */
Vec4f  Vec4fAddScaS (Vec4f v1, Vec4f v2, double s);    

Vec4f  Vec4fAvg (Vec4f v1, Vec4f v2, double w, Vec4f res); 
	    /* res = (v1 + v2)/w, if w=2 it gives the average, hence the name */
Vec4f  Vec4fCnvxComb (Vec4f v1, Vec4f v2, double t, Vec4f res); 
	                        /* res = t*v1 + (1-t)*v2,  convex combination */
              /* >>> return to Convex issue after polygon etc */
Vec4f  Vec4fLinearComb (Vec4f v1, double s1, Vec4f v2, double s2, Vec4f res);
						       /* res = s1*v1 + s2*v2 */
Vec4f  Vec4fLinearComb3 (Vec4f v1, double s1, Vec4f v2, double s2, 
			 Vec4f v3, double s3, Vec4f res); 
                                               /* res = s1*v1 + s2*v2 + s3*v3 */
Vec4f  Vec4fConvolve (Vec4f v1, Vec4f v2, Vec4f res);	     /* x = x1*x2 etc */

Vec3f  Vec4fProj (Vec4f v, AxisT a, Vec3f res); 

#endif
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

