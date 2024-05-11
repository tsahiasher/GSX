
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				aff3f.c
Purpose : 3D float affine transformations.
------------------------------------------------------------------------------*/

#define   FORMAT  "%f " 
#define   CODE_FORMAT  "%d" 
#define   MAXSTRLEN   255

#include <string.h>
#include <math.h>

#include "comparison.h"
#include "vec3f.h"
#include "vec4f.h"
#include "pnt3f.h"
#include "dir3f.h"

#include "aff3f_priv.h"
#include "aff_basic.h"
#include "aff3f.h"

/*----------------------------------------------------------------------------*/
/* internal */
static void  adjoint (Aff3f a, Aff3f adj);

/*----------------------------------------------------------------------------*/
/* GG II, p. 600 (adjusted to col vecs) */
Vec3f Aff3fTra (Aff3f a, Vec3f res)
{
	return (Vec3fFromXYZ (res, Aff3fIJ(a, 0, 3),
				   Aff3fIJ(a, 1, 3),
			     	   Aff3fIJ(a, 2, 3)));
}

/*----------------------------------------------------------------------------*/
/* GG II, p. 600 */
Vec3f Aff3fSca (Aff3f a, Vec3f res)
{
	Vec4fRec temp_vx, temp_vy, temp_vz;

	Aff3fRowToVec4f (a, 0, &temp_vx);
	Aff3fRowToVec4f (a, 1, &temp_vy);
	Aff3fRowToVec4f (a, 2, &temp_vz);

	return (Vec3fFromXYZ (res, (float)Vec4fLen (&temp_vx),
		 		   (float)Vec4fLen (&temp_vy),
				   (float)Vec4fLen (&temp_vz)));
}

/*----------------------------------------------------------------------------*/
/* GG II, p. 600 (adjusted to col vecs) */
	/* !!! has to be optimized using codes !!! */
void Aff3fXYZAngles (Aff3f a, Radian *x, Radian *y, Radian *z)
{
	Vec3fRec temp_v[3];
	Dir3fRec temp_d[3];
						/* eliminate scale */
	Aff3fColToVec3f (a, 0, &temp_v[0]);	
	Aff3fColToVec3f (a, 1, &temp_v[1]);
	Aff3fColToVec3f (a, 2, &temp_v[2]);

	Vec3fNormalize (&temp_v[0], &temp_d[0]);
	Vec3fNormalize (&temp_v[1], &temp_d[1]);
	Vec3fNormalize (&temp_v[2], &temp_d[2]);

					/* check for coordinate system flip. if
					   determinant is -1, negate matrix  */

	/* !!! formulate better (no matrix talk)
	   !!! GG : also negate sca factors. is this also
	   necessary without shear? where does the flip come from? */

	if (Dir3fDet (&temp_d[0], &temp_d[1], &temp_d[2]) < 0){
		Dir3fNegS (&temp_d[0]);
		Dir3fNegS (&temp_d[1]);
		Dir3fNegS (&temp_d[2]);
	}
						/* get rotations */
	*y = asin (-Dix(&temp_d[2]));
	if (!(DIsZero (cos (*y), epsilon))){
		*x = atan2 ((Dix(&temp_d[1])), (Dix(&temp_d[0])));
		*z = atan2 ((Diy(&temp_d[2])), (Diz(&temp_d[2])));
	}
	else{
		*x = atan2 ((Diz(&temp_d[1])), (Diy(&temp_d[1])));
		*z = 0.0;
	}
}

/*----------------------------------------------------------------------------*/
void Aff3fDirAngle (Aff3f a, Dir3f d, Radian *ang)
{
	/* !!!  not implemented yet !!!  */
}

/*----------------------------------------------------------------------------*/
void Aff3fDirCosSin (Aff3f a, Dir3f d, double *cos, double *sin)
{
	/* !!!  not implemented yet !!!  */
}

/*----------------------------------------------------------------------------*/
void Aff3fAxisAngle (Aff3f a, AxisT *ax, Radian *ang)
{
	/* !!!  not implemented yet !!!  */
}
/*----------------------------------------------------------------------------*/
void Aff3fZYZAngles (Aff3f z1, Radian *x, Radian *y, Radian *z2)
{ 
	/* !!!  not implemented yet !!!  */
}
 
