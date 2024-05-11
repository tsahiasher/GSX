# Microsoft Visual C++ generated build script - Do not modify

PROJ = DEMO
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\MSVC\GSX\DEMO\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = DEMO.C      
FIRSTCPP =             
RC = rc
CFLAGS_D_WEXE = /nologo /W3 /FR /G2 /Zi /D_DEBUG /Od /AM /GA /Fd"DEMO.PDB"
CFLAGS_R_WEXE = /nologo /W3 /FR /O1 /DNDEBUG /AM /GA
LFLAGS_D_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /ALIGN:16 /STACK:10240
LFLAGS_R_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /ALIGN:16 /STACK:10240
LIBS_D_WEXE = oldnames libw commdlg shell olecli olesvr mlibcew
LIBS_R_WEXE = oldnames libw commdlg shell olecli olesvr mlibcew
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = GSXW.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DEMO.SBR \
		GSXW.SBR


DEMO_DEP = c:\msvc\gsx\demo\gsxw.h


GSXW_DEP = c:\msvc\gsx\demo\gsxw.h


GSXW_RCDEP = c:\msvc\gsx\demo\gsxw.ico


all:	$(PROJ).EXE $(PROJ).BSC

DEMO.OBJ:	DEMO.C $(DEMO_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c DEMO.C

GSXW.OBJ:	GSXW.C $(GSXW_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c GSXW.C

GSXW.RES:	GSXW.RC $(GSXW_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r GSXW.RC


$(PROJ).EXE::	GSXW.RES

$(PROJ).EXE::	DEMO.OBJ GSXW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DEMO.OBJ +
GSXW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) GSXW.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	GSXW.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) GSXW.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
