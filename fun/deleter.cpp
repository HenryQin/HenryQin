#include<memory>
#include<stdio.h>
#include <system_error>

class Resource 
{
public:
      Resource()
      {
            printf("created Resource\n");
      }
      ~Resource()
      {
            printf("Resource deleted\n");
      }
      void Print() {
            printf("hello world!\n");
      }
};



class Deleter
{
public:
      void operator()(Resource* in) {
            printf("Delelter delete Resource\n");
            delete in;
            in = NULL;
      }
};

std::unique_ptr<Resource, Deleter> GetResource()
{
      return std::unique_ptr<Resource, Deleter>(new Resource(), Deleter());
}

int main()
{
      auto ptr_res = GetResource();
      ptr_res->Print();
      return 0;
}