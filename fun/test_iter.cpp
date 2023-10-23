#include<set>
#include<iostream>
using namespace std;

int main()
{
	set<int> myset = {1,2,3,4,5};
	set<int>::iterator iter = myset.begin();
	set<int>::iterator next = std::next(iter);
	cout<<*next<<endl;
	
	for(auto iter = myset.begin(); iter != myset.end();iter++)
	{
		if((iter+1) == myset.end())
		{
		   cout<<*iter<<endl;
		}
	}

	return 0;
}
