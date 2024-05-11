
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				dir_conversions.h
 Purpose : conversions between unit-length vectors, dirs,
	   differentiated by coordinate type.

 Usage   : include the relevant .h dir file before this one.
------------------------------------------------------------------------------*/

#ifndef dir_conversions_h
#define dir_conversions_h

/*----------------------------------------------------------------------------*/
/* Conversions */

/* Dir2, double <-> float */
#define Dir2d2f(d,f) Dir2fFromXY(f,(float)Dix(d),(float)Diy(d))	
#define Dir2f2d(f,d) Dir2dFromXY(d,(double)Dix(f),(double)Diy(f))

/* Dir3, double <-> float */
#define Dir3d3f(d,f) Dir3fFromXYZ(f,(float)Dix(d),(float)Diy(d),(float)Diz(d))
#define Dir3f3d(f,d) Dir3dFromXYZ(d,(double)Dix(f),(double)Diy(f), \
								(double)Diz(f)) 

#endif
/*----------------------------------------------------------------------------
				E O F					
------------------------------------------------------------------------------*/

