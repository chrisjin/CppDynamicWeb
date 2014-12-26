#pragma once
#include<map>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include<list>
#include"windows.h"
#include"../common/common.h"
#include"files.h"
#include"globalvars.h"
#include"StylePool.h"
using namespace std;


int dom_num=0;
class __WebObject
{
     public:
         string TagName;
         string ID; 
         string BegHtml;
         string EndHtml;
         string FullHtml;
         
         //string CSSClass;
         vector<string> RelatedCSSSelector;
         
         
         vector<__WebObject *> InnerObject;
         map<string,string> Properties;
         map<string,__WebObject *> Doms;
         
         vector<__WebObject *>::iterator InnerObject_itr;
         map<string,string>::iterator Properties_itr;
         map<string,__WebObject *>::iterator Doms_itr;
         
         
         __WebObject *parent;
         __WebObject()
         {
           
           TagName=ID=BegHtml=EndHtml="";
           parent=NULL;
           calflag=0;
         }
         void init(string tagname)
         {
            //  ID=tagname+I2S(dom_num);
         }
         bool add(__WebObject *s)
         {
              if(s->parent!=NULL)return 0;
              s->parent=this;
              InnerObject.push_back(s);
              calflag=1;
              return 1;
         }
         void addSrc( )
         {
              
             
         }
         string toURI()
         {
               string ret=URIBase+S("?")+S("srcpool=")+ID;
               Resource *r=new Resource;
               r->Type="TEXT";
               r->MimeType="text/html";
               r->Text=getHtml();
               r->obsolete=0;
               DllSourcePool[ret]=r;
               return ret;       
         }
         void write(string a);
         void  integrateCSS(__WebObject *a);
         int  integrateHtml(__WebObject *a)
         {
              calflag=0;
              integrateBegHtml(a);
              FullHtml+=a->BegHtml; 
              Doms.insert(pair<string,__WebObject *>(a->ID,a));  
              for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr<a->InnerObject.end();a->InnerObject_itr++)
              {
                   integrateHtml(*a->InnerObject_itr);
              }
              FullHtml+=a->EndHtml; 
             // FullHtml+="\n";
         }
         
         int  integrateDoms(__WebObject *a)
         {
              Doms.insert(pair<string,__WebObject *>(a->ID,a));  
              for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr!=a->InnerObject.end();a->InnerObject_itr++)
                 integrateDoms(*a->InnerObject_itr); 
         }
         int  integrateBegHtml(__WebObject *a)
         {
              if(a->TagName=="TEXT")return 1;
              string tmp="";
              for(Properties_itr=a->Properties.begin();Properties_itr!=a->Properties.end();Properties_itr++)
              {
                tmp+=" ";
                tmp+=(Properties_itr->first+S("=")+""+Properties_itr->second+"");
              }
              a->BegHtml=S("<")+a->TagName+tmp+">";
         }
         
         void destroy(__WebObject *a)
         {
              for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr<a->InnerObject.end();a->InnerObject_itr++)
                 destroy(*a->InnerObject_itr);
              InnerObject.clear();
              Properties.clear();
              Doms.clear();
         }
         void destroy()
         {
              destroy(this); 
         
         }
         int calflag;
         virtual string getHtml()
         {
              if(calflag)
              {
                integrateCSS(this);
                integrateHtml(this);
              }      
              return FullHtml;
         }
         void addProperty(string a,string b)
         {
              Properties.insert(pair<string,string>(a,b));  
         }
         void useStyle(Style css);
         
         __WebObject& operator[](int index)
         {
              return *InnerObject[index] ;          
                    
         }

};




static int tmp_text_id=0;
class __Text:public __WebObject
{
      public :
      __Text(string text)
      {
           TagName="TEXT";
           BegHtml=text;
           EndHtml="";
           tmp_text_id++;
           ID=TagName+I2S(tmp_text_id);
      }
      
};

static int tmp_ling_id=0;
class __Ling:public __WebObject
{
      public :
      __Ling(string text)
      {
           TagName=text;
           BegHtml=S("<")+text+">";
           EndHtml=S("</")+text+">";
           tmp_ling_id++;
           ID=TagName+I2S(tmp_ling_id);
      }
      
};
//////////////__WebObject/////////////////////
void __WebObject::write(string t)
{
     add(new __Text(t));
}
//////////////__WebObject/////////////////////

