
/*----------------------------------------------------------------------------**
**              Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                cext.c
Purpose : extensions to the C language.
------------------------------------------------------------------------------*/
 
#include <malloc.h>
#include <memory.h> /* memcpy */
 
#include <stdlib.h> /* for exit */
#include <string.h>
#include <stdio.h>

#include "cext.h"
 
/*----------------------------------------------------------------------------*/
#define _MEMPRINT   /* printfs memory allocation descriptions */

#define MEMTEST     /* test memory allocate/free consistency  */
#define MAGIC0 'x'
#define MAGIC1 'z'
#define MAGIC2 'v'
#define MAGIC3 'q'
 
#define SAFE_WORD 8 /* 4 didn't work on gronich, 1992 */

/*----------------------------------------------------------------------------*/
static Julong alloced_mem = 0;
static Julong mem_print = 0;
static char tmpstr[100];
 
/*----------------------------------------------------------------------------*/
void MemPrintBegin (void) 
{ 
	mem_print = 1; 
}

/*----------------------------------------------------------------------------*/
void MemPrintEnd (void) 
{ 
	mem_print = 0; 
}

/*----------------------------------------------------------------------------*/
Julong MemBalance(void)
{
	return alloced_mem;
}
 
/*----------------------------------------------------------------------------*/
JBool  MemBalanceTest(void)
{
	Julong m;

	if ((m=MemBalance()) != 0) {
		sprintf (tmpstr, "memory balance (%ld) not ok.", m);
		Bug (tmpstr);
		return JFalse;
	}
	Message ("memory balance ok.");
	return JTrue;
}

/*----------------------------------------------------------------------------*/
JPtr MemRealloc (JPtrPtr alloced, Julong oldsize, Julong newsize, JStr desc)
{
	int minn;
	char *nnew = MemAlloc (newsize, desc);

	if (nnew == NULL){
		sprintf (tmpstr, "Not enough memory for %s", desc);
		Warning (tmpstr);
		return NULL;
	}

	minn = JMin (oldsize, newsize);
	memcpy (nnew, *alloced, minn);

	sprintf (tmpstr, "Freeing %s in Realloc", desc);
	if (MemFree (alloced, oldsize, desc) == 0){
		sprintf (tmpstr, "MemFree fail for %s", desc);
		Bug (tmpstr);
		return NULL;
	}
	return nnew;
}

/*----------------------------------------------------------------------------*/
JPtr MemAlloc (Julong size, JStr desc)
{
#ifdef MEMTEST
	char *p = (char *)malloc (size + SAFE_WORD*2);
#else
	char *p = (char *)malloc (size);
#endif

	if (p == NULL){
		sprintf (tmpstr, "Not enough memory for %s", desc);
		Warning (tmpstr);
		return NULL;
	}
 
#ifdef MEMTEST
	*(p)        = MAGIC0;
	*(p+1)      = MAGIC1;
	*(p+SAFE_WORD+size) = MAGIC2;
	*(p+SAFE_WORD+1+size) = MAGIC3;
#endif
	alloced_mem += size;
 
	if (mem_print)
		fprintf (stderr, "+ %ld = %ld : %s\n", size, alloced_mem, desc);
 
#ifdef MEMTEST
	return (JPtr) (p+SAFE_WORD);
#else
	return (JPtr) p;
#endif 
}
 
/*----------------------------------------------------------------------------*/
JBool MemIsOk (JPtr p, Julong size)
{
	char *cp = (char *)p;
	if (cp == NULL)
		return JFalse;
#ifdef MEMTEST
	if ( *(cp-SAFE_WORD) != MAGIC0 || *(cp-SAFE_WORD+1) != MAGIC1
		|| *(cp+size) != MAGIC2 || *(cp+size+1) != MAGIC3)
		return JFalse;
	else
		return JTrue;
#else
	return JFalse; 
       /* this function should not be called at all when MEMTEST isnt defined */ 
#endif 
}

