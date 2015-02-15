#pragma once
#include<windows.h>

typedef struct ClientInfo
{
    SOCKET clientsocket;
    sockaddr_in address;
    char ip[20];
    char *PostSpace;
    char *PageSpace;
}ClientInfo; 
typedef int (*WebMainfun)(ClientInfo *a,char* arg[]); 
class WebInterface
{
    public:
      HINSTANCE h;
      WebMainfun webmainfun;
      WebInterface(char *name)
      {
        h=LoadLibrary(name);
        webmainfun=(WebMainfun)GetProcAddress(h,"_Z7WebMainP10ClientInfoPPc");
      }
      ~WebInterface()
      {
        FreeLibrary(h);
      }
      int webmain(ClientInfo *a,char* arg[])
      {
        return webmainfun(a,arg);
      } 
        
};
