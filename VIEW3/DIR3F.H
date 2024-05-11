
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				dir3f.h
 Purpose : Prototype header file for 3D normalized float vectors, dir's. 
 Verbs   : 
 Nouns   :
------------------------------------------------------------------------------*/

#ifndef _dir3f_h
#define _dir3f_h

#include <stdio.h>
#include "dir_basic.h"
#include "dir3f.t"

/*----------------------------------------------------------------------------*/
/* Queries */

#define Dir3fX(d)    Dix(d)
#define Dir3fY(d)    Diy(d)
#define Dir3fZ(d)    Diz(d)
#define Dir3fI(d,i)  Dii(d,i)
#define Dir3fEl(d)   DirEl(d)

double  Dir3fDot (Dir3f d1, Dir3f d2);
double  Dir3fDet (Dir3f a, Dir3f b, Dir3f c);

/*------------------------------------*/
/* angle queries;
   zero vectors are illegal as input. */

Radian  Dir3fRadianWithXY (Dir3f d);      /* angle between d and the xy plane */
Radian  Dir3fRadianInXY  (Dir3f d);          /* angle with x axis in xy plane */
Radian  Dir3fAngle (Dir3f d1, Dir3f d2); 	      /* 0 <= angle < 2*M_PI) */
double  Dir3fSin (Dir3f d1, Dir3f d2);
double  Dir3fCos (Dir3f d1, Dir3f d2);
/*------------------------------------*/

JBool  Dir3fDirAreEq (Dir3f d1, Dir3f d2);
AxisT  Dir3fMaxAxis (Dir3f d);                     /*  axis of max coordinate */

/*----------------------------------------------------------------------------*/
/* Standard Operations
   Dir3fFromVec3f, Dir3fFromXYZ: normalize to 
	get d. return NULL with input zero 
	vector, and d will hold garbage. */

Dir3f  Dir3fAlloc (void);
JBool  Dir3fFree (Dir3f d);

Dir3f  Dir3fInit (Dir3f d);                		/* inits to (1, 0, 0) */

Dir3f  Dir3fFromXYZ (Dir3f d, float x, float y, float z); 
Dir3f  Dir3fToXYZ (Dir3f d, float *x, float *y, float *z);
Dir3f  Dir3fFromPolar (Dir3f d, Radian in_xy, Radian with_xy);
Dir3f  Dir3fToPolar (Dir3f d, double *len, Radian *in_xy, Radian *with_xy);
Dir3f  Dir3fFromVec3f (Dir3f d, Vec3f v);     
Dir3f  Dir3fFromAxisT (Dir3f d, AxisT axis);
                          /* returns a dir in the direction of the input axis */
JBool  Dir3fDtor (Dir3f d);         /* does nothing, supplied for consistency */

Dir3f  Dir3fCreate (void);
Dir3f  Dir3fCreateFromXYZ (float x, float y, float z);
Dir3f  Dir3fCreateFromPolar (Radian in_xy, Radian with_xy);
Dir3f  Dir3fCreateFromVec3f (Vec3f v); 
Dir3f  Dir3fCreateFromAxisT (AxisT axis);

JBool  Dir3fDelete (Dir3f d);

Dir3f  Dir3fCopy (Dir3f orig, Dir3f dest);
Dir3f  Dir3fDup (Dir3f orig);

JBool   Dir3fRead (Dir3f d, FILE *fp);                   /* comment char is # */
JBool   Dir3fBasicRead (Dir3f d, FILE *fp);
JBool   Dir3fWrite (Dir3f d, FILE *fp);
#define Dir3fPrint(d)   Dir3fWrite(d, stdout)

int    Dir3fStrLen (Dir3f d);
JStr   Dir3fStrAllocWrite (Dir3f d, int len);
JStr   Dir3fStrWrite (Dir3f d, JStr s);

/*----------------------------------------------------------------------------*/
/* Synthesis Operations */

Dir3f  Dir3fNeg  (Dir3f d, Dir3f res);
Dir3f  Dir3fNegS (Dir3f d);

Dir3f  Dir3fReflect (Dir3f d, AxisT a, Dir3f res);

#endif
/*----------------------------------------------------------------------------
				EOF
------------------------------------------------------------------------------*/

