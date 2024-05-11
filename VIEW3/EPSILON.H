
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                epsilon.h
 Purpose : Header file for comparison tolerances (epsilons)
------------------------------------------------------------------------------*/

#ifndef epsilon_h
#define epsilon_h

typedef enum { Acc3T, Acc5T, Acc7T, Acc9T } AccuracyT; 

extern double epsilon;		                      /* default value 1.0E-5 */

extern double eps3;						    /* 1.0E-3 */
extern double eps5;		                                    /* 1.0E-5 */
extern double eps7;		                                    /* 1.0E-7 */
extern double eps9;		                                    /* 1.0E-9 */

double set_eps (AccuracyT acc);	      /* sets epsilon, returns previous value */

#endif
/*----------------------------------------------------------------------------
                                E O F
------------------------------------------------------------------------------*/
