
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				pnt3f.c
 Purpose : 3D float Point operations.

           The functions use allocation and deallocation routines declared
               in "cext.h", and vector functions declared in "vec3f.h".
	       <string.h> is also used.
------------------------------------------------------------------------------*/

#define   FORMAT      "%f"
#define   MAXSTRLEN   255

#include <string.h>
#include "comparison.h"
#include "cext.h"
#include "vec3f.h"
#include "pnt3f.h"

/*----------------------------------------------------------------------------*/
double Pnt3fDistFromOrigSq (Pnt3f p)
{
	Vec3fRec v;

	Vec3fFromPnt3f (&v, p);
	return (Vec3fLenSq (&v));
}

/*----------------------------------------------------------------------------*/
double Pnt3fDistFromOrig (Pnt3f p)
{
	Vec3fRec v;

	Vec3fFromPnt3f (&v, p);
	return (Vec3fLen (&v));
}

/*----------------------------------------------------------------------------*/
Radian Pnt3fRadianWithXY(Pnt3f p)
{
	Vec3fRec v;

	Vec3fFromPnt3f (&v, p);
	return (Vec3fRadianWithXY (&v));
}

/*----------------------------------------------------------------------------*/
Radian Pnt3fRadianInXY(Pnt3f p)
{
	Vec3fRec v;

	Vec3fFromPnt3f (&v, p);
	return (Vec3fRadianInXY (&v));
}

/*----------------------------------------------------------------------------*/
JBool Pnt3fPntAreEq (Pnt3f p1, Pnt3f p2)
{
        return ((JBool)(FIsEq (Pox(p1), Pox(p2), epsilon) &&
                FIsEq (Poy(p1), Poy(p2), epsilon) &&
                FIsEq (Poz(p1), Poz(p2), epsilon)) );
}

/*----------------------------------------------------------------------------*/
JBool  Pnt3fIsZero (Pnt3f p)
{
        return ((JBool)(FIsZero(Pox(p), epsilon) &&
                FIsZero(Poy(p), epsilon) &&
                FIsZero(Poz(p), epsilon)));
}

/*----------------------------------------------------------------------------*/
AxisT Pnt3fMaxAxis (Pnt3f p)
{
        return ((AxisT)(IndexOfMax3f (Pox(p), Poy(p), Poz(p))));
}

