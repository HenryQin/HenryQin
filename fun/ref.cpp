#include<vector>
#include<iostream>
#include<unistd.h>
#include<time.h>
using namespace std;

class Obj
{
public:
      Obj():x(0)
      {
            cout<<"construct object"<<endl;
      }

      ~Obj()
      {
            cout<<"deconstruct object"<<endl;
      }

      Obj(const Obj& e)
      {
            cout<<"copy object"<<endl;
      }

      void operator=(const Obj& e)
      {
            cout<<"copy obj in = "<<endl;
      }

      Obj(const Obj&& obj):x(obj.x)
      {
            cout<<"move object"<<endl;
      }
int x;
};

Obj GetTmp()
{    
      Obj Obj1;
      return Obj1;     
}

Obj GetTmpMove()
{
      Obj obj1;
      //return std::move(obj1);  
      return obj1; 
}

int main()
{
      // vector<Obj> vecObj;
      // vecObj.reserve(10);

      // cout<<"push_back object"<<endl;
      // vecObj.push_back(Obj());
      // cout<<endl;
      // cout<<"emplace_back object"<<endl;
      // vecObj.emplace_back();
      // cout<<endl<<endl;
      cout<<"get tmp with move"<<endl;
      Obj&& obj = GetTmpMove();
      cout<<endl;

      cout<<"get tmp "<<endl;
      const Obj& obj1 = GetTmp();
      cout<<endl;
      return 0;
}