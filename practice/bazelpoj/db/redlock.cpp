#include "redlock.h"
#include <semaphore.h>
#include <sstream>
#include <string>
#include <thread>
using namespace std;

RedLock ::RedLock(const std::string &key, int32_t expire_time)
    : lock_key_(key), expire_time_(expire_time), run_flag_(true),lock_succ_(false) {
  interval_sec_ = expire_time_ / 3 > 0 ? expire_time_ / 3 : 1;
}

RedLock ::~RedLock() { 
  if(lock_succ_) {
    UnLock(stid_);
  } 
}

int RedLock :: Lock() {
  std::thread::id t_id = std::this_thread::get_id();  // 理论上这里机器ID+线程ID
  std::stringstream sstid;
  sstid << t_id;
  stid_ = sstid.str();
  printf("RedLock thid:%s\n", stid_.c_str());
  int ret = redis_api_.SetNX(lock_key_, stid_, expire_time_);
  lock_succ_ = (ret == 0);
  return ret == 0;
}

int RedLock ::UnLock()

{
  std::thread::id t_id = std::this_thread::get_id();
  std::stringstream sstid;
  sstid << t_id;
  std::string curr_stid = curr_stid.c_str();
  return UnLock(curr_stid);
}

int RedLock ::UnLock(const std::string &stid) {
  std::string lua_script = "local redis_val = redis.call('get', KEYS[1]) if( not redis_val ) then return 0 end if(redis_val == ARGV[1]) then local del_ret = redis.call('del', KEYS[1])  if(del_ret == 0 or del_ret == 1) then return 0 else return -99 end else return -98 end";
  vector<std::tuple<std::string, std::string>> vec_params = {
        std::tuple<std::string, std::string>(lock_key_, stid_)
    };
  run_flag_ = false;
  const int ret = redis_api_.EVAL(lua_script, vec_params);
  if(ret == -98) {
    printf("unlock key fail, not hold for current thread");
    return ret;
  }
  else if(ret != 0){
    printf("excute lua fail [%d] \n", ret);
    return ret;
  };
  return ret;
}

int RedLock ::StartWatchDogThread() {
  run_flag_ = true;
  thread watch_thread([&]() -> void {
    do {

      sleep(interval_sec_);
      static const std::string lua_script = "local redis_val = redis.call('get', KEYS[1]) if(not redis_val) then return -99 end if( redis_val == ARGV[1] ) then return redis.call('set', KEYS[1], ARGV[1], 'EX', ARGV[2]) else return -100 end";
      vector<std::tuple<std::string, std::string>> vec_params = {
        std::tuple<std::string, std::string>(lock_key_, stid_),
        std::tuple<std::string, std::string>("expire_time", to_string(expire_time_))
      };
      printf("StartWatchDogThread thid:%s\n", stid_.c_str());

      const int ret = redis_api_.EVAL(lua_script, vec_params);
      if (ret == -100) {
        printf("not current task key\n");
        break;
      }
      if (ret == -99) {
        printf("redis lock not exist[%d] \n", ret);
        break;
      }
      if(ret == 0) {
        printf("keep lock succ\n");
        continue;
      }
      else {
        printf("keep lock fail ret[%d]\n ", ret);
      }
    } while (run_flag_);
  });
  watch_thread.detach();
  return 0;
}
