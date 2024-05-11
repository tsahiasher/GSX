#include "world.h"



void  World::AddPoligon(Poly2fptr poly)
{
    PolyList2f helpptr=list;
    list=new(PolyList2frec);
    list->current=poly;
    list->next=helpptr;
}


void  World::Dispose()
{
    PolyList2f helpptr=list;
	while(helpptr)
    {
        helpptr=helpptr->next;
        delete(list->current);
        delete(list);
		list=helpptr;
	}
}


void World::GetData(FILE *fin)
	// read numofpoly and then read exacly numofpoly of polygon
{
	int numofpoly;
	Poly2fptr pol;
	

	ReadString(fin,"number");
	fscanf (fin,"%d",&numofpoly);

	for(int i=1;i<=numofpoly;i++)
	{
		  pol=new(Poly2f);
		  pol->Read(fin);
		  AddPoligon(pol);
	}
};

/* end of file */

