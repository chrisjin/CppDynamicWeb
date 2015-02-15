#include<windows.h>
#include<iostream>
#include"server.h"
#include"request.h"
#include"response.h"
#include"bigfile.h"
#include"filesystem.h"
#include"decode.h"
void output()
{
     
     
     
} 
using namespace std;
void fun(const ClientInfo &a,const char *b)
{
     char buff[500]="./src";
     char recvbuff[1000];
     strcpy(recvbuff,b);
     List<Fileinfo> fileinfo;
     string sendbuff="";
     
     //cout<<endl<<a.ip<<endl;
     int sendsize;
     
     //cout<<endl<<"RECV: "<<"recvbuff:"<<recvbuff<<endl;
     cout<<b<<endl;
     Request req(b);
   //  cout<<a.ip<<" "<<req.content<<endl;
      ResponseHeader httpheader;
     if(req.content!="")
     {
         char revbuff[100];
         memset(revbuff,0,100);
         char *strrecv=UTF8ToANSI(req.content.c_str());
         strcpy(revbuff,strrecv);

         if(strcmp(revbuff,"0")==0)
         getfolderinfo(0,fileinfo);
         else
         getfolderinfo(revbuff,fileinfo);
         sendbuff+="<?xml version=\"1.0\" encoding=\"UTF-8\" ?> ";
         sendbuff+="<filesystem>";
         for(int i=0;i<fileinfo.size;i++)
         {
             sendbuff+="<file>" ;   
                 sendbuff+="<name>";
                     sendbuff+=fileinfo[i].name;
                 sendbuff+="</name>";   
                 sendbuff+="<isfolder>";
                     if(fileinfo[i].isfolder)
                     sendbuff+="1";
                     else
                     sendbuff+="0";
                 sendbuff+="</isfolder>";
             sendbuff+="</file>" ;  
      
         }
         if(fileinfo.size==0||(fileinfo.size==2&&strcmp(fileinfo[0].name,".")==0))
         {
            sendbuff+="<file>" ;   
                 sendbuff+="<name>";
                 sendbuff+="空";
                 sendbuff+="</name>"; 
            sendbuff+="</file>";
            sendbuff+="<isfolder>";
                 sendbuff+="5";
            sendbuff+="</isfolder>"; 
         
         }    
         sendbuff+="</filesystem>";
         
         //cout<<"******"<<sendbuff<<endl;
         char *utf8=ANSIToUTF8(sendbuff.c_str());
    
         //char utf8buff[500];
         //sprintf(utf8buff,utf8,"\\");
         httpheader.setsize(strlen(utf8));
         httpheader.settype("text/xml;charset=UTF-8");
         
         httpheader.prepareheader();
         //cout<<"___"<<httpheader.content;
         send(a.clientsocket,httpheader.content.c_str(),httpheader.content.size(),0);
         send(a.clientsocket,utf8,strlen(utf8),0);
         if(utf8) 
         free(utf8); 
         if(strrecv)
         free(strrecv);               
                          
     }
     else if(req.method=="GET")
     {
     
         string downfilename=URLToANSI(req.getrequest(1).c_str());
         
         if(downfilename.find("?")==-1&&downfilename.find("<")==-1)
         strcat(buff,req.getrequest().c_str());
         else if(downfilename.find("<")!=-1)
         {
              strcpy(buff,downfilename.substr(0,downfilename.size()).replace(1,1,":").c_str());
              
         }
         else if(downfilename.find("?")!=-1)
         {
             strcpy(buff,downfilename.substr(0,downfilename.size()).replace(1,1,":").c_str());
             
             httpheader.setdownload(); 
         }
     //    cout<<buff<<endl;
         BigFile file(buff);
         
         httpheader.setfile(file,file.size);
         httpheader.prepareheader();
         //cout<<httpheader.content<<endl;
         send(a.clientsocket,httpheader.content.c_str(),httpheader.content.size(),0);
         
         double flag=file.sendfile(a.clientsocket);  
          
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
