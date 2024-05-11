
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				aff3f_priv.h
------------------------------------------------------------------------------*/
#ifndef aff3f_priv_h
#define aff3f_priv_h

#include "aff3f.t"
#include "vec3f.t"
#include "vec4f.t"

void Aff3fTranspose (Aff3f a, Aff3f res);
void Aff3fTransposeS (Aff3f a);

void   	Aff3fRowToVec4f (Aff3f a, int i, Vec4f v);
void   	Aff3fColToVec3f (Aff3f a, int i, Vec3f v);

void 	Aff3fRowSet (Aff3f aff, int i, float a, float b, float c, float d);
void 	Aff3fColSet (Aff3f aff, int i, float a, float b, float c);

#endif
/*----------------------------------------------------------------------------
			       E O F
------------------------------------------------------------------------------*/


