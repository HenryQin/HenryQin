#include<iostream>
#include<memory>
using namespace std;

class Test {
public:
	Test():a(1),b(2){};
	int a;
	int b;
};

int main()
{
  Test * tmp_ptr = NULL;
  std::unique_ptr<Test> ptr1(new Test);
  std::unique_ptr<Test> ptr2(tmp_ptr);
  
  cout<<"ptr1:"<<ptr1.get()<<" ptr2:"<<ptr2.get()<<endl;
  cout<<"ptr1 a = "<<(*ptr1).a<<endl;
  
  Test obja;
  const Test & refa = obja;
  Test& refb = const_cast<Test& >(refa);
  refb.a = 2;
  cout<<refa.a<<endl;
  return 0;

}
