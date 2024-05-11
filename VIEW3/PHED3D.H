/*
  phedf2d : a phedron 2D with data type float. the phedron knows to
			operate a matrix on his self(by operating it on any point)
			, to get another phedron as an input and to do both
*/

#ifndef __PHEDF3D_
#define __PHEDF3D_

#define INFINIT 400000
#define SCREEN_OFFSET 10
#include <stdio.h>
#include "malloc.h"
// #include "matrix.hh"

#include "scr_mat.h"
#include "table.h"
#include "tring.h"
#include "square.h"
#include "tpnt3f.h"
#include "aff3f.h"

// #define MAX_POINTS 50

class Phed3f;
typedef Phed3f *Phed3fptr;

class Phed3f
{
private:
	tableptr vertex;
	tableptr trings;
	tableptr squares;
	Pnt3f OutP(int i)
	{
		tpnt3fptr p=(tpnt3fptr)vertex->Item(i);
		return (p->OutData());
	}

public:

   Phed3f()
   {
		vertex=new(table);
		trings=new(table);
		squares=new(table);
   };
   ~Phed3f()
   {
		delete(vertex);
		delete(trings);
		delete(squares);
   };
		// function to acces data types
	void GetVertex(tableptr nv){vertex=nv;}
	void GetTrings(tableptr nt){trings=nt;}
	void GetSquares(tableptr ns){squares=ns;}
/*   Pnt3f OutPoly(int polynum);
   int TriangleNum(){return (triangle_num);};
   int SqrNum(){return (sqr_num);};
*/
			// i/o : read data from file (in meters) and paint on screen
   void Read(FILE *fin);
   void Write(FILE *fin);
   void Paint(screen_matptr scrparam);
		// changing data using matrix + geting a phergon for input
   Phed3fptr Phed3f::Dup();
   void GetMatrix(Aff3f transform);
   void relese();
   Pnt3f MaxPoint();
   Pnt3f MinPoint();

};
	 // general input function
#endif



