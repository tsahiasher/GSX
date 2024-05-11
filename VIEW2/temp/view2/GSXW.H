/*
 * Module : gsx.c
 * Purpose: PC Simulation on Windows of GSX - SIMPLE Graphics Support for X.
 * Written by Tsahi on May 95.
 */

#ifndef gsxw_h
#define gsxw_h

#include <windows.h>            /* required for all Windows applications */

#define IDM_ABOUT   100
#define IDM_QUIT	101
#define GSX			200

#define colortype		COLORREF  /*to pass colors as parameters*/

#define FORE_BLACK		RGB(0,0,0)
#define FORE_RED		RGB(255,0,0)
#define FORE_GREEN		RGB(0,255,0)
#define FORE_BLUE		RGB(0,0,255)
#define FORE_WHITE		RGB(255,255,255)
#define FORE_YELLOW		RGB(255,255,0)
#define FORE_MAGENTA    RGB(255,0,255)
#define FORE_CYAN		RGB(0,255,255)

/*
 *	Possible events structure definition.
 */
typedef enum {
	GNull, GExpose, GRedraw,
	GButton1Press, GButton2Press, GButton3Press,
	GButton1Release, GButton2Release, GButton3Release,
	GDrag, GMotion, GKey
} GEventT;


/*
 *	Event strucure.
 */

typedef struct {
	GEventT event_type;
	int x;
	int y;
	unsigned int state;
	unsigned int key;
	char string[100];
} GEventRec, *GEvent;

#define GEventX(e)      ((e)->x)
#define GEventY(e)      ((e)->y)
#define GEventKey(e)    ((e)->key)
#define GEventType(e)   ((e)->event_type)
#define GEventString(e) ((e)->string)


/*
 *	Event handling function type definition.
 */

typedef void (*FuncV)(GEvent);
typedef void (*GFunction)(GEvent);
#define GNULLFUNCTION (GFunction) 0

/* Drag mouse button ids */

#define MOUSEBUTTON1 1
#define MOUSEBUTTON2 2
#define MOUSEBUTTON3 3

/* General functions prototyping. */
int GMainLoop(void);
void GFuncSet(FuncV, GEventT);
void GWindow(int x, int y, int width, int height, char* text);
void GCloseWindow (void);

/* Drawing functions prototyping. */
void GCircle(int x, int y, int r);
void GCircleFill(int x, int y, int r);
void GLine (int xStart,int yStart, int xEnd, int yEnd);
void GText(int x, int y, char *text_string);
void GRectangle(int x, int y, int w, int h);
void GRectangleFill(int x, int y, int w, int h);

/* Control functions prototyping. */
void GClear(void);
void GSetForeground(COLORREF c);
void GLinewidth(unsigned int w);

int Gmain(int,char *argv[]);

LRESULT CALLBACK  MainWndProc( HWND, UINT, WPARAM, LPARAM ) ;

#endif
