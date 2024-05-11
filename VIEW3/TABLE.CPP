#include "table.h"

int table::AddItem(baseitemptr newitem)
{
    if((data=(baseitemptr *)realloc((void *)data,(size+1)*sizeof(baseitemptr)))==NULL)   return 0;
    size++;
    data[size-1]=newitem;
    return 1;
};

void table::relese()
{
    for(int i=0;i<size;i++)
    {
        data[i]->relese();
    }
    free(data);
    size=0;
};

int table::ForEach(PCALLBACK func)
{
    int res=1,i=0;
    while((res!=0)&&(i<size))
    {
        res=func(data[i]);
        i++;
    }
    return i;
};

int table::ForEachp(PCALLBACK2 func,void *ptr)
{
    int res=1,i=0;
    while((res!=0)&&(i<size))
    {
        res=func(data[i],ptr);
        i++;
    }
    return i;
};

void table::WriteAll(FILE *f)
{
    fprintf(f,"%d ",size);
    for(int i=0;i<size;i++)
    {
        data[i]->write(f);
    }
}
tableptr table::Dup()
{
    tableptr newtable=new(table);
    baseitemptr item;
    for(int i=0;i<size;i++)
    {
        item=data[i]->Dup();
        newtable->AddItem(item);
    }
    return newtable;
}


