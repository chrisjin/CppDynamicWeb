#ifndef ______DECODE
#define ______DECODE
#include<stdio.h>
#include<windows.h>
wchar_t * UTF8ToUnicode( const char* str )
{
     int textlen ;
     wchar_t * result;
     textlen = MultiByteToWideChar( CP_UTF8, 0, str,-1, NULL,0 ); 
     result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
     memset(result,0,(textlen+1)*sizeof(wchar_t)); 
     MultiByteToWideChar(CP_UTF8, 0,str,-1,(LPWSTR)result,textlen ); 
     return result; 
}

char * UnicodeToANSI( const wchar_t* str )
{
     char* result;
     int textlen;
     textlen = WideCharToMultiByte( CP_ACP, 0, str, -1, NULL, 0, NULL, NULL );
     result =(char *)malloc((textlen+1)*sizeof(char));
     memset( result, 0, sizeof(char) * ( textlen + 1 ) );
     WideCharToMultiByte( CP_ACP, 0, str, -1, result, textlen, NULL, NULL );
     return result;
}


wchar_t * ANSIToUnicode( const char* str )
{
     int textlen ;
     wchar_t * result;
     textlen = MultiByteToWideChar( CP_ACP, 0, str,-1, NULL,0 ); 
     result = (wchar_t *)malloc((textlen+1)*sizeof(wchar_t)); 
     memset(result,0,(textlen+1)*sizeof(wchar_t)); 
     MultiByteToWideChar(CP_ACP, 0,str,-1,(LPWSTR)result,textlen ); 
     return result; 
}

char* w2m(const wchar_t* wcs)
{
      int len;
      char* buf;
      len =wcstombs(NULL,wcs,0);
      if (len == 0)
          return NULL;
      buf = (char *)malloc(sizeof(char)*(len+1));
      memset(buf, 0, sizeof(char) *(len+1));
      len =wcstombs(buf,wcs,len+1);
      return buf;
}

char * UnicodeToUTF8( const wchar_t* str )
{
     char* result;
     int textlen;
     textlen = WideCharToMultiByte( CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL );
     result =(char *)malloc((textlen+1)*sizeof(char));
     memset(result, 0, sizeof(char) * ( textlen + 1 ) );
     WideCharToMultiByte( CP_UTF8, 0, str, -1, result, textlen, NULL, NULL );
     return result;
}

char* ANSIToUTF8(const char* str)
{
     return UnicodeToUTF8(ANSIToUnicode(str));
}

char* UTF8ToANSI(const char* str)
{
     return UnicodeToANSI(UTF8ToUnicode(str));
}

char *URLToANSI(const char *url)
{
     char *whbuff=new char[strlen(url)+10];
     char *bybuff=new char[10];
     int by; 
     
     int urli=0;
     int whbuffi=0;
     while(1)
     {
          if(url[urli]=='%')   
           {
             memset(bybuff,0,10);
             strncpy(bybuff,url+urli+1,2);
             by=strtol(bybuff,0,16);
            // cout<<by<<endl;
             
             memcpy(whbuff+whbuffi,&by,1);
             whbuffi++;
             urli+=3;
           }
           else
           {
               whbuff[whbuffi]=url[urli];
               if(whbuff[whbuffi]=='\0')break;
               whbuffi++;
               urli++;
           }
           //cout<<endl;
           //fwrite(whbuff,10,1,stdout);
             
             
     }
     return UnicodeToANSI(UTF8ToUnicode(whbuff));
}
#endif



