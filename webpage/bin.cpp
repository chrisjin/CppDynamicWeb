#include"../dll/allheaders.h"
#define  $ Tag
#define  tag Tag
#define  file File
void drawBins(Image im,int *binheight,int size)
{
      for(int i=0;i<size;i++)
      {
      im<<C(0,255*((i+1)%2),255*(i%2));
      im<<R(P(i*10,0),P(10,binheight[i]),1);
      im<<CC(P(100,100),100);
      } 
}
int WebMain()
{
      
      Image im=File.Image(200,200);
      for(int i=0;i<200;i++)
      {
        im<<C(i,i,0);
        im<<L(i,0,i,199);
      }
      int binheight[7]={60,20,50,40,100,20,10};
      drawBins(im,binheight,7);
      
    
    Output<<im;
    
  return 0;    
}
