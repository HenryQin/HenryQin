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
using namespace std;

bool IsDigit(const char * str, int len)
{
	if(len <= 0) return false;

	int idx = 0;
	while(idx < len)
	{
	  if(!isdigit(*(str + idx)))
	  {
		return false;
	  }
	  idx++;
	}

	return true;
}

int main()
{
   std::string str_auto = ".-1";
  
   cout<<IsDigit(str_auto.c_str(), str_auto.length())<<endl;
   cout<<atoi(str_auto.c_str())<<endl;
   return 0;
}
