# Microsoft Visual C++ generated build script - Do not modify

PROJ = VIEW2
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\MSVC\GSX\VIEW2\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = CLIP.CPP    
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /FR /GA /Fd"VIEW2.PDB"
CFLAGS_R_WEXE = /nologo /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw llibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
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
SBRS = CLIP.SBR \
		GSXW.SBR \
		MATRIX.SBR \
		POLYF2D.SBR \
		VIEW.SBR \
		WORLD.SBR \
		VIEW2.SBR


CLIP_DEP = c:\msvc\gsx\view2\clip.h \
	c:\msvc\gsx\view2\gsxw.h


GSXW_DEP = c:\msvc\gsx\view2\gsxw.h


MATRIX_DEP = c:\msvc\gsx\view2\matrix.h


POLYF2D_DEP = c:\msvc\gsx\view2\polyf2d.h \
	c:\msvc\gsx\view2\matrix.h \
	c:\msvc\gsx\view2\clip.h \
	c:\msvc\gsx\view2\gsxw.h


VIEW_DEP = c:\msvc\gsx\view2\view.h \
	c:\msvc\gsx\view2\world.h \
	c:\msvc\gsx\view2\polyf2d.h \
	c:\msvc\gsx\view2\matrix.h \
	c:\msvc\gsx\view2\clip.h \
	c:\msvc\gsx\view2\gsxw.h


WORLD_DEP = c:\msvc\gsx\view2\world.h \
	c:\msvc\gsx\view2\polyf2d.h \
	c:\msvc\gsx\view2\matrix.h \
	c:\msvc\gsx\view2\clip.h \
	c:\msvc\gsx\view2\gsxw.h


GSXW_RCDEP = c:\msvc\gsx\view2\gsxw.ico


VIEW2_DEP = c:\msvc\gsx\view2\view.h \
	c:\msvc\gsx\view2\world.h \
	c:\msvc\gsx\view2\polyf2d.h \
	c:\msvc\gsx\view2\matrix.h \
	c:\msvc\gsx\view2\clip.h \
	c:\msvc\gsx\view2\gsxw.h


all:	$(PROJ).EXE $(PROJ).BSC

CLIP.OBJ:	CLIP.CPP $(CLIP_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c CLIP.CPP

GSXW.OBJ:	GSXW.CPP $(GSXW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GSXW.CPP

MATRIX.OBJ:	MATRIX.CPP $(MATRIX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATRIX.CPP

POLYF2D.OBJ:	POLYF2D.CPP $(POLYF2D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c POLYF2D.CPP

VIEW.OBJ:	VIEW.CPP $(VIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEW.CPP

WORLD.OBJ:	WORLD.CPP $(WORLD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WORLD.CPP

GSXW.RES:	GSXW.RC $(GSXW_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r GSXW.RC

VIEW2.OBJ:	VIEW2.CPP $(VIEW2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEW2.CPP


$(PROJ).EXE::	GSXW.RES

$(PROJ).EXE::	CLIP.OBJ GSXW.OBJ MATRIX.OBJ POLYF2D.OBJ VIEW.OBJ WORLD.OBJ VIEW2.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
CLIP.OBJ +
GSXW.OBJ +
MATRIX.OBJ +
POLYF2D.OBJ +
VIEW.OBJ +
WORLD.OBJ +
VIEW2.OBJ +
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
