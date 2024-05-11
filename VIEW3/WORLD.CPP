

#include "world.h"

#define TAN_DEF_XFOV 0.700207538  //35
#define TAN_DEF_YFOV 0.700207538  //35
#define DEF_XFOV	 0.610865238  //35 in rad
#define DEF_YFOV	 0.610865238  //35 in rad
#define DEF_XRES	 500
#define DEF_YRES	 347

float calc_eye_z(float dx,float dy, float min_z); 

void World::GetData(FILE *fin)
	// read numofphed and then read exacly numofphed of phed
{
	int numofphed;
	Phed3fptr phed;


	ReadString(fin,"object");
	fscanf (fin,"%d",&numofphed);

	for(int i=1;i<=numofphed;i++)
	{
		  phed=new(Phed3f);
		  phed->Read(fin);
		  AddPolihed(phed);
	}
}

void  World::AddPolihed(Phed3fptr phed) // add phed to poly list
{
	PhedList3f helpptr=list;
	list=new(PhedList3frec);                        //   ?????
	list->current=phed;
	list->next=helpptr;
}

void  World::Dispose()
{
	PhedList3f helpptr=list;
	while(helpptr)
	{
		helpptr=helpptr->next;
		delete(list->current);
		delete(list);
		list=helpptr;
	}
}

float calc_eye_z(float dx,float dy, float min_z)

{
	if (dx>=dy)
		return(min_z-dx/TAN_DEF_XFOV-10);
	return(min_z-dy/TAN_DEF_YFOV-10);
}

void World::BoundingBox(Viewptr boundview)
{
	PhedList3f 	curphed=list;
	Pnt3f 		max_phed,min_phed,max,min;
	Pnt3f 		beye,bcoi;
	Vec3f 		bupvec;
	float		dx,dy,dz;

	max=Pnt3fCreateFromXYZ(-INFINIT,-INFINIT,-INFINIT);
	min=Pnt3fCreateFromXYZ(INFINIT,INFINIT,INFINIT);
	while(curphed)
	{
		max_phed=curphed->current->MaxPoint();
		min_phed=curphed->current->MinPoint();
		MakeMax(max,max_phed);
		MakeMin(min,min_phed);
		free(max_phed);
		free(min_phed);
		curphed=curphed->next;
	}
	dx=(Pnt3fX(max)-Pnt3fX(min))/2;
	dy=(Pnt3fY(max)-Pnt3fY(min))/2;
	dz=(Pnt3fZ(max)-Pnt3fZ(min))/2;
	bcoi=Pnt3fCreateFromXYZ (dx+Pnt3fX(min),dy+Pnt3fY(min),dz+Pnt3fZ(min));
	if ((dz<=dy) && (dz<=dx))
	{
		beye=Pnt3fCreateFromXYZ (dx+Pnt3fX(min),dy+Pnt3fY(min),
                   calc_eye_z(dx,dy,Pnt3fZ(min)));
		bupvec=Vec3fCreateFromXYZ (0,1,0);
	}
	else
		if ((dy<=dz) && (dy<=dx))
		{
			beye=Pnt3fCreateFromXYZ (dx+Pnt3fX(min),calc_eye_z(dx,dz,Pnt3fY(min)),dz+Pnt3fZ(min));
			bupvec=Vec3fCreateFromXYZ (1,0,0);
		}
		else
		{
			beye=Pnt3fCreateFromXYZ (calc_eye_z(dy,dz,Pnt3fX(min)),dy+Pnt3fY(min),dz+Pnt3fZ(min));
			bupvec=Vec3fCreateFromXYZ (0,0,1);
		}
	(*boundview).InitCurView3(beye, bcoi, bupvec, DEF_XFOV, DEF_YFOV, DEF_XRES, DEF_YRES);
}


void World::Display(Viewptr boundview)
{
	PhedList3f curphed=list;

	while(curphed)
	{
		(*curphed->current).Paint((*boundview).screen_mat());
		curphed=curphed->next;
	}
}
