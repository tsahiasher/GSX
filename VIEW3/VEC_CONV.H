
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				vec_conversions.h
 Purpose : conversions between vectors differentiated by coordinate type.

 Usage   : include the relevant .h vec file before this one.
------------------------------------------------------------------------------*/

#ifndef vec_conversions_h
#define vec_conversions_h

/*----------------------------------------------------------------------------*/
/* Conversions */

/* Vec2, short <-> float */
#define Vec2s2f(s,f) Vec2fFromXY(f,(float)Vex(s),(float)Vey(s))	
#define Vec2f2s(f,s) Vec2sFromXY(s,(short)Vex(f),(short)Vey(f))

/* Vec2, double <-> float */
#define Vec2d2f(d,f) Vec2fFromXY(f,(float)Vex(d),(float)Vey(d))	
#define Vec2f2d(f,d) Vec2dFromXY(d,(double)Vex(f),(double)Vey(f))

/* Vec3, short <-> float */
#define Vec3s3f(s,f) Vec3fFromXYZ(f,(float)Vex(s),(float)Vey(s),(float)Vez(s))
#define Vec3f3s(f,s) Vec3sFromXYZ(s,(short)Vex(f),(short)Vey(f),(short)Vez(f)) 

/* Vec3, double <-> float */
#define Vec3d3f(d,f) Vec3fFromXYZ(f,(float)Vex(d),(float)Vey(d),(float)Vez(d))
#define Vec3f3d(f,d) Vec3dFromXYZ(d,(double)Vex(f),(double)Vey(f), \
								(double)Vez(f)) 

#endif
/*----------------------------------------------------------------------------
				E O F					
------------------------------------------------------------------------------*/

