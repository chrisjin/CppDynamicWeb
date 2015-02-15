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
         map<string,WebObject *> InnerObject;
         map<string,string> Properties;
         
         map<string,WebObject *>::iterator InnerObject_itr;
         map<string,string>::iterator Properties_itr;
         WebObject *parent;
         WebObject()
         {
           InnerHtml=TagName=ID=BegHtml=EndHtml="";
           parent=0;
         }
         void init(string tagname)
         {
            //  ID=tagname+I2S(dom_num);
         }
         void add(WebObject *s)
         {
              s->parent=this;
              InnerObject.insert(pair<string,WebObject *>(s->ID,s));
              InnerHtml+=(s->BegHtml+s->InnerHtml+s->EndHtml);
         }
         void integrateBegin(WebObject *s)
         {
              for(InnerObject_itr=InnerObject.begin();InnerObject_itr!=InnerObject.end();InnerObject_itr++)
              
              
         }
         void addProperty(string a,string b)
         {
              Properties.insert(pair<string,string>(a,b));  
              string tmp="";
              for(Properties_itr=Properties.begin();Properties_itr!=Properties.end();Properties_itr++)
              tmp+=(Properties_itr->first+S("=")+"\""+Properties_itr->second+"\""+" ");
              BegHtml=S("<")+TagName+S(" id=")+S("\"")+ID+S("\"")+S(" ")+tmp+">";
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
      Page page;
      
      Button b1;
      b1.InnerHtml=S("ssss");
      b1.addProperty("onclick","aaaa");
      
      Img  i1("http://a1.att.hudong.com/78/31/300000928390128868312951228_950.jpg");
      
      Script js("javascript");
      
      Link link("ssss");
      Link links("aaa");
      Link baidu("http://www.baidu.com","baidu");
      b1.add(&link);
      b1.add(&links);
      
      
      page.add(&b1);
      page.add(&i1);
      page.add(&js);
      page.add(&link);
      page.add(new Link("http://www.baidu.com","baidu"));
      page.formHtml();
      
      
      cout<<page.Html<<"*****"<<page.Doms.size();
      getchar();
      
      
      



}