/*----------------------------------------------------------------------------*/
JBool MemFree (JPtrPtr p, Julong size, JStr desc)
{
	JPtr  pointer = *p;
	char *cp = (char *)pointer;

	*p = NULL;
	if (cp == NULL)
		return JTrue;

#ifdef MEMTEST
	if ( *(cp-SAFE_WORD) != MAGIC0 || *(cp-SAFE_WORD+1) != MAGIC1
		|| *(cp+size) != MAGIC2 || *(cp+size+1) != MAGIC3)
	{
		sprintf (tmpstr, "Mem corrupted (for %s)", desc);
		Bug (tmpstr);
		return JFalse;
	}
#endif 
	alloced_mem -= size;

	if (mem_print)
		fprintf(stderr, "- %ld = %ld: %s\n", size, alloced_mem, desc);
 
#ifdef MEMTEST
	free(cp-SAFE_WORD); 
#else
	free(cp);
#endif
	return JTrue;
}
 
/*----------------------------------------------------------------------------*/
void Fail (JStr message)
{
	fprintf (stderr, "Fatal error: %s\n", message);
	fflush (stderr);
	exit (1);
}
 
/*----------------------------------------------------------------------------*/
void Bug (JStr message)
{
/*
	fprintf (stderr, "Bug:%c %s\n", 7, message);
*/
	fprintf (stderr, "Bug:%s\n", message);
	/* 7 is for beeping */
	/* >>> sb controlled by BugBeepBegin/End */
	fflush (stderr);
}
 
/*----------------------------------------------------------------------------*/
void Warning (JStr message)
{
/*
	fprintf (stderr, "Warning:%c %s\n", 7, message);
*/
	fprintf (stderr, "Warning:%s\n", message);
	fflush (stderr);
}
 
/*----------------------------------------------------------------------------*/
void Message (JStr message)
{
	fprintf (stderr, "%s\n", message);
	fflush (stderr);
}
 
/*----------------------------------------------------------------------------*/
void Assert (int cond, char *message)
{
	if (!cond) Bug(message);
}
 
/*----------------------------------------------------------------------------*/ 
JStr SkipComment(JStr line, int size, FILE *fp)
{
	int pos;

	while (fgets (line, size, fp)) {
		pos = strspn (line, "\t\n "); /* pos of first  non-whitespace */
                                   	      /* check if first non-whitespace
                                   	       character is NOT a # or a NULL */
		if (!(pos==strlen (line) || line[pos]=='#'))
			return (strtok (&line[pos], "#"));
	}
	return (NULL);
}

/*----------------------------------------------------------------------------*/
int WriteNamed (JPtr p, JStr name, int (*f)(JPtr,FILE*))
{
	FILE *fp = fopen (name, "w");
	int res;

	if (fp == NULL)
		return 0;
	else
		res = f (p, fp);
	fclose (fp);
	return (res);
}

/*----------------------------------------------------------------------------*/
int ReadNamed (JPtr p, JStr name, int (*f)(JPtr,FILE*))
{
	FILE *fp = fopen (name, "r");
	int res;

	if (fp == NULL)
		return 0;
	else
		res = f (p, fp);
	fclose (fp);
	return (res);
}

/*----------------------------------------------------------------------------*/
int IndexOfMax2f (float a, float b)
{ 
	if (a > b)
		return (0);
	return (1);
}

/*----------------------------------------------------------------------------*/
int IndexOfMax3f (float a, float b, float c)
{ 
	if (a > b)
		if (a > c)
			return (0); 
		else 
			return (2); 
	else 
		if (b > c)
			return (1); 
		else 
			return (2);
}

/*----------------------------------------------------------------------------*/
int IndexOfMax4f (float a, float b, float c, float d)
{ 
	
	int i;

	i = IndexOfMax3f (a, b, c);
	switch (i){
		case 0:
			return ( a > d ? 0 : 3 );
		case 1:
			return ( b > d ? 1 : 3 );
		case 2:
			return ( c > d ? 2 : 3 );
	}
	return (0);
}

/*----------------------------------------------------------------------------
                                E O F
------------------------------------------------------------------------------*/

