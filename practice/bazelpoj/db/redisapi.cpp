#include "redisapi.h"
#include "db/hredis/include/hiredis.h"
#include "db/hredis/include/read.h"
#include <memory>
#include <sstream>
#include <stdio.h>
#include <string>
std::string RedisApi ::ip_ = "127.0.0.1";
int RedisApi ::port_ = 6379;
long RedisApi ::connect_timeout_us_ = 100 * 1000; // 100ms
int RedisApi ::command_timeout_sec_ = 1;
int RedisApi ::connect_interval_sec_ = 10;

RedisApi ::RedisApi() : connected_(false), ptr_ctx_(NULL), last_acc_ts_(0) {
  Connect();
}

RedisApi :: ~RedisApi() {
  DisConnect();
}

int RedisApi :: Connect() {
  redisOptions opt = {0};
  REDIS_OPTIONS_SET_TCP(&opt, ip_.c_str(), port_);
  printf("%s ip:[%s], port[%d]\n", __func__, opt.endpoint.tcp.ip, opt.endpoint.tcp.port);
  ptr_ctx_ = redisConnectWithOptions(&opt);
  if (ptr_ctx_ == NULL) {
    printf("connect db ip[%s], port[%d], fail", ip_.c_str(), port_);
    return -99;
  } else if (ptr_ctx_->err) {
    printf("Connection error: %s", ptr_ctx_->errstr);
    redisFree(ptr_ctx_);
    return -99;
  } else {
    last_acc_ts_ = time(0);
    connected_ = true;
  }
  return 0;
}


int RedisApi ::CheckConnect() {
  bool need_reconnect = false;
  if (ptr_ctx_ == NULL) {
    need_reconnect = true;
  } else if (time(0) - last_acc_ts_ > connect_interval_sec_) {
    need_reconnect = true;
  }
  if (need_reconnect) {
    return ReConnect();
  }
  return 0;
};

int RedisApi :: DisConnect() {
  connected_ = false;
  if (ptr_ctx_) {
      redisFree(ptr_ctx_);
      ptr_ctx_ = NULL;
  } 
  return 0;
}

int RedisApi :: ReConnect() {
    this->DisConnect();
    return this->Connect();
}


std::unique_ptr<redisReply, Deleter> RedisApi :: RedisCommand(redisContext * c, const char * command)
{
  redisReply* reply_ptr = static_cast<redisReply*>(redisCommand(c, command));
  return std::unique_ptr<redisReply, Deleter>(reply_ptr, Deleter());
};

int RedisApi :: CheckRedisReply(const redisReply* resp)
{
  if(resp == NULL) {
    printf("reply is NULL");
    return -1;
  }
  // 返回类型错误
  if( resp->type == REDIS_REPLY_ERROR) {
    printf("redis reply error:[%s]", resp->str);
    return -2;
  } 
  // 没返回
  if( resp->type == REDIS_REPLY_NIL ) {
    printf("redis reply nil");
    return -3;
  }
  // 返回类型为数字
  if( resp->type == REDIS_REPLY_INTEGER) {
    return resp->integer;
  }
  // 返回类型为状态
  if(resp->type == REDIS_REPLY_STATUS && std::string(resp->str) != "OK") {
    printf("reply stauts:[%s]", resp->str);
    return -4;
  }

  return 0;
}

int RedisApi :: Set(const std::string &key, const std::string & value, uint32_t expire_time)
{ 
  // size_t buff_size = value.length() + key.length() + 128;
  // std::shared_ptr<char> buff(new char[buff_size]);
  // if(expire_time > 0) {
  //   snprintf(buff.get(), buff_size, "set %s %s EX %u", key.c_str(), value.c_str(), expire_time);
  // } 
  // else {
  //   snprintf(buff.get(), buff_size, "set %s %s", key.c_str(), value.c_str());
  // }

 
  std::vector<std::string> argvs = {
    "set",
    key, 
    value
  };

  if(expire_time > 0) {
    argvs.push_back("EX");
    argvs.push_back(std::to_string(expire_time));
  }

  int ret = CheckConnect();
  if(ret) return ret;
  // auto resp = RedisCommand(ptr_ctx_, buff.get());
  auto resp =  RedisCommandArgv(ptr_ctx_, argvs);
  if(CheckRedisReply(resp.get())) {
    return -1;
  }
  return 0;
};

