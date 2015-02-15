#ifndef ______BIT
#define ______BIT
#include"list.h"
class Bit
{
     public:
          List<unsigned int> rank;
          Bit(int anum)
          {
                  unsigned int judge=1;
                  for(int i=0;i<31;i++)
                  {
                        if((anum|judge)==anum)
                        rank.push_back(i);
                        judge=judge<<1;
                  }      
          }   
      
      
};

#endif

