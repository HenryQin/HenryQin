#include<iostream>
#include<mutex>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<functional>
#include "unistd.h"
#include <future>
#include <chrono>         // std::chrono::milliseconds
#include <exception>
using namespace std;

auto worker = [] () -> int {
      for (int x = 0; x < 10; x++)
      {
           cout << "this is async thread" << endl; 
           sleep(1);
      }
      throw "async exption";
      cout<< "async thread exit" <<endl;
      return 1;
};

int main()
{
    std::future<int> future;
    future = std::async(std::launch::async, worker);
   
    auto span = std::chrono::seconds(1);
    int idx = 0;
    while ( future.wait_for(span) != std::future_status::ready)
    {
      cout<<"this is main thread"<<endl;
    }
    return 0;
}