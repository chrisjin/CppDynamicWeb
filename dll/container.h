#pragma once
#include"doms.h"
class Container
{
    public:
    ClientInfo *ClientP;
    bool isneeddelay;
    __WebObject* delayedobject;
    Container(ClientInfo *a) 
    {
 
        ClientP=a;               
    }
    Container()
    { }
    void get(ClientInfo *a)
    {
        ClientP=a; 
    } 
    void add(__WebObject *s)
    {
        ClientP->MainSrc=new Resource;
        ClientP->MainSrc->Type="TEXT";
        ClientP->MainSrc->Text=s->getHtml();
        ClientP->MainSrc->MimeType="text/html";
        ClientP->SourcePool=new map<string,Resource*>;
        ClientP->SourcePool->swap(DllSourcePool);
        s->destroy();
    }
    void add(string s)
    {
        ClientP->MainSrc=new Resource;
        ClientP->MainSrc->Type="TEXT";
        ClientP->MainSrc->Text=s;
        ClientP->MainSrc->MimeType="text/plain";
        ClientP->SourcePool=new map<string,Resource*>;
        ClientP->SourcePool->swap(DllSourcePool); 
         
    }
    void add(__BinFile *s)
    {
        ClientP->MainSrc=new Resource;
        ClientP->MainSrc->Type="BIN";
        ClientP->MainSrc->Bin=s->FilePtr;
        ClientP->MainSrc->BinL=s->FileSize;
        ClientP->MainSrc->MimeType=s->MimeType;
        ClientP->SourcePool=new map<string,Resource*>;
        ClientP->SourcePool->swap(DllSourcePool); 
         
    } 
    void add(__TxtFile *s)
    {
        ClientP->MainSrc=new Resource;
        ClientP->MainSrc->Type="TEXT";
        ClientP->MainSrc->Text=s->Content;
        ClientP->MainSrc->MimeType="text/plain";
        ClientP->SourcePool=new map<string,Resource*>;
        ClientP->SourcePool->swap(DllSourcePool); 
    }
      
};
