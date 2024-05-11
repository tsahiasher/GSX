
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				vec3f.c
 Purpose : 3D float Vector operations.

           The functions use allocation and deallocation routines declared
           in "cext.h", and Vec3fFromPolar uses transformations from "aff3f.h".
	   <string.h> is also used.
------------------------------------------------------------------------------*/

#define   FORMAT      "%f"
#define   MAXSTRLEN   255
#define M_PI 3.141
#include <math.h>
#include <string.h>
#include "comparison.h"
#include "cext.h" 
#include "aff3f.h"
#include "vec3f.h"
#include "vec2f.h"
#include "pnt3f.h"
#include "dir3f.h"


/*----------------------------------------------------------------------------*/
double Vec3fLenSq (Vec3f v)
{
        return (Vec3fDot (v, v));
}

/*----------------------------------------------------------------------------*/
double Vec3fLen (Vec3f v)
{
	return (sqrt (Vec3fLenSq(v)));
}

/*----------------------------------------------------------------------------*/
double Vec3fDot (Vec3f v1, Vec3f v2)
{
	return ( (double)(Vex(v1)*Vex(v2)+ 
			  Vey(v1)*Vey(v2)+
			  Vez(v1)*Vez(v2)) );
}

/*----------------------------------------------------------------------------*/
double Vec3fDet (Vec3f a, Vec3f b, Vec3f c)
{
        return (Det3x3 (Vex(a), Vey(a), Vez(a), 
			Vex(b), Vey(b), Vez(b), 
               		Vex(c), Vey(c), Vez(c)));
}

/*----------------------------------------------------------------------------*/
Radian Vec3fRadianWithXY (Vec3f v)
{
        Vec3fRec proj;                    /* holds projection of v to Z plane */
        float x, y, z;
        double len, lensq;


        x = Vex (v);                                 /* projection to Z plane */
        y = Vey (v);
        z = 0.0;
        Vec3fFromXYZ (&proj, x, y, z);

        lensq = Vec3fLenSq (&proj);

        if (DIsZero (lensq, epsilon))
                return (M_PI/2);
	len = sqrt (lensq);

        return (Vec3fAngle (v, &proj));
}

