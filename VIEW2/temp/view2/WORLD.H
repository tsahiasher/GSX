/*
   world : a moudle to discribe a world (of polygon)  which is an unbounded
           list of polygon
*/

#ifndef world__
#define world__

#include "polyf2d.h"

typedef struct _PolyList2f
{Poly2f *current;
 _PolyList2f *next;}  PolyList2frec ,*PolyList2f;

class World;

typedef World *Worldptr;

class World
{
private:
      PolyList2f list;
public:
      World(){list=NULL;};
      ~World(){};

	  void GetData(FILE *fin);
      void AddPoligon(Poly2fptr poly);
      PolyList2f OutPolyList() {return list;};
      void GetList(PolyList2f alist) {list=alist;};
      void Dispose();

};

#endif
