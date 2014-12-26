#ifndef ______REQUEST
#define ______REQUEST
#include <WINSOCK2.H>
#include <stdio.h>
#include <windows.h>
#include<process.h>
#include<time.h>
#include<iostream>
using namespace std;
class Request
{
   public:
   char rbuff[1000];
   string str;
   string header;
   string content;
   string method;
   
   string uri_full;
   string uri_name;
   string uri_affix;
   string uri_arg;
   
   Request(){str=header=content=method="";}
   public:
   Request(const char *buff)
   {
      
       str=buff; 
       if(str.find("HTTP/1.1")!=-1)
       {
           int a,b;
           a=str.find("\r\n\r\n");
           b=str.find("\n\r\n\r");
           //printf("\n__a:%d b:%d___\n",a,b);
           int part=(a==-1)?b:a;
           if(part==-1)return;
           //printf("\n__part:%d___\n",part);
           header=str.substr(0,part);
           
           
           
           //printf("\n__repart:%d___\n",str.size()-part);
           method=header.substr(0,header.find(" "));
           if(method=="POST")
           content=str.substr(part+4,str.size()-part-4);
       }
       else
       {
           content=str;
       }
       uri_full=getrequest(1); 
       uri_name=uri_full.substr(0,uri_full.find("?")); 
       int pos1= uri_full.find(".")+1;
       int affixlength= uri_full.find("?")-pos1;
       uri_affix=uri_full.substr(pos1,affixlength);  
       if(uri_full.find("?")!=-1)
         uri_arg=uri_full.substr(uri_full.find("?")+1,uri_full.length());
       else
         uri_arg="";
   }
   char *getitem(char *itemname)
   {

        
        
   }
   string getrequest(int flag=0)
   {
       string con="";
       if(method=="GET"||method=="POST")
       {
            int l=header.find(" ");
            int r=header.find(" ",l+1);
            if(l==-1||r==-1)return 0;
            if(flag==0)
            con=header.substr(l+1,r-l-1);
            else
            con=header.substr(l+2,r-l-2);
            
        }
        return con;
   }
   string getaffix()
   {
        return uri_affix;
   }
   string getpost()
   {
       if(method=="POST")
       return content; 
       else return NULL;   
          
   }
   
         
};

#endif


