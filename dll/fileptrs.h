#pragma once
#include"files.h"
class FilePtr
{
 
};
class BinFilePtr:public FilePtr
{
     public:
     __BinFile *pFile;
     BinFilePtr()
     {
        pFile=new __BinFile;         
                 
     } 
      
};
class ImagePtr:public BinFilePtr
{
     public:
     __Image *pFile;
     ImagePtr(int x,int y,int depth=24) 
     {
       pFile=new __Image(x,y,depth); 
     }
     ImagePtr(string name)
     {
       pFile=new __Image(name);
     }
     string toURI()
     {
       return pFile->toURI();      
     }
      
};
class TxtFilePtr:public FilePtr
{
     public:
     __TxtFile *pFile;
     TxtFilePtr(string a){pFile=new __TxtFile(a);}
     TxtFilePtr(){pFile=new __TxtFile;}
     TxtFilePtr(FILE *fp){pFile=new __TxtFile(fp);}
     void load(string a) 
     {
        pFile->load(a); 
     }
      
};
