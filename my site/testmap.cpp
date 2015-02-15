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
class WebObject
{
     public:
         string TagName;
         string ID; 
         string BegHtml;
         string EndHtml;
         string InnerHtml;
         WebObject()
         {
           InnerHtml=TagName=ID=BegHtml=EndHtml="";
         }
         map<string,WebObject *> InnerObject;
         map<string,string> Properties;
         WebObject *parent;
         virtual void add(WebObject a)
         {
            
         }
         virtual void addProperty(string a,string b)
         {
            
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
      void add(WebObject *s)
      {
          s->parent=this;
          InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml);
      }
      virtual void addProperty(string a,string b)
      {
          Properties.insert(pair<string,string>(a,b));  
          string tmp="";
          for(int i=0;i<Properties.size();i++)
          tmp+=(a+S("=")+"\""+b+"\""+" ");
          BegHtml=S("<BUTTON id=")+S("\"")+ID+S("\"")+S(" ")+tmp+">";
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
      void add(WebObject *s)
      {
          s->parent=this;
          InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml);
      }
};

static int tmp_img_id=0;
class Img:public WebObject
{
    public :
      Img()
      {
           TagName="IMG";
           ID=S("IMG")+I2S(tmp_img_id);
           tmp_img_id++;
           BegHtml="<IMG id="+S("\"")+ID+S("\"")+">";
           EndHtml="";
           
      }
      void add(WebObject *s)
      {
          s->parent=this;
          InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml);
      }
};

class Body:public WebObject
{
      public :
      Body()
      {
           TagName="BODY";
           BegHtml="<BODY id="+S("\"")+ID+S("\"")+">";
           EndHtml="</BODY>";
           
      }
      void add(WebObject *s)
      {
          s->parent=this;
          InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml);
      }  
      
};

class Head:public WebObject
{
      public :
      Head()
      {
           TagName="Head";
           ID=S("Head")+I2S(0);
           tmp_button_id++;
           BegHtml="<HEAD>";
           EndHtml="</HEAD>";
           
      }
      void add(WebObject *s)
      {
          s->parent=this;
          InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml);
      }  
      
};

class Script:public WebObject
{
      public :
      Script(char* type)
      {
           TagName="Script";
           BegHtml="<SCRIPT language=\"text/"+S(type)+"\""+">";
           EndHtml="</SCRIPT>";
           
      }
      void add(WebObject *s)
      {
          s->parent=this;
          InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml);
      }  
      
};

class Page
{
    public:
      Body PageBody;  
      Head PageHead;
      string Html; 
      map<string,WebObject *> Doms;
      void add(WebObject *s) 
      {
          PageBody.InnerObject.insert(pair<string,WebObject *>(s->ID,s));
          Doms.insert(pair<string,WebObject *>(s->ID,s));
          PageBody.InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml); 
      }
      void formHtml()
      {
          Html=S("<HTML>")+
                (PageHead.BegHtml+PageHead.InnerHtml+PageHead.EndHtml+PageBody.BegHtml+PageBody.InnerHtml+PageBody.EndHtml)+
               S("</HTML>");  
      }
      
      
      
};

main()
{
      Page page;
      Button b1;
      b1.InnerHtml=S("ssss");
      
      b1.addProperty("onclick","aaaa");
      Img  i1;
      b1.add(&i1);
      Script js("javascript");
      page.add(&b1);
      page.add(&i1);
      page.add(&js);
      page.formHtml();
      cout<<page.Html;
      getchar();
      
      
      



}
