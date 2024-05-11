#include <stdlib.h>
#include "view.h"
#include "gsxw.h"

#define NO_MODE 0  //darg modes
#define MOVE 1
#define PULL 2
#define ROTATE 3
#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1
#define NONE 0
#define M_PI 3.141

#define STRECH_MIN 0.999


//************************** global vars ***********************************/

static int drag_mode,region_modex,region_modey;
static float start_angle,start_x,start_y;
static World myworld;
static view myview;
extern unsigned int Color;   /* to change color */

//************************** prototype ***********************************/

void draw_rectangle();
void draw_grid();


double get_angle(float x,float y)

/* this function caculates the angle between a given point (x,y) and the
   x axis. it subtracts screen_size/2 to get to the center of the screen
   where (0,0) is positiond. after taking -atan of that it changes the
  angle according to the quarter where the point is loctaed
*/
{
	double angle;

	if ((y==SCREEN_SIZEY/2) || (x==SCREEN_SIZEX/2))
		return(0);

	angle=-atan((y-SCREEN_SIZEY/2)/(x-SCREEN_SIZEX/2));
	if ((x>SCREEN_SIZEX/2) && (y>SCREEN_SIZEY/2))
		angle+=2*M_PI;
	if ((x<SCREEN_SIZEX/2) && (y<SCREEN_SIZEY/2))
		angle+=M_PI;
	if ((x<SCREEN_SIZEX/2) && (y>SCREEN_SIZEY/2))
		angle+=M_PI;

	return (angle);
}

void cb_drag (GEvent e)
{
/*The dragging is handeld like this:
  when the user presses the left mouse button the transform matrix is saved
  into start_transform. every change in mouse pos resets transform and multiply
  it by the new movment.*/


	double move_x,move_y,angle;

	move_x=(GEventX(e)-start_x);  //movement from start
	move_y=(GEventY(e)-start_y);

	if (drag_mode!=NO_MODE)
	{
		GClear();
		draw_rectangle();

	}



	switch (drag_mode)
	{
		case MOVE:
		myview.DragCenter(move_x/(SCREEN_SIZEX/2),move_y/(SCREEN_SIZEY/2));
		break;

		case PULL:
			move_x/=WORLD_METER;
			move_y/=WORLD_METER;
		if (!(1+move_x)) move_x = -STRECH_MIN;
		if (!(1+move_y)) move_y = -STRECH_MIN;

		myview.DragPull(1+move_x*region_modex,1+move_y*region_modey);
		break;

		  case ROTATE:
			angle=get_angle(GEventX(e),GEventY(e));
		angle=start_angle-angle;
		myview.DragRotate(angle*180/M_PI);

		break;
	}
}

int calc_region (float start_x,float start_y)
  //change drag_mode according to region
{
	static int sx=SCREEN_SIZEX/3,sy=SCREEN_SIZEY/3,ex=SCREEN_SIZEX/3*2,ey=SCREEN_SIZEY/3*2;

	if ((start_x>SCREEN_SIZEX-MINX) || (start_x<MINX) || (start_y<MINY)
		|| (start_y>SCREEN_SIZEY-MINY)) //out of rectangle
	{
		draw_grid();
		drag_mode=NO_MODE;
		return (TRUE);
	}

	if( (start_x>sx+10) && (start_y>sy+10)
	  &&  (start_x<ex-10) && (start_y<ey-10))  //reg 5
	{
		drag_mode=MOVE;
		return (TRUE);
	}

	if((start_x>sx+10) && (start_x<ex-10) && (start_y<sy-10)) //reg 2
	{
		drag_mode=PULL;
		region_modex=NONE;
		region_modey=UP;  // that mean up will streach
		return (TRUE);
	}

	if ((start_x>sx+10) && (start_x<ex-10) && (start_y>ey+10)) //reg 8
	{
		drag_mode=PULL;
		region_modex=NONE;
		region_modey=DOWN;
		return (TRUE);
	}

	if ((start_x<sx-10) && (start_y>sy+10) && (start_y<ey-10)) //reg 4
	{
		drag_mode=PULL;
		region_modex=LEFT;
			region_modey=NONE;
			return (TRUE);
	}

	if ((start_x>ex+10) && (start_y>sy+10) && (start_y<ey-10)) //reg 6
		{
		drag_mode=PULL;
		region_modex=RIGHT;
			region_modey=NONE;
			return (TRUE);
	}

	if(((start_x<sx-10) && (start_y<sy-10)) || //reg 1
		  ((start_x>ex+10) && (start_y<sy-10)) ||  //reg3
	  ((start_x<sx-10) && (start_y>ey+10)) ||  //reg 7
	  ((start_x>ex+10) && (start_y>ey+10))) //reg 9
	{
		 drag_mode=ROTATE;
		 return (TRUE);
		}
	return (FALSE);
}

