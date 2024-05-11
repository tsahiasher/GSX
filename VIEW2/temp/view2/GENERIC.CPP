#include "gsxw.h"

int __cdecl Gmain(int argc,char *argv[])
{
	GWindow(50,50,350,350,"Demo");
	GCircle(180,70,60);
	GSetForeground(FORE_RED);
	GCircleFill(200,200,50);
	GSetForeground(FORE_GREEN);
	GRectangleFill(200,200,60,60);
	GSetForeground(FORE_BLUE);
    GCircle(200,200,60);
	GLinewidth(5);
	GLine (10,10,100,100);
	GLinewidth(1);
	GText(120,120,"this is a test");
	GMainLoop();

	return(0);
}


