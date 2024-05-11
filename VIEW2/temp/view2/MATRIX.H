/*
  matrix : a module to implement the 3x3 matrix including the operator
           * as used in algebra and the posibility to define matrix
           for the graphic operiton of rotate in angle t strech and move 
  data types : pntf : a point in 2d with data type float , this data type is 
                      declerd here because a matix should know to operate
		      itself on a given point
               matrix : some of the fnction may work if you will change
                        MATRIX_LONG bt some , especily those concernd with
			2d will not work when MATRIX_LONG<>3
*/


#ifndef __MATRIX
#define __MATRIX

#include <math.h>

#ifndef __PNT2F_
#define __PNT2F_

typedef struct {
	float x, y;
} Pnt2fRec, *Pnt2f;


#define Pnt2fX(pnt)     ((pnt)->x)
#define Pnt2fY(pnt)     ((pnt)->y)
#endif

#define MATRIX_LONG 3

class matrix ;
typedef matrix *matrixptr;

typedef float matrixdata[MATRIX_LONG][MATRIX_LONG] ;

class matrix
{
private:
   matrixdata data ;
public:
   matrix(){};
   ~matrix(){};

          // interface to the data
   float OutData(int i,int j) {return(data[i-1][j-1]);};
   void GetData(int i,int j,float num){data[i-1][j-1]=num;};

         // initaling matrix to a desierd graphic 2d fnction  
   void Init_I();
   void InitScale(double xscale,double yscale);
   void InitRotate(double angle);
   void InitMove(double movex,double movey); 

         // operate matrix on a point (like multypling a vector (x,y,1)
   void TransPoint(Pnt2f apoint);

        // matrix operators   
   matrix operator*(matrix & other);
   matrix operator=(matrix & other);
 

};

#endif



