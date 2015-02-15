/* Replace "dll.h" with the name of your header */
#include"doms.h"
#include"dllmain.h"
#pragma   data_seg("Shared")
#pragma   data_seg()
#pragma   comment(linker,"/SECTION:Shared,RWS")  

int WebMain(ClientInfo *a,char* arg[])
{
      
      Html page;
      
      Button b1;
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
      if(strlen(a->PostSpace)>0)
      b1.write(a->PostSpace);
      
      page.add2Bo(&b1);
      page.add2Bo(&i1);
      page.add2Bo(&js);
      page.add2Bo(&link);
      page.add2Bo(new Link("http://www.baidu.com","baidu"));
      
      Container con(a);
      con.addHtml(&page);
    //  cout<<a->PostSpace;
      return 0;
}


