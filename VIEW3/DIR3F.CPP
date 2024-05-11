
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				dir3f.c
 Purpose : 3D float unit-length vector, dir, operations.
------------------------------------------------------------------------------*/

#define   FORMAT      "%f"
#define   MAXSTRLEN   255
#define M_PI 3.141

#include <math.h>
#include <string.h>
#include "comparison.h"
#include "cext.h" 
#include "aff3f.h"
#include "dir3f.h"
#include "vec3f.h"	 /* internal computations use Cross, projection, etc, */
			              /* which produce non-normalized vectors */

/*----------------------------------------------------------------------------*/
double Dir3fDot (Dir3f d1, Dir3f d2)
{
	return (double)(Dix(d1)*Dix(d2)+ 
			Diy(d1)*Diy(d2)+
			Diz(d1)*Diz(d2));
}

/*----------------------------------------------------------------------------*/
double Dir3fDet (Dir3f a, Dir3f b, Dir3f c)
{
        return (Det3x3 (Dix(a), Diy(a), Diz(a), 
			Dix(b), Diy(b), Diz(b), 
               		Dix(c), Diy(c), Diz(c)));
}

/*----------------------------------------------------------------------------*/
Radian Dir3fRadianWithXY (Dir3f d)
{
        Vec3fRec proj;                    /* holds projection of d to Z plane */
        float x, y, z;
        double sine, cosine, len, lensq;


        x = Dix (d);                                 /* projection to Z plane */
        y = Diy (d);
        z = 0.0;
        Vec3fFromXYZ (&proj, x, y, z);

        lensq = Vec3fLenSq (&proj);

        if (DIsZero (lensq, epsilon))
                return (M_PI/2);
	len = sqrt (lensq);

        return (Vec3fAngle ((Vec3f)d, &proj));
}

/*----------------------------------------------------------------------------*/
Radian Dir3fRadianInXY (Dir3f d)
{
        Vec3fRec proj;                    /* holds projection of d to Z plane */
        float x, y, z;
        double sine, cosine, len, lensq;


        x = Dix (d);                                 /* projection to Z plane */
        y = Diy (d);
        z = 0.0;
        Vec3fFromXYZ (&proj, x, y, z);

        lensq = Vec3fLenSq (&proj);

        if (DIsZero (lensq, epsilon))
                return (0.0);
	len = sqrt (lensq);

        sine = y / len;
        cosine = x / len;

        return (CosSinToRadian (cosine, sine));
}

/*----------------------------------------------------------------------------*/
Radian Dir3fAngle (Dir3f d1, Dir3f d2)
{
        double sine, cosine;
	Vec3fRec temp;

        cosine = Dir3fDot(d1, d2);
        sine = Vec3fLen (Vec3fCross((Vec3f)d1, (Vec3f)d2, &temp));

        return (atan2 (sine, cosine));
}
/*----------------------------------------------------------------------------*/
double Dir3fCos (Dir3f d1, Dir3f d2)
{
        return (Dir3fDot(d1, d2));
}

/*----------------------------------------------------------------------------*/
double Dir3fSin (Dir3f d1, Dir3f d2)
{
        Vec3fRec temp;
        return (Vec3fLen (Vec3fCross ((Vec3f)d1, (Vec3f)d2, &temp)));
}

/*----------------------------------------------------------------------------*/
JBool Dir3fDirAreEq (Dir3f d1, Dir3f d2)
{
        return ((JBool)(FIsEq (Dix(d1),Dix(d2), epsilon) &&
                FIsEq (Diy(d1),Diy(d2), epsilon) &&
                FIsEq (Diz(d1),Diz(d2), epsilon) ));
}

/*----------------------------------------------------------------------------*/
AxisT Dir3fMaxAxis (Dir3f d)
{
        return ((AxisT)(IndexOfMax3f (Dix(d), Diy(d), Diz(d))));
}

/*----------------------------------------------------------------------------*/
Dir3f Dir3fAlloc (void)
{
	Dir3f d;
	MemA (d, Dir3fRec, 1, "Dir3fAlloc");
	return (d);
}

/*----------------------------------------------------------------------------*/
JBool Dir3fFree (Dir3f d)
{
	return (MemF ((JPtrPtr)&d, Dir3fRec, 1, "Dir3fFree"));
}

