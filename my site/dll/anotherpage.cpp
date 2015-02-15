/* Replace "dll.h" with the name of your header */
#include"doms.h"
#include"dllmain.h"
#pragma   data_seg("Shared")
#pragma   data_seg()
#pragma   comment(linker,"/SECTION:Shared,RWS")  

int WebMain(ClientInfo *a,char* arg[])
{
      
      Html page;

      Button *btn=new Button();
      if(a->PostSpace)
      btn->write(a->PostSpace);
      
      
      page.add2Bo(btn);
      
      
      Container con(a);
      con.addHtml(&page);
      return 0;
}


