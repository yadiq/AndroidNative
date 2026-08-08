//
// Created by gyd on 2025/10/27.
//

#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

class ThreadBase
{
public:
    //ThreadBase();
    explicit ThreadBase(std::string threadName = ""); //构造直接传入线程名
    virtual ~ThreadBase();

    // 禁止拷贝
    ThreadBase(const ThreadBase&) = delete;
    ThreadBase& operator=(const ThreadBase&) = delete;

    // 启动线程
    bool start();

    // 请求停止线程（设置停止标记，唤醒等待）
    void stop();

    /// 阻塞等待线程结束
    void join();

    /// 是否正在运行
    bool isRunning() const;

    /// 获取平台原生线程句柄
//#if defined(_WIN32)
//    void* nativeHandle();
//#else
//    pthread_t nativeHandle();
//#endif

protected:
    /// 子类实现线程主逻辑
    virtual void run() = 0;

    /// 子类判断是否应该退出
    bool shouldStop() const;

    /// 带超时的等待函数，替代sleep_for (最多等待duration时间；或者收到停止信号提前返回)
    template<class Rep, class Period>
    void waitFor(std::chrono::duration<Rep, Period> duration)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cv.wait_for(lock, duration, [this]() {
            return m_stopFlag.load();
        });
    }

private:
    // 线程入口包装函数
    void threadEntry();

private:
    std::thread m_thread;
    std::atomic<bool> m_running;    // 是否正在运行
    std::atomic<bool> m_stopFlag;   // 请求停止标记
    std::mutex m_mtx;               // 用于waitFor的互斥锁
    std::condition_variable m_cv;   // 用于waitFor的条件变量

public:
    std::string m_threadName;       // 线程名，打印日志用
};