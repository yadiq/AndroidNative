//
// Created by gyd on 2025/10/27.
//

#include "ThreadBase.h"
#include "../utils_android/LogUtil.h"

ThreadBase::ThreadBase(std::string threadName)
        : m_running(false)
        , m_stopFlag(false)
        , m_threadName(std::move(threadName))
{
}

ThreadBase::~ThreadBase()
{
    // 析构自动停止并等待结束，防止资源泄露
    stop();
    join();
}

bool ThreadBase::start()
{
    if (m_running)
    {
        return false; // 已经启动
    }

    m_stopFlag = false;
    m_running = true;
    m_thread = std::thread(&ThreadBase::threadEntry, this);
    return true;
}

void ThreadBase::stop()
{
    m_stopFlag = true;
    m_cv.notify_all();
}

void ThreadBase::join()
{
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

bool ThreadBase::isRunning() const
{
    return m_running;
}

//#if defined(_WIN32)
//void* ThreadBase::nativeHandle()
//{
//	return m_thread.native_handle();
//}
//#else
//pthread_t ThreadBase::nativeHandle()
//{
//	return m_thread.native_handle();
//}
//#endif

bool ThreadBase::shouldStop() const
{
    return m_stopFlag;
}

void ThreadBase::threadEntry()
{
    try
    {
        LOGD_FILE("%s, 线程启动", m_threadName.c_str());
        run();
        LOGD_FILE("%s, 线程结束", m_threadName.c_str());
    }
    catch (const std::exception& e) //捕获C++标准异常
    {
        LOGD_FILE("%s, 线程异常结束,%s", m_threadName.c_str(), e.what());
    }
    catch (...) //捕获未知非标准异常
    {
        LOGD_FILE("%s, 线程异常结束,未知", m_threadName.c_str());
    }
    m_running = false;
}

