#include "view3.h"
#include "world.h"
#include "gsxw.h"
#include <stdlib.h>
#include <string.h>

#define ROT 1
#define ZOOM 2
#define MOVE 3

  // ************************** global varibels ***************************

View current_view,lastview;
World world;
Pnt3f start,end;
int state;


void cb_key (GEvent e)
{
	switch (e->key)
	{
		case '+':  current_view.Zoom(1);
				  break;
		case '-': current_view.Zoom(-1);
				  break;
		case '4': current_view.Move(0.2,0);
				  break;
		case '6': current_view.Move(-0.2,0);
				  break;
		case '8': current_view.Move(0,0.2);
				  break;
		case '2': current_view.Move(0,-0.2);
				  break;
		case 'r': current_view.BackToStart();
				  break;
		case 'p': break;
		case 'l': break;
		case 's': FILE * ff;
				  ff=fopen("view_temp_file","wt");
				  current_view.Write(ff);
				  fclose(ff);
				  break;
		case 'q': GCloseWindow();
				  exit(0);

		default : return;
	}
   GClear();
   world.Display(&current_view);

}

void redsplay(GEvent e)
{
   GClear();
   world.Display(&current_view);

}

void start_drag(GEvent e)
{
	Pnt3fX(start)=e->x-SCREEN_OFFSET;
	Pnt3fY(start)=e->y-SCREEN_OFFSET;
	if(Pnt3fX(start)<0)Pnt3fX(end)=0; 
	if(Pnt3fY(start)<0)Pnt3fY(start)=0; 
    lastview.GetView(&current_view);
}

void start_zoom (GEvent e)
{
    state=ZOOM;
    start_drag(e);
}

void start_move (GEvent e)
{
    state=MOVE;
    start_drag(e);
}

void start_rot (GEvent e)
{
    state=ROT;
    start_drag(e);
}

void in_rot (GEvent e)
{
	Pnt3fX(end)=e->x-SCREEN_OFFSET;
	Pnt3fY(end)=e->y-SCREEN_OFFSET;
	if(Pnt3fX(end)<0)Pnt3fX(end)=0; 
	if(Pnt3fY(end)<0)Pnt3fY(end)=0; 
	if ((Pnt3fX(start)==Pnt3fX(end)) && (Pnt3fY(start)==Pnt3fY(end)))
		return;
	current_view.GetView(&lastview);
	current_view.ArcBallRot(start ,end);
	GClear();
	world.Display(&current_view);
}

void in_zoom (GEvent e)
{
	Pnt3fX(end)=e->x;
	Pnt3fY(end)=e->y;
	if (Pnt3fY(start)==Pnt3fY(end))
		return;
	current_view.GetView(&lastview);
	float asize=(Poy(end)-Poy(start))/(current_view.Yres()) * 45;
	current_view.Zoom(asize);
	GClear();
	world.Display(&current_view);
	Pnt3fX(start)=e->x;
	Pnt3fY(start)=e->y;

}

void in_move (GEvent e)
{
	Pnt3fX(end)=e->x;
	Pnt3fY(end)=e->y;
	if ((Pnt3fX(start)==Pnt3fX(end)) && (Pnt3fY(start)==Pnt3fY(end)))
		return;
	current_view.GetView(&lastview);
	float xsize=(Pox(end)-Pox(start))/(current_view.Xres()/2);
	float ysize=(Poy(end)-Poy(start))/(current_view.Yres()/2);
	current_view.Move(-xsize,ysize);
	GClear();
	world.Display(&current_view);
}

void in_drag (GEvent e)
{
    switch (state)
	{
	  case ROT:in_rot(e);
              break;
	   case ZOOM:in_zoom(e);
              break;
	   case MOVE:in_move(e);
	      break;
   }
}


int Gmain(int argc, char *argv[])
{
	FILE 	*fin;
	int 	mesh_file=2;
	int 	view_file=4;

        if (argc==2)
	{
		if (!(fin=fopen(argv[1],"r")))
		{
			fprintf(stderr,"Cant Open file %s.\n",argv[1]);
			exit(1);
		}
		world.GetData(fin);
		world.BoundingBox(&current_view);
		fclose(fin);
	}
	else
		if (argc==4)
		{
			if (!strcmp(argv[1],"-v"))
			{
				mesh_file=3;
				view_file=2;
			}
			else
				if (!strcmp(argv[2],"-v"))
				{
					mesh_file=1;
					view_file=3;
				}
				else
				{
					fprintf(stderr,"Usage: view3 <mesh filename> <-v view filename>\n");
					exit(1);
				}
			if (!(fin=fopen(argv[mesh_file],"r")))
			{
				fprintf(stderr,"Cant Open file %s.\n",argv[mesh_file]);
				exit(1);
			}
			world.GetData(fin);
			fclose(fin);
			if (!(fin=fopen(argv[view_file],"r")))
			{
				fprintf(stderr,"Cant Open file %s.\n",argv[view_file]);
				exit(1);
			}
			current_view.GetData(fin);
			fclose(fin);
		}
		else
		{
			fprintf(stderr,"Usage: view3 <mesh filename> <-v view filename>\n");
			exit(1);
		}

	start=Pnt3fCreate();
	end=Pnt3fCreate();

	GWindow(0,0, current_view.Xres()+2*SCREEN_OFFSET,current_view.Yres()+2*SCREEN_OFFSET,"view 3");
	world.Display(&current_view);

	GFuncSet(start_rot,GButton1Press);
	GFuncSet(start_zoom, GButton2Press);
	GFuncSet(start_move, GButton3Press);
	GFuncSet(cb_key, GKey);
	GFuncSet(in_drag,GDrag);
	GFuncSet(redsplay,GRedraw);
	GMainLoop();
	world.Dispose();

return 0;
}













