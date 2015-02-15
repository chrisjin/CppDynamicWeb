#pragma once
#include"doms.h"
#include"common.h"
class Container
{
    public:
    ClientInfo *ClientP;
    Container(ClientInfo *a) 
    {
        ClientP=a;               
                         
    }
    void addHtml(WebObject *s)
    {
        string ht=s->getHtml();
        ClientP->PageSpace=(char *)malloc(ht.length()+2);
        strcpy(ClientP->PageSpace,ht.c_str());
    } 
      
};
int __declspec(dllexport)WebMain(ClientInfo *a,char* arg[]);
BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
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


