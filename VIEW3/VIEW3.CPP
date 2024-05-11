#include <stdlib.h>
#include <string.h>

#include "view3.h"
#include "dir3f.h"
#include "epsilon.h"

#define MINFOV 0.1    // 1 degree in rad
#define MAXFOV 1.56   // 179 degree in rad

double SizeToMove(Vec3f v);

inline double sqr(double a){return a*a;};

void Error_Exit(char messege[])
{
	 fprintf(stderr,"Error : %s \n",messege);
	 exit(1);

}

void View::GetData(FILE *fin)
{
		Dir3f	temp;

		ReadString(fin,"eye");
		int succes=Pnt3fRead (eye,fin);
		if (succes==0) Error_Exit("can not read eye ");

		ReadString(fin,"coi");
		succes=Pnt3fRead (coi,fin);
		if (!succes) Error_Exit("can not read coi ");
		if ((Pox(eye)==Pox(coi))&&(Poy(eye)==Poy(coi))&&(Poz(eye)==Poz(coi)) )
		Error_Exit("eye equale to coi cant display ");
		ReadString(fin,"up");
		succes=Vec3fRead (upvec,fin);
		if (!succes) Error_Exit("can not read up vec");
		ReadString(fin,"xfov");
		fscanf (fin,"%f",&xfov);
		ReadString(fin,"yfov");
		fscanf (fin,"%f",&yfov);
		if ((xfov==0)||(yfov==0)) Error_Exit("dont now how to show in 0 degree");
		xfov=DegreeToRadian (xfov)/2;
		yfov=DegreeToRadian (yfov)/2;
		ReadString(fin,"xres");
		fscanf (fin,"%d",&xres);
		ReadString(fin,"yres");
		fscanf (fin,"%d",&yres);

		temp=Dir3fCreateFromVec3f (upvec);
		upvec=Vec3fFromDir3f (upvec,temp);
		Dir3fDelete (temp);

		InitView3(eye, coi, upvec, xfov, yfov);
}

void View::InitView3(Pnt3f eye, Pnt3f coi, Vec3f upvec, float xfov,float yfov)
{
	s_eye=Pnt3fCopy (eye,s_eye);
	s_coi=Pnt3fCopy (coi,s_coi);
	s_upvec=Vec3fCopy (upvec,s_upvec);
	s_xfov=xfov;
	s_yfov=yfov;

}

void View::InitCurView3(Pnt3f aeye, Pnt3f acoi, Vec3f aupvec, float axfov,
									float ayfov, int axres, int ayres)
{
	Dir3f	temp;

	eye=aeye;
	coi=acoi;
	temp=Dir3fCreateFromVec3f (aupvec);
	upvec=Vec3fFromDir3f (upvec,temp);
	Dir3fDelete (temp);
	Vec3fDelete (aupvec);
	xfov=axfov;
	yfov=ayfov;
	xres=axres;
	yres=ayres;
	InitView3(eye,coi,upvec,xfov,yfov);
}



View::~View()
{
	Pnt3fFree(eye);
	Pnt3fFree(coi);
	Pnt3fFree(s_eye);
	Pnt3fFree(s_coi);
	Vec3fFree(upvec);
	Vec3fFree(s_upvec);
	free(view_to_screen);
}

void View::BackToStart()
{
	eye=Pnt3fCopy ( s_eye,eye);
	coi=Pnt3fCopy (s_coi,coi);
	upvec=Vec3fCopy ( s_upvec,upvec);
	xfov=s_xfov;
	yfov=s_yfov;
}

screen_matptr View::screen_mat()
{
	(*view_to_screen).calculate(eye,coi,upvec,xfov, yfov, xres, yres);
	return (view_to_screen);
}

int ReadString(FILE *input,char *str)
{
	char temp_str[255];

	fscanf(input,"%s",temp_str);
	if (strcmp(temp_str,str))
	{
		fprintf(stderr,"Errror : %s expected but %s found \n",str,temp_str);
		exit(1);
	}
	return 1;
}

