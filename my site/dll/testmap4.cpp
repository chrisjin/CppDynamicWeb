#include"doms.h"
typedef struct ClientInfo
{
    SOCKET clientsocket;
    sockaddr_in address;
    char ip[20];
    char *post;
}ClientInfo;  
typedef string (*WebMain)(ClientInfo *a,char* arg[]); 

main()
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
      b1.write("this is a button:::::");
      
      page.add2Bo(&b1);
      page.add2Bo(&i1);
      page.add2Bo(&js);
      page.add2Bo(&link);
      page.add2Bo(new Link("http://www.baidu.com","baidu"));
      page.getHtml();
     // b1.integrateHtml(&b1);
    //  cout<<"_____"<<b1.FullHtml<<"______";
      
      cout<<page.FullHtml<<"*****"<<page.Doms.size();
      HINSTANCE h=LoadLibrary("webmain.exe");
        WebMain mmadd=(WebMain)GetProcAddress(h,"_Z7WebMainv");
        
        cout<<"lllll"<<mmadd();
      getchar();
      
      
      



}
