#include "clip.h"

          // constants for the get region function

#define BOTTOM 4
#define TOP    8
#define RIGHT  2
#define LEFT   1

         // function prototypes

int GetRegion (float X, float Y);
int Clip (float *X1, float *Y1, float *X2, float *Y2);
extern unsigned int Color;   /* to change color */

	// clip get parametrs of a line and return FALSE if the line should
	// not be painted and TRUE if part of the line shuld be painted
    //  in this case.



 /* get parameters of line and use clip to cheak where it cut frame then
    draw a line in  CLIP_COLOR ouutside the frame and a line in normal_color
    in the frame
*/  
void MyLine(float x1, float y1, float x2, float y2)
{
 
        float new_x1=x1, new_y1=y1,new_x2=x2,new_y2=y2;
        int clip_result=Clip (&new_x1,&new_y1,&new_x2,&new_y2);
	
        if(clip_result)      // line is partly in
	{
		GSetForeground (CLIP_COLOR);
		GLine((short)x1,(short)y1,(short)new_x1,(short)new_y1);
		GLine((short)new_x2,(short)new_y2,(short)x2,(short)y2);
		GSetForeground (NORMAL_COLOR);
		GLine((short)new_x1,(short)new_y1,(short)new_x2,(short)new_y2);

	}

		else
	{
		GSetForeground (CLIP_COLOR);
		GLine((short)x1,(short)y1,(short)x2,(short)y2);
	}

}





int Clip (float *X1, float *Y1, float *X2, float *Y2)
/* uses the cohen saterlend algoritem to clip a line */
{

  int region, region1, region2, done = FALSE, draw = FALSE;
  float x, y;

  region1 = GetRegion(*X1, *Y1);
  region2 = GetRegion(*X2, *Y2);

  while (!done) {

  if (region1 & region2) {
	  done = TRUE;
	}
	else if (!(region1|region2)) {
	  done = draw = TRUE;
	}
	else {
	if (region1)
		region = region1;
	else region = region2;

	if (region & TOP) {
		x = *X1 +( (*X2 - *X1) / (*Y2 - *Y1) ) * (MINY-*Y1);
		y = MINY;
	}
	else if (region & LEFT) {
			y = *Y1 + (  (*Y2 - *Y1) / (*X2 - *X1) ) * (MINX-*X1);
			x = MINX;
		 }
		 else if (region & RIGHT) {
				y = *Y1 +( (*Y2 - *Y1) / (*X2 - *X1) ) * (SCREEN_SIZEX-MINX - *X1) ;
				x = SCREEN_SIZEX-MINX;
			  }
			  else if (region & BOTTOM) {
						x = *X1 + ( (*X2 - *X1) / (*Y2 - *Y1) )* (SCREEN_SIZEY-MINY - *Y1 ) ;
						y = SCREEN_SIZEY-MINY;
				   }

	  if (region == region1) {
		*X1 = x; *Y1 = y; region1 = GetRegion (*X1, *Y1);
	  }
	  else {
		*X2 = x; *Y2 = y; region2 = GetRegion (*X2, *Y2);
	  }
	}

  }

  return (draw);

}


/************************************************************************/
int GetRegion (float X, float Y)
{
/*
  The returned value is according to this sceme,
  where the screen itself is the 0000 (binary)
  region:

        |      |
   1001 | 1000 | 1010
  ---------------------
   0001 | 0000 | 0010
  ---------------------
   0101 | 0100 | 0110
        |      |
*/


  int region = 0;

  if (X < MINX) region |= LEFT;
  else if (X > SCREEN_SIZEX-MINX) region |= RIGHT;

  if (Y > SCREEN_SIZEY-MINY) region |= BOTTOM;
  else if (Y < MINY) region |= TOP;

  return (region);
}


/* end of file */









