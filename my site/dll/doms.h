#pragma once
#include<map>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include"windows.h"
using namespace std;
string S(char *a)
{
   string re(a);
   return re;       
}
string I2S(int a)
{
   stringstream t;
   string re;
   t<<a;
   t>>re;
   return re;
}
int dom_num=0;
class WebObject
{
     public:
         string TagName;
         string ID; 
         string BegHtml;
         string EndHtml;
         string InnerHtml;
         string FullHtml;
         vector<WebObject *> InnerObject;
         map<string,string> Properties;
         map<string,WebObject *> Doms;
         
         vector<WebObject *>::iterator InnerObject_itr;
         map<string,string>::iterator Properties_itr;
         map<string,WebObject *>::iterator Doms_itr;
         
         
         WebObject *parent;
         WebObject()
         {
           InnerHtml=TagName=ID=BegHtml=EndHtml="";
           parent=NULL;
           calflag=0;
         }
         void init(string tagname)
         {
            //  ID=tagname+I2S(dom_num);
         }
         bool add(WebObject *s)
         {
              if(s->parent!=NULL)return 0;
              s->parent=this;
              InnerObject.push_back(s);
              calflag=1;
              return 1;
         }
         void write(char *a);
         int  integrateHtml(WebObject *a)
         {
              calflag=0;
              integrateBegHtml(a);
              FullHtml+=a->BegHtml; 
              Doms.insert(pair<string,WebObject *>(a->ID,a));  
              for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr<a->InnerObject.end();a->InnerObject_itr++)
                 integrateHtml(*a->InnerObject_itr);
              FullHtml+=a->EndHtml; 
             // FullHtml+="\n";
         }
         int  integrateDoms(WebObject *a)
         {
              Doms.insert(pair<string,WebObject *>(a->ID,a));  
              for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr!=a->InnerObject.end();a->InnerObject_itr++)
                 integrateDoms(*a->InnerObject_itr); 
         }
         int  integrateBegHtml(WebObject *a)
         {
              if(a->TagName=="Text")return 1;
              string tmp="";
              for(Properties_itr=a->Properties.begin();Properties_itr!=a->Properties.end();Properties_itr++)
              tmp+=(Properties_itr->first+S("=")+"\""+Properties_itr->second+"\""+" ");
              if(a->ID.length()>0)
              a->BegHtml=S("<")+a->TagName+S(" id=")+S("\"")+a->ID+S("\"")+S(" ")+tmp+">";
              else
              a->BegHtml=S("<")+a->TagName+S(" ")+tmp+">";
         }
         int calflag;
         string getHtml()
         {
              if(calflag)
              integrateHtml(this);
              return FullHtml;
         }
         void addProperty(string a,string b)
         {
              Properties.insert(pair<string,string>(a,b));  
         }
};

class Text:public WebObject
{
      public :
      Text(char *text)
      {
           TagName="Text";
           BegHtml=text;
           EndHtml="";
      }
      
};
void WebObject::write(char *t)
{
     add(new Text(t));
}

static int tmp_button_id=0;
class Button:public WebObject
{
    public :
      Button()
      {
           TagName="BUTTON";
           ID=S("BUTTON")+I2S(tmp_button_id);
           tmp_button_id++;
           BegHtml="<BUTTON id="+S("\"")+ID+S("\"")+">";
           EndHtml="</BUTTON>";
           
      }
};

static int tmp_div_id=0;
class Div:public WebObject
{
    public :
      Div()
      {
          TagName="DIV";
          ID=S("DIV")+I2S(tmp_div_id);
          tmp_div_id++;
          BegHtml="<DIV id="+S("\"")+ID+S("\"")+">";
          EndHtml="</DIV>";
      }
};

static int tmp_img_id=0;
class Img:public WebObject
{
    public:
      string SrcURI;
      Img(char *srcuri="mmmm")
      {
           TagName="IMG";
           ID=S("IMG")+I2S(tmp_img_id);
           tmp_img_id++;
           BegHtml="<IMG id="+S("\"")+ID+S("\"")+">";
           EndHtml="";
           addProperty("src",srcuri);
           SrcURI=srcuri;
      }
};


static int tmp_link_id=0;
class Link:public WebObject
{
      public:
      Link(char *href,char *innerhtml="link")
      {
          TagName="A";  
          ID=S("A")+I2S(tmp_link_id);
          tmp_link_id++;
          BegHtml="<A id="+S("\"")+ID+S("\"")+">";
          EndHtml="</A>";  
          addProperty("href",href); 
          InnerHtml=S(innerhtml) ;
                
      }        
      
};

class Body:public WebObject
{
      public :
      Body()
      {
           TagName="BODY";
           BegHtml="<BODY>";
           EndHtml="</BODY>";
           
      }
};

class Head:public WebObject
{
      public :
      Head()
      {
           TagName="Head";
           ID=S("Head")+I2S(0);
           BegHtml="<HEAD>";
           EndHtml="</HEAD>";
           
      }
};

class Script:public WebObject
{
      public :
      Script(char* type)
      {
           TagName="SCRIPT";
           BegHtml="<SCRIPT type=\"text/"+S(type)+"\""+">";
           EndHtml="</SCRIPT>";
           
      } 
      
};

class Html:public WebObject
{
      public :
      Head PageHead;
      Body PageBody; 
      Html()
      {
           TagName="Html";
           BegHtml="<HTML>";
           EndHtml="</HTML>";
           add(&PageHead);
           add(&PageBody);

      }
      void add2Bo(WebObject *a) 
      {
           PageBody.add(a);
      }
      void add2He(WebObject *a) 
      {
           PageHead.add(a);
      }
 //     string operator
      
};

//class Html:public WebObject
