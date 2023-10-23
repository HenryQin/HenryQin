/*
 * @Author: hengruiqin
 * @Date: 2020-06-16 22:44:46
 * @Company: tencent
 * @Description: 
 */ 
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <unordered_set>
using namespace std;

void SplitString(std::string& sInput, std::unordered_set<string>& setOut, std::string sSep = "|")
{
    size_t index = 0;
    std::string::size_type pos;
    do
    {
        pos = sInput.find_first_of(sSep, index);
        if(std::string::npos != pos)
        {
            if(pos > 0)
            {
                setOut.insert(sInput.substr(index, pos - index));
            }

            index = pos + 1;
        }
        else
        {
            setOut.insert(sInput.substr(index));
            break;
        }
    }
    while(index < sInput.size());
}


int main()
{
   string sInput = "||-112||11||";
   std::unordered_set<string> setOut;
   SplitString(sInput, setOut);

   for(auto it : setOut)
   {
      cout<<it<<endl;
   }

   return 0;
}