static int tmp_button_id=0;
class __Button:public __WebObject
{
    public :
      __Button()
      {
           TagName="BUTTON";
           ID=S("BUTTON")+I2S(tmp_button_id);
           tmp_button_id++;
           BegHtml="<BUTTON>";
           EndHtml="</BUTTON>";
           addProperty("id",ID);
      }
      __Button(string title)
      {    
           TagName="BUTTON";
           ID=S("BUTTON")+I2S(tmp_button_id);
           tmp_button_id++;
           BegHtml="<BUTTON>";
           EndHtml="</BUTTON>";
           addProperty("id",ID);
           add(new __Text(title));
                    
      
      }
};

static int tmp_div_id=0;
class __Div:public __WebObject
{
    public :
      __Div()
      {
          TagName="DIV";
          ID=S("DIV")+I2S(tmp_div_id);
          tmp_div_id++;
          BegHtml="<DIV>";
          EndHtml="</DIV>";
          addProperty("id",ID);
      }
};

static int tmp_img_id=0;
class __Img:public __WebObject
{
    public:
      string SrcURI;

      __Img(string srcuri)
      {
           TagName="IMG";
           ID=S("IMG")+I2S(tmp_img_id);
           tmp_img_id++;
           BegHtml="<IMG>";
           EndHtml="";
           addProperty("src",srcuri);
           SrcURI=srcuri;
           addProperty("id",ID);
      }
};


static int tmp_link_id=0;
class __Link:public __WebObject
{
      public: 
      __Link(string href,string innertext="CLICK ME")
      {
          TagName="A";  
          ID=S("A")+I2S(tmp_link_id);
          tmp_link_id++;
          BegHtml="<A>";
          EndHtml="</A>";  
          addProperty("href",href); 
          addProperty("id",ID);
          write(innertext);
                
      }          
      
};

static int tmp_form_id=0;
class __Form:public __WebObject
{
      public:
      __Form()
      {
          TagName="FORM";  
          ID=S("FORM")+I2S(tmp_form_id);
          tmp_form_id++;
          BegHtml="<FORM>";
          EndHtml="</FORM>"; 
          addProperty("id",ID); 
                
      }        
      
};

static int tmp_table_id=0;
class __Table:public __WebObject
{
      public:
      __Table()
      {
          TagName="TABLE";  
          ID=S("TABLE")+I2S(tmp_table_id);
          tmp_table_id++;
          BegHtml="<TABLE>";
          EndHtml="</TABLE>"; 
          addProperty("id",ID); 
                
      }        
};

static int tmp_input_id=0;
class __Input:public __WebObject
{
      public:
      __Input(string type)
      {
          TagName="INPUT";  
          ID=S("INPUT")+I2S(tmp_input_id);
          tmp_input_id++;
          BegHtml="<INPUT>";
          EndHtml="";
          addProperty("type",type);  
          addProperty("id",ID);
                
      }         
      
};

static int tmp_frameset_id=0;
class __Frameset:public __WebObject
{
      public:
      __Frameset( )
      {
          TagName="FRAMESET";  
          ID=S("FRAMESET")+I2S(tmp_frameset_id);
          tmp_frameset_id++;
          BegHtml="<FRAMESET>";
          EndHtml="</FRAMESET>";
          addProperty("id",ID);
        //  addProperty("cols",type);  
                
      }        
      
};

static int tmp_frame_id=0;
class __Frame:public __WebObject
{
      public:
      __Frame(string src )
      {
          TagName="FRAME";  
          ID=S("Frame")+I2S(tmp_frame_id);
          tmp_frame_id++;
          BegHtml="<Frame>";
          EndHtml="";
          addProperty("src",src); 
          addProperty("id",ID); 
                
      }         
      
};

static int tmp_body_id=0;
class __Body:public __WebObject
{
      public :
      __Body()
      {
           TagName="BODY";
           BegHtml="<BODY>";
           EndHtml="</BODY>";
           tmp_body_id++;
           ID=TagName+I2S(tmp_body_id);
      }
};
static int tmp_head_id=0;
class __Head:public __WebObject
{
      public :
      __Head()
      {
           TagName="HEAD";
           ID=S("Head")+I2S(0);
           BegHtml="<HEAD>";
           EndHtml="</HEAD>";
           tmp_head_id++;
           ID=TagName+I2S(tmp_head_id);
      }
};
static int tmp_script_id=0;
class __Script:public __WebObject
{
      public :
      __Script(string type)
      {
           TagName="SCRIPT";
           BegHtml="<SCRIPT>";
           EndHtml="</SCRIPT>";
           addProperty("type",type);
           tmp_script_id++;
           ID=TagName+I2S(tmp_script_id);
      }
      
};

