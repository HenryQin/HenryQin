#include<iostream>
#include<thread>

class Test 
{
public:
    Test():local_(0){};
    static int Func()
    {
        static int count = 0;
        return count++;
    }
    int local()
    {
        return local_++;
    }
private: 
    int local_;
};

void fun()
{   
    Test test;
    std::cout<<Test::Func()<<std::endl;
    std::cout<<test.local()<<std::endl;
}

int main()
{
    std::thread t1(fun);
    std::thread t2(fun);
    std::thread t3(fun);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}