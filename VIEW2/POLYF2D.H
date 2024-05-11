/*
  polyf2d : a polygon 2D with data type float. the polygon knows to
            operate a matrix on his self(by operating it on any point)
            , to get another polygon as an input and to do both 
*/

#ifndef __POLYF2D_
#define __POLYF2D_

#include <stdio.h>
#include "malloc.h"
#include "matrix.h"
#include "clip.h"

#define MAX_POINTS 50

class Poly2f;
typedef Poly2f *Poly2fptr;

class Poly2f
{
private:
	Pnt2f pnts[MAX_POINTS];
	int Lines_Num;
	float OutX(int i){return Pnt2fX(pnts[i]);}
	float OutY(int i){return Pnt2fY(pnts[i]);}
public:

	Poly2f(){};
   ~Poly2f(){};
		// function to acces data types
   Pnt2f OutPoint(int pointnum){return (pnts[pointnum]);};
   int LinesNum(){return (Lines_Num);};
			// i/o : read data from file (in meters) and paint on screen
   void Read(FILE *fin);
   void Paint();
		// changing data using matrix + geting a polygon for input
   void GetPolyWithMatrix(Poly2fptr other,matrix transform);
   void GetPoly(Poly2fptr other);
   void GetMatrix(matrix transform);


};
     // general input function 
int ReadString(FILE *input,char *str);

#endif