/*----------------------------------------------------------------------------*/
Aff3f Aff3fAlloc (void)
{
	Aff3f a;
	MemA (a, Aff3fRec, 1, "Aff3fAlloc");
	return (a);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fFree (Aff3f a)
{
	return (MemF ((JPtrPtr)&a, Aff3fRec, 1, "Aff3fFree"));
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fInit (Aff3f a)
{
	int i, j;

	For3(i){
		For4(j){
			if (i==j)
				Aff3fIJ (a, i, j) = 1.0;
			else
				Aff3fIJ (a, i, j) = 0.0;		
		}
	}
	Aff3fCode(a) = NO_TRANS;
	return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fFromTra (Aff3f a, Vec3f v)
{
	Aff3fInit (a);
	Aff3fIJ (a, 0, 3) = Vex (v); 
	Aff3fIJ (a, 1, 3) = Vey (v); 
	Aff3fIJ (a, 2, 3) = Vez (v); 

	Aff3fCode(a) = TRA_CODE;
	return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fFromSca (Aff3f a, Vec3f v)
{ 
	Aff3fInit (a);	
        Aff3fIJ (a, 0, 0) = Vex (v);
	Aff3fIJ (a, 1, 1) = Vey (v);
	Aff3fIJ (a, 2, 2) = Vez (v);

	Aff3fCode(a) = SCA_CODE;
	return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fFromXYZRot (Aff3f a, Radian x, Radian y, Radian z)
{
	Aff3fRec affx, affy, affz, temp;

	Aff3fInit (&temp);
	Aff3fFromAxisAngleRot (&affx, AxisXT, x);
	Aff3fFromAxisAngleRot (&affy, AxisYT, y);
	Aff3fFromAxisAngleRot (&affz, AxisZT, z);

	Aff3fCompose (&affy, &affx, &temp);
	Aff3fCompose (&affz, &temp, a);

        Aff3fCode(a) = ROT_CODE;
	return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fFromDirAngleRot (Aff3f a, Dir3f d, Radian ang)
{
	double s, c, t;
	float x, y, z;

	Aff3fInit (a);	
	s = sin (ang);
	c = cos (ang);
	t =   1.0 - c;
	x = Dix(d); y = Diy(d); z = Diz(d);

	Aff3fIJ (a, 0, 0) = t*x*x + c;
	Aff3fIJ (a, 1, 1) = t*y*y + c;
	Aff3fIJ (a, 2, 2) = t*z*z + c;

	Aff3fIJ (a, 0, 1) = t*x*y - s*z;
	Aff3fIJ (a, 0, 2) = t*x*z + s*y;

	Aff3fIJ (a, 1, 0) = t*x*y + s*z;
	Aff3fIJ (a, 1, 2) = t*y*z - s*x;

	Aff3fIJ (a, 2, 0) = t*x*z - s*y;
	Aff3fIJ (a, 2, 1) = t*y*z + s*x;

        Aff3fCode(a) = ROT_CODE;
	return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fFromDirCosSinRot (Aff3f a, Dir3f d, double c, double s)
{
        double t;
	float x, y, z;

        Aff3fInit (a);
        t =   1.0 - c;
	x = Dix(d); y = Diy(d); z = Diz(d);

        Aff3fIJ (a, 0, 0) = t*x*x + c;
        Aff3fIJ (a, 1, 1) = t*y*y + c;
        Aff3fIJ (a, 2, 2) = t*z*z + c;

        Aff3fIJ (a, 0, 1) = t*x*y - s*z;
        Aff3fIJ (a, 0, 2) = t*x*z + s*y;

        Aff3fIJ (a, 1, 0) = t*x*y + s*z;
        Aff3fIJ (a, 1, 2) = t*y*z - s*x;

        Aff3fIJ (a, 2, 0) = t*x*z - s*y;
        Aff3fIJ (a, 2, 1) = t*y*z + s*x;

        Aff3fCode(a) = ROT_CODE;
        return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fFromAxisAngleRot (Aff3f a, AxisT ax, Radian ang)
{
	double c = cos (ang);
	double s = sin (ang);

	Aff3fInit (a);

	switch (ax){
		case AxisXT:
			Aff3fIJ(a,1,1) =  Aff3fIJ(a,2,2) = c;
			Aff3fIJ(a,1,2) = -s;
			Aff3fIJ(a,2,1) = s;
			break;
		case AxisYT:
			Aff3fIJ(a,0,0) = Aff3fIJ(a,2,2) = c;
			Aff3fIJ(a,0,2) = s;
			Aff3fIJ(a,2,0) = -s;
			break;
		case AxisZT:
			Aff3fIJ(a,0,0) = Aff3fIJ(a,1,1) = c;
			Aff3fIJ(a,0,1) = -s;
			Aff3fIJ(a,1,0) = s;
			break;
	}

        Aff3fCode(a) = ROT_CODE;
	return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fFromZYZRot (Aff3f a, Radian z1, Radian y, Radian z2)
{
/* !!!  not implemented yet !!!  */
return (0);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fDtor (Aff3f a) /* empty---supplied for consistency */
{
	return(JTrue);
}

/*----------------------------------------------------------------------------*/
Aff3f Aff3fCreate (void) 
{
	Aff3f a;

	a = Aff3fAlloc ();
	if (a != NULL )
		Aff3fInit (a);
	return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCreateFromTra (Vec3f v)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
		Aff3fFromTra (a, v);
        return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCreateFromSca (Vec3f v)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
		Aff3fFromSca (a, v);
        return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCreateFromXYZRot (Radian x, Radian y, Radian z)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
		Aff3fFromXYZRot (a, x, y, z);
        return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCreateFromDirAngleRot (Dir3f d, Radian ang)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
		Aff3fFromDirAngleRot (a, d, ang);
        return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCreateFromDirCosSinRot (Dir3f d, double c, double s)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
		Aff3fFromDirCosSinRot (a, d, c, s);
        return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCreateFromAxisAngleRot (AxisT ax, Radian ang)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
		Aff3fFromAxisAngleRot (a, ax, ang);
        return (a);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCreateFromZYZRot (Radian z1, Radian y, Radian z2)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
		Aff3fFromZYZRot (a, z1, y, z2);
        return (a);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fDelete (Aff3f a) 
{
	return (Aff3fFree (a));
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fCopy (Aff3f orig, Aff3f dest)
{
	int i,j;

	For3(i)
		For4(j)
			Aff3fIJ(dest, i, j) = Aff3fIJ(orig, i, j);

	Aff3fCode(dest) = Aff3fCode(orig);

	return (dest);
}

/*----------------------------------------------------------------------------*/
Aff3f  Aff3fDup (Aff3f orig)
{
	Aff3f a;

	a = Aff3fAlloc();
	if (a != NULL)
	    	return (Aff3fCopy (orig, a));
	return (NULL);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fRead (Aff3f a, FILE *fp)
{
        char line[LINELENGTH + 1];
        char *startline;

        if ((startline = SkipComment (line, LINELENGTH,fp)) == NULL)
                return (JFalse);
	sscanf (startline, FORMAT FORMAT FORMAT FORMAT,
	       &Aff3fIJ(a,0,0),&Aff3fIJ(a,0,1),&Aff3fIJ(a,0,2),&Aff3fIJ(a,0,3));
        if ((startline = SkipComment (line, LINELENGTH,fp)) == NULL)
                return (JFalse);
	sscanf (startline, FORMAT FORMAT FORMAT FORMAT,
	       &Aff3fIJ(a,1,0),&Aff3fIJ(a,1,1),&Aff3fIJ(a,1,2),&Aff3fIJ(a,1,3));
        if ((startline = SkipComment (line, LINELENGTH,fp)) == NULL)
                return (JFalse);
	sscanf (startline, FORMAT FORMAT FORMAT FORMAT,
	       &Aff3fIJ(a,2,0),&Aff3fIJ(a,2,1),&Aff3fIJ(a,2,2),&Aff3fIJ(a,2,3));

        if ((startline = SkipComment (line, LINELENGTH,fp)) == NULL)
                return (JFalse);
	sscanf (startline, CODE_FORMAT, &Aff3fCode(a));

	return (JTrue);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fBasicRead (Aff3f a, FILE *fp)            
{
	fscanf (fp, FORMAT FORMAT FORMAT FORMAT,
	       &Aff3fIJ(a,0,0),&Aff3fIJ(a,0,1),&Aff3fIJ(a,0,2),&Aff3fIJ(a,0,3));
	fscanf (fp, FORMAT FORMAT FORMAT FORMAT,
	       &Aff3fIJ(a,1,0),&Aff3fIJ(a,1,1),&Aff3fIJ(a,1,2),&Aff3fIJ(a,1,3));
	fscanf (fp, FORMAT FORMAT FORMAT FORMAT,
	       &Aff3fIJ(a,2,0),&Aff3fIJ(a,2,1),&Aff3fIJ(a,2,2),&Aff3fIJ(a,2,3));
	fscanf (fp, CODE_FORMAT, &Aff3fCode(a));
	return (JTrue);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fWrite (Aff3f a, FILE *fp)
{

	if (fprintf (fp, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT "\n",
		Aff3fIJ(a,0,0),Aff3fIJ(a,0,1),
		Aff3fIJ(a,0,2),Aff3fIJ(a,0,3)) > 0 &&
	    fprintf (fp, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT "\n",
		Aff3fIJ(a,1,0),Aff3fIJ(a,1,1),
		Aff3fIJ(a,1,2),Aff3fIJ(a,1,3)) > 0 &&
	    fprintf (fp, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT "\n",
		Aff3fIJ(a,2,0),Aff3fIJ(a,2,1),
		Aff3fIJ(a,2,2),Aff3fIJ(a,2,3)) > 0 &&
	    fprintf (fp, CODE_FORMAT "\n\n", Aff3fCode(a)) > 0)
		return (JTrue);
	else
		return (JFalse);
}

/*----------------------------------------------------------------------------*/
int Aff3fStrLen (Aff3f a)
{
	char s[MAXSTRLEN];

	Aff3fStrWrite (a, s);
	return (strlen (s)+1);
}

/*----------------------------------------------------------------------------*/
JStr Aff3fStrAllocWrite (Aff3f a, int len)
{
	JStr s;
	MemA (s, char, len, "Aff3fStrAllocWrite");
	if (s == NULL)
	    return (NULL);
    	return (Aff3fStrWrite (a, s));
}

/*----------------------------------------------------------------------------*/
JStr Aff3fStrWrite (Aff3f a, JStr s)
{
	char temp[MAXSTRLEN];

	sprintf (temp, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT "\n",
                        Aff3fIJ(a,0,0),Aff3fIJ(a,0,1),
                        Aff3fIJ(a,0,2),Aff3fIJ(a,0,3));
	strcpy (s, temp);
	sprintf (temp, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT "\n",
			Aff3fIJ(a,1,0),Aff3fIJ(a,1,1),
			Aff3fIJ(a,1,2),Aff3fIJ(a,1,3)); 
	strcat (s, temp);
	sprintf (temp, FORMAT "\t" FORMAT "\t" FORMAT "\t" FORMAT "\n",
			Aff3fIJ(a,2,0),Aff3fIJ(a,2,1),
			Aff3fIJ(a,2,2),Aff3fIJ(a,2,3));
	strcat (s, temp);
	sprintf (temp, CODE_FORMAT "\n\n", Aff3fCode(a));
	strcat (s, temp);

	return (s);
}

/*----------------------------------------------------------------------------*/
/*
Aff3f  Aff3fFromLcs (Aff3f a, Lcs3f l)
{
}
*/
/* !!!  not implemented yet !!!  */
/* sb the transformation from global to local, ie */
/* the inverse of l. do not forget codes */

/*----------------------------------------------------------------------------*/
/*
Aff3f  Aff3fCreateFromLcs (Lcs3f l)
{
        Aff3f a;

        a = Aff3fAlloc ();
        if (a != NULL )
             Aff3fFromLcs (a, l);
        return (a);
}
*/
/*----------------------------------------------------------------------------*/
/* !!! has to be optimized using codes !!! */
void Aff3fCompose (Aff3f a1, Aff3f a2, Aff3f res)
{
        int i,j,k;

        For3(i)
                For3(j) {
                        Aff3fIJ(res,i,j) = 0.0;
                        For3(k)
                                Aff3fIJ(res,i,j) = Aff3fIJ(res,i,j) +
                                        Aff3fIJ(a1,i,k) * Aff3fIJ(a2,k,j);
                }
      For3(i)
                Aff3fIJ(res,i,3) = 
                                         
                        Aff3fIJ(a1,i,0)*Aff3fIJ(a2,0,3) +
                        Aff3fIJ(a1,i,1)*Aff3fIJ(a2,1,3) +
                        Aff3fIJ(a1,i,2)*Aff3fIJ(a2,2,3) + Aff3fIJ(a1,i,3);

/*	   For3(i)
                Aff3fIJ(res,i,3) = 
			Aff3fIJ(a1,0,3)*Aff3fIJ(a2,i,0) +
                        Aff3fIJ(a1,1,3)*Aff3fIJ(a2,i,1) +
                        Aff3fIJ(a1,2,3)*Aff3fIJ(a2,i,2) + Aff3fIJ(a2,i,3);
*/
	Aff3fCode(res) = Aff3fCode(a1) | Aff3fCode(a2);
}

/*----------------------------------------------------------------------------*/
void Aff3fComposeS (Aff3f a, Aff3f a1)
{
        Aff3fRec tmp;
        Aff3fCompose (a1, a, &tmp);
        Aff3fCopy (&tmp, a);
}

/*----------------------------------------------------------------------------*/
/* !!! has to be optimized using codes !!! */
void Aff3fTraCompose (Aff3f a, Vec3f v, Aff3f res)
{
        Aff3fRec temp;

        if (FIsZero (Vex (v), epsilon) && FIsZero (Vey (v), epsilon) && 
	    FIsZero (Vez (v), epsilon)){
                	Aff3fCopy (a, res);
                	return ;
        }
        Aff3fInit (&temp);
        Aff3fIJ (&temp,0,3) = Vex (v);
        Aff3fIJ (&temp,1,3) = Vey (v);
        Aff3fIJ (&temp,2,3) = Vez (v);
	Aff3fCode(&temp) = TRA_CODE;

        Aff3fCompose(a, &temp, res);
}

/*----------------------------------------------------------------------------*/
void Aff3fScaCompose(Aff3f a, Vec3f v, Aff3f res)
{
        Vec4fRec row;
        int i;

        if (FIsEq (Vex (v), 1.0, epsilon) && FIsEq (Vey (v), 1.0, epsilon) && 
	    FIsEq (Vez (v), 1.0, epsilon)){
                Aff3fCopy (a, res);
                return ;
        }
        For3(i){
                Aff3fRowToVec4f (a,i,&row);
                Vec4fScaS (&row,VecI(v,i));
                Aff3fRowSet (res,i,Vex(&row),Vey(&row),Vez(&row),Vew(&row));
        }
	Aff3fCode(res) = Aff3fCode(a) | SCA_CODE;
}

/*----------------------------------------------------------------------------*/
void Aff3fDirAngleRotCompose (Aff3f a, Dir3f d, Radian ang, Aff3f res)
{
	Aff3fRec temp;

	if (RadianIsZero (ang, epsilon)){
                Aff3fCopy (a, res);
                return ;
	}
	Aff3fFromDirAngleRot (&temp, d, ang);
	Aff3fCompose (a, &temp, res);
}

/*----------------------------------------------------------------------------*/
void Aff3fAxisAngleRotCompose (Aff3f a, AxisT ax, Radian ang, Aff3f res)
{
        Aff3fRec temp;

        if (RadianIsZero (ang, epsilon)){
                Aff3fCopy (a, res);
                return ;
        }
        Aff3fFromAxisAngleRot (&temp, ax, ang);
        Aff3fCompose (a, &temp, res);
}

/*----------------------------------------------------------------------------*/
void Aff3fDirCosSinRotCompose (Aff3f a, Dir3f d, double c, double s, Aff3f res)
{
        Aff3fRec temp;

        if (DIsEq (c, 1.0, epsilon) && DIsZero (s, epsilon)){
                Aff3fCopy (a, res);
                return ;
        }
        Aff3fFromDirCosSinRot (&temp, d, c, s);
        Aff3fCompose (a, &temp, res);
}

/*----------------------------------------------------------------------------*/
void Aff3fXYZRotCompose (Aff3f a, Radian x, Radian y, Radian z, Aff3f res)
{
        Aff3fRec temp;

        if (RadianIsZero (x, epsilon) && RadianIsZero (y, epsilon) &&
	    RadianIsZero (z, epsilon)){
                Aff3fCopy (a, res);
                return ;
        }
        Aff3fFromXYZRot (&temp, x, y, z);
        Aff3fCompose (a, &temp, res);
}


/*----------------------------------------------------------------------------*/
void Aff3fZYZRotCompose (Aff3f a, Radian z1, Radian y, Radian z2, Aff3f res)
{
        Aff3fRec temp;

        if (RadianIsZero (z1, epsilon) && RadianIsZero (y, epsilon) &&
	    RadianIsZero (z2, epsilon)){
                Aff3fCopy (a, res);
                return ;
        }
        Aff3fFromZYZRot (&temp, z1, y, z2);
        Aff3fCompose (a, &temp, res);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fIsInvertible (Aff3f a, double *det)
{
        *det = Det3x3 (Aff3fIJ(a,0,0), Aff3fIJ(a,1,0), Aff3fIJ(a,2,0),
		       Aff3fIJ(a,0,1), Aff3fIJ(a,1,1), Aff3fIJ(a,2,1),
		       Aff3fIJ(a,0,2), Aff3fIJ(a,1,2), Aff3fIJ(a,2,2));
	
	if (!(DIsEq (*det, 0.0, epsilon)))
		return (JTrue);
	return (JFalse);
}

/*----------------------------------------------------------------------------
from GG I, page 766
	adapted to aff3f, adapted to col vecs
	bug corrected: det = det4x4(a), not det4x4(inv).
------------------------------------------------------------------------------*/
JBool Aff3fRotInverse (Aff3f a, Aff3f inv)
{
        int i,j;
	double det;

	if (Aff3fCode(a) == NO_TRANS){
		Aff3fCopy (a, inv);
		return (JTrue);
	}
	if (Aff3fCode(a) != ROT_CODE)
		return (JFalse);
	if (!(Aff3fIsInvertible (a, &det)))
		return (JFalse);

        adjoint (a, inv);
        For3(i)
                For3(j)
                        Aff3fIJ(inv,i,j) /= det;
        For3(i)
                Aff3fIJ(inv,i,3) = - Aff3fIJ(a,0,3)*Aff3fIJ(inv,i,0)
                                   - Aff3fIJ(a,1,3)*Aff3fIJ(inv,i,1)
                                   - Aff3fIJ(a,2,3)*Aff3fIJ(inv,i,2);

        return (JTrue);
}

/*----------------------------------------------------------------------------*/
JBool Aff3fRotInverseS (Aff3f a)
{
        Aff3fRec tmp;

        Aff3fCopy(a, &tmp);
        return Aff3fRotInverse(&tmp, a);
}

/*----------------------------------------------------------------------------*/
void Aff3fOrthagonalize (Aff3f a, Aff3f res)
{
/* TBI */
}

/*----------------------------------------------------------------------------*/
void Aff3fOrthagonalizeS (Aff3f a)
{
	Aff3fRec temp;
	Aff3fOrthagonalize (a, &temp);
	Aff3fCopy (&temp, a);
}

/*----------------------------------------------------------------------------*/
/* !!! has to be optimized using codes !!! */
void Aff3fPntApply (Aff3f a, Pnt3f p, Pnt3f res)
{
        Pox(res) =
                Pox(p)*Aff3fIJ(a,0,0) +
                Poy(p)*Aff3fIJ(a,0,1) +
                Poz(p)*Aff3fIJ(a,0,2) +
                Aff3fIJ(a,0,3);
        Poy(res) =
                Pox(p)*Aff3fIJ(a,1,0) +
                Poy(p)*Aff3fIJ(a,1,1) +
                Poz(p)*Aff3fIJ(a,1,2) +
                Aff3fIJ(a,1,3);
        Poz(res) =
                Pox(p)*Aff3fIJ(a,2,0) +
                Poy(p)*Aff3fIJ(a,2,1) +
                Poz(p)*Aff3fIJ(a,2,2) +
                Aff3fIJ(a,2,3);
}

/*----------------------------------------------------------------------------*/
/* !!! has to be optimized using codes !!! */
void Aff3fVecApply (Aff3f a, Vec3f v, Vec3f res)
{
        Vex(res) =
                Vex(v)*Aff3fIJ(a,0,0) +
                Vey(v)*Aff3fIJ(a,0,1) +
                Vez(v)*Aff3fIJ(a,0,2) +
                Aff3fIJ(a,0,3);
        Vey(res) =
                Vex(v)*Aff3fIJ(a,1,0) +
                Vey(v)*Aff3fIJ(a,1,1) +
                Vez(v)*Aff3fIJ(a,1,2) +
                Aff3fIJ(a,1,3);
        Vez(res) =
                Vex(v)*Aff3fIJ(a,2,0) +
                Vey(v)*Aff3fIJ(a,2,1) +
                Vez(v)*Aff3fIJ(a,2,2) +
                Aff3fIJ(a,2,3);
}

/*----------------------------------------------------------------------------*/
/* !!! has to be optimized using codes !!! */
void Aff3fDirApply (Aff3f a, Dir3f d, Dir3f res)
{
        Dix(res) =
                Dix(d)*Aff3fIJ(a,0,0) +
                Diy(d)*Aff3fIJ(a,0,1) +
                Diz(d)*Aff3fIJ(a,0,2) +
                Aff3fIJ(a,0,3);
        Diy(res) =
                Dix(d)*Aff3fIJ(a,1,0) +
                Diy(d)*Aff3fIJ(a,1,1) +
                Diz(d)*Aff3fIJ(a,1,2) +
                Aff3fIJ(a,1,3);
        Diz(res) =
                Dix(d)*Aff3fIJ(a,2,0) +
                Diy(d)*Aff3fIJ(a,2,1) +
                Diz(d)*Aff3fIJ(a,2,2) +
                Aff3fIJ(a,2,3);
}

/*----------------------------------------------------------------------------*/
static void adjoint (Aff3f a, Aff3f adj)
{
        float a1, a2, a3;
        float b1, b2, b3;
        float c1, c2, c3;

        a1=Aff3fIJ(a,0,0); a2=Aff3fIJ(a,1,0); a3=Aff3fIJ(a,2,0);
        b1=Aff3fIJ(a,0,1); b2=Aff3fIJ(a,1,1); b3=Aff3fIJ(a,2,1);
        c1=Aff3fIJ(a,0,2); c2=Aff3fIJ(a,1,2); c3=Aff3fIJ(a,2,2);

        Aff3fIJ(adj,0,0) =   Det2x2 (b2, b3, c2, c3);
        Aff3fIJ(adj,0,1) = - Det2x2 (b1, b3, c1, c3);
        Aff3fIJ(adj,0,2) =   Det2x2 (b1, b2, c1, c2);

        Aff3fIJ(adj,1,0) = - Det2x2 (a2, a3, c2, c3);
        Aff3fIJ(adj,1,1) =   Det2x2 (a1, a3, c1, c3);
        Aff3fIJ(adj,1,2) = - Det2x2 (a1, a2, c1, c2);

        Aff3fIJ(adj,2,0) =   Det2x2 (a2, a3, b2, b3);
        Aff3fIJ(adj,2,1) = - Det2x2 (a1, a3, b1, b3);
        Aff3fIJ(adj,2,2) =   Det2x2 (a1, a2, b1, b2);
}

/*----------------------------------------------------------------------------*/
void Aff3fTranspose (Aff3f a, Aff3f res)
{
        int i, j;

        For3(i)
                For3(j)
                        Aff3fIJ(res,i,j) = Aff3fIJ(a,j,i);
}

/*----------------------------------------------------------------------------*/
void Aff3fTransposeS (Aff3f a)
{
        Aff3fRec tmp;

        Aff3fCopy(a, &tmp);
        Aff3fTranspose(&tmp, a);
}

/*----------------------------------------------------------------------------*/
void Aff3fRowToVec4f (Aff3f a, int i, Vec4f v)
{
        Vec4fFromXYZW(v,Aff3fIJ(a,i,0),Aff3fIJ(a,i,1), 
		 	Aff3fIJ(a,i,2),Aff3fIJ(a,i,3));
}

/*----------------------------------------------------------------------------*/
void Aff3fColToVec3f (Aff3f a, int i, Vec3f v)
{
        Vec3fFromXYZ(v,Aff3fIJ(a,0,i),Aff3fIJ(a,1,i), Aff3fIJ(a,2,i));
}

/*----------------------------------------------------------------------------*/
void Aff3fColSet (Aff3f aff, int i, float a, float b, float c)
{
        Aff3fIJ(aff,0,i)=a; Aff3fIJ(aff,1,i)=b;
 	Aff3fIJ(aff,2,i)=c;
}

/*----------------------------------------------------------------------------*/
void Aff3fRowSet (Aff3f aff, int i, float a, float b, float c, float d)
{
        Aff3fIJ(aff,i,0)=a; Aff3fIJ(aff,i,1)=b;
	Aff3fIJ(aff,i,2)=c; Aff3fIJ(aff,i,3)=d;
}

#undef MAXSTRLEN
#undef FORMAT
/*----------------------------------------------------------------------------
				EOF
------------------------------------------------------------------------------*/

