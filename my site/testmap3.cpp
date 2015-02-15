#include<map>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
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
         map<string,WebObject *> InnerObject;
         map<string,string> Properties;
         map<string,WebObject *> Doms;
         
         map<string,WebObject *>::iterator InnerObject_itr,Doms_itr;
         map<string,string>::iterator Properties_itr;
         
         
         WebObject *parent;
         WebObject()
         {
           InnerHtml=TagName=ID=BegHtml=EndHtml="";
           parent=NULL;
         }
         void init(string tagname)
         {
            //  ID=tagname+I2S(dom_num);
         }
         void add(WebObject *s)
         {
              s->parent=this;
              InnerObject.insert(pair<string,WebObject *>(s->ID,s));
         }
         int  integrateHtml(WebObject *a)
         {
              integrateBegHtml(a);
              FullHtml+=a->BegHtml; 
              Doms.insert(pair<string,WebObject *>(a->ID,a));  
              for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr!=a->InnerObject.end();a->InnerObject_itr++)
                 integrateHtml(a->InnerObject_itr->second);
              FullHtml+=a->EndHtml; 
         }
         int  integrateDoms(WebObject *a)
         {
              Doms.insert(pair<string,WebObject *>(a->ID,a));  
              for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr!=a->InnerObject.end();a->InnerObject_itr++)
                 integrateDoms(a->InnerObject_itr->second); 
         }
         int  integrateBegHtml(WebObject *a)
         {
              string tmp="";
              for(Properties_itr=a->Properties.begin();Properties_itr!=a->Properties.end();Properties_itr++)
              tmp+=(Properties_itr->first+S("=")+"\""+Properties_itr->second+"\""+" ");
              a->BegHtml=S("<")+a->TagName+S(" id=")+S("\"")+a->ID+S("\"")+S(" ")+tmp+">";
         }
         void Html()
         {
              integrateHtml(this);
         }
         void addProperty(string a,string b)
         {
              Properties.insert(pair<string,string>(a,b));  
         }
};

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
           TagName="Script";
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
           add(&PageBody);
           add(&PageHead);

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



class Page
{
    public:
      Head PageHead;
      Body PageBody;  
      string Html; 
      map<string,WebObject *> Doms;
      void addChildDoms(WebObject *a)
      {
          
          Doms.insert(pair<string,WebObject *>(a->ID,a));   
          for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr!=a->InnerObject.end();a->InnerObject_itr++)
             addChildDoms(a->InnerObject_itr->second);
           
      }
      void add(WebObject *s) 
      {
          addChildDoms(s);
          PageBody.InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          PageBody.InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml); 
      }
      void formHtml()
      {
        //  addChildDoms(&PageBody);
          Html=S("<HTML>")+
                (PageHead.BegHtml+PageHead.InnerHtml+PageHead.EndHtml+PageBody.BegHtml+PageBody.InnerHtml+PageBody.EndHtml)+
               S("</HTML>");  
      }
      
      
      
};

main()
{
      Html page;
      
      Button b1;
      b1.InnerHtml=S("ssss");
      b1.addProperty("onclick","aaaa");
      
      Img  i1("http://a1.att.hudong.com/78/31/300000928390128868312951228_950.jpg");
      Button  i2;
      Button  i3;
      Button  i4;
      Script js("javascript");
      
      Link link("ssss");
      Link links("aaa");
      Link baidu("http://www.baidu.com","baidu");
      link.add(&js);
      links.add(&i2);
      i2.add(&i3);
      i3.add(&i4);
      b1.add(&link);
      b1.add(&links);
      
      
      page.add2Bo(&b1);
      page.add2Bo(&i1);
      page.add2Bo(&js);
      page.add2Bo(&link);
      page.add2Bo(new Link("http://www.baidu.com","baidu"));
      page.integrateHtml(&page);
      b1.integrateHtml(&b1);
      cout<<"_____"<<b1.FullHtml<<"______";
      
      cout<<page.FullHtml<<"*****"<<page.Doms.size();
      getchar();
      
      
      



}
