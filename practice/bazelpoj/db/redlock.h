/**
 * @file redlock.h
 * @author henryqin (you@domain.com)
 * @brief distributed locked using redis
 * @version 0.1
 * @date 2021-08-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "redisapi.h"
#include <string>
#include <mutex>
#include <map>
#include <unistd.h>  
#include <semaphore.h>  
#include <thread>

class RedLock
{
public:
      RedLock(const std::string & key, int32_t expire_time);
      ~RedLock();
      /**
       * @brief 加锁
       * 
       * @return int 1: Lock Succ, 0:Lock Fail
       */
      int Lock();
      /**
       * @brief 解锁
       * 
       * @return int 1:UnLock Succ, 0:UnLock Fail
       */
      int UnLock();

      int UnLock(const std::string & stid);

      int StartWatchDogThread();
private:
     
      std::string lock_key_;
      std::string stid_;
      int expire_time_;
      int interval_sec_;
      bool run_flag_;
      bool lock_succ_;
      RedisApi redis_api_;
};