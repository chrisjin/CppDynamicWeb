#include"../common/common.h"

static int tmp_css_id=0;
class CSS
{
     public:
       string Sheet;
       string Class;
       map<string,string> Item;
       CSS()
       {
            
       }
       CSS(string a)
       {
          Sheet=a;  
          Class=S("CSS")+I2S(tmp_css_id);  
       }
       void set(string a)
       {
          Sheet=a;     
       }
        
      
      
};
