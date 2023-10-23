#include<unordered_set>
#include<iostream>
#include<string>
using namespace std;

#define RESORCE_ENTRY_SET(...)\
unordered_set<string> setResourceEntry = {__VA_ARGS__};

struct TestStruct
{
   TestStruct(int z):a(1), b(z), c('3')
   {
   }

   int a;
   int b;
   char c;
};

int main()
{
   RESORCE_ENTRY_SET("next", "list", "then");  

   char Mem[18]={'\0'};

   TestStruct* ptrStruct1 = new(Mem) TestStruct(10);
   
   TestStruct* ptrStruct2 = new(ptrStruct1 + 1)TestStruct(20);

   cout<<ptrStruct1->a<<" "<<ptrStruct1->b<<" "<<ptrStruct1->c<<endl;
   cout<<ptrStruct2->a<<" "<<ptrStruct2->b<<" "<<ptrStruct2->c<<endl;
}