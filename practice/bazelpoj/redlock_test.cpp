/**
 * @file redlock_test.cpp
 * @author henryqin (you@domain.com)
 * @brief practise for districted lock using redis
 * @version 0.1
 * @date 2021-09-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "db/redisapi.h"
#include "db/redlock.h"
#include "proto/addressbook.pb.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <unistd.h>
using namespace std;

string GetThreadId() {
  std::thread::id t_id = std::this_thread::get_id();
  std::stringstream sstid;
  sstid << t_id << endl;
  std::string curr_sthid = sstid.str();
  return curr_sthid;
}

void TryLock(const std::string &key) {
  std::string sthid = GetThreadId();
  RedLock lock(key, 10);
  if (lock.Lock()) {
    printf("%s try to lock succ \n", sthid.c_str());
    sleep(10);
  } else {
    printf("%s try to lock fail \n", sthid.c_str());
  }
  return;
}

void TestThread() {
  static string lock_key = "helloworld";
  do {
    TryLock(lock_key);
    sleep(10);
  } while (true);
}

int main() {
  RedisApi redisApi;

  // addressbook::MyAddress address;
  // address.set_address("侨鑫汇悦台");
  // address.set_area("天河区");
  // address.set_city("广州市");

  // std::string pbstr = address.Utf8DebugString();
  // cout<< pbstr<<endl;

  // const std::string homekey = "homekey";

  // redisApi.Set(homekey, address.SerializeAsString());
  // std::string tmpstr;
  // redisApi.Get(homekey, tmpstr);
  // addressbook::MyAddress tmpAddr;
  // tmpAddr.ParseFromString(tmpstr);
  // cout<< tmpAddr.Utf8DebugString()<<endl;
  static string lock_key = "helloworld";
  RedLock lock(lock_key, 10);
  if (lock.Lock()) {
    printf("lock succ\n");
  } else {
    printf("lock fail\n");
  }
  lock.StartWatchDogThread();
  // sleep(60);
  std::thread th1(TestThread);
  th1.join();

  if (lock.UnLock() == 0) {
    printf("unlock succ\n");
  } else {
    printf("unlock fail\n");
  };
  // const std::string lua_script = "return redis.call('SET', KEYS[1], ARGV[1],
  // 'EX', 30)"; std::tuple<std::string, std::string> tp("TEST", "WORD");
  // std::vector<std::tuple<std::string ,std::string>> kv = {tp};
  // redisApi.EVAL(lua_script, kv);

  return 0;
}