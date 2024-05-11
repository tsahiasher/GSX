#include "phed3d.h"
#include <stdlib.h>
#include <string.h>
#include "gsxw.h"

#define PNEAR 0.03

#ifndef __BOOL
#define __BOOL
#define TRUE 1
#define FALSE 0
#endif

int Clip3d(Pnt3f pnt1,Pnt3f pnt2,Pnt3f res1,Pnt3f res2);
void ClipLine3D(Pnt3f pnt1,Pnt3f pnt2,screen_matptr scrparam);


void Error(char *t)
{
	fprintf(stderr,t);
	exit(1);
}

void Phed3f::Read(FILE *fin)
{
    char teststring[20];
    int number;
    tpnt3fptr point;    tringptr tringl;    squareptr asqure;

    fscanf(fin,"%s",teststring);
    if(strcmp(teststring,"v")!=0) Error("v expected");
    fscanf(fin,"%d",&number);
    for(int i=1;i<=number;i++)
    {
        point=new(tpnt3f);
        point->read(fin);
        vertex->AddItem((baseitemptr)point);
    }

    fscanf(fin,"%s",teststring);
    if(strcmp(teststring,"t")!=0) Error("t expected");
    fscanf(fin,"%d",&number);
    for(i=1;i<=number;i++)
    {
        tringl=new(tring);
        tringl->read(fin);
        trings->AddItem(tringl);
    }

    fscanf(fin,"%s",teststring);
    if(strcmp(teststring,"s")!=0) Error("s expected");
    fscanf(fin,"%d",&number);
    for(i=1;i<=number;i++)
    {
        asqure=new(square);
        asqure->read(fin);
        squares->AddItem(asqure);
    }

}


void Phed3f::Write(FILE *fin)
{
    fprintf(fin,"v ");
    vertex->WriteAll(fin);
    fprintf(fin,"t ");
    trings->WriteAll(fin);
    fprintf(fin,"s ");
    squares->WriteAll(fin);
}

void Phed3f::GetMatrix(Aff3f transform)
{
    vertex->ForEachp(&Aff3fPass,transform);
}


void Phed3f::Paint(screen_matptr scrparam)
{
    tpnt3fptr p1,p2,p3,p4,current,new_point;
    tringptr t1;
    squareptr s1;
    int i,tsize;
    table vertex_for_show;
    Pnt3f temp;

    tsize=vertex->Size();
    for(i=1;i<=tsize;i++)
    {
        current=(tpnt3fptr)vertex->Item(i);
        new_point=new(tpnt3f);
        temp=current->OutData();
        scrparam->pnt_to_view(temp,*new_point);

        vertex_for_show.AddItem((baseitemptr)new_point);
    }
    tsize=trings->Size();
    for(i=1;i<=tsize;i++)
    {
        t1=(tringptr)trings->Item(i);
        p1=(tpnt3fptr)vertex_for_show.Item(t1->OutData(1));  
        p2=(tpnt3fptr)vertex_for_show.Item(t1->OutData(2));  
        p3=(tpnt3fptr)vertex_for_show.Item(t1->OutData(3)); 

        ClipLine3D(p1->OutData(),p2->OutData(),scrparam);
        ClipLine3D(p2->OutData(),p3->OutData(),scrparam);
        ClipLine3D(p1->OutData(),p3->OutData(),scrparam);
   }
    tsize=squares->Size();
    for(i=1;i<=tsize;i++)
    {
        s1=(squareptr)squares->Item(i);
        p1=(tpnt3fptr)vertex_for_show.Item(s1->OutData(1));
        p2=(tpnt3fptr)vertex_for_show.Item(s1->OutData(2));
        p3=(tpnt3fptr)vertex_for_show.Item(s1->OutData(3));
        p4=(tpnt3fptr)vertex_for_show.Item(s1->OutData(4));

        ClipLine3D(p1->OutData(),p2->OutData(),scrparam);
        ClipLine3D(p2->OutData(),p3->OutData(),scrparam);
        ClipLine3D(p3->OutData(),p4->OutData(),scrparam);
        ClipLine3D(p4->OutData(),p1->OutData(),scrparam);

   }
   vertex_for_show.relese();
};

int Clip3d(Pnt3f pnt1,Pnt3f pnt2,Pnt3f res1,Pnt3f res2)
{
    // asuming that pnt1 is smaller then pnt2 in Z dirction
    if ((Poz(pnt1)>PNEAR)&&(Poz(pnt2)>PNEAR))
    {
        res1=Pnt3fCopy(pnt1,res1);
        res2=Pnt3fCopy(pnt2,res2);
        return (TRUE);
    }
    if ((Poz(pnt1)<PNEAR)&&(Poz(pnt2)<PNEAR)) return (FALSE);
    float alfa1=(Pox(pnt2)-Pox(pnt1))/(Poz(pnt2)-Poz(pnt1));
    float alfa2=(Poy(pnt2)-Poy(pnt1))/(Poz(pnt2)-Poz(pnt1));
    res2=Pnt3fCopy(pnt2,res2);
    Poz(res1)=PNEAR;
    Pox(res1)= -(alfa1*(Poz(pnt2)-PNEAR)-Pox(pnt2) );
    Poy(res1)= -(alfa2*(Poz(pnt2)-PNEAR)-Poy(pnt2) );
    return (TRUE);
}


void ClipLine3D(Pnt3f pnt1,Pnt3f pnt2,screen_matptr scrparam)
{
    int draw;
    Pnt3f res1,res2;
    res1=Pnt3fCreate();
    res2=Pnt3fCreate();
    if(Poz(pnt1)<=Poz(pnt2)) draw=Clip3d(pnt1,pnt2,res1,res2);
    else draw=Clip3d(pnt2,pnt1,res1,res2);
  
    if (draw)
    {
        scrparam->pnt_to_scr(res1);
        scrparam->pnt_to_scr(res2);
		GLine((int)Pox(res1)+SCREEN_OFFSET,(int)Poy(res1)+SCREEN_OFFSET,(int)Pox(res2)+SCREEN_OFFSET,(int)Poy(res2)+SCREEN_OFFSET);
    }
    Pnt3fDelete(res1);
    Pnt3fDelete(res2);
}


Phed3fptr Phed3f::Dup()
{
    Phed3fptr other=new(Phed3f);
    other->GetVertex(vertex->Dup());
    other->GetTrings(vertex->Dup());
    other->GetSquares(vertex->Dup());
    return other;
}

void Phed3f::relese()
{
    vertex->relese();
    trings->relese();
    squares->relese();
}

Pnt3f Phed3f::MaxPoint()
{
    Pnt3f result=Pnt3fCreateFromXYZ(-INFINIT,-INFINIT,-INFINIT);
    vertex->ForEachp(&GetMax,(void *)result);
    return result;
}

Pnt3f Phed3f::MinPoint()
{
    Pnt3f result=Pnt3fCreateFromXYZ(INFINIT,INFINIT,INFINIT);
    vertex->ForEachp(&GetMin,(void *)result);
    return result;
}















