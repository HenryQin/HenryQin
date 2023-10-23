/**
 * @file runlibco.cpp
 * @author henryqin 
 * @brief 
 * @version 0.1
 * @date 2023-09-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include "db/redisapi.h"
#include "libco/co_routine.h"
using namespace std;

struct ArgWrapper {
      std::string instr;
      stCoRoutine_t *co;
};

void* PollRoutine(void *arg) {
      co_enable_hook_sys();
      struct ArgWrapper *wrapper = reinterpret_cast<ArgWrapper*>(arg);
      RedisApi redisApi;
      const std::string key = "get";
      const std::string value = "hello world";
      redisApi.Set(key, value, 100);
      std::string resp;
      for(;;) {
            poll(NULL, 0, 1000);
            redisApi.Get(key, resp);
            printf("resp:%s\n",resp.c_str());
      }
      return NULL;
};

int main()
{     
      stCoRoutine_t *ptr_co;
      stCoRoutineAttr_t attr;
      struct ArgWrapper arg = {
            "hello world"
      };
      co_create(&ptr_co, &attr, &PollRoutine, static_cast<void *>(&arg));
      arg.co = ptr_co;
      co_resume(ptr_co);
      co_eventloop(co_get_epoll_ct(), NULL, NULL);
      // co_enable_hook_sys();
      // RedisApi redisApi;
      // const std::string key = "hello";
      // const std::string value = "world";
      // redisApi.Set(key, value);
      // std::string resp;
      // redisApi.Get(key, resp);
      // printf("resp:%s\n",resp.c_str());

      return 0;
}