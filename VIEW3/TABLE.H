#ifndef _table_
#define _table_

#include <malloc.h>
#include<stdio.h>
//#include <stdarg.h>

class baseitem;
typedef baseitem *baseitemptr;

class baseitem
{
public:
    baseitem(){};
    void write(FILE *outfile){};
    void relese(){};
    int read(FILE *infile){return 0;};
    baseitemptr Dup(){return NULL;};
};

// A pointer to a callback function
typedef int (CALLBACK) (baseitemptr b);
typedef int (CALLBACK2) (baseitemptr b,void *ptr);

typedef CALLBACK * PCALLBACK;
typedef CALLBACK2 * PCALLBACK2;

class table;
typedef table *tableptr;


class table
{
private:
        int size;
        baseitemptr *data;
public:
       table()
       {
           size=0;
           data=(baseitemptr *)malloc(sizeof(baseitemptr)); // initaling to one cell
       };
       ~table(){};
       int Size(){return size;};
       baseitemptr Item(int i)
       {
            if (i<=size) return data[i-1];
            else return NULL;
       }
       void relese();
       int AddItem(baseitemptr newitem);
       int ForEach(PCALLBACK func);
       int ForEachp(PCALLBACK2 func,void *ptr);
       void WriteAll(FILE *f);
       tableptr Dup();
       void Dispose();

};

#endif
