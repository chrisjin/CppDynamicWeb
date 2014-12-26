#include<windows.h>
#include<string>
using namespace std;
typedef int (*startWebMainfun)(ClientInfo *a,char* arg,string filename); 
class WebInterface
{
    public:
      HINSTANCE h;
      startWebMainfun startwebmainfun;
      WebInterface(string name)
      {
        h=LoadLibrary(name.c_str());
        if(h!=0)
        startwebmainfun=(startWebMainfun)GetProcAddress(h,"_Z12startWebMainP10ClientInfoPcSs");                  
                          
      }
      WebInterface(){}
      int getEntry(string name)
      {
        h=LoadLibrary(name.c_str());
        if(h!=0)
        startwebmainfun=(startWebMainfun)GetProcAddress(h,"_Z12startWebMainP10ClientInfoPcSs");
        return (int)h;         
      }
      ~WebInterface()
      {
        if(h!=0)
        FreeLibrary(h);
      }
      int webmain(ClientInfo *a,char* arg,string filename)
      {
        if(startwebmainfun!=0)
        return startwebmainfun(a,arg,filename);
        else
        return -1;
      } 
        
};
