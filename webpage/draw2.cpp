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

     Image im=file.Image(200,200);
     im<<C(0,255,0);
     im<<L(0,0,100,100);

//-----------------------------------------------------------------------------------------


   
      
      Style st=CSS("background:#FFF");
      Style nsel=CSS("button img","background:#0F0");
      Html kk=tag.Html();
   //   CSS css("KKKKKKKK");
    //  tag.begin(css);
     // ((__Html *)kk.pWebObject)->Css.add(tag.Text("ssssss").pWebObject);
      
      kk[1]<<(
            S("KKK")
             +(tag.Button("xxxxx")<<tag.Img(im.toURI()))
             +tag.Img(im.toURI())
             +S("ddddd")+S("<hr>")
             )%st;
      kk[1]<<tag.Form()<<"ssss"+tag.Input("submit");
    //  tag.end();
      Button bb=tag.Button("xxxxx");
      
      kk[1]<<(bb+tag.Button("aaa"))%st;
      kk[1]<<tag.Div()%CSS("background:#0F0")<<"TestDiv";
      kk[1]%nsel;
      Output<<kk;
      
//-----------------------------------------------------------------------------------------    
      
  
      return 0;
}


