#include<string>
using namespace std;

template<typename T>
void New(T * ptr)
{
  ptr = T::NEW();
}

int main()
{
  std::string * ptrStr;
  New(ptrStr);
  return 0;
}
