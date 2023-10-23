#include<iostream>
#include<memory>
#include <map>
using namespace std;

class Base 
{
public: 
  virtual ~Base(){};
  void F() {
    f();
  }
  virtual void f() = 0;
protected:
 int m;
};

class InstanceA : public Base {
public:
  void f() {
    m = 1;
    cout<<"this is class A"<<endl;
    cout<<m<<endl;
  }
  ~InstanceA(){
    cout<<"destroy a"<<endl;
  }
};

class InstanceB : public Base {
public:
  void f() {
    m = 2;
    cout<<"this is class B"<<endl;
    cout<<m<<endl;
  }
  ~InstanceB(){
    cout<<"destroy b"<<endl;
  }
};

unique_ptr<Base> MakeB()
{
  return unique_ptr<InstanceB>(new InstanceB());
}

int main()
{
  char * p = new char(10);
  snprintf(p, sizeof(p), "1115%d",5);
  cout<<"before:"<<p<<endl;
  {std::shared_ptr<char> sp(p);}
  cout<<"after:"<<p<<endl;
   std::map<std::string, unique_ptr<Base>> ptrMap;
  unique_ptr<Base> base;
  {
    // unique_ptr<InstanceA> shared_ptr_a(new InstanceA());
    // //unique_ptr<InstanceB> shared_ptr_b(new InstanceB());
    // // shared_ptr_a->f();
    // //shared_ptr_b->f();
    // base = move(shared_ptr_a);
    ptrMap["11"] = move(MakeB());
  }
  ptrMap["11"]->F();
  //base->F();
  // auto fptr = &Base::f;
  // (base.get()->*fptr)();
  // InstanceA a;
  // InstanceA b;
  return 0;
}
