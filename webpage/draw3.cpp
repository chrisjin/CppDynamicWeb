#include"../dll/allheaders.h"
#include"../dll/css.h"
#define  $ Tag
#define  tag Tag
#define  file File

int WebMain()
{




//-----------------------------------------------------------------------------------------

     Html page;
      page[1]<<tag.Button()<<tag.Img("bin.exe");
      page[1]<<tag.Form()<<S("Name:")+tag.Input("text")+
                         S("Input:")+tag.Input("text")
                         +tag.Input("submit");
      page[1]<<tag.Button("123333")+tag.Button("aaaa");
      page[1]<<S("444444")+(tag.Button()<<S("DDDDDDD"))+S("sdssss");
      page[1]<<tag.Div()<<S("sssss")+S("MMMMMM")+tag.Button("ÈË°¡ÈË");
      page[1]<<tag.Img("lan.exe");

      
      
      
      
      Output<<getIP();


//-----------------------------------------------------------------------------------------    
      
  
      return 0;
}


