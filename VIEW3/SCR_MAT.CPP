#include "scr_mat.h"
#include <math.h>
#include "dir3f.h"

screen_mat::screen_mat()
{
	world_to_view=Aff3fCreate();
	normelize_mat=Aff3fCreate();
}

screen_mat::~screen_mat()
{
	Aff3fFree(world_to_view);
	Aff3fFree(normelize_mat);
}

void screen_mat::calculate(Pnt3f eye,Pnt3f coi,Vec3f upvec, float afovx, float afovy,
											int xres, int yres)
{
	Aff3f temp_mat;
	Vec3f x,y,z,normal,tempv;
	Dir3f normal_x,normal_y,normal_z;

	Pnt3f t=Pnt3fCreate();
	x=Vec3fCreate();
	y=Vec3fCreate();
	z=Vec3fCreate();
	a_fovx=afovx;
	a_fovy=afovy;
	normal=Vec3fCreateFromXYZ(0.01,0.01,0.01);
	Aff3fFromSca(world_to_view,normal);
	temp_mat=Aff3fCreate();
	Aff3fIJ(temp_mat,0,3)=-Pnt3fX(eye)/100;     //move by -eye eye
	Aff3fIJ(temp_mat,1,3)=-Pnt3fY(eye)/100;
	Aff3fIJ(temp_mat,2,3)=-Pnt3fZ(eye)/100;
	Aff3fComposeS (world_to_view, temp_mat);
	normal_x=Dir3fCreate();                   //create x y z of lcs
	normal_y=Dir3fCreate();

	z=Pnt3fSub (coi, eye, z);
	normal_z=Dir3fCreateFromVec3f(z);

	z= Vec3fFromDir3f(z,normal_z);
	x=Vec3fCross (upvec, z, x);              // normal up vector !!!!!!!!!!!!
	normal_x=Dir3fFromVec3f(normal_x,x);
	x=Vec3fFromDir3f(x,normal_x);
	y=Vec3fCross (z ,x ,y);

	normal_y=Dir3fFromVec3f(normal_y,y);
	normal_z=Dir3fFromVec3f(normal_z,z);

	temp_mat=Aff3fInit(temp_mat);
	Aff3fIJ(temp_mat,0,0)=Dir3fX(normal_x);      // invert it
	Aff3fIJ(temp_mat,0,1)=Dir3fY(normal_x);
	Aff3fIJ(temp_mat,0,2)=Dir3fZ(normal_x);
	Aff3fIJ(temp_mat,1,0)=Dir3fX(normal_y);
	Aff3fIJ(temp_mat,1,1)=Dir3fY(normal_y);
	Aff3fIJ(temp_mat,1,2)=Dir3fZ(normal_y);
	Aff3fIJ(temp_mat,2,0)=Dir3fX(normal_z);
	Aff3fIJ(temp_mat,2,1)=Dir3fY(normal_z);
	Aff3fIJ(temp_mat,2,2)=Dir3fZ(normal_z);
	Aff3fComposeS (world_to_view, temp_mat);    // multiply by xyz of lcs

	tempv=Vec3fCreateFromXYZ(xres/2,-yres/2,1);
	normelize_mat=Aff3fFromSca(normelize_mat,tempv);
	tempv=Vec3fFromXYZ(tempv,xres/2,yres/2,1);
	temp_mat=Aff3fFromTra(temp_mat,tempv);
	Aff3fComposeS (normelize_mat,temp_mat);    // multiply by xyz of lcs
	Aff3fCode(normelize_mat)=4; // ROT_CODE
	Aff3fCode(world_to_view)=4; // ROT_CODE
	Aff3fFree(temp_mat);
	Vec3fFree(tempv);
	Vec3fFree(x);
	Vec3fFree(y);
	Vec3fFree(z);
}

void screen_mat::pnt_to_view(Pnt3f point, tpnt3f view_point)
{
	Aff3fPntApply (world_to_view, point, view_point.OutData());
};


void screen_mat::pnt_to_scr(Pnt3f point)
{

    Pnt3f tmp_point;

    tmp_point=Pnt3fCreateFromXYZ(
	      ( Pnt3fX(point) * (1/tan(a_fovx))  ) /(Pnt3fZ(point))
	    , ( Pnt3fY(point) * (1/( tan(a_fovy)) ) ) /(Pnt3fZ(point))
	    , 1);
    Aff3fPntApply(normelize_mat,tmp_point,point);

    Pnt3fDelete(tmp_point);
}
/* END OF FILE */












