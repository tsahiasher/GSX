
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				aff_basic.h
------------------------------------------------------------------------------*/

#ifndef aff_basic_h
#define aff_basic_h

/*----------------------------------------------------------------------------*/
#define NO_TRANS		0
#define SCA_CODE		01
#define TRA_CODE		02
#define ROT_CODE		04

#define SCA_TRA_CODE		03
#define SCA_ROT_CODE		05
#define TRA_ROT_CODE		06
#define SCA_TRA_ROT_CODE	07

/*----------------------------------------------------------------------------*/
typedef enum {
    Aff3noneT=-1,
    TraXT=0, TraYT=1, TraZT=2,
    RotXT=3, RotYT=4, RotZT=5,
    ScaXT=6, ScaYT=7, ScaZT=8
        /* the numbering is for Aff3ToAxisT() */
} Aff3T;


#define Aff3ToOp(tt)   ((tt)/3)
#define Aff3ToAxis(tt) ((tt)%3)
#define Aff3IsNone(tt) ((tt) < TraXT || (tt) > ScaZT)
#define Aff3IsTra(tt)  ((tt) >= TraXT && (tt) <= TraZT)
#define Aff3IsRot(tt)  ((tt) >= RotXT && (tt) <= RotZT)
#define Aff3IsSca(tt)  ((tt) >= ScaXT && (tt) <= ScaZT)

#endif
/*----------------------------------------------------------------------------
				E O F					
------------------------------------------------------------------------------*/

