#ifndef ______BIT
#define ______BIT
#include<vector>
#define List list
using namespace std;
class Bit
{
     public:
          vector<unsigned int> rank;
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