/*----------------------------------------------------------------------------*/
Dir3f Dir3fInit (Dir3f d)
{
	Dir3fFromXYZ (d, 1.0, 0.0, 0.0);
	return (d);
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fFromXYZ (Dir3f d, float x, float y, float z)
{
	Vec3fRec tmp;

	Vex(&tmp) = x; Vey(&tmp) = y; Vez(&tmp) = z;

	if ( !(DIsEq (Vec3fLenSq(&tmp), 1.0, epsilon)))
		Dir3fFromVec3f(d, &tmp);			 /* normalize */
	else
		Dix(d) = x; Diy(d) = y; Diz(d) = z;
	return (d);
}

/*----------------------------------------------------------------------------*/
Dir3f Dir3fToXYZ (Dir3f d, float *x, float *y, float *z) 
{ 
	*x = Dix(d); *y = Diy(d); *z = Diz(d);
	return (d);
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fFromPolar (Dir3f d, Radian in_xy, Radian with_xy)
{
	Aff3fRec aff;
	Vec3fRec aux, proj, axis, res;
	Dir3fRec axisdir;
	float x, y, z;

	Vec3fFromAxisT (&aux, AxisXT);            
	Aff3fFromAxisAngleRot(&aff, AxisZT,in_xy);/* rotate aux around Z axis */
	Aff3fVecApply (&aff, &aux, &proj);/* proj holds proj of d on XY plane */

	Vec3fFromAxisT (&aux, AxisZT);
	Vec3fCross (&aux, &proj, &axis);     
	Vec3fNormalize (&axis, &axisdir);
	Aff3fFromDirAngleRot (&aff, &axisdir, with_xy); 
	Aff3fVecApply (&aff, &proj, &res);     

	Dix(d) = Vex(&res); 
	Diy(d) = Vey(&res); 
	Diz(d) = Vez(&res);

	return (d);
	
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fToPolar (Dir3f d, double *len,
                      Radian *in_xy, Radian *with_xy)
{
        JBool ret;
        Vec3fRec proj;                    /* holds projection of d to Z plane */
        float x, y, z;
        double sine, cosine, templen;


        x = Dix (d);                                 /* projection to Z plane */
        y = Diy (d);
        z = 0.0;
        Vec3fFromXYZ (&proj, x, y, z);

        templen = Vec3fLen (&proj);

        if (DIsZero (templen, epsilon)){
                *in_xy = *with_xy = *len = 0.0;
                return (d);
        }

        sine = y / templen;
        cosine = x / templen;

        *in_xy = CosSinToRadian (cosine, sine);
        *with_xy = Vec3fAngle ((Vec3f)d, &proj);
        *len = 1.0;

        return (d);
}

/*----------------------------------------------------------------------------*/
Dir3f Dir3fFromVec3f (Dir3f d, Vec3f v)
{
        Vec3fRec temp;

        double len = Vec3fLen (v);
        if (!DIsZero(len, epsilon)){
                Vec3fSca (v, 1.0/len, &temp);
                Dir3fFromXYZ (d, Vex (&temp), Vey (&temp), Vez (&temp));
		return (d);
        }

	Dix(d) = GARB_COORD;
	Diy(d) = GARB_COORD;
	Diz(d) = GARB_COORD;
	return (NULL);
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fFromAxisT (Dir3f d, AxisT axis)
{
	switch (axis){
		case AxisXT: 
			Dir3fFromXYZ (d, 1.0, 0.0, 0.0);
			break;
                case AxisYT: 
                        Dir3fFromXYZ (d, 0.0, 1.0, 0.0);
                        break;
                case AxisZT: 
                        Dir3fFromXYZ (d, 0.0, 0.0, 1.0);
                        break;
	}
	return (d);
}

/*----------------------------------------------------------------------------*/
JBool Dir3fDtor (Dir3f d) 
{
	return (JTrue);
}

/*----------------------------------------------------------------------------*/
Dir3f Dir3fCreate (void) 
{
	Dir3f d;

	d = Dir3fAlloc ();
	if (d != NULL)
	     Dir3fInit (d);
	return (d);
}

/*----------------------------------------------------------------------------*/

Dir3f Dir3fCreateFromXYZ (float x, float y, float z)
{
	Dir3f d;
	Vec3fRec temp;

	Vec3fFromXYZ (&temp, x, y, z);
        if ( !(DIsEq (Vec3fLenSq(&temp), 1.0, epsilon)))
                return (NULL);

	d = Dir3fAlloc ();
	if ( d != NULL )
		Dir3fFromXYZ (d, x, y, z);
	return (d);
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fCreateFromPolar (Radian in_xy, Radian with_xy)
{
	Dir3f d;

	d = Dir3fAlloc ();
	if (d != NULL)
		Dir3fFromPolar (d, in_xy, with_xy);

	return (d);
}
/*----------------------------------------------------------------------------*/

Dir3f Dir3fCreateFromVec3f(Vec3f v)  // added by avi
{
	Dir3f d;

	d = Dir3fAlloc ();
	if (d != NULL) d=Dir3fFromVec3f(d,v);

	return (d);
}
/*----------------------------------------------------------------------------*/
JBool Dir3fDelete (Dir3f d)
{
	return (Dir3fFree (d));
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fCopy (Dir3f orig, Dir3f dest)
{
	return (Dir3fFromXYZ ( dest, Dix (orig), Diy (orig), 
			       Diz (orig)));
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fDup (Dir3f orig)
{
	Dir3f d;

	d = Dir3fAlloc();
	if (d != NULL)
	    return (Dir3fCopy (orig, d));
	return (NULL);
}

/*----------------------------------------------------------------------------*/
JBool Dir3fRead (Dir3f d, FILE *fp)            
{
        char line[LINELENGTH + 1];
        char *startline = SkipComment (line, LINELENGTH,fp);

        if (startline == NULL)
                return (JFalse);
        return ((JBool)(sscanf (line, FORMAT FORMAT FORMAT,
                &Dix(d), &Diy(d), &Diz(d)) == 3));

}

/*----------------------------------------------------------------------------*/
JBool Dir3fBasicRead (Dir3f d, FILE *fp)            
{
	return ((JBool)(fscanf (fp, FORMAT FORMAT FORMAT, 
			&Dix(d), &Diy(d), &Diz(d) ) == 3));
}

/*----------------------------------------------------------------------------*/
JBool Dir3fWrite (Dir3f d, FILE *fp)
{
	if (fprintf (fp, FORMAT "\t" FORMAT "\t" FORMAT "\n", 
			 Dix(d), Diy(d), Diz(d) ) > 0)
		return (JTrue);
	else 
		return (JFalse);
}

/*----------------------------------------------------------------------------*/
int Dir3fStrLen (Dir3f d)
{
        char s[MAXSTRLEN];

        Dir3fStrWrite (d, s);
        return (strlen (s)+1);
}

/*----------------------------------------------------------------------------*/
JStr Dir3fStrAllocWrite (Dir3f d, int len)
{
        char *s;
        MemA (s, char, len, "Dir3fStrAllocWrite");
        if (s == NULL)
                return (NULL);
        return (Dir3fStrWrite (d, s));
}

/*----------------------------------------------------------------------------*/
JStr Dir3fStrWrite (Dir3f d, char *s)
{
	if (sprintf (s, FORMAT "\t" FORMAT "\t" FORMAT, 
			 Dix(d), Diy(d), Diz(d) ) > 0 )
		return (s);
	return (NULL);
}

/*----------------------------------------------------------------------------*/
Dir3f Dir3fNeg (Dir3f d, Dir3f res)
{
        Dix(res) = -Dix(d);
        Diy(res) = -Diy(d);
        Diz(res) = -Diz(d);
        return (res);
}

/*----------------------------------------------------------------------------*/
Dir3f Dir3fNegS (Dir3f d)
{
        return (Dir3fNeg (d, d));
}

/*----------------------------------------------------------------------------*/
Dir3f  Dir3fReflect (Dir3f d, AxisT a, Dir3f res)
{
        switch (a){
                case AxisXT:
                        Dix(res) = -Dix(d);
                        Diy(res) =  Diy(d);
                        Diz(res) =  Diz(d);
                        break;
                case AxisYT:
                        Dix(res) =  Dix(d);
                        Diy(res) = -Diy(d);
                        Diz(res) =  Diz(d);
                        break;
                case AxisZT:
                        Dix(res) =  Dix(d);
                        Diy(res) =  Diy(d);
                        Diz(res) = -Diz(d);
                        break;
        }
        return (res);
}

#undef MAXSTRLEN
#undef FORMAT
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

