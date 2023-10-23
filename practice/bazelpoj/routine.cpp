/**
 * @file routine.cpp
 * @author henryqin (you@domain.com)
 * @brief practise for cpp20 corotine
 * @version 0.1
 * @date 2023-09-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <coroutine>
#include <iostream>
using namespace std;
struct Awaiter {
    Awaiter() {
      std::cout<<"2.co_wait"<<std::endl;
    }
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<>) { std::cout << "3.Waiting...\n"; }
    void await_resume() { std::cout << "4.Resumed!\n"; }
};

struct Task {
    struct promise_type {
        Task get_return_object() { 
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> coro;
    Task(std::coroutine_handle<promise_type> h) : coro(h) {}
    ~Task() { if (coro) coro.destroy(); }
};

Task asyncTask() {
    cout<<"1.asyncTask run"<<endl;
    co_await Awaiter{};
}

int main() {
    Task t = asyncTask();     // 协程在这里没有启动
    std::cout << "Resuming coroutine...\n";
    t.coro.resume();// 协程启动， 然后由于await_ready返回false于是协程被挂起
    t.coro.resume();// 协程再次启动
    return 0;
}

/**
 * 
Q:Awaiter的作用？
在这个例子中，Awaiter 是一个自定义的等待器类型。等待器是协程中的一个重要概念，它定义了协程在等待某个操作完成时的行为。

Awaiter 类型定义了三个方法：

await_ready：这个方法返回一个布尔值，表示被等待的操作是否已经完成。如果这个方法返回 true，那么协程将立即继续执行，而不会被挂起。在这个例子中，await_ready 总是返回 false，所以协程总是会被挂起。

await_suspend：这个方法在协程被挂起时被调用。它接受一个 std::coroutine_handle 参数，这个参数可以用来在未来某个时刻恢复协程的执行。在这个例子中，await_suspend 只是打印一条消息，然后返回。

await_resume：这个方法在协程被恢复时被调用。在这个例子中，await_resume 只是打印一条消息，然后返回。

在 asyncTask 函数中，我们使用 co_await 关键字来等待一个 Awaiter 对象。这会导致协程被挂起，然后在 Awaiter 对象表示的操作完成时被恢复。


Q:await_ready的作用？
await_ready 是一个协程等待器（awaiter）中的方法，它的作用是检查被等待的操作是否已经完成。

这个方法应该返回一个布尔值。如果返回 true，那么 co_await 表达式将立即完成，协程将继续执行，不会被挂起。如果返回 false，那么协程将被挂起，等待被等待的操作完成。

例如，如果你正在等待一个异步操作，如网络请求或者定时器，那么 await_ready 可以检查这个操作是否已经完成。如果已经完成，那么就没有必要挂起协程，可以直接继续执行。

在上述的例子中，await_ready 方法总是返回 false，这意味着协程总是会被挂起，等待 Awaiter 对象表示的操作完成


Q:协程一定要定义Awaiter吗？
不一定。协程不一定需要定义自己的等待器（Awaiter）。实际上，许多常见的异步操作，如等待一个定时器或一个网络请求，已经有现成的等待器可以使用。

然而，如果你需要等待一个特定的操作，这个操作没有现成的等待器，或者现成的等待器不能满足你的需求，那么你可能需要定义自己的等待器。

等待器需要定义三个方法：await_ready，await_suspend 和 await_resume。这三个方法控制了协程在等待操作完成时的行为。

await_ready 方法检查被等待的操作是否已经完成。
await_suspend 方法在协程被挂起时被调用。
await_resume 方法在协程被恢复时被调用。
如果你不需要自定义等待操作完成时的行为，那么你可能不需要定义自己的等待器。

Q:等待器一定要被声明成Awaiter吗？
编译器通过查看你的类型是否定义了 await_ready，await_suspend 和 await_resume 这三个方法来判断它是否是一个等待器（Awaiter）。这三个方法是等待器的要求，它们控制了协程在等待操作完成时的行为。

await_ready 方法应该返回一个布尔值，表示被等待的操作是否已经完成。如果这个方法返回 true，那么协程将不会被挂起，而是立即继续执行。
await_suspend 方法在协程被挂起时被调用。它接受一个 std::coroutine_handle 参数，这个句柄可以用来在被等待的操作完成时恢复协程的执行。
await_resume 方法在协程被恢复时被调用。它的返回值将作为 co_await 表达式的结果。
只要你的类型定义了这三个方法，并且这些方法的行为符合等待器的要求，那么它就可以作为一个等待器使用。所以不一定需要声明成Awaiter


Q:struct Task 和 struct promise_type的作用分别是什么?
struct Task：这是我们自定义的协程类型。它包含一个 std::coroutine_handle 成员，这个句柄可以用来恢复协程的执行。Task 类型还定义了一个构造函数，用来从一个 std::coroutine_handle 创建一个 Task 对象，以及一个析构函数，用来在 Task 对象被销毁时销毁协程。

struct promise_type：这是 Task 类型的承诺类型（promise type）。每个协程都有一个关联的承诺对象，这个对象用来存储协程的状态，并控制协程的执行。承诺类型需要定义一些特殊的方法，这些方法决定了协程的行为。例如，get_return_object 方法用来创建协程的返回对象，initial_suspend 和 final_suspend 方法用来控制协程在开始和结束时的行为，return_void 方法用来处理协程的返回值，unhandled_exception 方法用来处理协程中的未处理异常。

在这个例子中，promise_type 的 get_return_object 方法创建了一个 Task 对象，这个对象包含了一个指向承诺对象的 std::coroutine_handle。initial_suspend 和 final_suspend 方法都返回 std::suspend_always，这意味着协程在开始和结束时都会被挂起。return_void 方法什么也不做，因为这个协程没有返回值。unhandled_exception 方法也什么也不做，因为这个例子中没有处理异常的代码。
* 
*/