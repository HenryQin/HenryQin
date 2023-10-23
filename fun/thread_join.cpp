#include <thread>
#include <iostream>
#include <unistd.h>
#include <exception>
using namespace std;


bool runFlag = true;
void StartThread()
{   
    try {
        std::thread mythread([&]{
            do {
                cout<<"fuck hok"<<endl;
                sleep(1);
            }while(runFlag);
            cout<<"stop fucking"<<endl;
        });
        cout<< "thread detach"<<endl;
        mythread.detach();
    }
    catch(exception & e){
        cout<< "catch exception what:"<<e.what()<<endl;
    }
    catch(...){
        cout<< "catch unknow exception what:"<<endl;
    }
}

int main() 
{
    StartThread();
    cout<<"main thread create succ"<<endl;
    sleep(10);
    runFlag = false;
    cout<< "stop thread"<<endl;
    return 0;
}