void View::Zoom(float direction)
{
	xfov+=(DegreeToRadian(direction)); 
	yfov+=(DegreeToRadian(direction));

	if ((xfov<MINFOV) || (yfov<MINFOV)) {xfov=MINFOV; yfov=MINFOV;}
	if ((xfov>MAXFOV) || (yfov>MAXFOV)) {xfov=MAXFOV; yfov=MAXFOV;}
}


double View::SizeToMove(Vec3f v)
{
	float big_fov;
	if (xfov>yfov) big_fov=xfov;
	else  big_fov=yfov;
  
	 return (Vec3fLen(v)*tan(big_fov));
}



void View::Move(float xdirection,float ydirection)
{
	Vec3f   zview,xview,yview;

	zview=Vec3fCreate();
	xview=Vec3fCreate();
	yview=Vec3fCreate();

	zview=Pnt3fSub (coi, eye, zview);
	xview=Vec3fCross (upvec, zview, xview);
	yview=Vec3fCross (zview ,xview ,yview);

	Dir3f normal_y=Dir3fCreateFromVec3f(yview);  // normalize
 	Dir3f normal_x=Dir3fCreateFromVec3f(xview);  // normalize
	yview=Vec3fFromDir3f(yview,normal_y);
	xview=Vec3fFromDir3f(xview,normal_x);

	xview=Vec3fScaS (xview, xdirection*SizeToMove(zview));
	yview=Vec3fScaS (yview, ydirection*SizeToMove(zview));

	eye= Pnt3fVec3fAddS(eye,yview); // changing in one centimeter in world
	coi= Pnt3fVec3fAddS(coi,yview);
	eye= Pnt3fVec3fAddS(eye,xview); // changing in one centimeter in world
	coi= Pnt3fVec3fAddS(coi,xview);

	Dir3fDelete(normal_y);
	Vec3fDelete(xview);
	Vec3fDelete(yview);
	Vec3fDelete(zview);

}

Pnt3f View::Scr_to_world(Pnt3f s_pnt)
{
	Pnt3f   w_pnt,temp_pnt,v_eye,v_coi;
	Aff3f   temp_mat;
	Vec3f   z;
	float 	m,big_fov;

	z=Vec3fCreate();
	temp_mat=Aff3fCreate();
	temp_pnt=Pnt3fCreate();
	v_eye=Pnt3fCreate();
	v_coi=Pnt3fCreate();
	w_pnt=Pnt3fDup(s_pnt);


	      // takeing x,y -> (x',y',1) of view
	set_eps (Acc9T);
	Aff3fRotInverse(view_to_screen->Out_norm_mat(),temp_mat);
	set_eps (Acc5T);
	Poz(w_pnt)=1;
	Aff3fPntApply (temp_mat, w_pnt, temp_pnt);
	Aff3fPntApply (view_to_screen->Out_view_mat(), eye, v_eye);
	Aff3fPntApply (view_to_screen->Out_view_mat(), coi, v_coi);
	z=Pnt3fSub (v_coi, v_eye, z);
	double radios=(double)Vec3fLen(z);
	Pnt3fX(temp_pnt)=Pnt3fX(temp_pnt)*tan(xfov)*radios;
	Pnt3fY(temp_pnt)=Pnt3fY(temp_pnt)*tan(yfov)*radios;
	
	if (xfov>yfov)
		big_fov=xfov;
        else
		big_fov=yfov;
	
	radios=radios*tan(big_fov);
    
	double det=radios*radios-sqr((double)fabs(Pnt3fX(temp_pnt)))-sqr((double)fabs(Pnt3fY(temp_pnt)));
	if(det<0)
	{
		if (Pnt3fX(temp_pnt))
		{
			m=(Pnt3fY(temp_pnt)/Pnt3fX(temp_pnt));
			Pnt3fX(temp_pnt)=sqrt(radios*radios/(1+m*m));
			Pnt3fY(temp_pnt)=Pnt3fX(temp_pnt)*m;
		}
		else
		{
			Pnt3fX(temp_pnt)=0;
			Pnt3fY(temp_pnt)=radios;
		}
		Pnt3fZ(temp_pnt)=Pnt3fZ(v_coi);	
	}
	else
		Pnt3fZ(temp_pnt)= Pnt3fZ(v_coi)-sqrt(det);
                
	set_eps (Acc9T);
	Aff3fRotInverse(view_to_screen->Out_view_mat(),temp_mat);
	set_eps (Acc5T);
	Aff3fPntApply (temp_mat, temp_pnt, w_pnt);
	
          // finding the intersaction between the line (x,y,1) and the ball
          // if det<0 there is no intersaction and we calculate to which edge of
		  // the ball to rotate

	Aff3fDelete(temp_mat);
	Pnt3fDelete(temp_pnt);
	Pnt3fDelete(v_coi);
	Pnt3fDelete(v_eye);
	Vec3fDelete(z);
	
	return (w_pnt);
}

