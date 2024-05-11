#include "table.h"

class square;
typedef  square *squareptr;

class square:public baseitem
{
private:
       int data[4];
public:
    square(){};
    ~square(){};
    int OutData(int i)
    {
        if((i<4)&&(i>0)) return data[i-1];
        else return 0;
    }
    void GetData(int i,int newdata)
    {
        if((i<4)&&(i>0))  data[i-1]=newdata;
    }
    int read(FILE *infile)
    {
        int scan_res=fscanf(infile,"%d %d %d %d",&data[0],&data[1],&data[2],&data[3]);
        if(scan_res==4) return 1; else return 0;
    }
    void write(FILE *outfile)
    {
         fprintf(outfile,"%d %d %d %d ",data[0],data[1],data[2],data[3]);
    }
    void relese(){}; /* nothing to relese */

};
