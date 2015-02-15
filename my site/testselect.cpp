#include <WINSOCK2.H>
#include <stdio.h>
#include <windows.h>
#include<process.h>

main()
{
       WSADATA     wsaData;
       WSAStartup(0x0202, &wsaData);
       SOCKET allremote;
       struct sockaddr_in ser;
       memset(&ser,0, sizeof(ser));
       ser.sin_family = AF_INET;
       ser.sin_port = htons(80); 
       ser.sin_addr.s_addr = htonl(INADDR_ANY);
       allremote=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
       bind(allremote, (struct sockaddr *)&ser, sizeof(ser));
       listen(allremote, SOMAXCONN );
       int timeout=1000;
       setsockopt(allremote,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(int));
       
       timeval tim={0,10};
       fd_set socketset;
       SOCKET remotecomputer;
       char buff[5000];
       while(1)
       {
             FD_ZERO(&socketset); 
             FD_SET(allremote,&socketset); 
             int ret=select(0,&socketset,0,0,&tim);
             if(ret>0)
             {
                   remotecomputer=accept(allremote,(sockaddr  *)0,0);  
                   memset(buff,0,5000);
                   recv(remotecomputer,buff,5000,0); 
                   printf(buff);
                      
             }
       }      
      
}
