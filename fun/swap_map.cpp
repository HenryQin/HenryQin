#include<iostream>
#include<map>
#include<string>
using namespace std;

std::map<std::string, std::string> strmap = {
      {"str1", "1"},
      {"str2", "2"}
};

std::map<std::string, std::string> & Swap()
{     
      std::map<std::string, std::string> tmp ={
            {"str1", "3"},
            {"str2", "4"} 
      };
      strmap.clear();
      strmap["str1"] = "3";
      strmap["str2"] = "4";
      strmap["str0"] = "4";
      return strmap;
} 

int main()
{
    auto iter = strmap.find("str1");
    std::map<std::string, std::string> & tmp = Swap();
    cout<<iter->second<<endl;  
    iter = tmp.find("str1");
    cout<<iter->second<<endl;
}