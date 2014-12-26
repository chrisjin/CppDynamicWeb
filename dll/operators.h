#pragma once
#include<math.h>
#include"doms.h"
#include"domptrs.h"
#include"fileptrs.h"
#include"imageele.h"
#include"stylepool.h"
#define PI 3.141592653
#define DEG (double)(3.141592653/(double)180)

WebObjectPtr operator<<(Container& a,WebObjectPtr b)
{
     a.add(b.pWebObject);     
     return b;       
}
void operator<<(Container& a,BinFilePtr b)
{
     b.pFile->save();
     a.add(b.pFile);          
}
void operator<<(Container& a,TxtFilePtr b)
{
     a.add(b.pFile);          
}
void operator<<(Container& a,ImagePtr b)
{
     b.pFile->save();
     a.add(b.pFile);  
}
void operator<<(Container& a,string b)
{

     a.add(b);      
      
}

typedef  vector<WebObjectPtr> WebObjectPtrs;
typedef  vector<WebObjectPtr>::iterator WebObjectPtrs_itr;

typedef  list<WebObjectPtr> WebObjectPtrs_t;
typedef  list<WebObjectPtr>::iterator WebObjectPtrs_t_itr;


WebObjectPtrs operator+(WebObjectPtr a,WebObjectPtr b)
{
     WebObjectPtrs obs;
     obs.push_back(a);           
     obs.push_back(b); 
     return obs;          
               
}

WebObjectPtrs operator+(string con,WebObjectPtr b)
{
     WebObjectPtrs obs;
     TextPtr textp(con);
     obs.push_back(textp);           
     obs.push_back(b); 
     return obs;          
}

WebObjectPtrs operator+(WebObjectPtr b,string con)
{
     WebObjectPtrs obs;
     TextPtr textp(con);
     obs.push_back(b); 
     obs.push_back(textp); 
     return obs;          
               
}

//---------------------obssssss 

WebObjectPtrs operator+(WebObjectPtrs obs,WebObjectPtr b)
{
     obs.push_back(b);         
     return obs;         
}

WebObjectPtrs operator+(WebObjectPtr b,WebObjectPtrs obs)
{
     obs.insert(obs.begin(), b); 
     return obs;          
}



WebObjectPtrs operator+(string b,WebObjectPtrs obs)
{
     TextPtr textp(b);
     obs.insert(obs.begin(),textp);
     return obs;               
}

WebObjectPtrs operator+(WebObjectPtrs obs,string b)
{
     TextPtr textp(b);
     obs.push_back(textp);
     return obs;               
}


WebObjectPtrs operator+(WebObjectPtrs obs,WebObjectPtrs_t b)
{
     obs.push_back(*b.begin());
     return obs;      
}

WebObjectPtrs operator+(WebObjectPtr a,WebObjectPtrs_t b)
{
     WebObjectPtrs ret;
     ret.push_back(a);
     ret.push_back(*b.begin());
     return ret;      
}

WebObjectPtrs operator+(string a,WebObjectPtrs_t b)
{
     WebObjectPtrs ret;
     TextPtr textp(a);
     ret.push_back(textp);
     ret.push_back(*b.begin());
     return ret;      
}

WebObjectPtrs operator+(WebObjectPtrs_t obs,WebObjectPtrs b)
{
     b.insert(b.begin(),*obs.begin());
     return b;      
}

WebObjectPtrs operator+(WebObjectPtrs_t obs,WebObjectPtr b)
{
     WebObjectPtrs ret;
     ret.push_back(*obs.begin());
     ret.push_back( b);
     return ret;      
}

WebObjectPtrs operator+(WebObjectPtrs_t obs,string b)
{
     WebObjectPtrs ret;
     TextPtr textp(b);
     ret.push_back(*obs.begin());
     ret.push_back(textp);
     return ret;      
}
//---------------------


WebObjectPtrs_t operator<<(WebObjectPtr a,WebObjectPtr b)
{
     WebObjectPtrs_t ret;
     ret.push_back( a);
     ret.push_back( b);     
     a.pWebObject->add( b.pWebObject); 
     return ret;       
}

WebObjectPtrs_t operator<<(WebObjectPtr a,string b)
{
     WebObjectPtrs_t ret;
     ret.push_back(  a);
     TextPtr textp(b);
     ret.push_back(textp); 
     a.pWebObject->add(textp.pWebObject);     
     return ret;       
}

WebObjectPtrs_t operator<<(WebObjectPtr a,WebObjectPtrs b)
{
     WebObjectPtrs_t ret;
     ret.push_back(a);
     ret.push_back(*(b.end()-1));
     for(WebObjectPtrs_itr itr=b.begin();itr!=b.end();itr++)
       a.add((*itr)); 
     return ret;       
}

WebObjectPtrs_t operator<<(WebObjectPtrs_t a,string b)
{
     TextPtr textp(b);
     (--a.end())->pWebObject->add(textp.pWebObject);
     *(--a.end())=textp;
   
     return a;       
}

