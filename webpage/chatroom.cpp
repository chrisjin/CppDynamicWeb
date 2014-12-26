#include"../dll/allheaders.h"
#include"../common/filesystem.h"
#include"../common/decode.h"
#include<time.h>
#include <stdlib.h>
#define  $ Tag
#define  tag Tag
#define  file File
int WebMain()
{
    srand( (unsigned)time( NULL ) );
    Html page=tag.Html();
    Image im=file.Image(200,200);
    for(int i=0;i<256;i++)
    {
        im<<C(rand()%100+156,rand()%100+156,rand()%100+156);
        im<<L(i,0,i,199);
    }
    page[0]<<"<meta http-equiv=Content-Type content=text/html charset=GBK>"; 
    page[1]<<tag.Div()%CSS("background:#FF0;background-image:url("+im.toURI()+");"\
                            "background-repeat:repeat-x;"\
                            "font-size:200%;"\
                            "text-align:center;"\
                            "font-weight:bold;"\
                            "color:green")
           <<"CHATROOM";
    page[1]<<"<hr>";

    page[1]<<tag.Form()%Attr("method","post")%Attr("accept-charset","UTF-8")%Attr("onsubmit","\"document.charset=\'UTF-8\';\"")
           <<S("Name:")+tag.Input("text")%Attr("name","ccccc")+
             S("<br>")+
             S("Text:")+tag.Input("text")%Attr("name","aaaa")+
             S("<br>")+
             tag.Input("submit")%Attr("value","发帖");
    page[1]<<"<hr>";
    
    

    string mode="a+";
    if(A("clear")=="1")
    mode="w+";
    FILE *fp=fopen("log.txt",mode.c_str());

    if(P("ccccc")!=""||P("aaaa")!="")
    {
       string con=P("ccccc")==""?"_":P("ccccc").c_str();
       fwrite(con.c_str(),con.length(),1,fp);
       fprintf(fp," ");
       con=P("aaaa")==""?"_":P("aaaa").c_str();
       fwrite(con.c_str(),con.length(),1,fp);
       fprintf(fp," ");
    }
    fclose(fp);
    fp=fopen("log.txt","r");
    char con[400];
    for(;;)
    {
       int ret=fscanf(fp,"%s",con); 
       if(ret==EOF)break;   
       page[1]<<"Name:"<<URLToANSI(con);
       page[1]<<"<br>";
       ret=fscanf(fp,"%s",con); 
       if(ret==EOF)break; 
       page[1]<<"Text:"<<URLToANSI(con);
       page[1]<<"<br>";
       page[1]<<"<br>";
    }
    fclose(fp);
    Output<<page;
}
