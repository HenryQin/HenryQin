#include <string>
#include <chrono>
#include <iostream>
#include <unistd.h>
using namespace std;
uint64_t GetNowMs() 
{
    auto time_now = chrono::system_clock::now();
    auto duration_in_ms = chrono::duration_cast<chrono::milliseconds>(time_now.time_since_epoch());
    return duration_in_ms.count();
};


static int32_t RET_OK = 0;
class Obj
{
public:
    Obj(int p , const uint64_t & ret = RET_OK):begin_ts_(0), end_ts_(0),ret_(&ret)
    {   
        cout<<"constructor:"<<&ret<<endl;
        begin_ts_ = GetNowMs();
    }

    ~Obj()
    {   
        end_ts_ = GetNowMs();
	    cout<<*ret_<<endl;
        cout<<ret_<<endl;
    }
    
private:
    uint64_t begin_ts_;
    uint64_t end_ts_;
    const uint64_t *ret_;
};

int main()
{   
    cout<<"ptr:"<<&RET_OK<<endl;
    Obj obj(1,RET_OK);
    Obj obj1(1,2);
    Obj obj2(1,2);
}
