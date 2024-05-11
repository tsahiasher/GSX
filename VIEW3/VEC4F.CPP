
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				vec4f.c
 Purpose : 4D float Vector operations.

           The functions use allocation and deallocation routines declared
           in "cext.h".
	   <string.h> is also used.
------------------------------------------------------------------------------*/

#define   FORMAT      "%f"
#define   MAXSTRLEN   255

#include <string.h>
#include <math.h>
#include "comparison.h"
#include "cext.h" 
#include "vec3f.h"
#include "vec4f.h"


/*----------------------------------------------------------------------------*/
double Vec4fLenSq (Vec4f v)
{
        return (Vec4fDot (v, v));
}

/*----------------------------------------------------------------------------*/
double Vec4fLen (Vec4f v)
{
	return (sqrt (Vec4fLenSq(v)));
}

/*----------------------------------------------------------------------------*/
double Vec4fDot (Vec4f v1, Vec4f v2)
{
	return ( (double)(Vex(v1)*Vex(v2)+ 
			  Vey(v1)*Vey(v2)+
			  Vez(v1)*Vez(v2)+
			  Vew(v1)*Vew(v2)) );
}

/*----------------------------------------------------------------------------*/
double Vec4fDet (Vec4f a, Vec4f b, Vec4f c, Vec4f d)
{
        return (Det4x4 (Vex(a), Vey(a), Vez(a), Vew(a), 
			Vex(b), Vey(b), Vez(b), Vew(b), 
               		Vex(c), Vey(c), Vez(c), Vew(c),
			Vex(c), Vey(c), Vez(c), Vew(d)));
}

/*----------------------------------------------------------------------------*/
JBool Vec4fVecAreEq (Vec4f v1, Vec4f v2)
{
        return ((JBool)(FIsEq (Vex(v1),Vex(v2), epsilon) &&
                FIsEq (Vey(v1),Vey(v2), epsilon) &&
                FIsEq (Vez(v1),Vez(v2), epsilon) &&
                FIsEq (Vew(v1),Vew(v2), epsilon)) );
}

/*----------------------------------------------------------------------------*/
JBool  Vec4fIsZero (Vec4f v)
{
        return ((JBool)(FIsZero(Vex(v), epsilon) &&
                FIsZero(Vey(v), epsilon) &&
                FIsZero(Vez(v), epsilon) &&
                FIsZero(Vew(v), epsilon)));
}

