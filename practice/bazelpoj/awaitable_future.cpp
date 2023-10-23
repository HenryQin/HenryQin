/**
 * @file awaitable_future.cpp
 * @author henryqin
 * @brief practise for cpp20 coroutine
 * @version 0.1
 * @date 2023-10-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <chrono>
#include <coroutine>
#include <future>
#include <iostream>
#include <unistd.h>
using namespace std;

struct AwaitableFuture {
  std::future<int> fut;

  bool await_ready() const noexcept {
    return fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    return true;
  }

  void await_suspend(std::coroutine_handle<> handle) {
    std::thread([this, handle]() {
      fut.wait();
      handle.resume();
    }).detach();
  }

  int await_resume() {
    return fut.get(); // 返回数据结果
  }
};

struct Task {
  struct promise_type {
    Task get_return_object() {
      cout << "1.get_reurn_object" << endl;
      return Task{
          std::coroutine_handle<promise_type>::from_promise(
              *this) // 获取协程句柄
      };             // 执行协程函数
    }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
  std::coroutine_handle<promise_type> coro; // 协程函数
  Task(std::coroutine_handle<promise_type> h) : coro(h) {
    cout << "2.task constructed" << endl;
  } // 构造函数
  ~Task() {
    if (coro)
      coro.destroy();
  }
};

AwaitableFuture async_operation() {
  return AwaitableFuture{std::async(std::launch::async, []() {
    cout << "sleep for ..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42;
  })};
}

Task asyncTask() {
  cout << "3.asyncTask" << endl;
  int result = co_await async_operation();

  cout << "4. " << result << endl;
  co_return;
}

int main() {
  Task t = asyncTask(); // 协程对象
  t.coro.resume();      // 线程被启动的同事，被暂停
  sleep(10);   // sleep过程中被切回
  return 0;
}