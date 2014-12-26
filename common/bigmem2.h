#include"list.h"
#include<windows.h>
static int TIMES=0;
void *getfileptr(char *filename,DWORD size=500)
{
            HANDLE hfile= CreateFile(filename,GENERIC_WRITE|GENERIC_READ,
                                           FILE_SHARE_READ|FILE_SHARE_WRITE,
                                           0,
                                           CREATE_ALWAYS,
                                           FILE_ATTRIBUTE_NORMAL,
                                           0);
             char buffer[50];
             sprintf(buffer,"zz_%d",TIMES);
             TIMES++;
             HANDLE hmapfile=CreateFileMapping(hfile,NULL,PAGE_READWRITE,0,size,buffer);
             void *p=MapViewOfFile(hmapfile,FILE_MAP_WRITE|FILE_MAP_READ,0,0,size); 
             return p;
}
class BigMem
{
      public:
      List<BYTE *> ptrs;
      int gra;
      int currentsize;
      BigMem(int agra=10)
      {
                 gra=agra;
                 currentsize=0;
      }
      void loadblock(BYTE *p,int size)
      {
          
          int remaintostore=size;
          int restofblock;
          int usedofblock;
          BYTE *newspace;
          int tmp;
          for(int i=0;remaintostore>0;i++)
          {
              if(i==0)
              {
                  usedofblock=currentsize%gra;
                  restofblock=gra-usedofblock; 
                  if(usedofblock==0)
                  {
                     newspace=(BYTE *)malloc(gra);
                     ptrs.add(newspace);
                  }
                  else
                  newspace=ptrs.top()+usedofblock;
                  tmp=remaintostore<=restofblock?remaintostore:restofblock;
                  memcpy(newspace,p,tmp);
                  remaintostore-=tmp;
                  p+=tmp;
                  //printf("____%d\n",restofblock);
              }
              else
              {
                  newspace=(BYTE *)malloc(gra);
                  tmp=remaintostore<=gra?remaintostore:gra;
                  memcpy(newspace,p,tmp);
                  remaintostore-=tmp;
                  p+=tmp;
                  ptrs.add(newspace);
              } 
              
             // printf("____%d\n",tmp);
                   
          }
          
          currentsize+=size;
          
          
      }
      void writetofile(FILE *fp)
      {
          // printf("____%s\n",ptrs.size);
          for(int i=0;i<ptrs.size;i++)
          {
             
             if(i==ptrs.size-1)
             fwrite(ptrs[i],currentsize%gra?currentsize%gra:gra,1,fp);
             else
             fwrite(ptrs[i],gra,1,fp);
          
          } 
      }
      void writetofile(char *name)
      {
           BYTE *p=(BYTE *)getfileptr(name,currentsize);
           //printf("____%d\n",ptrs.size);
          for(int i=0;i<ptrs.size;i++)
          {
             
             if(i==ptrs.size-1)
             {
             memcpy(p,ptrs[i],currentsize%gra?currentsize%gra:gra);
             }
             else
             {
                 memcpy(p,ptrs[i],gra);
                 p+=gra;
             }
             
          
          } 
      }
      
};

