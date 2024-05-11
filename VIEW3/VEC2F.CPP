
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				vec2f.c
 Purpose : 2D float Vector operations.

           The functions use allocation and deallocation routines declared
           in "cext.h", and Vec2fFromPolar uses transformations from "aff2f.h".
	   <string.h> is also used.
------------------------------------------------------------------------------*/

#define   FORMAT      "%f"
#define   MAXSTRLEN   255

#include <math.h>
#include <string.h>
#include "comparison.h"
#include "cext.h" 
/* !!! TBI #include "aff2f.h" */
#include "vec2f.h"


/*----------------------------------------------------------------------------*/
double Vec2fLenSq (Vec2f v)
{
        return (Vec2fDot (v, v));
}

/*----------------------------------------------------------------------------*/
double Vec2fLen (Vec2f v)
{
	return (sqrt (Vec2fLenSq(v)));
}

/*----------------------------------------------------------------------------*/
double Vec2fDot (Vec2f v1, Vec2f v2)
{
	return ( (double)(Vex(v1)*Vex(v2)+ 
			  Vey(v1)*Vey(v2)) );
}

/*----------------------------------------------------------------------------*/
double Vec2fDet (Vec2f a, Vec2f b)
{
        return (Det2x2 (Vex(a), Vey(a),
			Vex(b), Vey(b)));
}

/*----------------------------------------------------------------------------*/
JBool Vec2fVecAreEq (Vec2f v1, Vec2f v2)
{
        return ((JBool)(FIsEq (Vex(v1),Vex(v2), epsilon) &&
                FIsEq (Vey(v1),Vey(v2), epsilon)) );
}

/*----------------------------------------------------------------------------*/
JBool Vec2fVecAreParallel (Vec2f v1, Vec2f v2)
{
	Vec2fRec temp;

        return ((JBool)( FIsZero (Vec2fLenSq (Vec2fCross (v1, v2, &temp)), epsilon)));
}

/*----------------------------------------------------------------------------*/
JBool  Vec2fIsZero (Vec2f v)
{
        return ((JBool)(FIsZero(Vex(v), epsilon) &&
                FIsZero(Vey(v), epsilon)));
}