int RedisApi :: SetNX(const std::string &key, const std::string & value, uint32_t expire_time)
{
  std::vector<std::string> argvs = {
    "set",
    key, 
    value
  };

  if(expire_time > 0) {
    argvs.push_back("NX");
    argvs.push_back("EX");
    argvs.push_back(std::to_string(expire_time));
  }

  int ret = CheckConnect();
  if(ret) return ret;
  auto resp = RedisCommandArgv(ptr_ctx_, argvs);
  ret = CheckRedisReply(resp.get());
  if(ret == -3) {
    return 1;
  }
  else if(ret != 0) {
    return -1;
  }
  return 0;
};

int RedisApi :: Get(const std::string & key, std::string & value)
{
  value.clear();
  size_t buff_size = key.length() + 128;
  std::shared_ptr<char> buff(new char[buff_size]);
  snprintf(buff.get(), buff_size, "get %s", key.c_str());
  int ret = CheckConnect();
  if(ret) return ret;
  auto resp = RedisCommand(ptr_ctx_, buff.get());
  ret = CheckRedisReply(resp.get());
  if(ret == 3) {
    return 1;
  }
  else if(ret != 0) {
    return -1;
  }
  value.append(resp->str, resp->len);
  return 0;
}

std::unique_ptr<redisReply, Deleter> RedisApi :: RedisCommandArgv(redisContext * c, std::vector<std::string> & params)
{ 
  int argc =  params.size();
  std::unique_ptr<char*[]>argv(new char*[argc]);
  std::unique_ptr<size_t> argvlen(new size_t[argc]);
  for(int i = 0; i < argc; i++) {
    *(argvlen.get() + i) = params[i].length();
    argv[i] = const_cast<char*>(params[i].c_str());
  }
  redisReply* reply_ptr = static_cast<redisReply*>(redisCommandArgv(c, argc, const_cast<const char**>(argv.get()), argvlen.get()));
  return std::unique_ptr<redisReply, Deleter>(reply_ptr, Deleter());
}

int RedisApi :: EVAL(const std::string & lua_script, std::vector<std::tuple<std::string , std::string> > &kv)
{
  int ret = CheckConnect();
  if(ret) return ret;
  
  std::vector<std::string> argvs = {
    "EVAL",
    lua_script,
    std::to_string(kv.size())
  };

  for(const auto & t : kv) {
    argvs.push_back(std::get<0>(t));
  }
  for(const auto & t : kv) {
    argvs.push_back(std::get<1>(t));
  }
  
  auto resp = RedisCommandArgv(ptr_ctx_, argvs);
  return CheckRedisReply(resp.get());
}

int RedisApi :: Del(const std::string &key)
{
  int ret = CheckConnect();
  if(ret) return ret;
  
  uint32_t buff_size = key.size() + 64;
  std::shared_ptr<char> buff(new char[buff_size]);
  snprintf(buff.get(), buff_size, "del %s", key.c_str());
  std::string command(buff.get());
  auto resp = RedisCommand(ptr_ctx_, command.c_str());

  return 1 == CheckRedisReply(resp.get());  // return 1表示删除成功
}


int RedisApi :: Expire(const std::string & key, const uint32_t expire_time_sec)
{
  int ret = CheckConnect();
  if(ret) return ret;
  std::vector<std::string> argvs = {
    "expire", 
    key, 
    std::to_string(expire_time_sec)
  };
  auto resp = RedisCommandArgv(ptr_ctx_, argvs);
  return 1 == CheckRedisReply(resp.get());
}
