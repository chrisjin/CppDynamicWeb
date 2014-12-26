#pragma once
#include"container.h"
#include"generator.h"
#include"../common/common.h"
using namespace std;
int WebMain();
Container Output;
DomsGenerator Tag;
FilesGenerator File;
CSSGenerator CSS;
string Arg;
ClientInfo *pClientInfo;
ArgParser Parser;
ArgParser postParser;
string getArg()
{
   return Arg;       
}
string getIP()
{
   return pClientInfo->ip;      
}
string getPost()
{
       
}
string A(string name)
{
    return Parser.get(name);   
}
string P(string name)
{
    return postParser.get(name);   
}

int __declspec(dllexport)startWebMain(ClientInfo *a,char* arg,string filename)
{
    Arg=arg;
    pClientInfo=a;
    URIBase=filename;
    Parser.parse(arg);
    if(a->PostSpace)
    postParser.parse(a->PostSpace);
    Output.get(a);
   // printf("^^^^^^%s\n",a->PostSpace);
    WebMain();
    Tag.destroy();
    File.destroy();
    for(map<string,Resource*>::iterator itr=DllSourcePool.begin();itr!=DllSourcePool.end();itr++)
    {
        if(itr->second)
        delete itr->second;                                
    }
    DllSourcePool.clear();
}

extern "C"
BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    char name[200];
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        
        break;

      case DLL_THREAD_DETACH:
 
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}


