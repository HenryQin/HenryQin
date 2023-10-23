#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
using namespace std;

template<typename T>
class Singletone
{
public:
    static T* GetInstance()
    {
        static T instance;
        return &instance;
    }

protected:
    virtual  ~Singletone(){};
    Singletone(){};
private:  
    Singletone(const Singletone&);
    Singletone& operator=( const Singletone& );
};

template<typename T>
class CacheBase
{
public:

    CacheBase(time_t uLastUpdateTime = 900)
        :m_uLastUpdateTime(0), 
        m_uThreshold(uLastUpdateTime) 
    {
    };

    virtual T& GetCache(int& iRet)
    {
        const time_t uCurrTime = time(NULL);
        if (uCurrTime - m_uLastUpdateTime > m_uThreshold)
        {
            iRet = UpdateCache();
            m_uLastUpdateTime = (iRet == 0) ? uCurrTime : m_uLastUpdateTime;
        }
        return m_CacheInfo;
    }

protected:
    virtual int UpdateCache() = 0;
    virtual ~CacheBase(){};

protected:
    time_t  m_uLastUpdateTime;
    time_t  m_uThreshold;
    T m_CacheInfo;
};

class TestCache: public CacheBase<vector<int>>, public Singletone<TestCache>
{
friend class Singletone<TestCache>;
public:
    int UpdateCache()
    {
        cout<<".....update......"<<endl;
        m_CacheInfo.push_back(1);
    }

    ~TestCache(){}
private:
    TestCache(){}
};

int main()
{   
    int iRet = 0;
    TestCache::GetInstance()->GetCache(iRet);
}
