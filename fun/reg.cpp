#include <regex>
#include <iostream>
#include <string>
using namespace std;

bool CheckPhone(const std::string & sPhoneNum)
{
    std::regex phoneReg("^1[3-9]\\d{9}$|^0\\d{2,3}-\\d{7,8}$");
    return std::regex_match(sPhoneNum, phoneReg);
}

int main() 
{
    cout<<CheckPhone("13580433262")<<endl;
    cout<<CheckPhone("020-22808304")<<endl;
    cout<<CheckPhone("13800000138")<<endl;

    return 0;
}