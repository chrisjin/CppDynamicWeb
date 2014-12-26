#include"../dll/allheaders.h"
#include"../common/filesystem.h"
#define  $ Tag
#define  tag Tag
#define  file File
int WebMain()
{
  //   printf("************");
    Html page=tag.Html();
    Image im=file.Image(200,200);
    for(int i=0;i<256;i++)
    {
        im<<C(30+i,30+i,0);
        im<<L(i,0,i,199);
    }
    page[1]<<tag.Div()%CSS("background:#FF0;background-image:url("+im.toURI()+");"\
                            "background-repeat:repeat-x;"\
                            "font-size:200%;"\
                            "text-align:center;")
           <<"ÎÒµÄµçÄÔ";
    page[1]<<"<hr>";

    vector<Fileinfo> fileinfo;
    if(A("dir")=="")
    {
        getfolderinfo(0,fileinfo);
    }
    else
    {
         getfolderinfo(A("dir").c_str(),fileinfo);   
    }
    int flag=A("dir").length()<=2?0:2;

    
    
    Image lo=file.Image(10,10);
    for(int i=0;i<10;i++)
    {
          lo<<C(255-i,255-i,0);
          lo<<L(i,0,i,199);  
    }
    for(int i=flag;i<fileinfo.size();i++)
    {
        if(!fileinfo[i].isfolder)continue;
        page[1]<<tag.Img(lo.toURI());
        if(A("dir")=="")
        page[1]<<tag.Link(S("filesystem1.exe?dir=")+fileinfo[i].name,fileinfo[i].name)  ;
        else
        page[1]<<tag.Link(S("filesystem1.exe?dir=")+A("dir")+"/"+fileinfo[i].name,fileinfo[i].name)  ;
        page[1]<<"<br>";  
    }
    
    for(int i=flag;i<fileinfo.size();i++)
    {
        if(fileinfo[i].isfolder)continue;
        if(A("dir")=="")
        page[1]<<tag.Link(S("filesystem1.exe?dir=")+fileinfo[i].name,fileinfo[i].name)  ;
        else
        page[1]<<tag.Link(S("filesystem1.exe?dir=")+A("dir")+"/"+fileinfo[i].name,fileinfo[i].name)  ;
        page[1]<<"<br>";  
    }


    Output<<page;
}
