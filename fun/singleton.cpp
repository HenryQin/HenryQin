#include<iostream>
#include<string.h>
#include<thread>
#include<mutex>
#include<vector>
#include<sstream>
using namespace std;
std::mutex mtx;

class Singletone
{

public:
    Singletone()
    {
        std::ostringstream oss;
        oss<< this_thread::get_id();
        string str_id = oss.str();
        for(int i = 0; i < 20; i++)
        {
            cout<<"th_id: "<< str_id <<" i: "<<i<< endl;
        }
    }
};

void GetSingltone()
{
    mtx.lock();
    Singletone single;
    mtx.unlock();
}

int main()
{

    // thread t1(GetSingltone);    
    // thread t2(GetSingltone);
    // thread t3(GetSingltone);
 
    // t1.join();
    // t2.join();
    // t3.join();
    return 0;
}
