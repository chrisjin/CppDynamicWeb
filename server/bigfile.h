#include<windows.h>
#include<stdio.h>
#ifndef ______BIGFILE
#define ______BIGFILE
#define FT_CONTENT 2
#define FT_DOWNLOAD 1
#define FT_HOME 0
int TIMES=0;
typedef struct Section
{
   char *con;
   int user;        
    Section()
    {user=0;con=NULL;}    
}Section;

void toLowerCase(string& str)
{
    for (int i = 0; i < str.length(); ++i)
        if (str[i] >= 'A' && str[i] <= 'Z')
             str[i] += ('a' - 'A');
}

void ExtToMime(char *mime,const char *ext)
{
     string nn=ext;
     toLowerCase(nn);
     if(nn==".jpg")
     strcpy(mime,"image/jpeg");
     else if(nn==".gif")
     strcpy(mime,"image/gif");
     else if(nn==".txt")
     strcpy(mime,"text/plain");
     else if(nn==".doc")
     strcpy(mime,"application/msword");
     else if(nn==".bmp")
     strcpy(mime,"image/x-ms-bmp");
     else if(nn==".mp3")
     strcpy(mime,"audio/mpeg");
     else if(nn==".pdf")
     strcpy(mime,"application/pdf");
     else if(nn==".avi")
     strcpy(mime,"video/x-msvideo");
     else if(nn==".png")
     strcpy(mime,"image/png");
     else 
     strcpy(mime,"text/html");
     
}
class BigFile
{
    public:
    HANDLE hmap;
    HANDLE hfile;
    char filename[500];
    char filetitle[200]; 
    char fileext[30];
    char mimetype[30];
    int size; 
    
    
    Section *section;
    int sectionnum;
    BigFile(const char *kfilename)
    {
     hmap=0;hfile=0;size=0;
     initfile(kfilename);initsection();
     }
    ~BigFile()
    {
       //!!!!!!???????为什么 loadsection之前就析构？？？？？ 
              
    }
    void initfile(const char *kfilename)
    {
          hfile= CreateFile(kfilename,GENERIC_WRITE|GENERIC_READ,
                                   FILE_SHARE_READ|FILE_SHARE_WRITE,
                                   0,
                                   OPEN_EXISTING,
                                   FILE_ATTRIBUTE_NORMAL,
                                   0);
          if(hfile==INVALID_HANDLE_VALUE)return;
          strcpy(filename,kfilename);
           //char filetitle[200];
           string nn;
           _splitpath(filename,0,0,filetitle,fileext);
           nn=filetitle;
           nn+=fileext;
           strcpy(filetitle,nn.c_str());
           ExtToMime(mimetype,fileext);
           //cout<<"title"<<fileext<<"name"<<filename<<endl;
          size=GetFileSize(hfile,0);
          
          char buffer[50];
          sprintf(buffer,"zz_%d",TIMES);
          TIMES++;
          hmap=CreateFileMapping(hfile,NULL,PAGE_READWRITE,0,0,buffer);
          
          if(hfile==0)return;
          
    }
    void initsection()
    {
          SYSTEM_INFO gra;
          GetSystemInfo(&gra);
          sectionnum=size/(int)gra.dwAllocationGranularity+1;
          //printf("sectionnum :%d \n",sectionnum );
          section=new Section[sectionnum];
    }
    char* loadsection(int i,int* sendsize)
    {
         SYSTEM_INFO a;
         GetSystemInfo(&a);
         int gra=a.dwAllocationGranularity;
         int remain=size%gra;
         if(section[i].user==0)
         {
             if(i<sectionnum-1)
             {
                  section[i].con=(char *)MapViewOfFile(hmap,PAGE_READONLY,0,i*gra,gra); 
                  *sendsize=gra;
             }
             else  if(i==sectionnum-1)
             {
                  section[i].con=(char *)MapViewOfFile(hmap,PAGE_READONLY,0,i*gra,remain); 
                  *sendsize=remain; 
             }                  
         }
         section[i].user++;
         //printf("____file:%d map:%d size:%d ptr:%d size: %d___",hfile,hmap,size,section[i].con,WSAGetLastError());
         //assert(section[i].con);
         return section[i].con;
    }
    void deloadsection(int i)
    {
        section[i].user--;
        if(section[i].user==0) 
        UnmapViewOfFile(section[i].con);
         
    }

    double sendfile(SOCKET s)
    {
          char *sbuffer;
          int sendsize;
          int feedback;
          int i;
          for(i=0;i<sectionnum;i++)
          {
                sbuffer=loadsection(i,&sendsize)  ;
                feedback=send(s,sbuffer,sendsize,0);
                deloadsection(i); 
                if(WSAGetLastError()==WSAESHUTDOWN)
                {
                 //cout<<endl<<"????"<<WSAGetLastError()<<"????"<<endl;
                 break;
                } 
                else
                if(WSAGetLastError()==10035)
                i--;      
          }  
          return (double)i/(double)sectionnum;     
    }

};
#endif


