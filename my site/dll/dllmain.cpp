/* Replace "dll.h" with the name of your header */

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#pragma   data_seg("Shared")
HINSTANCE g_hInstance = NULL;
HHOOK hhk=NULL;
HWND outhwnd=NULL;
#pragma   data_seg()
#pragma   comment(linker,"/SECTION:Shared,RWS")  

LRESULT CALLBACK MouseProc(
  int nCode,      // hook code
  WPARAM wParam,  // message identifier
  LPARAM lParam   // mouse coordinates
)
{
  
  MOUSEHOOKSTRUCT *p=(MOUSEHOOKSTRUCT *)lParam;
  char buff[200];
  HDC hdc=GetDC(NULL);
  HWND underhwnd=WindowFromPoint(p->pt);
  SetPixel(hdc,p->pt.x,p->pt.y,RGB(0,255,0));
  GetWindowText(underhwnd,buff,200);
  TextOut(GetDC(underhwnd),0,0,buff,strlen(buff));

  return CallNextHookEx(hhk,nCode,wParam,lParam);    
         
        
       
}
class __declspec(dllexport) test
{
  public: 
         void a(){int k;}      
      
};
int __declspec(dllexport)sethook(HWND hwnd)
{
//MessageBox(NULL,"success call","ssssss",MB_OK);
test m;
outhwnd=hwnd;
HHOOK hhk=SetWindowsHookEx(WH_MOUSE,MouseProc,g_hInstance,0);
//if(hhk==0)MessageBox (0, "hook fail!\n", "Hi", MB_OK);    
}

BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    
    int flag;
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        g_hInstance=hInst; 
        //sethook();
        //MessageBox(NULL,"success inject","ssssss",MB_OK);
        break;

      case DLL_PROCESS_DETACH:
        UnhookWindowsHookEx(hhk);
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
