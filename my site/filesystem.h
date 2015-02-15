#ifndef ______FILESYSTEM
#define ______FILESYSTEM
#include<windows.h>
#include"list.h"
#include"bit.h"
#include<iostream>
using namespace std;
typedef struct Fileinfo
{
     char name[100];
     int isfolder;  
     Fileinfo(){isfolder=0;}
}Fileinfo;
void getfolderinfo(const char *foldername,List<Fileinfo>& info)
{
     if(foldername==NULL)
     {
         Bit driveflag(GetLogicalDrives()); 
         for(int i=0;i<driveflag.rank.size;i++)
         {
                Fileinfo buff;
                string namebuff="";
                namebuff=('A'+driveflag.rank[i]);
                namebuff+=":";
                buff.isfolder=1;
                strcpy(buff.name,namebuff.c_str());
                info.push_back(buff);
         }                           
     }
     else
     {
         char buff[100];
         strcpy(buff,foldername);
         strcat(buff,"\\*");
         Fileinfo infobuff;
         HANDLE fi;
         WIN32_FIND_DATA databuff;
         fi=FindFirstFile(buff,&databuff);
         if(fi==INVALID_HANDLE_VALUE)return;
         if((databuff.dwFileAttributes|FILE_ATTRIBUTE_DIRECTORY)==databuff.dwFileAttributes)
         infobuff.isfolder=1;
         else
         infobuff.isfolder=0;
         strcpy(infobuff.name,databuff.cFileName);
         info.push_back(infobuff);
         for(;;)
         {
                int flag=FindNextFile(fi,&databuff);
                if(flag==0)break;
                if((databuff.dwFileAttributes|FILE_ATTRIBUTE_DIRECTORY)==databuff.dwFileAttributes)
                infobuff.isfolder=1;
                else
                infobuff.isfolder=0;
                strcpy(infobuff.name,databuff.cFileName);
                info.push_back(infobuff);
                
         }
     }
     
}

#endif
