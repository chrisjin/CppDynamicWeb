#ifndef ______RESPONSE
#define ______RESPONSE
#include <WINSOCK2.H>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include<time.h>
#include<iostream>
#include"bigfile.h"
using namespace std;
class ResponseHeader
{
     public:
     string content; 
     int size;
     int isdownload;
     char filename[200];
     char type[100];
    void setcontentsize(int a){size=a;}
    ResponseHeader(BigFile a,int asize=0)
    {
     if(asize==0)
     size=a.size;
     else
     size=asize;
     strcpy(filename,a.filename);isdownload=0;

     }
     ResponseHeader(int asize)
     {
        strcpy(type,"text/html");  
        size= asize;   
        isdownload=0;   
         
     }
     ResponseHeader(){;}
     void setsize(int asize)
     {

        size=asize;   
        isdownload=0;   
         
     }
     void settype(char *atype)
     {
       sttype,atypercpy();  
        isdownload=0;   
         
     }
     void setfile(BigFile a,int asize=0)
     {
         strcpy(type,"text/html")
         content="";
         if(asize==0)
         size=a.size;
         else
         size=asize;
         strcpy(filename,a.filename);isdownload=0;

     }
    void prepareheader()
    {
       char header[900];
       char buffer[200];
       strcpy(header,"HTTP/1.1 200 OK\r\n");
       strcat(header,"Server: JIN\r\n");
       strcat(header,"Date: Tue, 19 Nov 2000 07:33:20 GMT\r\n");
       
       sprintf(buffer,"Content-Length: %d\r\n",size);
       strcat(header,buffer);
       
       sprintf(buffer,"Location: http://%s\r\n","127.0.0.1");
       strcat(header,buffer);
       if(isdownload==1)
       {           
       sprintf(buffer,"Content-Disposition: attachment;filename=\"%s\"\r\n",filename+1);
       strcat(header,buffer);
       }
       strcat(header,"Connection: Keep-Alive\r\n");
       sprintf(buffer,"Content-Type: %s\r\n\r\n",type);
       strcat(header,buffer);
       content+=header;

  }
     
      
      
};
#endif

