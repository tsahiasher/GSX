#include "polyf2d.h"
#include <string.h>
#include <stdlib.h>
/*****************************************************************************/
/*                             i/o  functions                                */
/*****************************************************************************/


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
    
void PntRead(Pnt2f apoint,FILE *fin)
{
	fscanf(fin,"%f %f",&Pnt2fX(apoint),&Pnt2fY(apoint));
}

void Poly2f::Read(FILE *fin)
{
	   int i=0;


	   ReadString(fin,"size");
	   fscanf(fin,"%d",&Lines_Num);
	   while(i<Lines_Num)
	   {
			pnts[i]=(Pnt2f)malloc(sizeof(Pnt2fRec));
			PntRead(pnts[i],fin);
			i++;
	   }
}; //read


void Poly2f::Paint()
       //   same as GclosedPoly from gax.c but using MyLine for cliping 
{               
		for(int i=0; i<Lines_Num-1; i++)
			MyLine (Pnt2fX(pnts[i]),Pnt2fY(pnts[i])
			   ,Pnt2fX(pnts[i+1]),Pnt2fY(pnts[i+1]));

		if (Lines_Num > 0)
		   MyLine (Pnt2fX(pnts[Lines_Num-1]),Pnt2fY(pnts[Lines_Num-1])
			   ,Pnt2fX(pnts[0]),Pnt2fY(pnts[0]));
}

/*****************************************************************************/
/*       change data using other polygon & or matrix                         */
/*****************************************************************************/


void Poly2f::GetPolyWithMatrix(Poly2fptr other,matrix transform)
{
       int i=0;
       Lines_Num=other->LinesNum();
       while(i<Lines_Num)
         {
            pnts[i]=(Pnt2f)malloc(sizeof(Pnt2fRec));
			Pnt2fX(pnts[i])=other->OutX(i);
			Pnt2fY(pnts[i])=other->OutY(i);
			transform.TransPoint(pnts[i]);
			i++;
         }
};

void Poly2f::GetPoly(Poly2fptr other)
{
       int i=0;
       Lines_Num=other->LinesNum();
       while(i<Lines_Num)
         {
            pnts[i]=(Pnt2f)malloc(sizeof(Pnt2fRec));
            Pnt2fX(pnts[i])=other->OutX(i);
            Pnt2fY(pnts[i])=other->OutY(i);
            i++;
         }
};


void Poly2f::GetMatrix(matrix transform)
{
       int i=0;
       while(i<Lines_Num)
         {
            transform.TransPoint(pnts[i]);
            i++;
         }
};


/* end of file */