/*----------------------------------------------------------------------------*/
AxisT Vec2fMaxAxis (Vec2f v)
{
        return ((AxisT)(IndexOfMax2f (Vex(v), Vey(v))));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAlloc (void)
{
	Vec2f v;
	MemA (v, Vec2fRec, 1, "Vec2fAlloc");
	return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec2fFree (Vec2f v)
{
	return (MemF ((JPtrPtr)&v, Vec2fRec, 1, "Vec2fFree"));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fInit (Vec2f v)
{
	Vec2fFromXY (v, 1.0, 0.0);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fFromXY (Vec2f v, float x, float y)
{
	Vex(v) = x; Vey(v) = y; 
	return (v);
}

/*----------------------------------------------------------------------------*/
void Vec2fToXY (Vec2f v, float *x, float *y) 
{ 
	*x = Vex(v); *y = Vey(v);
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fFromAxisT (Vec2f v, AxisT axis)
{
	switch (axis){
		case AxisXT: 
			Vec2fFromXY (v, 1.0, 0.0);
			break;
                case AxisYT: 
                        Vec2fFromXY (v, 0.0, 1.0);
                        break;
		default:
			Vec2fFromXY (v, 0.0, 0.0);
			break;
	}
	return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec2fDtor (Vec2f v) 
{
	return (JTrue);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fCreate (void) 
{
	Vec2f v;

	v = Vec2fAlloc ();
	if (v != NULL)
	     Vec2fInit (v);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fCreateFromXY (float x, float y) 
{
	Vec2f v;

	v = Vec2fAlloc ();
	if ( v != NULL )
	    Vec2fFromXY (v, x, y);
	return (v);
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fCreateFromAxisT (AxisT axis)
{
        Vec2f v;

        v = Vec2fAlloc ();
        if (v != NULL)
                Vec2fFromAxisT (v, axis);
        return (v);
}

/*----------------------------------------------------------------------------*/
JBool Vec2fDelete (Vec2f v) 
{
	return (Vec2fFree (v));
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fCopy (Vec2f orig, Vec2f dest)
{
	return (Vec2fFromXY ( dest, Vex (orig), Vey (orig)));
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fDup (Vec2f orig)
{
	Vec2f v;

	v = Vec2fAlloc();
	if (v != NULL)
	    return (Vec2fCopy (orig, v));
	return (NULL);
}

/*----------------------------------------------------------------------------*/
JBool Vec2fRead (Vec2f v, FILE *fp)            
{
	char line[LINELENGTH + 1];
	char *startline = SkipComment (line, LINELENGTH,fp);

	if (startline == NULL)
		return (JFalse);
	return ((JBool)(sscanf (line, FORMAT FORMAT, 
		&Vex(v), &Vey(v)) == 2));
}

/*----------------------------------------------------------------------------*/
JBool Vec2fBasicRead (Vec2f v, FILE *fp)            
{
	return ((JBool)(fscanf (fp, FORMAT FORMAT, 
			&Vex(v), &Vey(v)) == 2));
}

/*----------------------------------------------------------------------------*/
JBool Vec2fWrite (Vec2f v, FILE *fp)
{
	if (fprintf (fp, FORMAT "\t" FORMAT "\n", 
			 Vex(v), Vey(v)) > 0)
		return (JTrue);
	else 
		return (JFalse);
}

/*----------------------------------------------------------------------------*/
int Vec2fStrLen (Vec2f v)
{
        char s[MAXSTRLEN];

        Vec2fStrWrite (v, s);
        return (strlen (s)+1);
}

/*----------------------------------------------------------------------------*/
JStr Vec2fStrAllocWrite (Vec2f v, int len)
{
        char *s;
        MemA (s, char, len, "Vec2fStrAllocWrite");
        if (s == NULL)
                return (NULL);
        return (Vec2fStrWrite (v, s));
}

/*----------------------------------------------------------------------------*/
JStr Vec2fStrWrite (Vec2f v, char *s)
{
	if (sprintf (s, FORMAT "\t" FORMAT, 
			 Vex(v), Vey(v)) > 0 )
		return (s);
	return (NULL);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAdd (Vec2f v1, Vec2f v2, Vec2f res)
{
	Vex(res) = Vex(v1) + Vex(v2);
	Vey(res) = Vey(v1) + Vey(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAddS (Vec2f v, Vec2f v1)
{
	return (Vec2fAdd (v, v1, v));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fSub (Vec2f v1, Vec2f v2, Vec2f res)
{
	Vex(res) = Vex(v1) - Vex(v2);
	Vey(res) = Vey(v1) - Vey(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fSubS (Vec2f v, Vec2f v1)
{
	return (Vec2fSub (v, v1, v));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fSca (Vec2f v, double s, Vec2f res)
{
	Vex(res) = Vex(v)*s;
	Vey(res) = Vey(v)*s;
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fScaS (Vec2f v, double s)
{
	return (Vec2fSca (v,s,v));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fNeg (Vec2f v, Vec2f res)
{
	Vex(res) = -Vex(v);
	Vey(res) = -Vey(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fNegS (Vec2f v)
{
	return (Vec2fNeg (v, v));
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fReflect (Vec2f v, AxisT a, Vec2f res)
{
	switch (a){
		case AxisXT:
			Vex(res) = -Vex(v);
			Vey(res) = Vey(v);
			break;
		case AxisYT:
			Vex(res) = Vex(v);
			Vey(res) = -Vey(v);
			break;
	}
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fReflectS (Vec2f v, AxisT a)
{
	return (Vec2fReflect (v, a, v));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAbs (Vec2f v, Vec2f res)
{
	Vex(res) = (Vex(v) < 0) ? -Vex(v) : Vex(v);
	Vey(res) = (Vey(v) < 0) ? -Vey(v) : Vey(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAbsS (Vec2f v)
{
	return (Vec2fAbs (v, v));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fCross (Vec2f v1, Vec2f v2, Vec2f res)          
{
	Vex(res) =  Vey(v1)*Vez(v2)  -  Vez(v1)*Vey(v2);
	Vey(res) = -Vex(v1)*Vez(v2)  +  Vez(v1)*Vex(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fCrossS (Vec2f v, Vec2f v1)
{
	Vec2fRec temp;

	Vec2fCross (v, v1, &temp);
	return (Vec2fCopy (&temp, v));
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fOrthog (Vec2f v, Vec2f res)
{
	if (!Vec2fIsZero (v)){
		if (!FIsZero (Vex (v), epsilon)){
			Vec2fFromXY (res, Vey (v), -Vex (v));
			return (res);
		}
		if (!FIsZero (Vey (v), epsilon)){
			Vec2fFromXY (res, -Vey (v), Vex (v));
			return (res);
		}
	}
	Vec2fFromXY (res, 0.0, 0.0);
	return (NULL);
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fOrthogS (Vec2f v)
{
	return (Vec2fOrthog (v, v));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAddSca (Vec2f v1, Vec2f v2, double s, Vec2f res)
{
        Vex(res) = Vex(v1) + s*Vex(v2);
        Vey(res) = Vey(v1) + s*Vey(v2);
        return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAddScaS (Vec2f v1, Vec2f v2, double s)
{
        return (Vec2fAddSca (v1, v2, s, v1));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fAvg (Vec2f v1, Vec2f v2, double w, Vec2f res)
{
        Vex(res) = (Vex(v1) + Vex(v2))/w;
        Vey(res) = (Vey(v1) + Vey(v2))/w;
        return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f  Vec2fCnvxComb (Vec2f v1, Vec2f v2, double t, Vec2f res)
{
        return (Vec2fLinearComb (v1, t, v2, 1.0-t, res));
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fLinearComb (Vec2f v1, double s1, Vec2f v2, double s2, Vec2f res)
{
	Vex(res) = s1*Vex(v1) + s2*Vex(v2);
	Vey(res) = s1*Vey(v1) + s2*Vey(v2);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fLinearComb3 (Vec2f v1, double s1, Vec2f v2, double s2, 
			Vec2f v3, double s3, Vec2f res)
{
	Vex(res) = s1*Vex(v1) + s2*Vex(v2) + s3*Vex(v3);
	Vey(res) = s1*Vey(v1) + s2*Vey(v2) + s3*Vey(v3);
	return (res);
}

/*----------------------------------------------------------------------------*/
Vec2f Vec2fConvolve (Vec2f v1, Vec2f v2, Vec2f res)
{
	Vex(res)=Vex(v1)*Vex(v2);
	Vey(res)=Vey(v1)*Vey(v2);
	return (res);
}

#undef MAXSTRLEN
#undef FORMAT
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

