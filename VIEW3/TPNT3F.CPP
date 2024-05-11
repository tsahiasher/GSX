#include "tpnt3f.h"

int tpnt3f::read(FILE *infile)
{
     float x,y,z;
     int scan_res=fscanf(infile,"%f %f %f",&x,&y,&z);
     if(scan_res!=3) return 0;
     Pnt3fFromXYZ(data,x,y,z);
     return 1;
}

void tpnt3f::write(FILE *outfile)
{
    Pnt3fWrite(data,outfile);
};

//int Aff3fPass(tpnt3fptr p,void * ptr)
int Aff3fPass(baseitemptr p,void * ptr)
{
    tpnt3fptr thepoint=(tpnt3fptr)p;
    Pnt3f newp=Pnt3fAlloc();
    Aff3f mat=(Aff3f)ptr;
    Aff3fPntApply(mat,thepoint->Data(),newp);
    thepoint->GetData(Pnt3fCopy (thepoint->Data(),newp));
    return Pnt3fFree (newp);
}

tpnt3fptr tpnt3f::Dup()
{
    tpnt3fptr newpnt=new(tpnt3f);
    newpnt->data=Pnt3fDup(data);
    return newpnt;
}

/* int ChangeToScr(baseitemptr tpnt,void *scrmat)
{
    tpnt3fptr thepoint=(tpnt3fptr)tpnt;
    screen_matptr mat=(screen_matptr)scrmat;
    Pnt3f pnt=thepoint->OutData();


    Pnt3fX(pnt)*=(mat->Outa1())/( Pnt3fZ(pnt)); //*mat->Outb()+mat->Outc()
    Pnt3fY(pnt)*=(mat->Outa2())/( Pnt3fZ(pnt)); //*mat->Outb()+mat->Outc()
    return 1;
}; */


float max(float a,float b)
{
    if (a>b) return a; else return b;
}

float min(float a,float b)
{
    if (a<b) return a; else return b;
}

void MakeMax(Pnt3f to_be_max,Pnt3f other)
{
     PntX(to_be_max)=max(PntX(to_be_max),PntX(other));
     PntY(to_be_max)=max(PntY(to_be_max),PntY(other));
     PntZ(to_be_max)=max(PntZ(to_be_max),PntZ(other));
}

void MakeMin(Pnt3f to_be_min,Pnt3f other)
{
     PntX(to_be_min)=min(PntX(to_be_min),PntX(other));
     PntY(to_be_min)=min(PntY(to_be_min),PntY(other));
     PntZ(to_be_min)=min(PntZ(to_be_min),PntZ(other));
}

//int GetMax(tpnt3fptr tpnt,void *maxpnt)
int GetMax(baseitemptr tpnt,void *maxpnt)
{
    tpnt3fptr thepoint=(tpnt3fptr)tpnt;
    Pnt3f tempmax=(Pnt3f)maxpnt;
    MakeMax(tempmax,thepoint->Data());
    return (1);
}

//int GetMin(tpnt3fptr tpnt,void *minpnt)
int GetMin(baseitemptr tpnt,void *minpnt)
{
    tpnt3fptr thepoint=(tpnt3fptr)tpnt;
    Pnt3f tempmin=(Pnt3f)minpnt;
    MakeMin(tempmin,thepoint->Data());
    return (1);
}


