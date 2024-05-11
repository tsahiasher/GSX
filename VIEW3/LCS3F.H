
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

!!!sb in lcs_basic.h
typedef enum { TraT=0, RotT=1, ScaT=2 } AffT;
#define LcsIJ(m,i,j)              ((m)->el[(i)][(j)])
#define LcsEntry(m,i,j)           LcsIJ(m,i,j)


void Lcs3fPntExpress
void Lcs3fDirExpress
void Lcs3fVecExpress

void Lcs3fFromAff (Lcs3f lcs, Aff3f a, Lcs3f res);

void Lcs3fFromSca (Lcs3f lcs, Vec3f v, Lcs3f res);

/* these utilities will NOT be given at the moment.
 to use them, create an Aff and convert.
void Lcs3fScaCompose (Lcs3f lcs, Vec3f v, Lcs3f res);
 ...
 */

+ local versions of Compose funcs:

void  Lcs3fScaComposeLocal (Aff3f a1, Vec3f v, Aff3f res);
