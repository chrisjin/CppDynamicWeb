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




//-----------------------------------------------------------------------------------------

      Html page;
      Image im=File.Image(200,200);
      for(int i=0;i<200;i++)
      {
        im<<C(i,i,0);
        im<<L(i,0,i,199);
        
      }
  
      int binheight[7]={60,20,200,40,100,20,10};
      drawBins(im,binheight,7);
      
      Html pp=tag.Html();
      pp<<Button()<<Img(im.toURI());
      page[1]<<tag.Form()<<S("Name:")+tag.Input("text")+
                         S("Input:")+tag.Input("text")
                         +tag.Input("submit");
      page[1]<<tag.Button("123333")+tag.Button("aaaa");
      page[1]<<S("444444")+(tag.Button()<<S("DDDDDDD"))+S("sdssss");
      page[1]<<tag.Div()<<S("sssss")+S("MMMMMM")+tag.Button("ÈË°¡ÈË");
      
      Image im2("src/Landda.bmp");
      im2<<C(0,255,0)<<L(0,0,400,400);
      page[1]<<tag.Button()<<tag.Img(file.Image("src/file.png").toURI()); 
      page[1]<<tag.Img(im2.toURI());
      
      TxtFile test;
      test.load("src/v.txt");
   //   cout<<"::::::"<<test.Content<<endl;
      
      
      
    
      Output<<im;


//-----------------------------------------------------------------------------------------    
      
  
      return 0;
}


