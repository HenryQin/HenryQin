#include<iostream>
#include<map>
using namespace std;

class TestClass
{

public:
    TestClass():map_iter(testMap.cbegin())
    {
    }

    void PrintMap()
    {
        if(map_iter != testMap.end())
        {
            cout<<map_iter->first<<" "<<map_iter->second<<endl;
            map_iter++;
        }
    }

private:
    static const map<string, string> testMap;
    map<string, string>::const_iterator map_iter;
};

const map<string, string> TestClass::testMap = {
	{"1111","1111"},
	{"2222", "2222"}
};

int main()
{
    TestClass oTest;
    oTest.PrintMap();
    oTest.PrintMap();
}