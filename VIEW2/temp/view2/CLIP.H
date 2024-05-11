/*
  clip : a modle to implement cliping a line on a screen , the function
         MyLine could be use to replace GLine with the difrence that this 
         function uses float
         do change the constants of screen size and min to your needs
*/



#ifndef __CLIP__
#define __CLIP_

#include "gsxw.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define SCREEN_SIZEX 500
#define SCREEN_SIZEY 420
#define MINX 60
#define MINY 30

#define CLIP_COLOR FORE_BLUE
#define NORMAL_COLOR FORE_GREEN

void MyLine(float x1, float y1, float x2, float y2);

#endif






