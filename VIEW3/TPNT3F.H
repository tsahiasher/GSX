#ifndef __tpnt3f_
#define __tpnt3f_

#include "pnt3f.h"
#include "aff3f.h"
#include "table.h"


class tpnt3f;
typedef tpnt3f *tpnt3fptr;

class tpnt3f:public baseitem
{
private:
	   Pnt3f data;
public:
	tpnt3f(){data=Pnt3fAlloc();};
	~tpnt3f(){};
    Pnt3f Data()	{		return data;	}; // DOS
    void GetData(Pnt3f d)	{data=d;};

	Pnt3f OutData()
	{
		return data;
	};
	int read(FILE *infile);
	void write(FILE *outfile);
	void relese()
	{
		Pnt3fDelete(data);
	};
//   friend int Aff3fPass(tpnt3fptr p,void * ptr);
   friend int Aff3fPass(baseitemptr p,void * ptr); // DOS
   tpnt3fptr Dup();
   friend int ChangeToScr(tpnt3fptr tpnt,void *scrmat);
   friend int GetMax(baseitemptr tpnt,void *maxpnt);
   friend int GetMin(baseitemptr tpnt,void *minpnt);

};
void MakeMax(Pnt3f to_be_max,Pnt3f other);
void MakeMin(Pnt3f to_be_min,Pnt3f other);



#endif

