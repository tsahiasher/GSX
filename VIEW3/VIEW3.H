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

//#include "world.hh"
#include "scr_mat.h"

#define WORLD_METER 100.0


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

class View;

typedef View *Viewptr;

class View
{
private:

	  screen_matptr view_to_screen;
	  Pnt3f eye;
	  Pnt3f coi;
	  Vec3f upvec;
	  float yfov;
	  float xfov;
	  int   xres;
	  int   yres;

	  Pnt3f s_eye;
	  Pnt3f s_coi;
	  Vec3f s_upvec;
	  float s_yfov;
	  float s_xfov;

	  double SizeToMove(Vec3f v);
	  Pnt3f Scr_to_world(Pnt3f s_pnt);
	  //Pnt3f Scr_to_world(Pnt3f s_pnt,Pnt3f temp_pnt,Pnt3f v_coi);
	  void InitView3(Pnt3f eye, Pnt3f coi, Vec3f upvec, float xfov,float yfov);

public:
	  View()
	  {
			eye=Pnt3fCreate();
			coi=Pnt3fCreate();
			s_eye=Pnt3fCreate();
			s_coi=Pnt3fCreate();
			upvec=Vec3fCreate();
			s_upvec=Vec3fCreate();
			view_to_screen = new( screen_matrec );
	  }

	  ~View();
      void GetView(Viewptr other)
{
	eye=Pnt3fCopy(other->EyeOut(),eye);
	coi=Pnt3fCopy(other->CoiOut(),coi);
	upvec=Vec3fCopy(other->UpOut(),upvec);
    view_to_screen->GetScr(other->OutMat());
}


	  void EyeSet(Pnt3f neye){eye=Pnt3fCopy (eye, neye);};
	  Pnt3f EyeOut(){return eye;};
	  void CoiSet(Pnt3f ncoi){coi=Pnt3fCopy (coi, ncoi);};
	  Pnt3f CoiOut(){return coi;};
	  void UpSet(Vec3f nupvec){upvec=Vec3fCopy (upvec, nupvec);};
	  Vec3f UpOut(){return upvec;};
      screen_matptr OutMat(){return view_to_screen;}
	  void YFovSet(float nyfov){yfov=nyfov;};
	  void XFovSet(float nxfov){xfov=nxfov;};
	  void XResSet(int nxres){xres=nxres;};
	  void YResSet(int nyres){yres=nyres;};
	  int Xres(){return xres;}
	  int Yres(){return yres;}
	  void Move(float xdirection,float ydirection);
	  void Zoom(float direction); // -1 to 1

/*	  float *OutYFov() {return(&yfov);};
	  float *OutXFov() {return(&xfov);};
  */
	  void Write(FILE *fout);
			// function to accses data
	  screen_matptr screen_mat(void);
				// function for input
	  void GetData(FILE *fin);
	  void InitCurView3(Pnt3f aeye, Pnt3f acoi, Vec3f aupvec, float axfov,
									float ayfov, int axres, int ayres);
				// function for output
      void ArcBallRot(Pnt3f start ,Pnt3f end);

			 // operiton on a view
	  void BackToStart();

};

int ReadString(FILE *input,char *str);

#endif
