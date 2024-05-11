/*
   world : a moudle to discribe a world (of phedgon)  which is an unbounded
		   list of phedgon
*/

#ifndef world__
#define world__


#include "phed3d.h"
#include "vec3f.h"
#include "pnt3f.h"
#include "view3.h"

typedef struct _PhedList3f
{
	Phed3f *current;
	_PhedList3f *next;
}PhedList3frec ,*PhedList3f;

class World;

typedef World *Worldptr;

class World
{
	private:
		PhedList3f list;
	public:
		World(){list=NULL;};
		~World(){};

		void GetData(FILE *fin);
		void AddPolihed(Phed3fptr phed);
		PhedList3f OutPhedList() {return list;};
		void GetList(PhedList3f alist) {list=alist;};  //do we need?
		void Dispose();     //why do we need
		void BoundingBox(Viewptr boundview);
		void Display(Viewptr boundview);
};

#endif
