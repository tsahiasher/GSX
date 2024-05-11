# Microsoft Visual C++ generated build script - Do not modify

PROJ = WVIEW3
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = name.scn -v name.viw
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\MSVC\GSX\VIEW3\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = AFF3F.CPP   
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /FR /GA /Fd"WVIEW3.PDB"
CFLAGS_R_WEXE = /nologo /W3 /AL /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:65500 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw llibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw llibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo /k
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
SBRS = AFF3F.SBR \
		CEXT.SBR \
		CLIP.SBR \
		COMPARIS.SBR \
		DIR3F.SBR \
		EPSILON.SBR \
		GEO.SBR \
		MAIN.SBR \
		MATRIX.SBR \
		PHED3D.SBR \
		PNT3F.SBR \
		SCR_MAT.SBR \
		SQUARE.SBR \
		TABLE.SBR \
		TPNT3F.SBR \
		VEC2F.SBR \
		VEC3F.SBR \
		VEC4F.SBR \
		VIEW3.SBR \
		WORLD.SBR \
		GSXW.SBR


AFF3F_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\vec4f.h \
	c:\msvc\gsx\view3\vec4f.t \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\dir3f.h \
	c:\msvc\gsx\view3\dir_basi.h \
	c:\msvc\gsx\view3\aff3f_pr.h \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\aff_basi.h \
	c:\msvc\gsx\view3\aff3f.h


CEXT_DEP = c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h


CLIP_DEP = c:\msvc\gsx\view3\clip.h \
	c:\msvc\gsx\view3\gsxw.h


COMPARIS_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h


DIR3F_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\dir3f.h \
	c:\msvc\gsx\view3\dir_basi.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t


EPSILON_DEP = c:\msvc\gsx\view3\epsilon.h


GEO_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h


MAIN_DEP = c:\msvc\gsx\view3\view3.h \
	c:\msvc\gsx\view3\scr_mat.h \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\tpnt3f.h \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\table.h \
	c:\msvc\gsx\view3\world.h \
	c:\msvc\gsx\view3\phed3d.h \
	c:\msvc\gsx\view3\tring.h \
	c:\msvc\gsx\view3\square.h \
	c:\msvc\gsx\view3\gsxw.h


MATRIX_DEP = c:\msvc\gsx\view3\matrix.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\pnt_basi.h


PHED3D_DEP = c:\msvc\gsx\view3\phed3d.h \
	c:\msvc\gsx\view3\scr_mat.h \
	c:\msvc\gsx\view3\table.h \
	c:\msvc\gsx\view3\tring.h \
	c:\msvc\gsx\view3\square.h \
	c:\msvc\gsx\view3\tpnt3f.h \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\gsxw.h


PNT3F_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\pnt2f.t


SCR_MAT_DEP = c:\msvc\gsx\view3\scr_mat.h \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\tpnt3f.h \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\table.h \
	c:\msvc\gsx\view3\dir3f.h \
	c:\msvc\gsx\view3\dir_basi.h


SQUARE_DEP = c:\msvc\gsx\view3\table.h


TABLE_DEP = c:\msvc\gsx\view3\table.h


TPNT3F_DEP = c:\msvc\gsx\view3\tpnt3f.h \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\table.h


VEC2F_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec2f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t


VEC3F_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\vec2f.h \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\dir3f.h \
	c:\msvc\gsx\view3\dir_basi.h


VEC4F_DEP = c:\msvc\gsx\view3\comparis.h \
	c:\msvc\gsx\view3\epsilon.h \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\cext_pri.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\vec4f.h \
	c:\msvc\gsx\view3\vec4f.t


VIEW3_DEP = c:\msvc\gsx\view3\view3.h \
	c:\msvc\gsx\view3\scr_mat.h \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\tpnt3f.h \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\table.h \
	c:\msvc\gsx\view3\dir3f.h \
	c:\msvc\gsx\view3\dir_basi.h \
	c:\msvc\gsx\view3\epsilon.h


