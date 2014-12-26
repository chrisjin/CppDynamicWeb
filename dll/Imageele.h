#pragma once
#include<windows.h>
#include<string>
using namespace std;
class Point;
class _RGB
{
   public:
         _RGB(){};
         _RGB(BYTE rr,BYTE gg,BYTE bb)
         {
           r=rr;
           g=gg;
           b=bb;         
         }
         BYTE b;
         BYTE g;
         BYTE r;   
 
};
enum ImageEleEnum{IM_POINT,IM_LINE};
class ImageEle
{
    public:
    ImageEleEnum Type;
    ImageEleEnum getType()
    {
        return Type; 
    }
};

class Point:public ImageEle
{
  public:
  int x;
  int y;
   
  Point(){Type=IM_POINT;}
  Point(int xx,int yy)
  {
    x=xx;
    y=yy;
    Type= IM_LINE;         
  }    
};
class Line:public ImageEle
{
  public:
  Point p1;
  Point p2;
  Line(){Type=IM_LINE;}
  Line(Point *x1,Point *x2)
  {
     Type=IM_LINE;
     p1=*x1;
     p2=*x2;          
  }
  Line(Point x1,Point x2)
  {
     Type=IM_LINE;
     p1=x1;
     p2=x2;          
  }
  Line(int a,int b,int c,int d)
  {
     Type=IM_LINE;
     p1.x=a;
     p1.y=b;
     p2.x=c;
     p2.y=d;
  }      
};
class Rect:public ImageEle
{
  public:
     Point b;
     Point size;
     bool isfill;
     Rect(Point ab,Point asize,bool aisfill=0)
     {
        b=ab;
        isfill=aisfill;
        size=asize;        
     }    
};
class Circle:public ImageEle
{
  public:
     
     int r;
     Point org;
     bool isfill;
     int gran;
     Circle(Point aor,int rr,int agra=180,bool aisfill=0)
     {
        org=aor;
        isfill=aisfill;
        r=rr; 
        gran= agra;      
     }    
};
Line L(int a,int b,int c,int d)
{
  Line k(a,b,c,d);
  return k;   
}
Line L(Point a,Point b)
{
  Line k(a,b);
  return k;   
}
Rect R(Point a,Point b,bool aisfill=0)
{
  Rect k(a,b,aisfill);
  return k;   
}
Point P(int x,int y)
{
  Point k(x,y);
  return k;    
}
_RGB C(int a,int b,int c)
{
  _RGB k(a,b,c);
  return k;   
}
Circle CC(Point org,int r)
{
   Circle k(org,r);
   return k;       
}
