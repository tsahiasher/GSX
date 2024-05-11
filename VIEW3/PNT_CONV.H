
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				pnt_conversions.h
 Purpose : conversions between points differentiated by coordinate type.

 Usage   : include the relevant .h vec file before this one.
------------------------------------------------------------------------------*/

#ifndef _pnt_conversions_h
#define _pnt_conversions_h

/*----------------------------------------------------------------------------*/
/* Conversions */

/* Pnt2, short <-> float */
#define Pnt2s2f(s,f) Pnt2fFromXY(f,(float)Pox(s),(float)Poy(s))	
#define Pnt2f2s(f,s) Pnt2sFromXY(s,(short)Pox(f),(short)Poy(f))

/* Pnt2, double <-> float */
#define Pnt2d2f(d,f) Pnt2fFromXY(f,(float)Pox(d),(float)Poy(d))	
#define Pnt2f2d(f,d) Pnt2dFromXY(d,(double)Pox(f),(double)Poy(f))

/* Pnt3, short <-> float */
#define Pnt3s3f(s,f) Pnt3fFromXYZ(f,(float)Pox(s),(float)Poy(s),(float)Poz(s))
#define Pnt3f3s(f,s) Pnt3sFromXYZ(s,(short)Pox(f),(short)Poy(f),(short)Poz(f)) 

/* Pnt3, double <-> float */
#define Pnt3d3f(d,f) Pnt3fFromXYZ(f,(float)Pox(d),(float)Poy(d),(float)Poz(d))
#define Pnt3f3d(f,d) Pnt3dFromXYZ(d,(double)Pox(f),(double)Poy(f), \
								(double)Poz(f)) 

#endif

/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

