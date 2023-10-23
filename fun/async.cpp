#include<iostream>
#include<mutex>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<functional>
#include "unistd.h"
#include <future>
#include <chrono>         // std::chrono::milliseconds
using namespace std;

std::mutex mtx;


int main()
{
      srand(time(0));
      std::vector<int> vec;
      for(int idx = 0; idx < 1000; idx++)
      {
            vec.push_back(rand() % 1000 + 1);
      }
      
      auto workerFunc = [&] (const vector<int>& vec, int iBegin, int iEnd) -> int {
            for(int idx = iBegin; idx < iEnd; idx++) {
                  sleep(1);
                  cout<<std::this_thread::get_id()<<", "<<"iBegin:"<<iBegin<<" ,iEnd: "<<iEnd<<", :"<< vec[idx]<<endl;
            }
            return 1;
      };

      const int iThreadNum = 10;
      const int iSlice = vec.size() > iThreadNum ?  vec.size() / iThreadNum : vec.size();

      vector< std::future<int> > futVec;
      int iBegin = 0;
      while(iBegin < vec.size())
      {
            int iEnd = min((int)(iBegin + iSlice), (int)vec.size());
            futVec.push_back(std::async(std::launch::async, workerFunc, vec, iBegin, iEnd));
            iBegin = iEnd;
      }
      

      std::chrono::seconds span (11);
      bool bPromiseAll;
      do
      {
        bPromiseAll = true;
        int idx = 0;
        for(auto & fut : futVec)
        {
          const std::future_status status = fut.wait_for(span);
          if( status == std::future_status::ready )
          {
            cout<<"ready"<<endl;
          }
          else if( status == std::future_status::timeout)
          {
            cout<<"timeout"<<endl;
          }
          else if (status == future_status::deferred)
          {
            cout<<"deferred"<<endl;
          }
          idx++;
          bPromiseAll &= ( status == std::future_status::ready);
          cout<< "....this is heart beat in for...."<<idx<<endl;
        }
      }
      while(!bPromiseAll);
      
      for(auto & fut : futVec)
      {
        cout<<fut.get()<<endl;
      }
      
      return 0;
}