void View::ArcBallRot(Pnt3f start ,Pnt3f end)
{
	Vec3f temp_vec=Vec3fCreate();
	Pnt3f world_p1=Pnt3fCreate();
	Pnt3f world_p2=Pnt3fCreate();
	Vec3f vec1=Vec3fCreate();
	Vec3f vec2=Vec3fCreate();

				 // moving point in screen to point in world

	world_p1=Scr_to_world(start);
	world_p2=Scr_to_world(end);
	
	if (Pnt3fPntAreEq(world_p1,world_p2))
	{
		Vec3fDelete(temp_vec);
		Vec3fDelete(vec1);
		Vec3fDelete(vec2);
		Pnt3fDelete(world_p1);
		Pnt3fDelete(world_p2);
		return;
	}
	vec1=Pnt3fSub (world_p1,coi, vec1);
	vec2=Pnt3fSub (world_p2,coi, vec2);
	
	Dir3f norvec1=Dir3fCreateFromVec3f(vec1);
	Dir3f norvec2=Dir3fCreateFromVec3f(vec2);
	vec1=Vec3fFromDir3f(vec1,norvec1);
	vec2=Vec3fFromDir3f(vec2,norvec2);
	temp_vec=Vec3fCross (vec1,vec2,temp_vec);
	Dir3f rotate_axis=Dir3fCreateFromVec3f(temp_vec);
	set_eps (Acc3T);
	double s=Dir3fCos(norvec1,norvec2);
        set_eps (Acc5T);
	if(s<-1) s=-1;
        if(s>1) s=1;
	if(!((s>-1)&&(s<1)))
		s=0;  // Dir3fCos returned an illegal value
        Radian rotate_angle=-(acos (s)*2); // -alfa*2
	Aff3f rot_mat=Aff3fCreateFromDirAngleRot(rotate_axis,rotate_angle);
	
	Pnt3f temp_eye=Pnt3fDup(eye);
	Pox(temp_eye)-=Pox(coi);
	Poy(temp_eye)-=Poy(coi);
	Poz(temp_eye)-=Poz(coi);
	Aff3fPntApply (rot_mat, temp_eye, eye);
	Pox(eye)+=Pox(coi);
	Poy(eye)+=Poy(coi);
	Poz(eye)+=Poz(coi);

	Aff3fVecApply  (rot_mat, upvec, temp_vec);
	Vec3fCopy (temp_vec, upvec);
        
	Pnt3fDelete(temp_eye);
	Aff3fDelete(rot_mat);
	Dir3fDelete(rotate_axis);
	Vec3fDelete(temp_vec);
	Vec3fDelete(vec1);
	Vec3fDelete(vec2);
	Pnt3fDelete(world_p1);
	Pnt3fDelete(world_p2);
	Dir3fDelete(norvec1);
	Dir3fDelete(norvec2);
}

void View::Write(FILE *fout)
{
	fprintf(fout,"eye %f %f %f\ncoi %f %f %f\nup %f %f %f\nxfov %f\nyfov %f\nxres %d\nyres %d\n",
		Pnt3fX(eye),Pnt3fY(eye),Pnt3fZ(eye),Pnt3fX(coi),Pnt3fY(coi),Pnt3fZ(coi),
		Vec3fX(upvec),Vec3fY(upvec),Vec3fZ(upvec),
		RadianToDegree (2*xfov),RadianToDegree (2*yfov),xres,yres);
}














