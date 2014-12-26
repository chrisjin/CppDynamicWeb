#pragma once
#include<iostream>
#include<string>
using namespace std;
class Style
{ 
   public:
      string Selector;
      string StyleClass;
      string StyleCon;  
      Style()
      {
             
      }  
      Style(string a,string b)
      {
         Selector=a; 
         if(Selector[0]=='.')
           StyleClass=Selector.substr(1,Selector.length());
         else 
           StyleClass=""; 
         StyleCon=b;        
      }
};
//map<string,string> StylePoolbyClass;
//map<string,string> StylePoolbyID;
//map<string,string> StylePoolbyTag;
map<string,string> StylePool;

