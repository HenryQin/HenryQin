#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<cstdlib>
#include<ctime>
#include <algorithm> 
#include<functional>
#include "unistd.h"
using namespace std;

std::mutex mtx;

void testFunc()
{
    srand(time(0));
    std::vector<int> vec;
    for(int idx = 0; idx < 100; idx++)
    {
        vec.push_back(rand() % 1000 + 1);
    }


    std::thread t([](){
        while(true)
        {
            sleep(1);
            cout<< "....this is heart beat...."<<endl;
        }
    });
    t.detach();

    auto workerFunc = [] (const vector<int>& vec, int iBegin, int iEnd) {
        for(int idx = iBegin; idx < iEnd; idx++) {
            sleep(1);
            cout<<std::this_thread::get_id()<<", "<<"iBegin:"<<iBegin<<" ,iEnd: "<<iEnd<<", :"<< vec[idx]<<endl;
        }
    };

    const int iThreadNum = 10;
    const int iSlice = vec.size() > iThreadNum ?  vec.size() / iThreadNum : vec.size();

    vector<thread> workerVec;
    int iBegin = 0;
    while(iBegin < vec.size())
    {
        int iEnd = min((int)(iBegin + iSlice), (int)vec.size());
        workerVec.push_back(std::thread(workerFunc, vec, iBegin, iEnd));
        iBegin = iEnd;
    }

    std::for_each(workerVec.begin(), workerVec.end(), std::mem_fn(&std::thread::join));
}

int main()
{
    testFunc();
    //cout<<ceil(1.0/10)<<endl;
 
    sleep(10);

}
