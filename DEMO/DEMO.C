#include "gsxw.h"
#include <stdlib.h>

void cb_move (GEvent e)
{
	GSetForeground (FORE_GREEN);
	GLine (0,0,e->x, e->y);
	GText (e->x, e->y, "motion");
}

void cb_drag (GEvent e)
{
	GSetForeground (FORE_BLUE);
	GLine (0,0,e->x, e->y);
	GText (e->x, e->y, "drag");
}

void cb_quit (GEvent e)
{
	if (e->key == 'q')
		{
			GCloseWindow();
			exit(0);
		}
}

void cb_msg (GEvent e)
{
	GSetForeground (FORE_RED);
	GLine (0,0,e->x, e->y);
	GText (e->x, e->y, "Twas brillig,...");
}

void cb_clear (GEvent e)
{
	GClear();
}

int Gmain(int argc, char *argv[])
{
	GWindow(10,10,600,400,"test");
	GFuncSet(cb_msg, GButton1Press);
	GFuncSet(cb_drag, GDrag);
	GFuncSet(cb_move, GMotion);
	GFuncSet(cb_quit, GKey);
	GFuncSet(cb_clear, GButton3Press);

	GMainLoop();

}



