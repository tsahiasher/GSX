/*
   view
   in my way of looking a view is a world that thet move rotate and scaling
   where defined on it
   all this transforms are regular (afiniuot) 
   once we now this parameters we can the calculte how would the world polygons
   would look in the view coordinates and : forget about the transforms since
   the view data contain all the points of the world after the transformaition
   for doing transforms on the view the matrix "transform" contain all the
   transforms which where made on the inital view , there for to show the view
   on the screen all you need is to operate the transformaiton on the inital 
   view (combine with the moving to the screen 
   there for view is implementd as a world (a list of polygon) + matrix
*/

#ifndef __VIEW_
#define __VIEW_

#include "world.h"
#include "matrix.h"

#define WORLD_METER 100.0


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

class view :public World
{
private:
	  matrix transform;
	  void CalculateMatrix(Pnt2f center,float angale_from_x,float witdh,float hight);

public:
	  view()   {};
	  ~view()  {};
	        // function to accses data
	  matrixptr transform_mat() {return (&transform);};
                // function for input
	  void GetData(FILE *fin);
	  void GetWorld(World aworld);
				// function for output
	  void Display();
			 // operiton on a view
	  void BackToStart();
	  void Rotate(float angle);
	  void Pull(float directionx,float directiony);
	  void MoveCenter(float directionx,float directiony);

	  void DragStart(void);
	  void DragCenter(float directionx,float directiony);
	  void DragPull(float directionx,float directiony);
	  void DragRotate(float angle);

};

#endif