void start_move(GEvent e)
{
	static int sx=SCREEN_SIZEX/3,sy=SCREEN_SIZEY/3,ex=SCREEN_SIZEX/3*2,ey=SCREEN_SIZEY/3*2;

	start_x=GEventX(e);
	start_y=GEventY(e);

	myview.DragStart();
	start_angle=get_angle(start_x,start_y);

		calc_region (start_x,start_y);  //change drag_mode according to region

}


void end_drag (GEvent e)
{
	drag_mode=NO_MODE;
}

void cb_refresh()
{
	GClear();
	draw_rectangle();
	myview.BackToStart();
}


void cb_quit (GEvent e)
{
	GCloseWindow();
	exit(0);
}

void draw_grid()
{
	int sx=SCREEN_SIZEX/3,sy=SCREEN_SIZEY/3,ex=SCREEN_SIZEX/3*2,ey=SCREEN_SIZEY/3*2;

	GSetForeground (FORE_RED);
	GLine((int)sx,0,(int)sx,SCREEN_SIZEY);
	GLine((int)ex,0,(int)ex,SCREEN_SIZEY);
	GLine(0,(int)ey,SCREEN_SIZEX,(int)ey);
	GLine(0,(int)sy,SCREEN_SIZEX,(int)sy);
}

void cb_grid(GEvent e)
{
	if (e->key == 'g')
		   draw_grid();
	else
		if (e->key == 'r')
			cb_refresh();
}


void draw_rectangle()
{
	GSetForeground (FORE_BLUE);
	GLine(MINX,MINY,SCREEN_SIZEX-MINX,MINY);
	GLine(SCREEN_SIZEX-MINX,MINY,SCREEN_SIZEX-MINX,SCREEN_SIZEY-MINY);
	GLine(SCREEN_SIZEX-MINX,SCREEN_SIZEY-MINY,MINX,SCREEN_SIZEY-MINY);
	GLine(MINX,SCREEN_SIZEY-MINY,MINX,MINY);
}

void redraw(GEvent e)
{
	GClear();
	draw_rectangle();
	myview.Display();
}

int Gmain(int argc, char *argv[])
{
	FILE  *fin;


	if ((fin=fopen("square.scn","r"))==NULL)   /*open to read */
	{
			fprintf(stderr,"Error: in opening file.\n");
			exit(1);
	}

	myview.GetData(fin);
	myworld.GetData(fin);
		fclose(fin);
	myview.GetWorld(myworld);
	GWindow(0,0,SCREEN_SIZEX ,SCREEN_SIZEY ,"view");
	draw_rectangle();
	myview.Display();
	GFuncSet(start_move, GButton1Press);
	GFuncSet(cb_drag, GDrag);
	GFuncSet(cb_grid, GKey);
	GFuncSet(cb_quit, GButton3Press);
	GFuncSet(end_drag,GButton1Release);
	GFuncSet(redraw,GRedraw);
	GMainLoop();
	myview.Dispose();
	myworld.Dispose();
	return (0);
}

/* end of file */
