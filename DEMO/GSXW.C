#include "gsxw.h"
#include <string.h>
#include <malloc.h>

#define NUM_OF_ARGS 16
#define LENGTH_OF_ARG 64
#define WM_REDRAW WM_USER

void 	getcmdline(LPSTR lpCmdLine,int *argc,char *argv[]);
static 	InitApplication(HANDLE);


static HWND		hWnd;
static HANDLE 	GhInstance;
static int	    GnCmdShow;
static COLORREF	fore_color=FORE_BLACK;
static int		pen_width=1;
static HPEN		hpen;
static HBRUSH	hbr;
static HDC hdc;

FuncV g_function[] = {
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
GNULLFUNCTION,
};

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance,
										 LPSTR lpCmdLine, int nCmdShow)
{
	int		argc=1;
	char	*argv[NUM_OF_ARGS];
	
	if (!hPrevInstance)          /* Other instances of app running? */
	if (!InitApplication(hInstance)) /* Initialize shared things */
		return (FALSE);      /* Exits if unable to initialize     */

	GhInstance=hInstance;
	GnCmdShow=nCmdShow;
	getcmdline(lpCmdLine,&argc,argv);
	Gmain(argc,argv);
	return(0);
}

void getcmdline(LPSTR lpCmdLine,int *argc,char *argv[])
/*change lpCmdLine format to argc and argv*/
{
	int		i=0,j=0;
	
	argv[(*argc)] = (char*)malloc(LENGTH_OF_ARG);
	while ((lpCmdLine[i]) && ((lpCmdLine[i]==' ') || (lpCmdLine[i]=='\t')))
		i++;
	while (lpCmdLine[i])
	{
		if ((lpCmdLine[i]==' ') || (lpCmdLine[i]=='\t'))
		{
			(argv[(*argc)][j])=0;
			j=0;
			while ((lpCmdLine[i]) && ((lpCmdLine[i]==' ') || (lpCmdLine[i]=='\t')))
		    	i++;
		    (*argc)++;
		    if (lpCmdLine[i])
		    	argv[(*argc)] = (char*)malloc(LENGTH_OF_ARG);
	    }
		else
		{
			(argv[(*argc)][j++])=lpCmdLine[i];
			i++;
			if (!lpCmdLine[i])
			{
				(argv[(*argc)][j])=0;
				(*argc)++;
			}
		}
	}
}

