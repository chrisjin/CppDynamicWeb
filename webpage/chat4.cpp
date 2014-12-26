#include"../dll/doms.h"
#include"../dll/dllmain.h"
#include"../dll/argparser.h"
#include"../common/common.h"

int WebMain(ClientInfo *a,char* arg)
{
      
      ArgParser parser;
      printf("%s",URIBase.c_str());
      FILE *fp=fopen("log10.txt","a+");
      if(fp==0) return 0;
      char *buff;
      string str1,str2;
      if(a->PostSpace)
      {
             parser.parse(a->PostSpace);
             str1=parser.get("INPUT0");
             str2=parser.get("INPUT1");
             if(str1=="")
             str1="-";
             if(str2=="")
             str2="-";
             fwrite(str1.c_str(),str1.length(),1,fp);
             fwrite(" ",1,1,fp);
             fwrite(str2.c_str(),str2.length(),1,fp);
             fwrite(" ",1,1,fp);
             fclose(fp);
       }
      
      
      Html pagetotal(0);
      Frameset frmst;
      frmst.addProperty("rows","%20,%80");
      Frame fm1("chat3.exe?frame=0");
      Frame fm2("chat3.exe?frame=1");
      frmst.add(&fm1);
      frmst.add(&fm2);
      pagetotal.add(&frmst);



      Html pagetop;
      Form form;
      WebObject *ob;
      form.write("Name:");ob=new Input("text");ob->addProperty("name",ob->ID);
      form.add(ob);
      form.write("Input:");ob=new Input("text");ob->addProperty("name",ob->ID);
      form.add(ob);
      form.write("FILE:");ob=new Input("file");ob->addProperty("name",ob->ID);
      form.add(ob);
      form.write("<br>");
      ob=new Input("submit");
      form.add(ob);
      form.addProperty("method","post");
      form.addProperty("enctype","multipart/form-data");
      pagetop.add2Bo(&form);
      
      Link lk("javascript:sendContent(\'POST\',\'SSSSSS\',\'11\')");
      lk.write("LLL");
      pagetop.add(&lk);
      pagetop.AJAX_init();


      

      
      
      Html pagebottom;
      Script js("javascript");
     // js.write("window.setInterval(\"parent.frames[1].location.reload()\",1000);");
      pagebottom.add2Bo(&js);
      char tmp[100];
      fp=fopen("log10.txt","r");
      if(fp==0)return 0;
      for(;;)
      {
          
          buff=(char *)malloc(410);
          memset(buff,0,410);
              
          int ret=fscanf(fp,"%s",tmp);
          if(feof(fp)||ret==EOF)
          {
          fclose(fp);
          break;
          }
          strcat(buff,tmp);
          strcat(buff,": "); 
          ret=fscanf(fp,"%s",tmp);
          if(feof(fp)||ret==EOF)
          {
          fclose(fp);
          break;
          } 
          strcat(buff,tmp);
          strcat(buff,"<br>"); 
          pagebottom.add2Bo(new Text(buff));     
      } 

     
      
      
      
      
      
   end:   
      parser.parse(arg);
      Container con(a);
      if(parser.get("frame")=="")
      con.addHtml(&pagetotal);
      else if(parser.get("frame")=="0")
      con.addHtml(&pagetop);
      else if(parser.get("frame")=="1")
      con.addHtml(&pagebottom);
      return 0;
}


