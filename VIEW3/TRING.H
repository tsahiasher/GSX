#ifndef TRING_H_
#define TRING_H_

#include "table.h"

class tring;
typedef tring *tringptr;

class tring:public baseitem
{
private:
       int data[3];
public:
    tring(){};
    ~tring(){};
    int OutData(int i)
    {
        if((i<=3)&&(i>0)) return data[i-1];
        else return -1;
    }
    void GetData(int i,int newdata)
    {
        if((i<=3)&&(i>0))  data[i-1]=newdata;
    }
    int read(FILE *infile)
    {
        int scan_res=fscanf(infile,"%d %d %d",&data[0],&data[1],&data[2]);
        if(scan_res==3) return 1; else return 0;
    }
    void write(FILE *outfile)
    {
         fprintf(outfile,"%d %d %d ",data[0],data[1],data[2]);
    }
    void relese(){}; /* nothing to relese */

    baseitemptr Dup()
    {
        tringptr newtring=new(tring);
        newtring->GetData(1,data[0]);
        newtring->GetData(2,data[1]);
        newtring->GetData(3,data[2]);
        return  (baseitemptr)newtring;

    }

};

#endif
