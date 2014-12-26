#pragma once
#include"doms.h"


#define DefOpjectClass(type,argtype) \
class type##Ptr:public WebObjectPtr\
{\
   public:\
      type##Ptr(argtype a)\
      {\
         pWebObject = new __##type(a);\
      }\
}

#define DefOpjectClassWithTwoArg(type,argtype1,argtype2) \
class type##Ptr:public WebObjectPtr\
{\
   public:\
      type##Ptr(argtype1 a,argtype2 b)\
      {\
         pWebObject = new __##type(a,b);\
      }\
}

#define DefOpjectClassWithnoArg(type) \
class type##Ptr:public WebObjectPtr\
{\
   public:\
      type##Ptr()\
      {\
         pWebObject = new __##type;\
      }\
}


#define DefOpjectClassWithDualCst(type,argtype) \
class type##Ptr:public WebObjectPtr\
{\
   public:\
      type##Ptr()\
      {\
         pWebObject = new __##type;\
      }\
      type##Ptr(argtype a)\
      {\
         pWebObject = new __##type(a);\
      }\
}
class WebObjectPtr
{
   public:
        WebObjectPtr(){}
        WebObjectPtr(__WebObject *p){pWebObject=p;}
         __WebObject *pWebObject; 
        WebObjectPtr add(const WebObjectPtr &k)
        {
             pWebObject->add(k.pWebObject);
             return k;
        }
        WebObjectPtr addProperty(string a,string b)
        {
             pWebObject->addProperty(a,b);
             return *this;
        }
        void useStyle(Style k)
        {
             pWebObject->useStyle(k);
        } 
        WebObjectPtr operator[](int i)  
        {
            WebObjectPtr ret(pWebObject->InnerObject[i]);
            return ret;             
        }  
      
};
DefOpjectClass(Text,string);
DefOpjectClassWithDualCst(Button,string);
DefOpjectClass(Img,string);
DefOpjectClass(Ling,string);
DefOpjectClassWithTwoArg(Link,string,string);
DefOpjectClass(Input,string);  
DefOpjectClass(Frame,string);
DefOpjectClass(Script,string);
DefOpjectClass(JSFunc,string);
DefOpjectClassWithnoArg(Div);
DefOpjectClassWithnoArg(Form);
DefOpjectClassWithnoArg(Table);
DefOpjectClassWithnoArg(Frameset);
DefOpjectClassWithnoArg(Body);   
DefOpjectClassWithnoArg(Head);  
DefOpjectClassWithnoArg(JavaScript);   
//DefOpjectClassWithnoArg(CSS);  
DefOpjectClassWithnoArg(AJAX_send); 
DefOpjectClassWithnoArg(Html);   