long CALLBACK __export MainWndProc(HWND hWnd, UINT message,
										WPARAM wParam, LPARAM lParam)
{
	GEventRec	g_event_rec;
	PAINTSTRUCT ps;
	HDC thdc;
	    
	switch (message)
	{
		case WM_COMMAND:       
			switch (wParam)
			{
				case IDM_ABOUT:
					MessageBox (hWnd, "Gsx library for windows\n by Tsahi Asher\n 1/1995",
					"GSX", MB_OK | MB_ICONINFORMATION);
					break;

				case IDM_QUIT:
					DestroyWindow(hWnd);
					break;
			}
			break;

		case WM_MOUSEMOVE:

			g_event_rec.x = LOWORD(lParam);
			g_event_rec.y = HIWORD(lParam);
			if (g_function[GMotion] && (wParam!=MK_LBUTTON) &&
							(wParam!=MK_MBUTTON) && (wParam!=MK_RBUTTON))
			{
				(*g_function[GMotion])(&g_event_rec);
			}
			else if (g_function[GDrag] && (wParam==MK_LBUTTON))
			{
				g_event_rec.state = MOUSEBUTTON1;
				(*g_function[GDrag])(&g_event_rec);
			}
			else if (g_function[GDrag] && (wParam==MK_MBUTTON))
			{
				g_event_rec.state = MOUSEBUTTON2;
				(*g_function[GDrag])(&g_event_rec);
			}
			else if (g_function[GDrag] && (wParam==MK_RBUTTON))
			{
				g_event_rec.state = MOUSEBUTTON3;
				(*g_function[GDrag])(&g_event_rec);
			}
			break;

		case WM_LBUTTONDOWN:

			g_event_rec.x = LOWORD(lParam);
			g_event_rec.y = HIWORD(lParam);
			if (g_function[GButton1Press])
				(*g_function[GButton1Press])(&g_event_rec);
			break;

		case WM_LBUTTONUP:

			g_event_rec.x = LOWORD(lParam);
			g_event_rec.y = HIWORD(lParam);
			if (g_function[GButton1Release])
				(*g_function[GButton1Release])(&g_event_rec);
			break;

		case WM_MBUTTONDOWN:

			g_event_rec.x = LOWORD(lParam);
			g_event_rec.y = HIWORD(lParam);
			if (g_function[GButton2Press])
				(*g_function[GButton2Press])(&g_event_rec);
			break;

		case WM_MBUTTONUP:

			g_event_rec.x = LOWORD(lParam);
			g_event_rec.y = HIWORD(lParam);
			if (g_function[GButton2Release])
				(*g_function[GButton2Release])(&g_event_rec);
			break;

		case WM_RBUTTONDOWN:

			g_event_rec.x = LOWORD(lParam);
			g_event_rec.y = HIWORD(lParam);
			if (g_function[GButton3Press])
				(*g_function[GButton3Press])(&g_event_rec);
			break;

		case WM_RBUTTONUP:

			g_event_rec.x = LOWORD(lParam);
			g_event_rec.y = HIWORD(lParam);
			if (g_function[GButton3Release])
				(*g_function[GButton3Release])(&g_event_rec);
			break;

		case WM_CHAR:

			g_event_rec.key = (unsigned char)wParam ;
			if (g_function[GKey])
				(*g_function[GKey])(&g_event_rec);
			break;

		/*case WM_PAINT:
			
			BeginPaint(hWnd, &ps);
		    thdc = hdc;
		    hdc = ps.hdc;
		    if (g_function[GRedraw])
				(*g_function[GRedraw])(&g_event_rec);
			EndPaint(hWnd, &ps);
    		hdc = thdc ;
    		break;*/
			
		case WM_DESTROY:          /* message: window being destroyed */
				ReleaseDC(hWnd, hdc);
				PostQuitMessage(0);
			break;

		default:                  /* Passes it on if unproccessed    */
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (NULL);
}

BOOL InitApplication(HANDLE hInstance)
{
	WNDCLASS  wc;

	wc.style = CS_HREDRAW | CS_VREDRAW; /* Class style(s).                    */
	wc.lpfnWndProc = MainWndProc;       /* Function to retrieve messages for  */
										/* windows of this class.             */
	wc.cbClsExtra = 0;                  /* No per-class extra data.           */
	wc.cbWndExtra = 0;                  /* No per-window extra data.          */
	wc.hInstance = hInstance;           /* Application that owns the class.   */
	wc.hIcon = LoadIcon( (HINSTANCE)hInstance, MAKEINTRESOURCE( GSX ) );
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName =  "GsxMenu";   /* Name of menu resource in .RC file. */
	wc.lpszClassName = "GsxWClass"; /* Name used in call to CreateWindow. */

	return (RegisterClass(&wc));

}

void GClear()
{
   RECT	r;

   GetWindowRect ( hWnd, &r );
   r.left=0;
   r.top=0;
   FillRect( hdc, &r, (HBRUSH) GetStockObject( WHITE_BRUSH ) );
}

void GFuncSet(FuncV func, GEventT type)

{
	g_function[type] = func;
}

void GWindow(int x, int y, int width, int height, char* text)
{
	HPEN 	phpen;
	HBRUSH	phbr;

	hWnd = CreateWindow(
		"GsxWClass",                /* See RegisterClass() call.          */
		text,					    /* Text for window title bar.         */
		WS_OVERLAPPEDWINDOW,        /* Window style.                      */
		x,
		y,
		width+5,
		height+50,
		NULL,                           /* Overlapped windows have no parent. */
		NULL,                           /* Use the window class menu.         */
		GhInstance,                     /* This instance owns this window.    */
		NULL                            /* Pointer not needed.                */
	);

	hdc=GetDC(hWnd);
	hbr = CreateSolidBrush(fore_color);
	phpen=SelectObject(hdc, hpen);
	hbr = CreateSolidBrush(fore_color);
	phbr=SelectObject(hdc, hbr);
	DeleteObject(phpen);
	DeleteObject(phbr);
	
	ShowWindow(hWnd, GnCmdShow);
	UpdateWindow(hWnd);
	GClear();
}

int GMainLoop(void)
{
	MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}

void GLine (int xStart,int yStart, int xEnd, int yEnd)
{
	MoveToEx(hdc,xStart,yStart,NULL);
	LineTo(hdc,xEnd,yEnd);
}

void GCloseWindow (void)
{
	PostMessage (hWnd,WM_DESTROY,0,0);
}

void GSetForeground(COLORREF c)
{
	HPEN 	phpen;
	HBRUSH	phbr;

	fore_color=c;
	hpen = CreatePen(PS_SOLID, pen_width, fore_color);
	phpen=SelectObject(hdc, hpen);
	hbr = CreateSolidBrush(fore_color);
	phbr=SelectObject(hdc, hbr);
	DeleteObject(phpen);
	DeleteObject(phbr);
}

void GLinewidth(unsigned int w)
{
	HPEN 	phpen;

	pen_width=w;
	hpen = CreatePen(PS_SOLID, pen_width, fore_color);
	phpen=SelectObject(hdc, hpen);
	DeleteObject(phpen);
}

void GCircleFill(int x, int y, int r)
{
	Ellipse(hdc, x-r, y-r, x+r, y+r);
}


void GCircle(int x, int y, int r)
{
	RECT 	rc;
	POINT 	ptStart,ptEnd;

	rc.left=x-r;rc.right=x+r;
	rc.top=y-r;rc.bottom=y+r;
	ptStart.x=x-r;ptStart.y=y;
	ptEnd.x=x-r;ptEnd.y=y;
	Arc(hdc, rc.left, rc.top, rc.right, rc.bottom,
	ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}


void GText(int x, int y, char *text_string)
{
	TextOut( hdc, x, y, text_string, strlen( text_string ) );
}

void GRectangleFill(int x, int y, int w, int h)
{
	Rectangle(hdc, x, y, x+w, y+h);
}

void GRectangle(int x, int y, int w, int h)
{
	POINT aPoints[5];

	aPoints[0].x = x;
	aPoints[0].y = y;
	aPoints[1].x = x+w;
	aPoints[1].y = y;
	aPoints[2].x = x+w;
	aPoints[2].y = y+h;
	aPoints[3].x = x;
	aPoints[3].y = y+h;
	aPoints[4].x = x;
	aPoints[4].y = y;

	Polyline(hdc, aPoints, sizeof(aPoints) / sizeof(POINT));
}