WORLD_DEP = c:\msvc\gsx\view3\world.h \
	c:\msvc\gsx\view3\phed3d.h \
	c:\msvc\gsx\view3\scr_mat.h \
	c:\msvc\gsx\view3\table.h \
	c:\msvc\gsx\view3\tring.h \
	c:\msvc\gsx\view3\square.h \
	c:\msvc\gsx\view3\tpnt3f.h \
	c:\msvc\gsx\view3\aff3f.h \
	c:\msvc\gsx\view3\vec3f.t \
	c:\msvc\gsx\view3\pnt3f.t \
	c:\msvc\gsx\view3\dir3f.t \
	c:\msvc\gsx\view3\aff3f.t \
	c:\msvc\gsx\view3\cext.h \
	c:\msvc\gsx\view3\geo.h \
	c:\msvc\gsx\view3\vec3f.h \
	c:\msvc\gsx\view3\vec_basi.h \
	c:\msvc\gsx\view3\vec2f.t \
	c:\msvc\gsx\view3\pnt3f.h \
	c:\msvc\gsx\view3\pnt_basi.h \
	c:\msvc\gsx\view3\pnt2f.t \
	c:\msvc\gsx\view3\view3.h


GSXW_DEP = c:\msvc\gsx\view3\gsxw.h


GSXW_RCDEP = c:\msvc\gsx\view3\gsxw.ico


all:	$(PROJ).EXE $(PROJ).BSC

AFF3F.OBJ:	AFF3F.CPP $(AFF3F_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c AFF3F.CPP

CEXT.OBJ:	CEXT.CPP $(CEXT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CEXT.CPP

CLIP.OBJ:	CLIP.CPP $(CLIP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLIP.CPP

COMPARIS.OBJ:	COMPARIS.CPP $(COMPARIS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMPARIS.CPP

DIR3F.OBJ:	DIR3F.CPP $(DIR3F_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DIR3F.CPP

EPSILON.OBJ:	EPSILON.CPP $(EPSILON_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EPSILON.CPP

GEO.OBJ:	GEO.CPP $(GEO_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GEO.CPP

MAIN.OBJ:	MAIN.CPP $(MAIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAIN.CPP

MATRIX.OBJ:	MATRIX.CPP $(MATRIX_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATRIX.CPP

PHED3D.OBJ:	PHED3D.CPP $(PHED3D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PHED3D.CPP

PNT3F.OBJ:	PNT3F.CPP $(PNT3F_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PNT3F.CPP

SCR_MAT.OBJ:	SCR_MAT.CPP $(SCR_MAT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SCR_MAT.CPP

SQUARE.OBJ:	SQUARE.CPP $(SQUARE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SQUARE.CPP

TABLE.OBJ:	TABLE.CPP $(TABLE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TABLE.CPP

TPNT3F.OBJ:	TPNT3F.CPP $(TPNT3F_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TPNT3F.CPP

VEC2F.OBJ:	VEC2F.CPP $(VEC2F_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VEC2F.CPP

VEC3F.OBJ:	VEC3F.CPP $(VEC3F_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VEC3F.CPP

VEC4F.OBJ:	VEC4F.CPP $(VEC4F_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VEC4F.CPP

VIEW3.OBJ:	VIEW3.CPP $(VIEW3_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c VIEW3.CPP

WORLD.OBJ:	WORLD.CPP $(WORLD_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c WORLD.CPP

GSXW.OBJ:	GSXW.CPP $(GSXW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c GSXW.CPP

GSXW.RES:	GSXW.RC $(GSXW_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r GSXW.RC


$(PROJ).EXE::	GSXW.RES

$(PROJ).EXE::	AFF3F.OBJ CEXT.OBJ CLIP.OBJ COMPARIS.OBJ DIR3F.OBJ EPSILON.OBJ GEO.OBJ \
	MAIN.OBJ MATRIX.OBJ PHED3D.OBJ PNT3F.OBJ SCR_MAT.OBJ SQUARE.OBJ TABLE.OBJ TPNT3F.OBJ \
	VEC2F.OBJ VEC3F.OBJ VEC4F.OBJ VIEW3.OBJ WORLD.OBJ GSXW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
AFF3F.OBJ +
CEXT.OBJ +
CLIP.OBJ +
COMPARIS.OBJ +
DIR3F.OBJ +
EPSILON.OBJ +
GEO.OBJ +
MAIN.OBJ +
MATRIX.OBJ +
PHED3D.OBJ +
PNT3F.OBJ +
SCR_MAT.OBJ +
SQUARE.OBJ +
TABLE.OBJ +
TPNT3F.OBJ +
VEC2F.OBJ +
VEC3F.OBJ +
VEC4F.OBJ +
VIEW3.OBJ +
WORLD.OBJ +
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
