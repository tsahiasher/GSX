#include "matrix.h"
#define M_PI 3.141



void matrix::TransPoint(Pnt2f apoint)
    // transformaition on point , work only in size 3
{
     float newX,newY;
     newX=( OutData(1,1)*Pnt2fX(apoint)
		   +OutData(1,2)*Pnt2fY(apoint)
		   +OutData(1,3)*1);
     newY=( OutData(2,1)*Pnt2fX(apoint)
		   +OutData(2,2)*Pnt2fY(apoint)
		   +OutData(2,3)*1 );
     Pnt2fX(apoint)=newX;
     Pnt2fY(apoint)=newY;
} //TransPoint


/***************************************************************************/
/*                      operators for matrix                               */
/***************************************************************************/
matrix matrix::operator=(matrix & other)	
{//assign
	for(int i=1;i<=MATRIX_LONG;i++)
	 {
		  for (int j=1;j<=MATRIX_LONG;j++)
		  {
				GetData(i,j,(other.OutData(i,j)));
		  }
	 }
	 return (*this);
}

matrix  matrix::operator*(matrix & other)
{//vectore mul
	 matrixdata help_table ;   
	                                       // multipling
	 for (int i=1;i<=MATRIX_LONG;i++)
	 {
		  for (int j=1;j<=MATRIX_LONG;j++)
		  {
				help_table[j-1][i-1]=0;
				for (int k=1;k<=MATRIX_LONG;k++)
				help_table[j-1][i-1]+=OutData(k,i)*other.OutData(j,k);
		   }
	 }
                                         // coping reslts to current matrix
	 for(i=1;i<=MATRIX_LONG;i++)
	 {
		  for (int j=1;j<=MATRIX_LONG;j++)
		  {
				GetData(i,j,help_table[i-1][j-1]);
		  }
	 }
	 return (*this);
}


/***************************************************************************/
/*            initialing matrix for graphics operition                     */
/***************************************************************************/


void matrix::Init_I()
{
	 for (int i=1;i<=MATRIX_LONG;i++)
	 {
		  for (int j=1;j<=MATRIX_LONG;j++)
		  {
			if(i==j) GetData(i,j,1);
			else GetData(i,j,0);
		  }
	  }
};

void matrix::InitScale(double xscale,double yscale)
{
	   Init_I();
	   GetData(1,1,xscale);
	   GetData(2,2,yscale);
}

void matrix::InitRotate(double angle)
{
	  Init_I();
	  angle=(angle/180)*M_PI;  // degrees to radians
	  GetData(1,1,cos(angle));
	  GetData(2,2,OutData(1,1));
	  GetData(2,1,sin(angle));
	  GetData(1,2,-OutData(2,1));
}

void matrix::InitMove(double movex,double movey)
{
	  Init_I();
	  GetData(1,3,movex);
	  GetData(2,3,movey);
}



// end of file






