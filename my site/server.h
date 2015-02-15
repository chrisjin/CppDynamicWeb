#ifndef ______SERVER
#define ______SERVER

#include <WINSOCK2.H>
#include <stdio.h>
#include <windows.h>
#include<process.h>

#include"list.h"


typedef struct ClientInfo
{
    SOCKET clientsocket;
    sockaddr_in address;
    char ip[20];
}ClientInfo;    
  
typedef void (* ReceiveProcess)(const ClientInfo& userinfo,const char* receivetext);

void servefunc(SOCKET *param);

class Server
{
  public:

  SOCKET allremote;

  List<ClientInfo> clientpool;
  ReceiveProcess receivefunc;
  void setprocessfunc(ReceiveProcess a)
  {receivefunc=a;}
  
  void init(int PORT=80)
  {
       //prepareheader();
       WSADATA     wsaData;
       WSAStartup(0x0202, &wsaData);
       struct sockaddr_in ser;
       memset(&ser,0, sizeof(ser));
       ser.sin_family = AF_INET;
       ser.sin_port = htons(PORT); 
       ser.sin_addr.s_addr = htonl(INADDR_ANY);
       allremote=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
       bind(allremote, (struct sockaddr *)&ser, sizeof(ser));
       listen(allremote, SOMAXCONN );
  }
  void run(int port);
};
void servefunc(void *param)
{
       printf("\nBEGIN THREAD______________________________\n");
       char* textbuffer;
       unsigned long textsize;
       
       Server *ser=(Server *)param;
       ClientInfo clientinfo=ser->clientpool.take();
       SOCKET clientsocket=clientinfo.clientsocket;
       int flag;
       int timeout=10;
       setsockopt(clientsocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(int));
       WSAEVENT event=WSACreateEvent();
       WSAEventSelect(clientsocket,event,FD_READ|FD_CLOSE); 
       while(1) 
       { 
          WaitForSingleObject(event,INFINITE);
          textsize=0;
          ioctlsocket(clientsocket,FIONREAD,&textsize);
          if(textsize==0)break;
          textbuffer=(char *)malloc(textsize+3);
          memset(textbuffer,0,textsize+3);
          flag=recv(clientsocket,textbuffer,textsize,0);
          if(flag<=0)break;
          else WSAResetEvent(event);
          
          //printf("\n____RAW %d::%s",textsize,textbuffer);

          strcpy(clientinfo.ip,inet_ntoa(clientinfo.address.sin_addr));
          ser->receivefunc(clientinfo,textbuffer);
          free(textbuffer);
       } 
       shutdown(clientsocket,SD_SEND);
       closesocket(clientsocket);
       printf("\nEND THREAD______________________________\n");
}

void Server::run(int port=80)
{
       struct sockaddr_in client;
       int len=sizeof(sockaddr_in);
       SOCKET remotecomputer;
       ClientInfo buff;
       init(port);
       while(1)
       {
           remotecomputer=accept(allremote,(sockaddr  *)&client,&len);
           buff.clientsocket=remotecomputer;
           buff.address=client;

           clientpool.push_back(buff);
           _beginthread(servefunc,0,this);
       }
}
#endif


