#include<iostream>
#include <mutex>
#include <functional>
#include <algorithm>

using namespace std;
int Wrapper(int iUin, std::function<int( int )> func)
{
  return func(iUin);
};

int main()
{
  cout<< Wrapper(10, [](int idx)-> int {
    cout<<idx<<endl;
    return 1;
  } ) <<endl;

  vector<int> vec = {12,10, 1, 9};
  std::sort(vec.begin(), vec.end(), [](const int& a, const int& b)->bool { return a > b;});  
  for(auto a : vec)
  {
	  cout<<a<<" ";
  }
  return 0;
};