class __JavaScript:public __WebObject
{
      public :
      __JavaScript()
      {
           TagName="SCRIPT";
           BegHtml="<SCRIPT>";
           EndHtml="</SCRIPT>";
           addProperty("type","text/javascript");
      } 
};

class __CSS:public __WebObject
{
      public :
      
      map<string,string> Item;
      __CSS(string a,string b)
      {
           TagName="STYLE";
           BegHtml="<STYLE>";
           EndHtml="</STYLE>";
           addProperty("type","text/css");
      } 
      __CSS()
      {
           TagName="STYLE";
           BegHtml="<STYLE>";
           EndHtml="</STYLE>";
           addProperty("type","text/css");  
      }
      void addItem(string a,string b)//ø…±‹√‚÷ÿ∏¥ 
      {
           bool ret=Item.insert(pair<string,string>(a,b)).second;
           if(ret)
           add(new __Text(a+"{"+b+"}"));
      }
};

//style:two part:1,in Webobject.2,in StylePool
void __WebObject::useStyle(Style css)
{
      if(css.StyleClass!="")
      addProperty("class",css.StyleClass);
      bool ret=StylePool.insert(pair<string,string>(css.Selector,css.StyleCon)).second;
      if(ret)
      RelatedCSSSelector.push_back(css.Selector);
}

class __JSFunc:public __WebObject
{
      public :
      __JSFunc(string declare)
      {
           TagName="TEXT";
           BegHtml=S("function ")+declare+"{";
           EndHtml="}";  
      }
};

class __AJAX_send:public __WebObject
{
      public :
      __AJAX_send()
      {
           TagName="TEXT";
           BegHtml="function sendContent(method,titlecon,postcon){AJAX_object.open(method,titlecon,true);AJAX_object.onreadystatechange=processRequest;AJAX_object.setRequestHeader(\"Content-Type\",\"text/xml;charset=UTF-8\");if(method=\"POST\")AJAX_object.send(postcon);";
           EndHtml="}";  
      }
      string call(string parlist)
      {
             
           return S("sendContent")+parlist; 
      }
};


static int tmp_html_id=0;
class __Html:public __WebObject
{
      public :
      __Head PageHead;
      __JavaScript HeadScript;
      __CSS Css;
      bool isCSS;
      __Body PageBody; 
      __JavaScript BodyScript;
      __Html()
      {
           TagName="HTML";
           BegHtml="<HTML>";
           EndHtml="</HTML>";
           add(&PageHead);
           add(&PageBody);
           tmp_html_id++;
           ID=TagName+I2S(tmp_html_id);
           isCSS=0;
      }
      __Html(int flag)
      {
           TagName="Html";
           BegHtml="<HTML>";
           EndHtml="</HTML>";
           if(flag==1)
           add(&PageHead);
           if(flag==1)
           add(&PageBody);
           tmp_html_id++;
           ID=TagName+I2S(tmp_html_id);
           isCSS=0;

      }
      void add2Bo(__WebObject *a) 
      {
           PageBody.add(a);
      }
      void add2He(__WebObject *a) 
      {
           PageHead.add(a);
      }
      __AJAX_send *sendCon;
      __JSFunc    *processReq;
      void AJAX_init()
      {
           sendCon=new __AJAX_send();
           processReq=new __JSFunc("processRequest()");
           HeadScript.write("var AJAX_object=0;");
           HeadScript.add(sendCon);
           HeadScript.add(processReq);
           BodyScript.write("AJAX_object=window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject(\"Microsoft.XMLHTTP\");");
      }
     // CSS Css;
 //     string operator
      
};
//////////////__WebObject/////////////////////
void  __WebObject::integrateCSS(__WebObject *a)
{
      static bool isHtml=a->TagName=="HTML";
      static int Rec=0;
      if(!isHtml)return;
      static __Html *page=(__Html *)a;
      static bool Cssflag=page->isCSS;
      for(a->InnerObject_itr=a->InnerObject.begin();a->InnerObject_itr!=a->InnerObject.end();a->InnerObject_itr++)
      {
         vector<string>& CSSSelector=(*a->InnerObject_itr)->RelatedCSSSelector;
         for(int i=0;i<CSSSelector.size();i++)
         {
                if(Cssflag==0)  
                {
                   page->PageHead.add(&page->Css);  
                   page->isCSS=1;                
                }
                page->Css.addItem(CSSSelector[i],StylePool[CSSSelector[i]]);
         }
         integrateCSS(*a->InnerObject_itr);
      } 
}
//////////////__WebObject/////////////////////
//class Html:public __WebObject
