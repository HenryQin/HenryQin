/**
 * @file async_routine.cpp
 * @author henryqin
 * @brief practise for cpp20 coroutine
 * @version 0.1
 * @date 2023-10-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <coroutine>
#include <iostream>
#include <thread>
#include <string>
#include <set>
#include<vector>
using namespace std;

// 定义等待器
struct AsyncOperation {
  std::jthread jt;

  bool await_ready() const noexcept {
    cout << "await_ready" << endl;
    return false;
  }

  void await_suspend(std::coroutine_handle<> handle) {
    cout << "await_suspend" << endl;
    jt = std::jthread([handle](std::stop_token stoken) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      if (!stoken.stop_requested()) {
        handle.resume();
      }
    });
  }

  int await_resume() { return 42; }
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

Task asyncTask() {
  cout << "3.asyncTask" << endl;
  int result = co_await AsyncOperation{};

  cout << "4. " << result << endl;
}

int main() {
  Task t = asyncTask(); // 协程对象
  t.coro.resume();      // 线程被启动的同时，被暂停
  t.coro.resume();      // 线程启动后返回42
  std::set<string> s;
  vector<int> v1;
  return 0;
}

/*
在这个例子中，AsyncOperation是一个等待器，它启动一个std::jthread来执行异步操作。async_operation函数返回一个AsyncOperation对象。test函数是一个协程，它等待async_operation的完成，并且打印结果。


std::coroutine_handle::from_promise是一个静态成员函数，用于从协程的promise对象创建一个协程句柄。

在C++的协程中，协程函数的promise对象负责管理协程的状态和控制流。协程句柄则用于操作和管理协程的执行。

std::coroutine_handle::from_promise函数接受一个promise对象作为参数，并返回一个对应的协程句柄。这个句柄可以用于启动、暂停、恢复和销毁协程。

在协程的promise类型中，通常会定义一个get_return_object成员函数，用于返回一个协程句柄。这个函数可以使用std::coroutine_handle::from_promise来获取协程句柄，然后返回给调用者。

以下是一个示例，展示了如何使用std::coroutine_handle::from_promise来获取协程句柄：
*/