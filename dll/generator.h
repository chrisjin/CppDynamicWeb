#pragma once
#include"doms.h"
#include"domptrs.h"
#include"files.h"
#include"fileptrs.h"
#include"stylepool.h"
//#include"css.h" 
#include<string>

#define GeneFactoryFunc(type,argtype) \
  type##Ptr type(argtype a)\
{\
    type##Ptr p(a);\
    if(p.pWebObject->TagName=="HTML")\
    Page.push_back(p.pWebObject);\
    Pool.push_back(p.pWebObject);\
    return p;\
}

#define GeneFactoryFuncWithTwoArg(type,argtype1,argtype2) \
  type##Ptr type(argtype1 a,argtype2 b)\
{\
    type##Ptr p(a,b);\
    if(p.pWebObject->TagName=="HTML")\
    Page.push_back(p.pWebObject);\
    Pool.push_back(p.pWebObject);\
    return p;\
}

#define GeneFactoryFuncWithnoArg(type) \
type##Ptr type()\
{\
    type##Ptr p;\
    if(p.pWebObject->TagName=="HTML")\
    Page.push_back(p.pWebObject);\
    Pool.push_back(p.pWebObject);\
    return p;\
}


class Generator
{
     public:

        typedef BinFilePtr _BinFile;
        typedef ImagePtr _Image;
        Generator(){}
         
};
class DomsGenerator:public Generator
{
     public:
      vector<__WebObject *> Pool; 
      vector<__WebObject *> Page; 
      GeneFactoryFuncWithnoArg(Button)
      GeneFactoryFunc(Button,string)
      GeneFactoryFuncWithnoArg(Form)
      GeneFactoryFuncWithnoArg(Div)  
      GeneFactoryFuncWithnoArg(Html)      
      GeneFactoryFuncWithnoArg(Table) 
      GeneFactoryFunc(Img,string)
      GeneFactoryFunc(Ling,string)
      GeneFactoryFunc(Input,string)
      GeneFactoryFunc(Text,string)
      GeneFactoryFuncWithTwoArg(Link,string,string)
      string CurrentCSS;
      bool isCSS;
      DomsGenerator()
      {
          isCSS=0; 
          CurrentCSS="";           
      }
      void destroy()
      {
         for(vector<__WebObject *>::iterator itr=Pool.begin();itr!=Pool.end();itr++)
         {
           delete *itr  ;              
         }     
      }
      
};
class FilesGenerator:public Generator
{
      public:
      vector<__File *> Pool; 
      _BinFile BinFile()
      {
         BinFilePtr p;
         Pool.push_back(p.pFile); 
         return p;          
      }
      _Image Image(int x,int y,int d=24)
      {
         ImagePtr p(x,y,d); 
         Pool.push_back(p.pFile); 
         return p;   
              
      }
      _Image Image(string name)
      {
         _Image p(name); 
         Pool.push_back(p.pFile); 
         return p;      
      }
      void destroy()
      {
         for(vector<__File *>::iterator itr=Pool.begin();itr!=Pool.end();itr++)
         {
           delete *itr  ;              
         }     
      }
};
class CSSGenerator:public Generator
{
      public:
       int CSSNo;
       CSSGenerator()
       {
            CSSNo=0;         
       }
       Style CSS(string a,string b)
       {
           Style st(a,b);
           return st;  
       }
       Style CSS(string b)
       {
           Style st(S(".INNERENCODE")+I2S(CSSNo),b);
           CSSNo++;
           return st;   
       }
       Style operator()(string a,string b)
       {
           return CSS(a,b);      
       }
       Style operator()(string b)
       {
           return CSS(b);      
       }
      
};


