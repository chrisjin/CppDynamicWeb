#pragma once
#include"allheaders.h"

class Control:public WebObjectPtr
{
      
      
      
};

class Table:public Control
{
      public:
          vector<WebObjectPtr> Rows;
          Table(int r,int c)
          {
              pWebObject=Tag.Table().pWebObject;
              for(int i=0;i<r;i++)
              {
                 WebObjectPtr row=add(Tag.Ling("TR"));
                 add(row);
                 Rows.push_back(row);
                 for(int j=0;j<c;j++)
                 {
                     row.add(Tag.Ling("TD"));
                 }
              }
          }
          vector<WebObjectPtr> get()
          {
              return Rows;                 
                                   
          }
      
      
};
