#include<iostream>
#include<string>
#include<map>
using namespace std;

class FuncMap
{
public:
      int op(const std::string & action, const std::string & a, const std::string & b)
      {
            //printf("%p\n",func_map[action]);
            (this->*func_map[action])(a, b);
            return 0;
      }
private:
int funca(const std::string & a, const std::string &b);
static std::map<string, int(FuncMap::*)(const string& a, const string &b)> func_map;
};

std::map<string, int(FuncMap::*)(const string& a, const string &b)> FuncMap::func_map = {
      {"funca", &FuncMap::funca}
};

int FuncMap::funca(const string& a, const string &b)
{
      cout<<a<<" "<<b<<endl; 
      return 0;   
};

int main()
{
      FuncMap obj;
      obj.op("funca", "aaa", "bbb");
      return 0;
}