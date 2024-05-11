
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                               aff3f.h
 Purpose : Prototype header file for 3D affine transformations.
	 The Aff3f is basically a 4x3 matrix. We treat vectors as columns.
	 The upper left 3x3 of the Aff3f contains
	 the scale and rotations parameters.
	 The fourth column contains the translation.
	 It is equivalent to the 4x4 matrix which has
	 as a fourth row (0,0,0,1).

	 !!! sb in text

		-----------------------	        -----------------------
Sca,	| Sca1  0    0   Tra1 |	Y rot:  |  c    0    s    0   |
Tra:	|  				      |	        |                     |
		|  0   Sca2  0   Tra2 |	        |  0    1    0    0   |
		|  				      |	        |                     |
		|  0    0   Sca3 Tra3 |	        |  -s   0    c    0   |
		-----------------------	        -----------------------
X rot:	|  1    0    0    0   |	Z rot:  |  c    -s   0    0   |
		|  		      		  |	        |                     |
		|  0    c    -s   0   |	        |  s    c    0    0   |
		|  		      		  |	        |                     |
		|  0    s    c    0   |	        |  0    0    1    0   |
		-----------------------         -----------------------
------------------------------------------------------------------------------*/

#ifndef aff3f_h
#define aff3f_h

#include "vec3f.t"
#include "pnt3f.t"
#include "dir3f.t"
#include "aff3f.t"
#include "cext.h"
#include "geo.h"

/*----------------------------------------------------------------------------*/
/* Queries */

#define Aff3fIJ(a,i,j)  ((a)->el[(i)][(j)])
#define Aff3fI(a,i)     ((a)->el[(i)])
#define Aff3fCode(a)	((a)->code)

/*------------------------------------
 The following queries extract the transformations
 from an Aff3f, in such a way that the following
 composition will reproduce the Aff3f:
	Sca * Rot * Tra
 We assume the Aff3f contains no shear or perspective
 components.
--------------------------------------*/
Vec3f Aff3fTra (Aff3f a, Vec3f res);
Vec3f Aff3fSca (Aff3f a, Vec3f res);
void Aff3fXYZAngles (Aff3f a, Radian *x, Radian *y, Radian *z);
/* TBI */ void Aff3fDirAngle (Aff3f a, Dir3f d, Radian *ang);
/* TBI */ void Aff3fDirCosSin (Aff3f a, Dir3f d, double *cos, double *sin);
/* TBI */ void Aff3fAxisAngle (Aff3f a, AxisT *ax, Radian *ang);
/* TBI */ void Aff3fZYZAngles (Aff3f z1, Radian *x, Radian *y, Radian *z2);


/*----------------------------------------------------------------------------*/
/* Standard Operations */

Aff3f  Aff3fAlloc (void);    
JBool  Aff3fFree (Aff3f a);

Aff3f  Aff3fInit (Aff3f a);                                    /* inits to Id */
Aff3f  Aff3fFromTra (Aff3f a, Vec3f v);
Aff3f  Aff3fFromSca (Aff3f a, Vec3f v);
Aff3f  Aff3fFromXYZRot (Aff3f a, Radian x, Radian y, Radian z);
Aff3f  Aff3fFromDirAngleRot (Aff3f a, Dir3f d, Radian ang);
Aff3f  Aff3fFromDirCosSinRot (Aff3f a, Dir3f d, double c, double s);
Aff3f  Aff3fFromAxisAngleRot (Aff3f a, AxisT ax, Radian ang);
/* TBI */ Aff3f  Aff3fFromZYZRot (Aff3f a, Radian z1, Radian y, Radian z2);
JBool  Aff3fDtor (Aff3f a);         /* does nothing, supplied for consistency */

Aff3f  Aff3fCreate (void);
Aff3f  Aff3fCreateFromTra (Vec3f v);
Aff3f  Aff3fCreateFromSca (Vec3f v);
Aff3f  Aff3fCreateFromXYZRot (Radian x, Radian y, Radian z);
Aff3f  Aff3fCreateFromDirAngleRot (Dir3f d, Radian ang);
Aff3f  Aff3fCreateFromDirCosSinRot (Dir3f d, double c, double s);
Aff3f  Aff3fCreateFromAxisAngleRot (AxisT ax, Radian ang);
Aff3f  Aff3fCreateFromZYZRot (Radian z1, Radian y, Radian z2);
						 /* calls TBI Aff3fFromZYZRot */
JBool  Aff3fDelete (Aff3f a);

Aff3f  Aff3fCopy (Aff3f orig, Aff3f dest);
Aff3f  Aff3fDup (Aff3f orig);

JBool   Aff3fRead (Aff3f a, FILE *fp);                   /* comment char is # */
JBool   Aff3fBasicRead (Aff3f a, FILE *fp);
JBool   Aff3fWrite (Aff3f a, FILE *fp);		 
#define Aff3fPrint(a)   Aff3fWrite(a, stdout)

int    Aff3fStrLen (Aff3f a);
JStr   Aff3fStrAllocWrite (Aff3f a, int len);
JStr   Aff3fStrWrite (Aff3f a, JStr s);   

/*----------------------------------------------------------------------------*/
/* Conversions */
/* TBI */ /* Aff3f  Aff3fFromLcs (Aff3f a, Lcs3f l);  */
/* TBI */ /* Aff3f  Aff3fCreateFromLcs (Lcs3f l);  */

/*----------------------------------------------------------------------------*/
/* Synthesis Operations */
						/* res should not be a1 or a2 */
void  Aff3fCompose (Aff3f a1, Aff3f a2, Aff3f res); 
void  Aff3fComposeS (Aff3f a, Aff3f a1); 

/*------------------------------------
  utilities only:
--------------------------------------*/
void  Aff3fTraCompose (Aff3f a, Vec3f v, Aff3f res);
void  Aff3fScaCompose (Aff3f a, Vec3f v, Aff3f res);

void Aff3fDirAngleRotCompose (Aff3f a, Dir3f d, Radian ang, Aff3f res);
void Aff3fAxisAngleRotCompose (Aff3f a, AxisT ax, Radian ang, Aff3f res);
void Aff3fDirCosSinRotCompose (Aff3f a, Dir3f d, double cos, double sin, 
	Aff3f res); 
void Aff3fXYZRotCompose (Aff3f a, Radian x, Radian y, Radian z, Aff3f res);
void Aff3fZYZRotCompose (Aff3f a, Radian z1, Radian y, Radian z2, Aff3f res);
/*------------------------------------*/

JBool Aff3fIsInvertible (Aff3f a, double *det);
JBool Aff3fRotInverse(Aff3f a, Aff3f inv);  	   /* JFalse if not invertible,
							 or not only rotation */
JBool Aff3fRotInverseS (Aff3f a); 

void Aff3fOrthagonalize (Aff3f a, Aff3f res);
void Aff3fOrthagonalizeS (Aff3f a);

/*----------------------------------------------------------------------------*/
/* (Pnt, Dir, Vec)-Apply are here since they are basic.
   others are in their respective modules. */

void Aff3fPntApply  (Aff3f a, Pnt3f p, Pnt3f res);
void Aff3fVecApply  (Aff3f a, Vec3f v, Vec3f res);
void Aff3fDirApply  (Aff3f a, Dir3f d, Dir3f res);

#endif
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

