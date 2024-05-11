
/*----------------------------------------------------------------------------**
** 		Copyright @ 1994 HUJI. All rights reserved.                   **
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
				cext.h
 Purpose : Header file for extensions to and utilities for the C language:
	definition of JPtr, JBool and friends
	Memory Management
	Messages
	Write and Read with Named Files
------------------------------------------------------------------------------*/

#ifndef cext_h
#define cext_h
 
#include <stdio.h>
#include "cext_priv.h"
 
/*----------------------------------------------------------------------------*/
/* types and constants */

#define JPtr   		char *
#define JStr   		char *
#define Julong  	unsigned long
#define Juchar   	unsigned char

#define LINELENGTH	80		

typedef enum { JFalse = 0, JTrue } JBool;

/*----------------------------------------------------------------------------*/
/* conversions and utilities */

#define FToI(f)        ((int)((f)+0.5))
#define JAbs(a)        ((a) > (0) ? (a) : -(a))
#define JMax(a,b)      ((a) > (b) ? (a) : (b))
#define JMin(a,b)      ((a) > (b) ? (b) : (a))

/*----------------------------------------------------------------------------
 return 0, or 1 (2) (3). use the C built-in float comparisons. 
------------------------------------------------------------------------------*/
int     IndexOfMax2f (float a, float b); 
int     IndexOfMax3f (float a, float b, float c); 
int     IndexOfMax4f (float a, float b, float c, float d); 

#define For3(i) for ((i) = 0; (i) < 3; (i)++)
#define For4(i) for ((i) = 0; (i) < 4; (i)++)

/*----------------------------------------------------------------------------*/
/* string macros */

#define JStrIsEq(s1,s2)    (strcmp(s1,s2)==0)
#define JStrIsEmpty(s)     ((s)[0] == '\0')

/*----------------------------------------------------------------------------
 Memory management (argument order: pointer - type - size - message).  
------------------------------------------------------------------------------*/

typedef char ** JPtrPtr;

/*--------------------------------------------------------------------------
  allocates one piece of memory of size size and returns it. 
  if MemPrint is enabled, prints the message m. on failure, returns NULL.
--------------------------------------------------------------------------*/
JPtr  MemAlloc (Julong size, JStr m);

/*--------------------------------------------------------------------------
  frees one piece of memory of size size and returns it. 
  nullifies the pointer *p.
  if MemPrint is enabled, prints the message m. on failure, returns JFalse.
--------------------------------------------------------------------------*/
JBool  MemFree (JPtrPtr p, Julong size, JStr m);

/*--------------------------------------------------------------------------
  allocates newsize bytes, copies the data pointed to by *alloced
  (which was allocated using MemAlloc with size = oldsize) to the
  newly obtained memory, and frees alloced.
  the number of copied bytes is: minimum(newsize, oldsize).
  if MemPrint is enabled, prints m. returns NULL on failure.
--------------------------------------------------------------------------*/
JPtr MemRealloc (JPtr *alloced, Julong oldsize, Julong newsize, JStr m);

/*--------------------------------------------------------------------------
  returns JFalse iff memory pointed to by p, which was allocated using
  MemAlloc with size size, is not ok (ie magic guards are not ok).
--------------------------------------------------------------------------*/
JBool MemIsOk (JPtr p, Julong size);

/*--------------------------------------------------------------------------
  allocated s pieces of memory of type t into p; if MemPrint is enabled,
  prints the message m. returns p. on failure, p is NULL.
--------------------------------------------------------------------------*/
#define  MemA(p,t,s,m)     ((p)=(t*)MemAlloc(sizeof(t)*(s), m))

/*--------------------------------------------------------------------------
  frees s pieces of memory of type t from *p and nullifies *p.
  if MemPrint is enabled, prints the message m. on failure, returns 0.  
  Note that p should contain the ADDRESS of the pointer which points to the 
  allocated storage; use an explicit cast to JPtrPtr. For example, 
	MemF ((JPtrPtr)&pnt_array, Pnt3fRec, 10, "point array");
--------------------------------------------------------------------------*/
#define  MemF(p,t,s,m)     MemFree(p,sizeof(t)*(s),m)

/*--------------------------------------------------------------------------
  reallocates the os (old size) items of data whose type is t and 
  which is pointed to by *op (old pointer) into the new pointer np.
  space for ns new items is allocated. if MemPrint is enabled, m
  is printed. 
  Cast op explicitly to JPtrPtr (see MemF).
--------------------------------------------------------------------------*/
#define  MemRA(np,op,t,os,ns,m) \
		((np)=(t*)MemRealloc(op,sizeof(t)*(os),sizeof(t)*(ns), m))

/*--------------------------------------------------------------------------
  enable (Begin) and disable (End) memory printing when allocating and
  freeing memory.
--------------------------------------------------------------------------*/
void    MemPrintBegin (void); 
void    MemPrintEnd (void); 

/*--------------------------------------------------------------------------
  returns the memory balance: (allocated mem) - (freed mem).
--------------------------------------------------------------------------*/
Julong    MemBalance (void);

/*--------------------------------------------------------------------------
  if mem balance is not zero, prints a "balance not ok" message and
  returns JFalse. 
  should be the last thing a program does before exiting.
--------------------------------------------------------------------------*/
JBool   MemBalanceTest (void); 
 
/*------------------------------------------------------------------------*/
/* Messages */

void Fail (JStr message);
void Bug  (JStr message);
void Message (JStr message);
void Warning (JStr message);

/*--------------------------------------------------------------------------
 if cond is 0, calls Bug with message. Assert(c,m) means "c is supposed
 to be true now; if it isn't, it's a bug".
--------------------------------------------------------------------------*/
void Assert (int cond, JStr message);

/*----------------------------------------------------------------------------
  The function searches the given file for a meaningful line- one   
  that is not all blank, and doesn't start in a comment. The string    
  printed into the output is stripped from comments. If no such string 
  exists in the file, NULL is returned, and the calling function should
  assume that the reading is done.                                     
  A comment starts with the character '#' and extends to the end of the line.
------------------------------------------------------------------------------*/
JStr SkipComment (JStr line, int size, FILE *fp);

/*--------------------------------------------------------------------------
  opens the file name for write and invokes f(p, FILE *). f is a
  function that knows how to write the data pointed to by p into an open file.
  on failure returns 0. otherwise, returns what f returns.
--------------------------------------------------------------------------*/
int WriteNamed (JPtr p, JStr name, int (*f)(JPtr,FILE*));

/*--------------------------------------------------------------------------
  opens the file name for read and invokes f(p, FILE *). f is a
  function that knows how to read the data pointed to by p from an open file.
--------------------------------------------------------------------------*/
int ReadNamed (JPtr p, JStr name, int (*f)(JPtr,FILE*));

#endif 
/*----------------------------------------------------------------------------
				E O F
------------------------------------------------------------------------------*/

