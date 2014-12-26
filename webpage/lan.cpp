#include"../dll/allheaders.h"
#define  $ Tag
#define  tag Tag
#define  file File

int WebMain()
{
      Image im2=file.Image("src/Landda.bmp");
      im2<<C(0,255,0)<<L(0,0,400,400);
    
    
    Output<<im2;
    
  return 0;    
}
