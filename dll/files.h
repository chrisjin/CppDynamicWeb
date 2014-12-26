#pragma once
#include"globalvars.h"
#include<windows.h>
#include<string>
#include"imageele.h"
#include"freeimage.h"
using namespace std;

class __File
{
        public:
        virtual void* save(BYTE *pFile=0)
        {}  
        virtual void destroy()
        {} 
};
class __BinFile:public __File
{
   public:
        string ID;  
        BYTE *FilePtr;
        DWORD FileSize; 
        string MimeType; 



};

static int tmp_image_id=0;
class __Image:public __BinFile
{
    public:
    
    FIBITMAP* hImage;
    BYTE *Bits;
    
    DWORD Pitch;
    DWORD Height;
    DWORD Width;
    DWORD Depth;
    
    _RGB CurrentClr;
    
    
    __Image(int x,int y,int depth=24)
    { 
       CurrentClr.r=0;
       CurrentClr.g=0;
       CurrentClr.b=0;
       ID="Image"+I2S(tmp_image_id);
       tmp_image_id++;
       hImage=FreeImage_Allocate (x , y ,depth,0x0000ff) ;
       Bits=FreeImage_GetBits(hImage);  
       Pitch=FreeImage_GetPitch(hImage);
       Height=x;
       Width=y;
       Depth=depth;
       MimeType="image/jpeg";
    }
    __Image(string name)
    {
        CurrentClr.r=0;
        CurrentClr.g=0;
        CurrentClr.b=0;
        ID="Image"+I2S(tmp_image_id);
        tmp_image_id++;
        load(name); 
        MimeType="image/jpeg";         
    }
    void setColor(_RGB *p)
    {
        memcpy(&CurrentClr,p,sizeof(_RGB));

         
    }
    void load(string filename)
    {
       string afilename="../webpage/";//服务器相对于资源的位置 此变量日后应改为环境变量由服务器传入 
       afilename+=filename;
       ID="Image"+I2S(tmp_image_id);
       tmp_image_id++;
       FREE_IMAGE_FORMAT format=FreeImage_GetFileType(afilename.c_str());  
       hImage=FreeImage_Load(format,afilename.c_str());
       
       Bits=FreeImage_GetBits(hImage); 
      // 
       Pitch=FreeImage_GetPitch(hImage); 
       Height= FreeImage_GetHeight(hImage);  
       Width=FreeImage_GetWidth(hImage);
       Depth=FreeImage_GetBPP(hImage);
    } 
    void* save(BYTE *pFile=0)
    {
       if(pFile==0)
       {
            FIMEMORY* mem=FreeImage_OpenMemory(); 
           // FreeImage_Invert(hImage);
          //  FreeImage_ConvertTo24Bits(hImage); 
            int ret=FreeImage_SaveToMemory(FIF_JPEG,hImage,mem,JPEG_DEFAULT);   
            FreeImage_AcquireMemory(mem,&FilePtr,&FileSize);
         //   printf(":::::%d,%d,%d\n",hImage,FileSize,ret);   
         return mem;
       }     
    }
    BYTE *get(int x,int y)
    {
       BYTE *ret=Bits;
      // cout<<":::::"<<Width<<endl;
       x=x>=Width?(Width-1):x;
       y=y>=Height?(Height-1):y;
       if(x<0)x=0;
       if(y<0)y=0;
       ret+=y*Pitch+x*Depth/8; 
       return ret;   
         
    }
    void fill(void *p)
    {
       FreeImage_FillBackground(hImage,p);   
    }
    void putLine(int x1,int y1,int x2,int y2,_RGB* color=0)
    {
        
        if(color==0)
            color=&CurrentClr;
        
    	int xinc1, xinc2, yinc1, yinc2, den, num, numadd, numpixels;
    	int deltax = abs(x2 - x1);        	// The difference between the x's
    	int deltay = abs(y2 - y1);        	// The difference between the y's
    	int x = x1;                       	// Start x off at the first pixel
    	int y = y1;                       	// Start y off at the first pixel
    	
    	if (x2 >= x1)                 		// The x-values are increasing
    	{
    		xinc1 = 1;
    		xinc2 = 1;
    	}
    	else                          		// The x-values are decreasing
    	{
    		xinc1 = -1;
    		xinc2 = -1;
    	}
    	
    	if (y2 >= y1)                 		// The y-values are increasing
    	{
    		yinc1 = 1;
    		yinc2 = 1;
    	}
    	else                          		// The y-values are decreasing
    	{
    		yinc1 = -1;
    		yinc2 = -1;
    	}
    	
    	if (deltax >= deltay)         		// There is at least one x-value for every y-value
    	{
    		xinc1 = 0;                  	// Don't change the x when numerator >= denominator
    		yinc2 = 0;                  	// Don't change the y for every iteration
    		den = deltax;
    		num = deltax / 2;
    		numadd = deltay;
    		numpixels = deltax;         	// There are more x-values than y-values
    	}
    	else                          		// There is at least one y-value for every x-value
    	{
    		xinc2 = 0;                  	// Don't change the x for every iteration
    		yinc1 = 0;                  	// Don't change the y when numerator >= denominator
    		den = deltay;
    		num = deltay / 2;
    		numadd = deltax;
    		numpixels = deltay;         	// There are more y-values than x-values
    	}
    	
    	for (int curpixel = 0; curpixel <= numpixels; curpixel++)
    	{
    		this->get(x, y)[FI_RGBA_RED]=color->r;   // Draw the current pixel
    		this->get(x, y)[FI_RGBA_GREEN]=color->g;
            this->get(x, y)[FI_RGBA_BLUE]=color->b;
            num += numadd;              	// Increase the numerator by the top of the fraction
    		if (num >= den)             	// Check if numerator >= denominator
    		{
    			num -= den;               	// Calculate the new numerator value
    			x += xinc1;               	// Change the x as appropriate
    			y += yinc1;               	// Change the y as appropriate
    		}
    		x += xinc2;                 	// Change the x as appropriate
    		y += yinc2;                 	// Change the y as appropriate
    	}
             
    } 
    void putRect(Point a,Point b)
    {
        putLine(a.x    ,a.y    ,a.x+b.x,a.y    ); 
        putLine(a.x+b.x,a.y    ,a.x+b.x,a.y+b.y);
        putLine(a.x    ,a.y+b.y,a.x+b.x,a.y+b.y);
        putLine(a.x    ,a.y+b.y,a.x    ,a.y    );
         
    }
    BYTE *operator()(int x,int y)
    {
       BYTE *ret=Bits;
       ret+=y*Pitch+x*Depth/8; 
       return ret; 
    }
    string toURI()
    {
               FIMEMORY *p=(FIMEMORY *)save();
               string ret=URIBase+S("?")+S("srcpool=")+ID;
               Resource *r=new Resource;
               r->Type="BIN";
               r->MimeType=MimeType;
               r->Bin=(BYTE *)malloc(FileSize);//必须分配全局指针 否则可能dll内存地址和exe地址有错位 
               memcpy(r->Bin,FilePtr,FileSize);
               r->BinL=FileSize;
            //   printf("DLLIMAGEsize:%d,Ptr:%d\n",FileSize,FilePtr);
               r->obsolete=0;
              // FreeImage_CloseMemory(p);    此句不能要 
               DllSourcePool[ret]=r;
               return ret;       
    }
    void destroy()
    {
         
         
    }
    
     
};
static int tmp_txtfile_id=0;
class __TxtFile:public __File
{
    public:
    FILE *fp;
    string ID; 
    string MimeType; 
    string Content;
    void init()
    {
       ID="TxtFile"+I2S(tmp_txtfile_id); 
      tmp_txtfile_id++;
       MimeType="text/plain";    
    }
    __TxtFile()
    {init();}
    __TxtFile(string con)
    {
       init();
       Content=con;            
    }
    __TxtFile(FILE *fp)
    {
       init();      
    }
    void load(string name)
    {
       string afilename="../webpage/";
       fp=fopen((afilename+name).c_str(),"r");
       if(!fp)cout<<"::::::TxtFile"<<endl;
       fseek(fp,0,SEEK_END );
       int l=ftell(fp);
       fseek(fp,0,SEEK_SET );
       char *buff=(char *)malloc(l+5);
       memset(buff,0,l+5);
       if(!buff)cout<<"::::::TxtFile"<<endl;
       fread(buff,l,1,fp);
       Content=buff;
       free(buff);
       fclose(fp);
    }
        
};
