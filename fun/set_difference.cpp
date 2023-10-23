#include<set>
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
      set<int> s1 = {1,2,3,4,5,6};
      set<int> s2 = {4,5,6,7};

      std::set_difference(s1.begin(),s1.end(), s2.begin(), s2.end());
}