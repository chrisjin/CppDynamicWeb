#include<windows.h>
#include<iostream>
#include<map>
#include"../common/common.h"
#include"../server/server.h"
#include"../server/request.h"
#include"../server/response.h"
#include"../server/bigfile.h"
#include"../server/filesystem.h"
#include"../server/decode.h"
#include"../server/webinterface.h"
using namespace std;
void clearClientInfo(ClientInfo *clientinfo)
{
     if(!clientinfo)
        return;
     
     if(clientinfo->PostSpace)
        free(clientinfo->PostSpace);
     
     if(clientinfo->PageSpace)
        free(clientinfo->PageSpace);
     getchar();
     if(clientinfo->MainSrc)
        clientinfo->MainSrc->destroy();
     
     if(clientinfo->SourcePool)
     {
        for(map<string,Resource*>::iterator itr=clientinfo->SourcePool->begin();itr!=clientinfo->SourcePool->end();itr++)
        {
             if(itr->second)
               delete itr->second  ;                                                                       
        } 
        clientinfo->SourcePool->clear();
        delete  clientinfo->SourcePool;         
     }
     
}

map<string,Resource*> SerSourcePool;
void output()
{
     
     
     
} 
using namespace std;

void fun(ClientInfo *clientinfo,const char *b)
{
     
     printf("Server:ENTER PROCESS______________________________\n");
     string localfilename="../webpage"; 
     Request req(b);
     ResponseHeader httpheader;
     ArgParser parser;
     string affix;
     string arg;
     string filename;
     char param[500];
     
     


     if(req.method=="GET"||req.content!="")
     {
         if(req.method=="GET")
         cout<<"(IP: "<<clientinfo->ip<<")"<<"Browser:GET "<<req.uri_full<<endl;
         else if(req.content!="")
         cout<<"(IP: "<<clientinfo->ip<<")"<<"Browser:POST "<<req.content<<endl;
         //全请求 
         string fullfilename=req.uri_full;
         //请求文件 
         filename=req.uri_name;
         localfilename+="/";
         localfilename+=filename;
         //请求文件后缀 
         affix=req.uri_affix;  
         //请求参数 
         arg=req.uri_arg;
         strcpy(param,arg.c_str());
         //获得接口 
         
         if(req.content!="")
         {
           clientinfo->PostSpace=(char *)malloc(req.content.length()+3);
           if(clientinfo->PostSpace==0)
           cout<<endl<<"Server:PostSpace Allocate Error"<<endl;
           memset(clientinfo->PostSpace,0,req.content.length()+3);
           strcpy(clientinfo->PostSpace,req.content.c_str());
         }
         else
           clientinfo->PostSpace=0;
           
           
         parser.parse(arg.c_str());
         string src=parser.get("srcpool");
         string stobesent;
         BYTE* btobesent;
         Resource *presorce;
         int ret;
         WebInterface inter;
         if(src!="")
         {
             cout<<"Server:Load Src"<<endl;
  
             presorce=SerSourcePool[fullfilename];
             if(presorce==0)
             {
             cout<<"Server:Load SRC ERR"<<endl;
             return;
             }
             cout<<"Server:Load Over"<<endl;
              //getchar();
             if(presorce->obsolete==1||clientinfo->PostSpace)
             {
               inter.getEntry(localfilename);
               cout<<"Server:Src Obosolete"<<endl;
               //  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  
               ret=inter.webmain(clientinfo,param,filename);
               if(ret==-1)
               {
               cout<<"Server:Load DLL Err"<<endl;
               return ; 
               }
             }
              
             
             if(presorce->Type=="TEXT")
             {
               stobesent=SerSourcePool[fullfilename]->Text; 
               httpheader.settype(presorce->MimeType.c_str());
               httpheader.setsize(stobesent.length());
               httpheader.prepareheader();  
               //send   send   send   send   send   send   send   send   send   send   send   send   send   send   send   send   
               send(clientinfo->clientsocket,httpheader.content.c_str(),httpheader.content.size(),0);
               send(clientinfo->clientsocket,stobesent.c_str(),stobesent.length(),0);
               //clearClientInfo(clientinfo);
               presorce->obsolete=1;
               return ;
               
             }
             if(presorce->Type=="BIN")
             {
           //     printf("SERIMAGEsize:%d,Ptr:%d\n",SerSourcePool[fullfilename]->BinL,SerSourcePool[fullfilename]->Bin);
                
                
                btobesent= SerSourcePool[fullfilename]->Bin;  
                httpheader.settype(presorce->MimeType.c_str()); 
                httpheader.setsize(presorce->BinL);     
                httpheader.prepareheader(); 
                //send   send   send   send   send   send   send   send   send   send   send   send   send   send   send   send 
                send(clientinfo->clientsocket,httpheader.content.c_str(),httpheader.content.size(),0);    
                send(clientinfo->clientsocket,(char *)btobesent,presorce->BinL,0);  
                //clearClientInfo(clientinfo);
                return;       
                                      
             }

                    
                    
         }
         

         
         
         if(affix=="exe"||affix=="dll")
         {
           //  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  Webmain  
           cout<<"Server:WebMain Entry"<<endl;
           inter.getEntry(localfilename);
           ret=inter.webmain(clientinfo,param,filename);
           cout<<"Server:WebMain Ret"<<endl;
           if(ret==-1)
           {
             cout<<"Server:Load DLL Err";
             return ; 
           }
           cout<<"Server:Extract Src From Dll"<<endl;
           for(map<string,Resource*>::iterator itr=clientinfo->SourcePool->begin();itr!=clientinfo->SourcePool->end();
               itr++)
           {
              SerSourcePool[itr->first]=itr->second; 
           }
           cout<<"Server:Extract Src Over"<<endl;
           
           httpheader.settype(clientinfo->MainSrc->MimeType.c_str());
           if(clientinfo->MainSrc->Type=="TEXT")
           httpheader.setsize(clientinfo->MainSrc->Text.length());
           else if(clientinfo->MainSrc->Type=="BIN")
           httpheader.setsize(clientinfo->MainSrc->BinL);
           httpheader.prepareheader();
           
           //send   send   send   send   send   send   send   send   send   send   send   send   send   send   send   send 
           send(clientinfo->clientsocket,httpheader.content.c_str(),httpheader.content.size(),0);
           if(clientinfo->MainSrc->Type=="TEXT")
           send(clientinfo->clientsocket,clientinfo->MainSrc->Text.c_str(),clientinfo->MainSrc->Text.length(),0);
           else if(clientinfo->MainSrc->Type=="BIN")
           send(clientinfo->clientsocket,(char *)clientinfo->MainSrc->Bin,clientinfo->MainSrc->BinL,0);
           //clearClientInfo(clientinfo);
           return ;
          }
          
          else
          {
             
             BigFile file(localfilename.c_str());   
               
             httpheader.setfile(file,file.size);
             httpheader.prepareheader();
             send(clientinfo->clientsocket,httpheader.content.c_str(),httpheader.content.size(),0);
             double flag=file.sendfile(clientinfo->clientsocket);  
             return;
              
          }

         
          
     }

     
}
main()
{
      Server test;
      test.setprocessfunc(fun);
      //printf("请输入端口号然后按回车(推荐输入80):");
      int port;
      //scanf("%d",&port);
      test.run(999);
      getchar();    
}
