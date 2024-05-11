#include "view.h"

static matrix start_transform;


void view::CalculateMatrix(Pnt2f center,double angale_from_x,double width,double hight)
// a function to calculate the matrix from the inital parameters
// this function does also the nirmol  
{
    matrix temp;
        //move -x -y
    transform.InitMove(-Pnt2fX(center),-Pnt2fY(center));


		//screatch 1/width,1/hight
	temp.InitScale(1/width,1/hight);
	transform=transform*temp;

	   //rotate -alfa
	temp.InitRotate(-angale_from_x);
	transform=transform*temp;

		//normalize so that 1 come for  one world meter
	temp.InitScale(1/WORLD_METER,1/ WORLD_METER);
	transform=transform*temp;

}

void view::GetWorld(World aworld)
	  // copy world polygon to normlize view list
{
	  PolyList2f world_list;
	  Poly2fptr helppoly;
	  world_list=aworld.OutPolyList();
	  GetList(NULL);
	  while(world_list)
		  // for each polygon : alocate place & convert
	  {
		 helppoly=new(Poly2f);
		 helppoly->GetPolyWithMatrix(world_list->current,transform);
		 AddPoligon(helppoly);
		 world_list=world_list->next;
	  }
	  transform.Init_I();
}


void view::GetData(FILE *fin)
{
		Pnt2f center;

		center=(Pnt2f)malloc(sizeof(Pnt2fRec));
		double angale_from_x,width,height;
			ReadString(fin,"center");
		fscanf (fin,"%f %f",&Pnt2fX(center),&Pnt2fY(center));
		ReadString(fin,"angle");
		fscanf (fin,"%f",&angale_from_x);
			ReadString(fin,"width");
		fscanf (fin,"%f",&width);
		ReadString(fin,"height");
		fscanf (fin,"%f",&height);

		CalculateMatrix(center,angale_from_x,width,height);
		free(center);
}

void  view::Display()
/*
	 the matrix normal_to_screen is initilize (once) to the transformaition
	 from an normlized view to the screen
	 the matrix that should be preformd is R=T*normal_to_screen where T is
	 the transformaition so far
	 after calculting r i operat R on every polygon and display it
*/

{
	static firstime=TRUE;
	static matrix normal_to_screen;
	static matrix move_to_screen_matrix;

	if(firstime)
	{
		normal_to_screen.InitScale(SCREEN_SIZEX/2,SCREEN_SIZEY/2);
		move_to_screen_matrix.InitMove((SCREEN_SIZEX)/2,(SCREEN_SIZEY)/2);
		normal_to_screen=normal_to_screen*move_to_screen_matrix;
		firstime=FALSE;
	}

	matrix result;
	result.Init_I();
	result=result*transform;
	result=result*normal_to_screen;
	PolyList2f helpptr=OutPolyList();
	Poly2fptr  current;
	while(helpptr)
	{
		current=new Poly2f;
		current->GetPolyWithMatrix(helpptr->current,result);
		current->Paint();
		helpptr=helpptr->next;
		delete current;
	}
}

void view::Rotate(double angle)
{
	matrix round;
	round.InitRotate(angle);
	transform=transform*round;
	Display();
};

void view::Pull(double directionx,double directiony)
{
	matrix M;
	M.InitScale(directionx,directiony);
	transform=transform*M;
	Display();
};

void view::MoveCenter(double directionx,double directiony)
{
	matrix move;
	move.InitMove(directionx, directiony);
	transform=transform*move;
	Display();
}

void view::DragStart(void)
     // keep the situation for start drag
{
	start_transform=transform;

}

void view::DragCenter(double directionx,double directiony)
{
    transform=start_transform;
    MoveCenter(directionx,directiony);
}

void view::DragRotate(double angle)
{
    transform=start_transform;
    Rotate(angle);

}

void view::DragPull(double directionx,double directiony)
{
    transform=start_transform;
    Pull(directionx,directiony);
}

void view::BackToStart()
{
	transform.Init_I();
	Display();
};



/* end of file */







