/*----------------------------------------------------------------------------*/
Radian Vec3fRadianInXY (Vec3f v)
{
        Vec3fRec proj;                    /* holds projection of v to Z plane */
        float x, y, z;
        double sine, cosine, len, lensq;


        x = Vex (v);                                 /* projection to Z plane */
        y = Vey (v);
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
Radian Vec3fAngle (Vec3f v1, Vec3f v2)
{
        double sine, cosine;
        double lenprod, lenprodsq;
	Vec3fRec temp;

        lenprodsq = Vec3fLenSq(v1) * Vec3fLenSq(v2);
        if (DIsZero (lenprodsq, epsilon))
            return (GARB_ANGLE);
	lenprod = sqrt (lenprodsq);

        cosine = Vec3fDot(v1, v2)/lenprod;
        sine = Vec3fLen (Vec3fCross(v1, v2, &temp)) / lenprod;

	return (atan2 (sine, cosine));
}

/*----------------------------------------------------------------------------*/
double Vec3fSin (Vec3f v1, Vec3f v2)
{
        double lenprod, lenprodsq;
        Vec3fRec temp;
	double sine;

        lenprodsq = Vec3fLenSq(v1) * Vec3fLenSq(v2);
        if (DIsZero (lenprodsq, epsilon))
            return (GARB_TRIG);
	lenprod = sqrt (lenprodsq);

        sine = Vec3fLen (Vec3fCross(v1, v2, &temp)) / lenprod;
        return (sine);
}

/*----------------------------------------------------------------------------*/
double Vec3fCos (Vec3f v1, Vec3f v2)
{
        double lenprod, lenprodsq;
	double cosine;

        lenprodsq = Vec3fLenSq(v1) * Vec3fLenSq(v2);
	if (DIsZero (lenprodsq, epsilon))
	    return (GARB_TRIG);
	lenprod = sqrt (lenprodsq);

        cosine = Vec3fDot(v1, v2)/lenprod;
        return (cosine);
}

/*----------------------------------------------------------------------------*/
JBool Vec3fVecAreEq (Vec3f v1, Vec3f v2)
{
        return ((JBool)(FIsEq (Vex(v1),Vex(v2), epsilon) &&
                FIsEq (Vey(v1),Vey(v2), epsilon) &&
                FIsEq (Vez(v1),Vez(v2), epsilon)) );
}

/*----------------------------------------------------------------------------*/
JBool Vec3fVecAreParallel (Vec3f v1, Vec3f v2)
{
	Vec3fRec temp;

        return ( DIsZero (Vec3fLenSq (Vec3fCross (v1, v2, &temp)), epsilon));
}

/*----------------------------------------------------------------------------*/
JBool  Vec3fIsZero (Vec3f v)
{
        return ((JBool)(FIsZero(Vex(v), epsilon) &&
                FIsZero(Vey(v), epsilon) &&
                FIsZero(Vez(v), epsilon)));
}

/*----------------------------------------------------------------------------*/
AxisT Vec3fMaxAxis (Vec3f v)
{
        return ((AxisT)(IndexOfMax3f (Vex(v), Vey(v), Vez(v))));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAlloc (void)
{
	Vec3f v;
	MemA (v, Vec3fRec, 1, "Vec3fAlloc");
	return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec3fFree (Vec3f v)
{
	return (MemF ((JPtrPtr)&v, Vec3fRec, 1, "Vec3fFree"));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fInit (Vec3f v)
{
	Vec3fFromXYZ (v, 1.0, 0.0, 0.0);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fFromXYZ (Vec3f v, float x, float y, float z)
{
	Vex(v) = x; Vey(v) = y; Vez(v) = z;
	return (v);
}

/*----------------------------------------------------------------------------*/
void Vec3fToXYZ (Vec3f v, float *x, float *y, float *z) 
{ 
	*x = Vex(v); *y = Vey(v); *z = Vez(v);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fFromPnt3f (Vec3f v, Pnt3f p)
{
        Vex(v) = Pox(p); Vey(v) = Poy(p); Vez(v) = Poz(p);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fFromPolar (Vec3f v, double len, 
		       Radian in_xy, Radian with_xy)
{
	Aff3fRec aff;
	Vec3fRec aux, proj, axis;
	Dir3fRec axisdir;
	float x, y, z;

	Vec3fFromXYZ (&aux, 1.0, 0.0, 0.0);       /* rotate aux to point to v */
	Aff3fFromAxisAngleRot(&aff, AxisZT,in_xy);/* rotate aux around Z axis */
	Aff3fVecApply (&aff, &aux, &proj);/* proj holds proj of v on XY plane */

	Vec3fFromXYZ (&aux, 0.0, 0.0, 1.0);       /* reset aux to create axis */
	Vec3fCross (&aux, &proj, &axis);     
	Vec3fNormalize (&axis, &axisdir);
	Aff3fFromDirAngleRot (&aff, &axisdir, with_xy); 
	Aff3fVecApply (&aff, &proj, v);          /* v is rotated, lacks scale */

	Vec3fScaS (v, len);

	return (v);
	
}

/*----------------------------------------------------------------------------*/
void  Vec3fToPolar (Vec3f v, double *len,
                      Radian *in_xy, Radian *with_xy)
{
        JBool ret;
        Vec3fRec proj;                    /* holds projection of v to Z plane */
        float x, y, z;
        double sine, cosine, templen;


        x = Vex (v);                                 /* projection to Z plane */
        y = Vey (v);
        z = 0.0;
        Vec3fFromXYZ (&proj, x, y, z);

        templen = Vec3fLen (&proj);

        if (DIsZero (templen, epsilon)){
                *in_xy = *with_xy = 0.0;
		*len = Vez(v);			    /* since v lies on z axis */
                return ;
        }

        sine = y / templen;
        cosine = x / templen;

        *in_xy = CosSinToRadian (cosine, sine);
        *with_xy = Vec3fAngle (v, &proj);
        *len = Vec3fLen (v);
}

/*----------------------------------------------------------------------------*/
Vec3f   Vec3fFromDir3f (Vec3f v, Dir3f d) 
{
	return (Vec3fFromXYZ (v, Dix (d), Diy (d), Diz (d)));
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fFromAxisT (Vec3f v, AxisT axis)
{
	switch (axis){
		case AxisXT: 
			Vec3fFromXYZ (v, 1.0, 0.0, 0.0);
			break;
                case AxisYT: 
                        Vec3fFromXYZ (v, 0.0, 1.0, 0.0);
                        break;
                case AxisZT: 
                        Vec3fFromXYZ (v, 0.0, 0.0, 1.0);
                        break;
                default:
			Vec3fFromXYZ (v, 0.0, 0.0, 0.0);
			break;

	}
	return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec3fDtor (Vec3f v) 
{
	return (JTrue);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fCreate (void) 
{
	Vec3f v;

	v = Vec3fAlloc ();
	if (v != NULL)
	     Vec3fInit (v);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fCreateFromXYZ (float x, float y, float z) 
{
	Vec3f v;

	v = Vec3fAlloc ();
	if ( v != NULL )
	    Vec3fFromXYZ (v, x, y, z);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fCreateFromPnt3f (Pnt3f p)
{
        Vec3f v;

        v = Vec3fAlloc ();
        if (v != NULL)
		Vec3fFromPnt3f (v, p);
        return (v);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fCreateFromPolar (double size, Radian in_xy, Radian with_xy)
{
	Vec3f v;

	v = Vec3fAlloc ();
	if (v != NULL)
	    Vec3fFromPolar (v, size, in_xy, with_xy);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fCreateFromDir3f (Dir3f d)
{
        Vec3f v;

        v = Vec3fAlloc ();
        if (v != NULL)
		Vec3fFromDir3f (v, d);
        return (v);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fCreateFromAxisT (AxisT axis)
{
        Vec3f v;

        v = Vec3fAlloc ();
        if (v != NULL)
                Vec3fFromAxisT (v, axis);
        return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec3fDelete (Vec3f v) 
{
	return (Vec3fFree (v));
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fCopy (Vec3f orig, Vec3f dest)
{
	return (Vec3fFromXYZ ( dest, Vex (orig), Vey (orig), 
			       Vez (orig)));
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fDup (Vec3f orig)
{
	Vec3f v;

	v = Vec3fAlloc();
	if (v != NULL)
	    return (Vec3fCopy (orig, v));
	return (NULL);
}

/*----------------------------------------------------------------------------*/
JBool Vec3fRead (Vec3f v, FILE *fp)            
{
	char line[LINELENGTH + 1];
	char *startline = SkipComment (line, LINELENGTH,fp);

	if (startline == NULL)
		return (JFalse);
	return ((JBool)(sscanf (line, FORMAT FORMAT FORMAT, 
		&Vex(v), &Vey(v), &Vez(v)) == 3));
}

/*----------------------------------------------------------------------------*/
JBool Vec3fBasicRead (Vec3f v, FILE *fp)            
{
	return ((JBool)(fscanf (fp, FORMAT FORMAT FORMAT, 
			&Vex(v), &Vey(v), &Vez(v) ) == 3));
}

/*----------------------------------------------------------------------------*/
JBool Vec3fWrite (Vec3f v, FILE *fp)
{
	if (fprintf (fp, FORMAT "\t" FORMAT "\t" FORMAT "\n", 
			 Vex(v), Vey(v), Vez(v) ) > 0)
		return (JTrue);
	else 
		return (JFalse);
}

/*----------------------------------------------------------------------------*/
int Vec3fStrLen (Vec3f v)
{
        char s[MAXSTRLEN];

        Vec3fStrWrite (v, s);
        return (strlen (s)+1);
}

/*----------------------------------------------------------------------------*/
JStr Vec3fStrAllocWrite (Vec3f v, int len)
{
        char *s;
        MemA (s, char, len, "Vec3fStrAllocWrite");
        if (s == NULL)
                return (NULL);
        return (Vec3fStrWrite (v, s));
}

/*----------------------------------------------------------------------------*/
JStr Vec3fStrWrite (Vec3f v, char *s)
{
	if (sprintf (s, FORMAT "\t" FORMAT "\t" FORMAT, 
			 Vex(v), Vey(v), Vez(v) ) > 0 )
		return (s);
	return (NULL);
}


/*----------------------------------------------------------------------------*/
double Vec3fNormalize (Vec3f v, Dir3f res)
{
	Dir3fFromVec3f (res, v);
	return (Vec3fLen (v));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAdd (Vec3f v1, Vec3f v2, Vec3f res)
{
	Vex(res) = Vex(v1) + Vex(v2);
	Vey(res) = Vey(v1) + Vey(v2);
	Vez(res) = Vez(v1) + Vez(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAddS (Vec3f v, Vec3f v1)
{
	return (Vec3fAdd (v, v1, v));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fSub (Vec3f v1, Vec3f v2, Vec3f res)
{
	Vex(res) = Vex(v1) - Vex(v2);
	Vey(res) = Vey(v1) - Vey(v2);
	Vez(res) = Vez(v1) - Vez(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fSubS (Vec3f v, Vec3f v1)
{
	return (Vec3fSub (v, v1, v));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fSca (Vec3f v, double s, Vec3f res)
{
	Vex(res) = Vex(v)*s;
	Vey(res) = Vey(v)*s;
	Vez(res) = Vez(v)*s;
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fScaS (Vec3f v, double s)
{
	return (Vec3fSca (v,s,v));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fNeg (Vec3f v, Vec3f res)
{
	Vex(res) = -Vex(v);
	Vey(res) = -Vey(v);
	Vez(res) = -Vez(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fNegS (Vec3f v)
{
	return (Vec3fNeg (v, v));
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fReflect (Vec3f v, AxisT a, Vec3f res)
{
	switch (a){
		case AxisXT:
			Vex(res) = -Vex(v);
			Vey(res) = Vey(v);
			Vez(res) = Vez(v);
			break;
		case AxisYT:
			Vex(res) = Vex(v);
			Vey(res) = -Vey(v);
			Vez(res) = Vez(v);
			break;
		case AxisZT:
			Vex(res) = Vex(v);
			Vey(res) = Vey(v);
			Vez(res) = -Vez(v);
			break;
	}
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fReflectS (Vec3f v, AxisT a)
{
	return (Vec3fReflect (v, a, v));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAbs (Vec3f v, Vec3f res)
{
	Vex(res) = (Vex(v) < 0) ? -Vex(v) : Vex(v);
	Vey(res) = (Vey(v) < 0) ? -Vey(v) : Vey(v);
	Vez(res) = (Vez(v) < 0) ? -Vez(v) : Vez(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAbsS (Vec3f v)
{
	return (Vec3fAbs (v, v));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fCross (Vec3f v1, Vec3f v2, Vec3f res)          
{
	Vex(res) =  Vey(v1)*Vez(v2)  -  Vez(v1)*Vey(v2);
	Vey(res) = -Vex(v1)*Vez(v2)  +  Vez(v1)*Vex(v2);
	Vez(res) =  Vex(v1)*Vey(v2)  -  Vey(v1)*Vex(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fCrossS (Vec3f v, Vec3f v1)
{
	Vec3fRec temp;

	Vec3fCross (v, v1, &temp);
	return (Vec3fCopy (&temp, v));
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fOrthog (Vec3f v, Vec3f res)
{
	if (!Vec3fIsZero (v)){
		if (!FIsZero (Vex (v), epsilon)){
			Vec3fFromXYZ (res, Vey (v), -Vex (v), Vez (v));
			return (res);
		}
		if (!FIsZero (Vey (v), epsilon)){
			Vec3fFromXYZ (res, -Vey (v), Vex (v), Vez (v));
			return (res);
		}
		if (!FIsZero (Vez (v), epsilon)){
			Vec3fFromXYZ (res, Vex (v), -Vez (v), Vey (v));
			return (res);
		}
	}
	Vec3fFromXYZ (res, 0.0, 0.0, 0.0);
	return (NULL);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fOrthogS (Vec3f v)
{
	return (Vec3fOrthog (v, v));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAddSca (Vec3f v1, Vec3f v2, double s, Vec3f res)
{
        Vex(res) = Vex(v1) + s*Vex(v2);
        Vey(res) = Vey(v1) + s*Vey(v2);
        Vez(res) = Vez(v1) + s*Vez(v2);
        return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAddScaS (Vec3f v1, Vec3f v2, double s)
{
        return (Vec3fAddSca (v1, v2, s, v1));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fAvg (Vec3f v1, Vec3f v2, double w, Vec3f res)
{
	if ( DIsEq (w, 0.0, epsilon )){
		Bug("Vec3fAvg: Zero division.");
		return (NULL);
	}
        Vex(res) = (Vex(v1) + Vex(v2))/w;
        Vey(res) = (Vey(v1) + Vey(v2))/w;
        Vez(res) = (Vez(v1) + Vez(v2))/w;
        return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec3fCnvxComb (Vec3f v1, Vec3f v2, double t, Vec3f res)
{
        return (Vec3fLinearComb (v1, t, v2, 1.0-t, res));
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fLinearComb (Vec3f v1, double s1, Vec3f v2, double s2, Vec3f res)
{
	Vex(res) = s1*Vex(v1) + s2*Vex(v2);
	Vey(res) = s1*Vey(v1) + s2*Vey(v2);
	Vez(res) = s1*Vez(v1) + s2*Vez(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fLinearComb3 (Vec3f v1, double s1, Vec3f v2, double s2, 
			Vec3f v3, double s3, Vec3f res)
{
	Vex(res) = s1*Vex(v1) + s2*Vex(v2) + s3*Vex(v3);
	Vey(res) = s1*Vey(v1) + s2*Vey(v2) + s3*Vey(v3);
	Vez(res) = s1*Vez(v1) + s2*Vez(v2) + s3*Vez(v3);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f Vec3fConvolve (Vec3f v1, Vec3f v2, Vec3f res)
{
	Vex(res)=Vex(v1)*Vex(v2);
	Vey(res)=Vey(v1)*Vey(v2);
	Vez(res)=Vez(v1)*Vez(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec3fProj (Vec3f v, AxisT a, Vec2f res)
{
	switch (a){
		case AxisXT:	Vec2fFromXY (res, Vey (v), Vez (v));
				break;
		case AxisYT:	Vec2fFromXY (res, Vex (v), Vez (v));
				break;
		case AxisZT:	Vec2fFromXY (res, Vex (v), Vey (v));
				break;
	}
	return (res);
}

#undef MAXSTRLEN
#undef FORMAT
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

