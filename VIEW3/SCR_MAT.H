#ifndef __scr_mat
#define __scr_mat

#include <math.h>
#include "aff3f.h"
#include "vec3f.h"

#include "tpnt3f.h"

class screen_mat;
typedef screen_mat *screen_matptr;
typedef screen_mat screen_matrec;

class screen_mat
{
private:
		Aff3f world_to_view;
		Aff3f normelize_mat;
		float a_fovx;
		float a_fovy;

public:
	   screen_mat();
	   ~screen_mat();

		Aff3f Outworld_to_view(){return world_to_view;}
		Aff3f Outnormelize_mat(){return normelize_mat;}
		float Outa_fovx(){return a_fovx;}
		float Outa_fovy(){return a_fovy;}
        void GetScr(screen_matptr mat)
{

    world_to_view=Aff3fCopy(mat->Outworld_to_view(),world_to_view);
    normelize_mat=Aff3fCopy(mat->Outnormelize_mat(),normelize_mat);
    a_fovx=mat->Outa_fovx();
    a_fovy=mat->Outa_fovy();
}

	   void calculate(Pnt3f eye,Pnt3f coi,Vec3f upvec, float afovx, float afovy,
											int xres, int yres);

       void pnt_to_scr(Pnt3f point);
       void pnt_to_view(Pnt3f point, tpnt3f view_point);

       Aff3f Out_norm_mat(){return normelize_mat;};
       Aff3f Out_view_mat(){return world_to_view;};
};

#endif