/*----------------------------------------------------------------------------*/
double Pnt3fDet (Pnt3f a, Pnt3f b, Pnt3f c)
{
        return (Det3x3 (Pox(a), Poy(a), Poz(a),
                        Pox(b), Poy(b), Poz(b),
                        Pox(c), Poy(c), Poz(c)));
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fAlloc (void)
{
	Pnt3f p;
	MemA (p, Pnt3fRec, 1, "Pnt3fAlloc");
	return (p);
}

/*----------------------------------------------------------------------------*/
JBool Pnt3fFree (Pnt3f p)
{
	return (MemF ((JPtrPtr)&p, Pnt3fRec, 1, "Pnt3fFree"));
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fInit (Pnt3f p)
{
	Pnt3fFromXYZ (p, 0.0, 0.0, 0.0);
	return (p);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fFromXYZ (Pnt3f p, float x, float y, float z)
{
	Pox(p) = x; Poy(p) = y; Poz(p) = z;
	return (p);
}

/*----------------------------------------------------------------------------*/
void Pnt3fToXYZ (Pnt3f p, float *x, float *y, float *z)
{
        *x = Pox(p); *y = Poy(p); *z = Poz(p);
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fFromVec3f (Pnt3f p, Vec3f v)
{
	Pox(p) = Vex(v); Poy(p) = Vey(v); Poz(p) = Vez(v);
	return (p);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fFromPolar (Pnt3f p, double radius, 
		       Radian in_xy, Radian with_xy)
{
	Vec3fRec v;

	Vec3fFromPolar (&v, radius, in_xy, with_xy);

	Pnt3fFromVec3f (p, &v);

	return (p);
}

/*----------------------------------------------------------------------------*/
void  Pnt3fToPolar (Pnt3f p, double *radius,
                      Radian *in_xy, Radian *with_xy)
{
        Vec3fRec v;

        Vec3fFromPnt3f (&v, p);
        Vec3fToPolar (&v, radius, in_xy, with_xy);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fFromAxisT (Pnt3f p, AxisT axis)
{
        switch (axis){
                case AxisXT:
                        Pnt3fFromXYZ (p, 1.0, 0.0, 0.0);
                        break;
                case AxisYT:
                        Pnt3fFromXYZ (p, 0.0, 1.0, 0.0);
                        break;
                case AxisZT:
                        Pnt3fFromXYZ (p, 0.0, 0.0, 1.0);
                        break;
        }
	return (p);
}

/*----------------------------------------------------------------------------*/
JBool Pnt3fDtor (Pnt3f p) /* empty---supplied for consistency */
{
	return(JTrue);
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fCreate (void) 
{
	Pnt3f p;

	p = Pnt3fAlloc ();
	if (p != NULL )
	     Pnt3fInit (p);
	return (p);
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fCreateFromXYZ (float x, float y, float z) 
{
	Pnt3f p;

	p = Pnt3fAlloc ();
	if ( p != NULL )
	    Pnt3fFromXYZ (p, x, y, z);
	return (p);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fCreateFromPolar (double radius, 
			     Radian ang_in_Z, Radian ang_with_Z)
{
	Pnt3f p;

	p = Pnt3fAlloc ();
	if ( p != NULL )
	    Pnt3fFromPolar (p, radius, ang_in_Z, ang_with_Z);
	return (p);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fCreateFromVec3f (Vec3f v)
{
        Pnt3f p;

        p = Pnt3fAlloc ();
        if ( p != NULL )
            Pnt3fFromVec3f (p, v);
        return (p);
}

/*----------------------------------------------------------------------------*/
JBool Pnt3fDelete (Pnt3f p) 
{
	return (Pnt3fFree (p));
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fCopy (Pnt3f orig, Pnt3f dest)
{
	return (Pnt3fFromXYZ ( dest, Pox (orig), Poy (orig), 
			       Poz (orig)));
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fDup (Pnt3f orig)
{
	Pnt3f p;

	p = Pnt3fAlloc();
	if (p != NULL)
	    return (Pnt3fCopy (orig, p));
	return (NULL);
}

/*----------------------------------------------------------------------------*/
JBool Pnt3fRead (Pnt3f p, FILE *fp)            
{
        char line[LINELENGTH + 1];
        char *startline = SkipComment (line, LINELENGTH,fp);

        if (startline == NULL)
                return (JFalse);
        return ((JBool)(sscanf (line, FORMAT FORMAT FORMAT,
                &Pox(p), &Poy(p), &Poz(p)) == 3));

}

/*----------------------------------------------------------------------------*/
JBool Pnt3fBasicRead (Pnt3f p, FILE *fp)
{
	return ((JBool)(fscanf (fp, FORMAT FORMAT FORMAT, 
			&Pox(p), &Poy(p), &Poz(p) ) == 3));
}

/*----------------------------------------------------------------------------*/
JBool Pnt3fWrite (Pnt3f p, FILE *fp)
{
if (fprintf (fp, FORMAT "\t" FORMAT "\t" FORMAT "\n",
		Pox(p), Poy(p), Poz(p) ) > 0)
		return (JTrue);
	else 
		return (JFalse);

}

/*----------------------------------------------------------------------------*/
int Pnt3fStrLen (Pnt3f p)
{
        char s[MAXSTRLEN];

        Pnt3fStrWrite (p, s);
        return (strlen (s)+1);
}

/*----------------------------------------------------------------------------*/
JStr Pnt3fStrAllocWrite (Pnt3f p, int len)
{
	char *s;
	MemA (s, char, len, "Pnt3fStrAllocWrite");
	if (s == NULL)
	    return (NULL);
	if (sprintf (s, FORMAT "\t" FORMAT "\t" FORMAT, 
			 Pox(p), Poy(p), Poz(p) ) > 0 )
	    return (s);
	return (NULL);
}

/*----------------------------------------------------------------------------*/
JStr Pnt3fStrWrite (Pnt3f p, char *s)
{
        if (sprintf (s, FORMAT "\t" FORMAT "\t" FORMAT,
                         Pox(p), Poy(p), Poz(p) ) > 0 )
                return (s);
        return (NULL);
}

/*----------------------------------------------------------------------------*/
double Pnt3fDist (Pnt3f p1, Pnt3f p2)
{
	Vec3fRec tmp;

	return (Vec3fLen (Pnt3fSub (p1, p2, &tmp)));
}

/*----------------------------------------------------------------------------*/
double Pnt3fDistSq (Pnt3f p1, Pnt3f p2)
{
	Vec3fRec tmp;

	return (Vec3fLenSq (Pnt3fSub (p1, p2, &tmp)));
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fVec3fAdd (Pnt3f p, Vec3f v, Pnt3f res)
{
	Pox(res) = Pox(p) + Vex(v);
	Poy(res) = Poy(p) + Vey(v);
	Poz(res) = Poz(p) + Vez(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fVec3fAddS (Pnt3f p, Vec3f v)
{
	return (Pnt3fVec3fAdd (p, v, p));
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fVec3fSub (Pnt3f p, Vec3f v, Pnt3f res)
{
	Pox(res) = Pox(p) - Vex(v);
	Poy(res) = Poy(p) - Vey(v);
	Poz(res) = Poz(p) - Vez(v);
	return (res);
}

/*----------------------------------------------------------------------------*/
Pnt3f Pnt3fVec3fSubS (Pnt3f p, Vec3f v)
{
	return (Pnt3fVec3fSub (p, v, p));
}

/*----------------------------------------------------------------------------*/
Vec3f Pnt3fSub (Pnt3f p1, Pnt3f p2, Vec3f res)
{
	Vex(res) = Pox(p1) - Pox(p2);
	Vey(res) = Poy(p1) - Poy(p2);
	Vez(res) = Poz(p1) - Poz(p2);
	return (res);
}

/*----------------------------------------------------------------------------*/
double ThreePnt3fDot (Pnt3f p1, Pnt3f center, Pnt3f p2)
{
	Vec3fRec tmp1, tmp2;

	return ( Vec3fDot (Pnt3fSub (p1, center, &tmp1), 
			   Pnt3fSub (p2, center, &tmp2)));
}

/*----------------------------------------------------------------------------*/
Vec3f  ThreePnt3fCross (Pnt3f p1, Pnt3f center, Pnt3f p2)
{
	Vec3fRec tmp1, tmp2, tmp3;

	return (Vec3fCross (Pnt3fSub (p1, center, &tmp1), 
			    Pnt3fSub (p2, center, &tmp2), &tmp3));
}

/*----------------------------------------------------------------------------*/
Radian  ThreePnt3fAngle (Pnt3f p1, Pnt3f center, Pnt3f p2)
{
	Vec3fRec tmp1, tmp2;

	return ( Vec3fAngle (Pnt3fSub (p1, center, &tmp1), 
			     Pnt3fSub (p2, center, &tmp2)));
}

/*----------------------------------------------------------------------------*/
double ThreePnt3fSin (Pnt3f p1, Pnt3f center, Pnt3f p2)
{
	Vec3fRec tmp1, tmp2;

	return ( Vec3fSin (Pnt3fSub (p1, center, &tmp1), 
			   Pnt3fSub (p2, center, &tmp2)));
}

/*----------------------------------------------------------------------------*/
double ThreePnt3fCos (Pnt3f p1, Pnt3f center, Pnt3f p2)
{
	Vec3fRec tmp1, tmp2;

	return ( Vec3fCos (Pnt3fSub (p1, center, &tmp1), 
			   Pnt3fSub (p2, center, &tmp2)));
}


/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fNeg  (Pnt3f p, Pnt3f res)
{
	Pox(res) = -Pox(p);
	Poy(res) = -Poy(p);
	Poz(res) = -Poz(p);
	return (res);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fNegS (Pnt3f p)
{
	return (Pnt3fNeg (p, p));
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fReflect (Pnt3f p, AxisT a, Pnt3f res)
{
        switch (a){
                case AxisXT:
                        Pox(res) = -Pox(p);
                        Poy(res) = Poy(p);
                        Poz(res) = Poz(p);
                        break;
                case AxisYT:
                        Pox(res) = Pox(p);
                        Poy(res) = -Poy(p);
                        Poz(res) = Poz(p);
                        break;
                case AxisZT:
                        Pox(res) = Pox(p);
                        Poy(res) = Poy(p);
                        Poz(res) = -Poz(p);
                        break;
        }
        return (res);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fReflectS (Pnt3f p, AxisT a)
{
	return (Pnt3fReflect (p, a, p));
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fAbs  (Pnt3f p, Pnt3f res)
{
        Pox(res) = (Pox(p) < 0) ? -Pox(p) : Pox(p);
        Poy(res) = (Poy(p) < 0) ? -Poy(p) : Poy(p);
        Poz(res) = (Poz(p) < 0) ? -Poz(p) : Poz(p);
	return (res);
}

/*----------------------------------------------------------------------------*/
Pnt3f  Pnt3fAbsS (Pnt3f p)
{
	return (Pnt3fAbs (p, p));
}

/*----------------------------------------------------------------------------*/
Pnt2f  Pnt3fProj (Pnt3f p, AxisT a, Pnt2f res)
{
/****
 !!!! until pnt2f.h exists !!!!
 ****
        switch (a){
                case AxisXT:     Pnt2fFromXY (res, Poy (p), Poz (p));
                                break;
                case AxisYT:     Pnt2fFromXY (res, Pox (p), Poz (p));
                                break;
                case AxisZT:     Pnt2fFromXY (res, Pox (p), Poy (p));
                                break;
        }
        return (res);
****/
	return (res);
}
/*----------------------------------------------------------------------------*/

#undef MAXSTRLEN
#undef FORMAT

/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

