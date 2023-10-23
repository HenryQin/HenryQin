#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

class TestClass;
typedef void (TestClass:: *SetString)(const char* x);
typedef void (TestClass:: *SetNumber)(unsigned int x);

class TestClass
{

public:
      TestClass(){};
      ~TestClass(){};

public:
      void SetName1(const char* x)
      {
          cout<<"SetName:"<<x<<endl;
      }

      void SetName2(const char* x)
      {
          cout<<"SetName:"<<x<<endl;
      }

      void SetUnsigned(unsigned int x)
      {
         cout<<"SetNumber:"<<x<<endl;
      }

public:
      void TestMapFunc(std::string & input, unsigned int x)
      {
            SetString func_ptr1 = string_func_map["SetName1"];
            (this->*func_ptr1)(input.c_str());
            SetString func_ptr2 = string_func_map["SetName2"];
            (this->*func_ptr2)(input.c_str());
            SetNumber func_ptr3 = number_func_map["SetNumber"];
            (this->*func_ptr3)(x);
      }
private:
      static std::unordered_map<std::string, SetString> string_func_map;
      static std::unordered_map<std::string, SetNumber> number_func_map;
};

std::unordered_map<std::string, SetString> TestClass::string_func_map = {
    {"SetName1", &TestClass::SetName1},
    {"SetName2", &TestClass::SetName2}
};

std::unordered_map<std::string, SetNumber> TestClass::number_func_map = {
      {"SetNumber", &TestClass::SetUnsigned}
};

int main()
{
      TestClass obj;
      std::string input("input string");
      unsigned int x = 100;
      obj.TestMapFunc(input, x);
}