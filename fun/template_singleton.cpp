#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>

using namespace std;

template <typename CACHE_TYPE, typename CLASS_TYPE>
class MMizIndustryBiCacheBase
{
public:
    static MMizIndustryBiCacheBase& GetInstance()
    {
        static MMizIndustryBiCacheBase<CACHE_TYPE, CLASS_TYPE> instance; // CPP11 静态变量初始化线程安全
        return instance;
    }

    const virtual CACHE_TYPE& GetCache(int& iRet)
    {
        const time_t uCurrTime = time(NULL);
        if (uCurrTime - m_uLastUpdateTime > m_uThreshold)
        {
            iRet = UpdateCache();
            m_uLastUpdateTime = (iRet == 0) ? uCurrTime : m_uLastUpdateTime;
        }
        return m_CacheInfo;
    }

    virtual int UpdateCache(){};

protected:
    MMizIndustryBiCacheBase(const time_t uThreshold = 9)
        : m_uLastUpdateTime(0), 
          m_uThreshold(uThreshold)
    {}
    virtual ~MMizIndustryBiCacheBase() {}
 
private:
    
    MMizIndustryBiCacheBase( const MMizIndustryBiCacheBase& );
    MMizIndustryBiCacheBase& operator=( const MMizIndustryBiCacheBase& );

protected:
    CACHE_TYPE m_CacheInfo;
    time_t  m_uLastUpdateTime;
    time_t  m_uThreshold;
};

class CacheClass: public MMizIndustryBiCacheBase<vector<int>, CacheClass>
{
    friend class MMizIndustryBiCacheBase<vector<int>, CacheClass>;
    int UpdateCache()
    {
        cout<<".....update......"<<endl;
        m_CacheInfo.push_back(1);
    }
private:
    CacheClass():MMizIndustryBiCacheBase(2)
    {
    }
};

int main()
{

    // for(int idx = 0; idx < 10; idx++)
    // {   
    //     int iRet = 0;
    //     vector<int>& cache = CacheClass::GetInstance()->GetCache(iRet);

    //     for(auto elem:cache)
    //     {
    //         cout<<elem<<" ";
    //     }
    //     usleep(5 * 1000 * 1000);
    //     cout<<endl;
    // }

    auto& obj1 = CacheClass::GetInstance();
    auto& obj2 = CacheClass::GetInstance();

    cout<<"ptr1: " << &obj1<<endl;
    cout<<"ptr2: " << &obj2<<endl;

    // CacheClass cacheObj1;
    // CacheClass cacheObj2;

    // CacheClass obj3 = cacheObj1;
    return 0;
}