//
// Created by gyd on 2025/10/27.
//

#ifndef ANDROIDNATIVE_THREADBASE_H
#define ANDROIDNATIVE_THREADBASE_H

#include <thread>
#include <atomic>
#include <string>
#include <iostream>
#include <chrono>

#include "../utils_android/LogUtil.h"

class ThreadBase {
public:
    explicit ThreadBase(const std::string& name = "ThreadBase");
    virtual ~ThreadBase();

    // 启动线程
    bool start();

    // 停止线程（安全回收）
    void stop();

    // 判断线程是否在运行
    bool isRunning() const; //const 表示这个函数不会修改类的成员变量

protected:
    // 派生类实现此函数作为线程主体
    virtual void run() = 0;

    // 在线程执行函数中使用，用于判断是否需要退出
    //bool shouldExit() const;

    // 线程名称（可用于日志）
    std::string m_name;

    const char* TAG = "Thread"; //日志TAG

private:
    // 线程入口包装函数
    void threadEntry();

    std::thread m_thread;
    std::atomic<bool> m_running; //原子类型。在多线程环境下，线程安全
};



#endif //ANDROIDNATIVE_THREADBASE_H