WebObjectPtrs_t operator<<(WebObjectPtrs_t a,WebObjectPtr b)
{
 
     (--a.end())->pWebObject->add(b.pWebObject);
     *(--a.end())=b;
   
     return a;       
}

WebObjectPtrs_t operator<<(WebObjectPtrs_t a,WebObjectPtrs b)
{
     
     for(WebObjectPtrs_itr itr=b.begin();itr!=b.end();itr++)
       (--a.end())->pWebObject->add(itr->pWebObject);  
     *(--a.end())=*(--b.end()); 
     return a;       
}

WebObjectPtr operator%(WebObjectPtr a,Style b)
{
     a.useStyle(b);
     return a;        
}

WebObjectPtrs operator%(WebObjectPtrs a,Style b)
{
     for(WebObjectPtrs_itr itr=a.begin();itr!=a.end();itr++)
       (*itr).useStyle(b); 
     return a;        
}

WebObjectPtr operator%(Style b,WebObjectPtr a)
{
     a.useStyle(b);
     return a;        
}

WebObjectPtrs operator%(Style b,WebObjectPtrs a)
{
     for(WebObjectPtrs_itr itr=a.begin();itr!=a.end();itr++)
       (*itr).useStyle(b); 
     return a;        
}

struct _Attr
{
  _Attr(string aa,string bb)
  {
     a=aa;
     b=bb;
  }
  string a;
  string b;     
};
_Attr Attr(string a,string b)
{
    _Attr ret(a,b);
    return ret;      
}

WebObjectPtr operator%(WebObjectPtr a,_Attr b)
{
     a.addProperty(b.a,b.b);
     return a;        
}

WebObjectPtrs operator%(WebObjectPtrs a,_Attr b)
{
     for(WebObjectPtrs_itr itr=a.begin();itr!=a.end();itr++)
       (*itr).addProperty(b.a,b.b); 
     return a;        
}

WebObjectPtr operator%(_Attr b,WebObjectPtr a)
{
     a.addProperty(b.a,b.b);
     return a;        
}

WebObjectPtrs operator%(_Attr b,WebObjectPtrs a)
{
     for(WebObjectPtrs_itr itr=a.begin();itr!=a.end();itr++)
       (*itr).addProperty(b.a,b.b); 
     return a;        
}

ImagePtr operator<<(ImagePtr a,_RGB *r)
{  
     a.pFile->setColor(r);  
     return a;   
}
ImagePtr operator<<(ImagePtr a,_RGB r)
{  
     a.pFile->setColor(&r);  
     return a;   
}

void operator<<(ImagePtr a,ImageEle *ob)
{
     
     switch(ob->getType())
     {
       case IM_POINT:
           (*a.pFile)(((Point *)ob)->x,((Point *)ob)->y)[FI_RGBA_GREEN]=a.pFile->CurrentClr.g;
           (*a.pFile)(((Point *)ob)->x,((Point *)ob)->y)[FI_RGBA_RED]=a.pFile->CurrentClr.r;
           (*a.pFile)(((Point *)ob)->x,((Point *)ob)->y)[FI_RGBA_BLUE]=a.pFile->CurrentClr.b;
           break;
       case IM_LINE:
           (*a.pFile).putLine(((Line*)ob)->p1.x,((Line*)ob)->p1.y,((Line*)ob)->p2.x,((Line*)ob)->p2.y,&a.pFile->CurrentClr);
           break;                   
                        
     }   
}
void operator<<(ImagePtr a,Point ob)
{
    (*a.pFile)(ob.x,ob.y)[FI_RGBA_GREEN]=a.pFile->CurrentClr.g;
    (*a.pFile)(ob.x,ob.y)[FI_RGBA_RED]=a.pFile->CurrentClr.r;
    (*a.pFile)(ob.x,ob.y)[FI_RGBA_BLUE]=a.pFile->CurrentClr.b;
}

void operator<<(ImagePtr a,Line ob)
{
    a.pFile->putLine(ob.p1.x,ob.p1.y,ob.p2.x,ob.p2.y,&a.pFile->CurrentClr); 
     
}

void operator<<(ImagePtr a,Rect ob)
{
    if(!ob.isfill)
    a.pFile->putRect(ob.b,ob.size);
    else
    {
    for(int x=ob.b.x;x<ob.b.x+ob.size.x;x++)
      for(int y=ob.b.y;y<ob.b.y+ob.size.y;y++)
        FreeImage_SetPixelColor(a.pFile->hImage,x,y,(RGBQUAD *)&a.pFile->CurrentClr);
    } 
     
}
void operator<<(ImagePtr a,Circle ob)
{
    for(int i=0;i<ob.gran;i++)
    {
        FreeImage_SetPixelColor(a.pFile->hImage,
                               (int)((double)ob.org.x+(double)ob.r*cos(DEG*i)),
                               (int)((double)ob.org.y+(double)ob.r*sin(DEG*i)),
                               (RGBQUAD *)&a.pFile->CurrentClr) ;   
            
    } 
     
}

