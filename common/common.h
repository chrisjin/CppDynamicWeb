#pragma once
#include<windows.h>
#include<string>
#include<sstream>
#include<map>
using namespace std;
string S(const char *a)
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
class ArgParser
{
      public:
        string name;
        string value;
        map<string,string> argmap;
        map<string,string>::iterator argmap_itr;
        ArgParser(char *pp)
        {
            parse(pp);
                       
                       
        }
        ArgParser()
        {}
        void parse(const char *pp)
        {
            char *p=(char *)malloc(strlen(pp)+1);
            strcpy(p,pp);
            char *tmp=p;
            if(!p)
            cout<<"ArgParser_NULL"<<endl;
            for(int i=0;;i++)
            {
                 if(p[i]=='=')
                 {
              
                   p[i]=0;
                   name=tmp;
                   tmp=p+i+1;
                 }
                 else if(p[i]=='&')
                 {
                   p[i]='\0'; 
                   value=tmp; 
                   tmp=p+i+1; 
                   argmap.insert(pair<string,string>(name,value));  
                   
                 }
                 else if(p[i]=='\0')
                 {
                   value=tmp;   
                   argmap.insert(pair<string,string>(name,value));  
                   break;
                 }
                 
            }
            free(p);
                       
                       
        }
        string get(string value)
        {
            argmap_itr=argmap.find(value); 
            if(argmap_itr==argmap.end())
            return S("");
            else
            return argmap_itr->second; 
               
        }
      
      
      
};
typedef struct Resource
{
   string Type;//TEXT BIN
   string MimeType;
   string Text;    
   BYTE *Bin;
   int BinL;
   bool obsolete; 
   bool download;
   Resource(){obsolete=0;download=0;} 
   void destroy()
   {
      if(Type=="BIN")
      {
        if(Bin)
        free(Bin);
      }  
   }   
}Resource;
typedef struct ClientInfo
{
    SOCKET clientsocket;
    sockaddr_in address;
    char ip[20];
    char *PostSpace;
    char *PageSpace;
    Resource* MainSrc;
    map<string,Resource*> *SourcePool;
}ClientInfo; 





