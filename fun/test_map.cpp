#include<unordered_map>
#include<unordered_set>
#include<iostream>
using namespace std;

unordered_map<std::string, unordered_set<int> > mapSet;

void ADD(std::string name)
{
	mapSet[name].insert(0);
	mapSet[name].insert(1);
};

void GET(std::string name)
{
	for(auto elem : mapSet[name])
	{
		cout<<elem<<endl;
	}
};

int main()
{
  ADD("MY");
  ADD("MY1");

  GET("MY");
  GET("MY1");
  
  return 0;
}
