/*
 * @Author: hengruiqin
 * @Date: 2020-05-13 16:38:29
 * @Company: tencent
 * @Description: 
 */
#include <iostream>
using namespace std;

class Base 
{
public:
    virtual void f1()
    {
        cout<<"this is base"<<endl;
    }

    void f2()
    {
        f1();
    }
};

class Child : public Base
{

public :
    virtual void f1()
    {
        cout<< "this is child"<<endl;
    }
};

int main()
{
    Child c;

    c.f2();
}
