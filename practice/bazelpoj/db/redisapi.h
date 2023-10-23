/**
 * @file redisapi.h
 * @author henryqin (you@domain.com)
 * @brief easy use redis api in cpp
 * @version 0.1
 * @date 2023-10-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include "hredis/include/hiredis.h"


class Deleter
{
public:
      void operator()(redisReply * reply) 
      {
            freeReplyObject(static_cast<void*>(reply));
      }
};

class RedisApi 
{
public:
      RedisApi ();
      ~RedisApi();
      int Set(const std::string& key, const std::string & value, uint32_t expire_time_sec = 0);
      int SetNX(const std::string& key, const std::string & value, uint32_t expire_time_sec = 10);
      int Get(const std::string& key, std::string& value);
      int EVAL(const std::string & lua_script, std::vector<std::tuple<std::string , std::string>> & kvs);
      int Del(const std::string &key);
      int Expire(const std::string & key, const uint32_t expire_time_sec);
private:
      int CheckConnect();
      int Connect();
      int ReConnect();
      int DisConnect();
      std::unique_ptr<redisReply, Deleter> RedisCommand(redisContext * c, const char * command);
      /*将数据放到管道内，一起发送给redis服务器，一次性执行*/
      std::unique_ptr<redisReply, Deleter> RedisCommandArgv(redisContext * c, std::vector<std::string> & params);
      int CheckRedisReply(const redisReply*);
      static std::string ip_;
      static int port_;
      static long connect_timeout_us_;
      static int command_timeout_sec_;
      static int connect_interval_sec_;
      bool connected_;
      redisContext * ptr_ctx_;
      uint32_t last_acc_ts_;
};