/*----------------------------------------------------------------------------*/
AxisT Vec4fMaxAxis (Vec4f v)
{
        return ((AxisT)(IndexOfMax4f (Vex(v), Vey(v), Vez(v), Vew(v))));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fAlloc (void)
{
	Vec4f v;
	MemA (v, Vec4fRec, 1, "Vec4fAlloc");
	return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec4fFree (Vec4f v)
{
	return (MemF ((JPtrPtr)&v, Vec4fRec, 1, "Vec4fFree"));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fInit (Vec4f v)
{
	Vec4fFromXYZW (v, 1.0, 0.0, 0.0, 0.0);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fFromXYZW (Vec4f v, float x, float y, float z, float w)
{
	Vex(v) = x; Vey(v) = y; Vez(v) = z; Vew(v) = w;
	return (v);
}

/*----------------------------------------------------------------------------*/
void Vec4fToXYZW (Vec4f v, float *x, float *y, float *z, float *w) 
{ 
	*x = Vex(v); *y = Vey(v); *z = Vez(v); *w = Vew(v);
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fFromAxisT (Vec4f v, AxisT axis)
{
	switch (axis){
		case AxisXT: 
			Vec4fFromXYZW (v, 1.0, 0.0, 0.0, 0.0);
			break;
                case AxisYT: 
                        Vec4fFromXYZW (v, 0.0, 1.0, 0.0, 0.0);
                        break;
                case AxisZT: 
                        Vec4fFromXYZW (v, 0.0, 0.0, 1.0, 0.0);
                        break;
                case AxisWT: 
                        Vec4fFromXYZW (v, 0.0, 0.0, 0.0, 1.0);
                        break;
	}
	return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec4fDtor (Vec4f v) 
{
	return (JTrue);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fCreate (void) 
{
	Vec4f v;

	v = Vec4fAlloc ();
	if (v != NULL)
	     Vec4fInit (v);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fCreateFromXYZW (float x, float y, float z, float w) 
{
	Vec4f v;

	v = Vec4fAlloc ();
	if ( v != NULL )
	    Vec4fFromXYZW (v, x, y, z, w);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fCreateFromAxisT (AxisT axis)
{
        Vec4f v;

        v = Vec4fAlloc ();
        if (v != NULL)
                Vec4fFromAxisT (v, axis);
        return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec4fDelete (Vec4f v) 
{
	return (Vec4fFree (v));
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fCopy (Vec4f orig, Vec4f dest)
{
	return (Vec4fFromXYZW ( dest, Vex (orig), Vey (orig), 
			       Vez (orig), Vew (orig)));
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fDup (Vec4f orig)
{
	Vec4f v;

	v = Vec4fAlloc();
	if (v != NULL)
	    return (Vec4fCopy (orig, v));
	return (NULL);
}

/*----------------------------------------------------------------------------*/
JBool Vec4fRead (Vec4f v, FILE *fp)            
{
	char line[LINELENGTH + 1];
	char *startline = SkipComment (line, LINELENGTH,fp);

	if (startline == NULL)
		return (JFalse);
	return ((JBool)(sscanf (line, FORMAT FORMAT FORMAT FORMAT, 
		&Vex(v), &Vey(v), &Vez(v), &Vew(v)) == 4));
}

/*----------------------------------------------------------------------------*/
JBool Vec4fBasicRead (Vec4f v, FILE *fp)            
{
	return ((JBool)(fscanf (fp, FORMAT FORMAT FORMAT FORMAT, 
			&Vex(v), &Vey(v), &Vez(v), &Vew(v) ) == 4));
}

/*----------------------------------------------------------------------------*/
JBool Vec4fWrite (Vec4f v, FILE *fp)
{
	if (fprintf (fp, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT "\n", 
			 Vex(v), Vey(v), Vez(v), Vew(v) ) > 0)
		return (JTrue);
	else 
		return (JFalse);
}

/*----------------------------------------------------------------------------*/
int Vec4fStrLen (Vec4f v)
{
        char s[MAXSTRLEN];

        Vec4fStrWrite (v, s);
        return (strlen (s)+1);
}

/*----------------------------------------------------------------------------*/
JStr Vec4fStrAllocWrite (Vec4f v, int len)
{
        char *s;
        MemA (s, char, len, "Vec4fStrAllocWrite");
        if (s == NULL)
                return (NULL);
        return (Vec4fStrWrite (v, s));
}

/*----------------------------------------------------------------------------*/
JStr Vec4fStrWrite (Vec4f v, char *s)
{
	if (sprintf (s, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT, 
			 Vex(v), Vey(v), Vez(v), Vew(v) ) > 0 )
		return (s);
	return (NULL);
}


/*----------------------------------------------------------------------------*/
Vec4f Vec4fAdd (Vec4f v1, Vec4f v2, Vec4f res)
{
	Vex(res) = Vex(v1) + Vex(v2);
	Vey(res) = Vey(v1) + Vey(v2);
	Vez(res) = Vez(v1) + Vez(v2);
	Vew(res) = Vew(v1) + Vew(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fAddS (Vec4f v, Vec4f v1)
{
	return (Vec4fAdd (v, v1, v));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fSub (Vec4f v1, Vec4f v2, Vec4f res)
{
	Vex(res) = Vex(v1) - Vex(v2);
	Vey(res) = Vey(v1) - Vey(v2);
	Vez(res) = Vez(v1) - Vez(v2);
	Vew(res) = Vew(v1) - Vew(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fSubS (Vec4f v, Vec4f v1)
{
	return (Vec4fSub (v, v1, v));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fSca (Vec4f v, double s, Vec4f res)
{
	Vex(res) = Vex(v)*s;
	Vey(res) = Vey(v)*s;
	Vez(res) = Vez(v)*s;
	Vew(res) = Vew(v)*s;
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fScaS (Vec4f v, double s)
{
	return (Vec4fSca (v,s,v));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fNeg (Vec4f v, Vec4f res)
{
	Vex(res) = -Vex(v);
	Vey(res) = -Vey(v);
	Vez(res) = -Vez(v);
	Vew(res) = -Vew(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fNegS (Vec4f v)
{
	return (Vec4fNeg (v, v));
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fReflect (Vec4f v, AxisT a, Vec4f res)
{
	switch (a){
		case AxisXT:
			Vex(res) = -Vex(v);
			Vey(res) = Vey(v);
			Vez(res) = Vez(v);
			Vew(res) = Vew(v);
			break;
		case AxisYT:
			Vex(res) = Vex(v);
			Vey(res) = -Vey(v);
			Vez(res) = Vez(v);
			Vew(res) = Vew(v);
			break;
		case AxisZT:
			Vex(res) = Vex(v);
			Vey(res) = Vey(v);
			Vez(res) = -Vez(v);
			Vew(res) = Vew(v);
			break;
		case AxisWT:
			Vex(res) = Vex(v);
			Vey(res) = Vey(v);
			Vez(res) = Vez(v);
			Vew(res) = -Vew(v);
			break;
	}
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fReflectS (Vec4f v, AxisT a)
{
	return (Vec4fReflect (v, a, v));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fAbs (Vec4f v, Vec4f res)
{
	Vex(res) = (Vex(v) < 0) ? -Vex(v) : Vex(v);
	Vey(res) = (Vey(v) < 0) ? -Vey(v) : Vey(v);
	Vez(res) = (Vez(v) < 0) ? -Vez(v) : Vez(v);
	Vew(res) = (Vew(v) < 0) ? -Vew(v) : Vew(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fAbsS (Vec4f v)
{
	return (Vec4fAbs (v, v));
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fOrthog (Vec4f v, Vec4f res)
{
	if (!Vec4fIsZero (v)){
		if (!FIsZero (Vex (v), epsilon)){
			Vec4fFromXYZW (res, Vey(v), -Vex(v), Vez(v), Vew(v));
			return (res);
		}
		if (!FIsZero (Vey (v), epsilon)){
			Vec4fFromXYZW (res, -Vey(v), Vex(v), Vez(v), Vew(v));
			return (res);
		}
		if (!FIsZero (Vez (v), epsilon)){
			Vec4fFromXYZW (res, Vex(v), -Vez(v), Vey(v), Vew(v));
			return (res);
		}
		if (!FIsZero (Vew (v), epsilon)){
			Vec4fFromXYZW (res, Vex(v), Vey(v), -Vew(v), Vez(v));
			return (res);
		}
	}
	Vec4fFromXYZW (res, 0.0, 0.0, 0.0, 0.0);
	return (NULL);
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fOrthogS (Vec4f v)
{
	return (Vec4fOrthog (v, v));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fAddSca (Vec4f v1, Vec4f v2, double s, Vec4f res)
{
        Vex(res) = Vex(v1) + s*Vex(v2);
        Vey(res) = Vey(v1) + s*Vey(v2);
        Vez(res) = Vez(v1) + s*Vez(v2);
        Vew(res) = Vew(v1) + s*Vew(v2);
        return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fAddScaS (Vec4f v1, Vec4f v2, double s)
{
        return (Vec4fAddSca (v1, v2, s, v1));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fAvg (Vec4f v1, Vec4f v2, double w, Vec4f res)
{
        Vex(res) = (Vex(v1) + Vex(v2))/w;
        Vey(res) = (Vey(v1) + Vey(v2))/w;
        Vez(res) = (Vez(v1) + Vez(v2))/w;
        Vew(res) = (Vew(v1) + Vew(v2))/w;
        return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f  Vec4fCnvxComb (Vec4f v1, Vec4f v2, double t, Vec4f res)
{
        return (Vec4fLinearComb (v1, t, v2, 1.0-t, res));
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fLinearComb (Vec4f v1, double s1, Vec4f v2, double s2, Vec4f res)
{
	Vex(res) = s1*Vex(v1) + s2*Vex(v2);
	Vey(res) = s1*Vey(v1) + s2*Vey(v2);
	Vez(res) = s1*Vez(v1) + s2*Vez(v2);
	Vew(res) = s1*Vew(v1) + s2*Vew(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fLinearComb3 (Vec4f v1, double s1, Vec4f v2, double s2, 
			Vec4f v3, double s3, Vec4f res)
{
	Vex(res) = s1*Vex(v1) + s2*Vex(v2) + s3*Vex(v3);
	Vey(res) = s1*Vey(v1) + s2*Vey(v2) + s3*Vey(v3);
	Vez(res) = s1*Vez(v1) + s2*Vez(v2) + s3*Vez(v3);
	Vew(res) = s1*Vew(v1) + s2*Vew(v2) + s3*Vew(v3);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec4f Vec4fConvolve (Vec4f v1, Vec4f v2, Vec4f res)
{
	Vex(res)=Vex(v1)*Vex(v2);
	Vey(res)=Vey(v1)*Vey(v2);
	Vez(res)=Vez(v1)*Vez(v2);
	Vew(res)=Vew(v1)*Vew(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec3f  Vec4fProj (Vec4f v, AxisT a, Vec3f res)
{
	switch (a){
		case AxisXT:	Vec3fFromXYZ (res, Vey (v), Vez (v), Vew (v));
				break;
		case AxisYT:	Vec3fFromXYZ (res, Vex (v), Vez (v), Vew (v));
				break;
		case AxisZT:	Vec3fFromXYZ (res, Vex (v), Vey (v), Vew (v));
				break;
		case AxisWT:	Vec3fFromXYZ (res, Vex (v), Vey (v), Vez (v));
				break;
	}
	return (res);
}

#undef MAXSTRLEN
#undef FORMAT
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

